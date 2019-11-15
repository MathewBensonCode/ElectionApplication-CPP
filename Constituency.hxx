#pragma once

#include <string>
#include <odb/core.hxx>
#include <memory>
#include "County.hxx"

#pragma db object
class Constituencies
{
#pragma db id
	int _id;
	std::string _name;
	std::unique_ptr<Counties> _CountyId;

	friend odb::access;
public:
	Constituencies():_id(0), _name(""), _CountyId(nullptr)
	{}

	const int& Id() const {return _id;}
	void Id(const int& id){_id = id;}

	const std::string& Name() const {return _name;}
	void Name(const std::string& name) {_name = name;}

	Counties& County() const { return *_CountyId;}
};
