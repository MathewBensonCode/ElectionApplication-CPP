#pragma once

#include <string>
#include <odb/core.hxx>
#include "Ward.hxx"
#include <memory>

#pragma db object
class PollingCentres
{
	friend odb::access;

#pragma db id
	int _id;
	std::string _name;
	std::unique_ptr<Wards> _WardId;
public:

	PollingCentres():_id(0),_name(""), _WardId(nullptr) { }

	const int& Id() const {return _id;} 
	void Id(const int& myid){_id=myid;}

	const std::string& Name() const {return _name; }
	void Name(const std::string& name) { _name = name;}

	Wards& Ward() const {return *_WardId;}
};
