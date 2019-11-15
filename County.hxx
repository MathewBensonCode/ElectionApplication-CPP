#pragma once

#include <string>
#include <vector>
#include <memory>
#include <odb/core.hxx>
#include <ostream>

#pragma db object
class Counties
{
	friend odb::access;

#pragma db id
	int _id;
	std::string _name;
//	std::vector<std::shared_ptr<Constituencies>> _constituencies;
public:

	Counties():_id(0),_name("")/*,_constituencies(0)*/ { }

	const int& Id() const {return _id;} 
	void Id(const int& myid){_id=myid;}

	const std::string& Name() const {return _name; }
	void Name(const std::string& name) { _name = name;}
	
/*	std::ostream& operator<<(std::ostream& stream )
	{
		stream<<"County Name :"<< _name;
		return stream;
	}
*/

/*	const std::vector<std::shared_ptr<Constituencies>>& MyConstituencies()
	{
		return _constituencies;
	}
	*/
};
