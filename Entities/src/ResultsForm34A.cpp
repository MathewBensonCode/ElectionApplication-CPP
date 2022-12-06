#include "ResultsForm34A.hxx"

unsigned int ResultsForm34A::Id() const
{
    return m_id;
}

void ResultsForm34A::Id(unsigned int newid)
{
    m_id = newid;
}

const std::string& ResultsForm34A::ImageUrl() const
{
    return m_imageUrl;
}

void ResultsForm34A::ImageUrl(const std::string &imageurl)
{
    m_imageUrl.assign(imageurl);
}

const std::shared_ptr<PollingStation>& ResultsForm34A::Pollingstation() const
{
    return m_pollingstation;
}

const std::vector<std::weak_ptr<CandidateResult>> &ResultsForm34A::Candidateresults() const
{
    return m_candidateresults;
}

