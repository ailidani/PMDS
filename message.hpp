
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/shared_ptr.hpp>

enum message_type
{
	INVALID = -1,
	Update = 0,
	Request,
	Response,
	Ready,
	Accept,
	MAX_TYPE
};

enum answer_type { No=0, Yes=1 };

class message_header
{
public:
	message_header() : type(INVALID) {};

	message_type type;
	std::string group;
	std::string source;

protected:
	message_header(message_type type, std::string group, std::string source) :
		type(type), group(group), source(source)
	{
	};

private:
	friend class boost::serialization::access;
	template< class Archive >
	void serialize( Archive & ar, const unsigned int version )
	{
		ar & BOOST_SERIALIZATION_NVP(type);
		ar & BOOST_SERIALIZATION_NVP(group);
		ar & BOOST_SERIALIZATION_NVP(source);
	};

};


class message_update : public message_header
{
public:
	message_update() :
	message_header(Update, "my_group", "me")
	{
	};

private:
	std::string commond;


};

#endif
