#include "County.hxx"

unsigned int County::Id() const
{
    return m_id;
}

void County::Id(unsigned int newid)
{
    m_id = newid;
}

const std::string& County::Name() const
{
    return m_name;
}

void County::Name(const std::string& name)
{
    m_name.assign(name);
}

const std::vector<std::weak_ptr<Constituency>> &County::Constituencies() const
{
    return m_constituencies;
}
