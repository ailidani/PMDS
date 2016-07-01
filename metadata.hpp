
#ifndef METADATA_HPP
#define METADATA_HPP

#include <unordered_map>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include "pmds.hpp"

typedef uint64_t FID;
typedef std::string PATH;
typedef enum MDS_FILE_TYPE
{
    FILETYPE_NULL,
    FILETYPE_COMMITTED,
    FILETYPE_DIRTY,
} MDS_FILE_TYPE;

struct stat {
		MDS_FILE_TYPE	type;			/* [MDS] Directory = 0, File = 1 */
		uint64_t		fid;				/* [MDS] FID */
        int32_t         st_dev;         /* [XSI] ID of device containing file */
        uint64_t        st_ino;         /* [XSI] File serial number */
        uint16_t        st_mode;        /* [XSI] Mode of file (see below) */
        uint16_t        st_nlink;       /* [XSI] Number of hard links */
        uint32_t        st_uid;         /* [XSI] User ID of the file */
        uint32_t        st_gid;         /* [XSI] Group ID of the file */
        int32_t         st_rdev;        /* [XSI] Device ID */
        time_t          st_atime;       /* [XSI] Time of last access */
        long            st_atimensec;   /* nsec of last access */
        time_t          st_mtime;       /* [XSI] Last data modification time */
        long            st_mtimensec;   /* last data modification nsec */
        time_t          st_ctime;       /* [XSI] Time of last status change */
        long            st_ctimensec;   /* nsec of last status change */
        uint64_t        st_size;        /* [XSI] file size, in bytes */
        uint64_t        st_blocks;      /* [XSI] blocks allocated for file */
        uint64_t		st_blksize;     /* [XSI] optimal blocksize for I/O */
        uint32_t		st_flags;       /* user defined flags for file */
        uint32_t		st_gen;         /* file generation number */
        int32_t       	st_lspare;      /* RESERVED: DO NOT USE! */
        int64_t       	st_qspare[2];   /* RESERVED: DO NOT USE! */
};

class dir
{
public:
	typedef std::map<PATH, FID>::iterator iterator;
	dir() {}
	~dir() {}
    void add(const PATH &name, FID id)
    {
        entries[name] = id;
        setDirty();
    }
    void remove(const std::string &name)
    {
        assert(entries.find(name) != entries.end());
        entries.erase(name);
        setDirty();
    }
    bool isEmpty() { return entries.size() == 0; }
    void setDirty() { dirty = true; }
    void clrDirty() { dirty = true; }
    bool isDirty() { return dirty; }
    iterator begin() { return entries.begin(); }
    iterator end() { return entries.end(); }
    iterator find(const std::string &name) { return entries.find(name); }

	bool dirty;
	std::map<PATH, FID> entries;

};

class file_info
{
public:
    file_info()
	{
        memset(&stat_info, 0, sizeof(stat_info));
        type = FILETYPE_NULL;
        id = 0;
        path = "";
        fd = -1;
        refCount = 1;
        openCount = 0;
        dirLoaded = false;
    }
    ~file_info()
    {
        assert(refCount == 0);
        assert(openCount == 0);
        // Delete temporary file
        if (path != "")
            boost::filesystem::remove(path);
    }
    /*
     * Tracks the number of handles to a file if this drops to zero the file
     * should be deleted along with this object.  This helps to handle the case
     * that unlink is called while a file is still open.
     */
    void retain() {
        assert(refCount != 0);
        refCount++;
    }
    void release() {
        refCount--;
        if (refCount == 0) {
            delete this;
        }
    }
    /*
     * Tracks the number of open handles to a file so that we can close the
     * temporary file when there are no file descriptors left.
     */
    void retainFd() { openCount++; }
    void releaseFd() {
        openCount--;
        assert(openCount >= 0);
    }
    bool isDir() const { return (stat_info.st_mode & S_IFDIR) == S_IFDIR; }
    bool isSymlink() const { return (stat_info.st_mode & S_IFLNK) == S_IFLNK; }
    bool isReg() const { return (stat_info.st_mode & S_IFREG) == S_IFREG; }
    void loadAttr(const AttrMap &attr);
    void storeAttr(AttrMap *attr) const;

    struct stat stat_info;
    ObjectHash hash;
    ObjectHash largeHash;
    MDS_FILE_TYPE type;
    FID id;
    PATH path; // temporary file
    PATH link; // link target
    int fd;
    int refCount;
    int openCount;
    bool dirLoaded;
};

class metadata
{
public:
	metadata()
	{
		// Create root directory info
		stat *rootdir = new stat();
		rootdir->st_uid = geteuid();
		rootdir->st_gid = getegid();
		rootdir->st_mode = 0755 | S_IFDIR;
		rootdir->st_nlink = 2;
		rootdir->st_blksize = 4096;
		rootdir->st_blocks = 1;
		rootdir->st_size = 512;
		rootdir->fid = generateID();
		time_t now = time(NULL);
		rootdir->st_mtime = now;
		rootdir->st_ctime = now;
		rootdir->type = FILETYPE_DIRTY;
		dirs[rootdir->fid] = new dir();
	};
	~metadata() {};

	FID generateID()
	{
		FID id = nextID;
		nextID++;
		return id;
	}

private:
	FID nextID;
	std::map<FID, dir*> dirs;
    std::map<PATH, file_info*> paths;
    std::unordered_map<uint64_t, file_info*> handles;
};

metadata * GetMetadata()
{
    return (metadata*)fuse_get_context()->private_data;
}

namespace boost {
namespace serialization {

template<class Archive>
void serialize(Archive & ar, ObjectHash & hash, const unsigned int version)
{
	ar & hash.hash;
}

template<class Archive>
void serialize(Archive & ar, file_info & info, const unsigned int version)
{
	ar & info.stat_info;
	ar & info.hash;
	ar & info.largeHash;
	ar & info.type;
	ar & info.id;
	ar & info.path;
	ar & info.link;
	ar & info.fd;
	ar & info.refCount;
	ar & info.openCount;
	ar & info.dirLoaded;
}

template<class Archive>
void serialize(Archive & ar, dir & dir, const unsigned int version)
{
	ar & dir.dirty;
	ar & dir.entries;
}

}
} /* end of namespace boost */

#endif
