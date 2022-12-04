#include "Ward.hxx"

unsigned int Ward::Id() const
{
    return m_id;
}

void Ward::Id(unsigned int newid)
{
    m_id = newid;
}

const std::string& Ward::Name() const
{
    return m_name;
}

void Ward::Name(const std::string &name)
{
    m_name.assign(name);
}

const std::shared_ptr<Constituency>& Ward::WardConstituency() const
{
    return m_constituency;
}

const std::vector<std::weak_ptr<PollingCenter> > &Ward::PollingCenters() const
{
    return m_pollingcenters;
}
