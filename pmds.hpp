
#ifndef PMDS_HPP
#define PMDS_HPP

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/singleton.hpp>

#include <boost/filesystem.hpp>

// Announcement port
#define PMDS_CLIENT_PORT        5001
// Messaging port
#define PMDS_SERVER_PORT		5002
// Advertisement interval
#define PMDS_ADVINTERVAL     10
// Reject advertisements with large time skew
#define PMDS_ADVSKEW         50
// Repository check interval
#define PMDS_MONINTERVAL     20
// Sync interval
#define PMDS_SYNCINTERVAL    10

#define PMDS_LOGFILE        "pmds.log"
#define PMDS_CONFFILE		"pmds.conf"
#define PMDS_METAFILE		"pmds_meta.xml"

class PMDS
{
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & mypaths;
	}

	static PMDS& instance()
	{
		static PMDS pmds;
		return pmds;
	}

	void init();
	int start_server();

	int mds_unlink(const std::string &path, bool fromFUSE);
	int mds_symlink(const std::string &target_path, const std::string &link_path, bool fromFUSE);
	int mds_readlink(const std::string &path, char* buf, size_t size);
	int mds_rename(const std::string &from_path, const std::string &to_path, bool fromFUSE);
	int mds_mkdir(const std::string &path, mode_t mode, bool fromFUSE);
	int mds_rmdir(const std::string &path, bool fromFUSE);

protected:
	inline bool is_master(std::string path)
	{
		std::set<std::string>::iterator it;
		it = mypaths.find(path);
		return it != mypaths.end();
	}

private:
	PMDS()
	{
		// XXX get mypaths from metafile
		boost::filesystem::path home = fsutil::get_home();
		assert(home != "");
		if (!boost::filesystem::exists(home + "/petafs"))
		{
			boost::filesystem::create_directory(home + "/petafs");
		}
		metafile = home + PMDS_METAFILE;
		if (boost::filesystem::exists(metafile))
		{
			load();
		}
	}
	PMDS(PMDS const & copy);				// Not Implemented
	PMDS & operator=(PMDS const & copy);	// Not Implemented
	~PMDS() { save(); }

	std::set<std::string> mypaths;

	void load()
	{
		std::ifstream ifs(metafile);
		assert(ifs.good());
		boost::archive::xml_iarchive ia(ifs);
		ia >> BOOST_SERIALIZATION_NVP(mypaths);
	}
	void save() const
	{
		if(metafile != "")
		{
			std::ofstream ofs(metafile);
			assert(ofs.good());
			boost::archive::xml_oarchive oa(ofs);
			oa << BOOST_SERIALIZATION_NVP(mypaths);
		}
	}

	std::string metafile;

};

#endif
