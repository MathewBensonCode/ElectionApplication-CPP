#include "PollingCenter.hxx"

unsigned int PollingCenter::Id() const
{
    return m_id;
}

void PollingCenter::Id(const unsigned int newid)
{
    m_id = newid;
}

const std::string& PollingCenter::Name() const
{
    return m_name;
}

void PollingCenter::Name(const std::string &name)
{
    m_name.assign(name);
}

const std::shared_ptr<Ward>& PollingCenter::ConsituencyWard() const
{
    return m_ward;
}

const std::vector<std::weak_ptr<PollingStation>> &PollingCenter::PollingStations() const
{
    return m_pollingstations;
}
