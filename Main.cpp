#include "database.h"
#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include "County-odb.hxx"
#include "County.hxx"

#include "Constituency-odb.hxx"
#include "Constituency.hxx"

#include "Ward-odb.hxx"
#include "Ward.hxx"

#include "PollingCenter-odb.hxx"
#include "PollingCenter.hxx"

#include "PollingStation-odb.hxx"
#include "PollingStation.hxx"

#include "ResultsForm34A-odb.hxx"
#include "ResultsForm34A.hxx"

#include "CandidateResult-odb.hxx"
#include "CandidateResult.hxx"

#include "Candidate-odb.hxx"
#include "Candidate.hxx"

#include <algorithm>
#include <execution>

std::ostream& operator<<(std::ostream& os, const Counties& county)
{
	os<<"County : "<< county.Name()<<"\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, const Constituencies& constituency)
{
	os<<"Constituency : "<< constituency.Name()<<" \t"<<constituency.County();
	return os;

}

std::ostream& operator<<(std::ostream& os, const Wards& ward)
{
	os<<"Ward : "<< ward.Name()<< "  \t" << ward.Constituency();
	return os;
}

std::ostream& operator<<(std::ostream& os, const PollingCentres& pollingCenter)
{
	os<<"Polling Center : "<<pollingCenter.Name()<<" \t"<< pollingCenter.Ward();
	return os;
}

std::ostream& operator<<(std::ostream& os, const PollingStation& pollingStation)
{
	os<<"Polling Station : "<<pollingStation.AltId()<<" \t"<<pollingStation.PollingCenter();
	return os;
}


std::ostream& operator<<(std::ostream& os, const ResultsForm34As& results)
{
	os<<"\n\nResults From : " << results.GetPollingStation()<< " : -> \n";
	

	return os;
}


int main(int /*argc*/, char** /*argv*/)
{
	auto db = create_database();

	using resultsquery = odb::query<CandidateResults>;
	using candidatequery = odb::query<Candidates>;
	using pollingstationquery = odb::query<PollingStation>;

	auto findAllResults = resultsquery();
	auto findAllCandidates = candidatequery();
	auto findAllPollingStations = pollingstationquery();
	
	try{
        odb::transaction t(db->begin());

	const int arraysize = 8;

	auto votescount = std::array<int, arraysize>{0};

	auto r = db->query(resultsquery());

	std::for_each(std::begin(r), std::end(r), [&](auto &a)
			{
				votescount[a.Candidate().Id()-1] += a.Votes();
						
			});
	auto r2 = db->query(findAllCandidates);

	std::for_each(std::begin(r2), std::end(r2), [&](auto &a2)
			{
				std::cout<<"Candidate : "<< a2.Name()<<" Got : "<<votescount[a2.Id()-1]<<" Votes \n";
			});


	
	t.commit();

	}

	catch(std::exception & e)
	{
		std::cerr<< e.what();
		return 1;
	}

	return 0;
}
