#pragma once

#include <string>
#include <odb/core.hxx>
#include "Candidate.hxx"
#include "ResultsForm34A.hxx"
#include <memory>

#pragma db object
class CandidateResults
{
	friend odb::access;

#pragma db id
	int _id;
	std::unique_ptr<Candidates> _CandidateId;
	std::unique_ptr<ResultsForm34As> _ResultsForm34AId;
	int _Votes;

public:

	CandidateResults():_id(0), _CandidateId(nullptr), _ResultsForm34AId(nullptr),  _Votes(0) { }

	const int& Id() {return _id;} const
	void Id(const int& myid){_id=myid;}

	Candidates& Candidate(){return *_CandidateId;}

	ResultsForm34As& ResultsForm34A(){return *_ResultsForm34AId;}	

	const int& Votes(){return _Votes;}
};
