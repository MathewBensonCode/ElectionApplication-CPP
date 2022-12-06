#pragma once

#include <memory>
#include <string>
#include <vector>
#include <odb/core.hxx>

class PollingCenter;
class ResultsForm34A;

class PollingStation {
  unsigned int m_id{};

  unsigned int m_altId{};

  std::string m_name{};

  std::shared_ptr<PollingCenter> m_pollingcenter{};

  std::vector<std::weak_ptr<ResultsForm34A>> m_resultsform34As{};

  friend odb::access;

public:
  [[nodiscard]] unsigned int Id() const;
  void Id(unsigned int);

  [[nodiscard]] unsigned int altId() const;

  [[nodiscard]] const std::string &Name() const;
  void Name(const std::string &);

  [[nodiscard]] const std::shared_ptr<PollingCenter> &WardPollingCenter() const;

  [[nodiscard]] const std::vector<std::weak_ptr<ResultsForm34A>> &ResultsForm34As() const;
};

#ifdef ODB_COMPILER
#include "PollingCenter.hxx"
#include "ResultsForm34A.hxx"
#pragma db object(PollingStation) table("PollingStation")
#pragma db member(PollingStation::m_id) id
#pragma db member(PollingStation::m_altId) column("AltId")
#pragma db member(PollingStation::m_pollingcenter) column("PollingCenterId") not_null
#pragma db member(PollingStation::m_resultsform34As) inverse(m_pollingstation)

#endif
