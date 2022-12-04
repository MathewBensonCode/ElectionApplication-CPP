#include "CandidateResult.hxx"

unsigned int CandidateResult::Id() const
{
    return m_id;
}

void CandidateResult::Id(unsigned int newid)
{
    m_id = newid;
}

const std::shared_ptr<Candidate> &CandidateResult::ElectionCandidate() const
{
    return m_candidate;
}

const std::shared_ptr<ResultsForm34A> &CandidateResult::ResultsForm() const
{
    return m_resultsform34A;
}

unsigned int CandidateResult::Votes() const
{
    return m_votes;
}
