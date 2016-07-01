
#ifndef STAT_HPP
#define STAT_HPP

#include <sys/types.h>

struct stat {
		MDS_FILE_TYPE	type;			/* [MDS] Directory = 0, File = 1 */
		uint64_t		id;				/* [MDS] FID */
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



#endif
