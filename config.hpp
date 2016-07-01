
#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <iostream>
#include <list>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>

#include "util/fsutil.hpp"

class config
{
public:
	config()
	{
		std::string home = fsutil::get_home();
		assert(home != "");
		if (!boost::filesystem::exists(MDS_CONFFILE))
		{
			save();
		}
		else load();
	}
	~config();

	int port = 5001;
	int paxos_port = 1337;			// Paxos server port
	std::set<std::string, int> peers;	// Peers ip and port
	int advertise_interval = 10;	// Advertisement interval
	int advertise_skew = 50;		// Reject advertisements with large time skew
	int monitor_interval = 20;		// Repository check interval
	int sync_interval = 10;			// Sync interval

	std::string MDS_LOGFILE = "pmds.log";
	std::string MDS_CONFFILE = "pmds_conf.xml";
	std::string MDS_METAFILE = "pmds_meta.xml";

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & MDS_LOGFILE;
		ar & MDS_CONFFILE;
		ar & MDS_METAFILE;
		ar & port;
		ar & paxos_port;
		ar & peers;
		ar & advertise_interval;
		ar & advertise_skew;
		ar & monitor_interval;
		ar & sync_interval;
	}

	void load()
	{
		std::ifstream ifs(MDS_CONFFILE);
		assert(ifs.good());
		boost::archive::xml_iarchive ia(ifs);
		ia >> BOOST_SERIALIZATION_NVP(MDS_LOGFILE);
		ia >> BOOST_SERIALIZATION_NVP(MDS_CONFFILE);
		ia >> BOOST_SERIALIZATION_NVP(MDS_METAFILE);
		ia >> BOOST_SERIALIZATION_NVP(port);
		ia >> BOOST_SERIALIZATION_NVP(paxos_port);
		ia >> BOOST_SERIALIZATION_NVP(peers);
		ia >> BOOST_SERIALIZATION_NVP(advertise_interval);
		ia >> BOOST_SERIALIZATION_NVP(advertise_skew);
		ia >> BOOST_SERIALIZATION_NVP(monitor_interval);
		ia >> BOOST_SERIALIZATION_NVP(sync_interval);
	}

	void save() const
	{
		if(MDS_CONFFILE != "")
		{
			std::ofstream ofs(MDS_CONFFILE);
			assert(ofs.good());
			boost::archive::xml_oarchive oa(ofs);
			oa << BOOST_SERIALIZATION_NVP(MDS_LOGFILE);
			oa << BOOST_SERIALIZATION_NVP(MDS_CONFFILE);
			oa << BOOST_SERIALIZATION_NVP(MDS_METAFILE);
			oa << BOOST_SERIALIZATION_NVP(port);
			oa << BOOST_SERIALIZATION_NVP(paxos_port);
			oa << BOOST_SERIALIZATION_NVP(peers);
			oa << BOOST_SERIALIZATION_NVP(advertise_interval);
			oa << BOOST_SERIALIZATION_NVP(advertise_skew);
			oa << BOOST_SERIALIZATION_NVP(monitor_interval);
			oa << BOOST_SERIALIZATION_NVP(sync_interval);
		}
	}
};


#endif
