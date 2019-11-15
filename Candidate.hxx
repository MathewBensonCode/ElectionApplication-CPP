#pragma once

#include <string>
#include <odb/core.hxx>

#pragma db object
class Candidates
{
	friend odb::access;

#pragma db id
	int _id;
	std::string _name;
public:

	Candidates():_id(0),_name("") { }

	const int& Id() {return _id;} const
	void Id(const int& myid){_id=myid;}

	const std::string& Name(){return _name; }const
	void Name(const std::string& name) { _name = name;}
	
};
