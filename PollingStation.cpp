#include "PollingStation.hxx"

unsigned int PollingStation::Id() const { return m_id; }

void PollingStation::Id(const unsigned int newid) { m_id = newid; }

unsigned int PollingStation::altId() const { return m_altId; }

const std::string &PollingStation::Name() const { return m_name; }

void PollingStation::Name(const std::string &name) { m_name.assign(name); }

const std::shared_ptr<PollingCenter> &PollingStation::WardPollingCenter() const {
  return m_pollingcenter;
}

const std::vector<std::weak_ptr<ResultsForm34A>> &PollingStation::ResultsForm34As() const {
  return m_resultsform34As;
}
