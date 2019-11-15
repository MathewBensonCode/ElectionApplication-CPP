#pragma once

#include <string>
#include <odb/core.hxx>
#include "PollingStation.hxx"

#pragma db object
class ResultsForm34As
{
	friend odb::access;

#pragma db id
	int _id;
	std::string _ImageUrl;
	std::unique_ptr<PollingStation> _PollingStationId;
public:

	ResultsForm34As():_id(0), _ImageUrl(""), _PollingStationId(nullptr) { }

	const int& Id() const {return _id;} 
	void Id(const int& myid){_id=myid;}

	const std::string& ImageUrl() const {return _ImageUrl; }
	void ImageUrl(const std::string& imageurl) { _ImageUrl = imageurl;}

	PollingStation& GetPollingStation() const {return *_PollingStationId;}

};

