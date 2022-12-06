#include "Candidate.hxx"

unsigned int Candidate::Id() const
{
    return m_id;
}

void Candidate::Id(unsigned int newid)
{
    m_id = newid;
}

const std::string& Candidate::Name() const
{
    return m_name;
}

void Candidate::Name(const std::string& name)
{
    m_name.assign(name);
}

const std::vector<std::weak_ptr<CandidateResult>> &Candidate::CandidateResults() const
{
    return m_candidateresults;
}
