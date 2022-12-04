#include "Constituency.hxx"

unsigned int Constituency::Id() const
{
    return m_id;
}

void Constituency::Id(unsigned int newid)
{
    m_id = newid;
}

const std::string& Constituency::Name() const
{
    return m_name;
}

void Constituency::Name(const std::string &name)
{
    m_name.assign(name);
}

const std::shared_ptr<County>& Constituency::ConstituencyCounty() const
{
    return m_county;
}

const std::vector<std::weak_ptr<Ward>> &Constituency::Wards() const
{
    return m_wards;
}
