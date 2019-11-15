#pragma once

#include <string>
#include <odb/core.hxx>
#include <memory>
#include "Constituency.hxx"

#pragma db object
class Wards
{
	friend odb::access;

#pragma db id
	int _id;
	std::string _name;
	std::unique_ptr<Constituencies> _ConstituencyId;
public:

	Wards():_id(0),_name(""), _ConstituencyId(nullptr) { }

	const int& Id() const {return _id;} 
	void Id(const int& myid){_id=myid;}

	const std::string& Name() const {return _name; }
	void Name(const std::string& name) { _name = name;}

	Constituencies& Constituency() const {return *_ConstituencyId;}
};
