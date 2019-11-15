#pragma once

#include <string>
#include <odb/core.hxx>
#include "PollingCenter.hxx"
#include <memory>

#pragma db object
class PollingStation
{
	friend odb::access;

#pragma db id
	int _id;
	int _AltId;
	std::string _name;
	std::unique_ptr<PollingCentres> _PollingCenterId;
public:

	PollingStation():_id(0), _AltId(0), _name(""), _PollingCenterId(nullptr) { }

	const int& Id() const {return _id;}
	void Id(const int& myid){_id=myid;}

	const int& AltId() const {return _AltId;};

	const std::string& Name() const {return _name; }
	void Name(const std::string& name) { _name = name;}

	PollingCentres& PollingCenter() const {return *_PollingCenterId;}
};
