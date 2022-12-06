#pragma once

#include <memory>
#include <odb/core.hxx>
#include <string>
#include <vector>

class Ward;
class PollingStation;

class PollingCenter {

  int m_id{};

  std::string m_name{};

  std::shared_ptr<Ward> m_ward{};

  std::vector<std::weak_ptr<PollingStation>> m_pollingstations;

  friend odb::access;

public:
  [[nodiscard]] int Id() const;
  void Id(int);

  [[nodiscard]] const std::string &Name() const;
  void Name(const std::string &);

  [[nodiscard]] const std::shared_ptr<Ward> &ConsituencyWard() const;

  [[nodiscard]] const std::vector<std::weak_ptr<PollingStation>> &
  PollingStations() const;
};

#ifdef ODB_COMPILER

#include "PollingStation.hxx"
#include "Ward.hxx"

#pragma db object(PollingCenter) table("PollingCentres")
#pragma db member(PollingCenter::m_id) id
#pragma db member(PollingCenter::m_ward) column("WardId") not_null
#pragma db member(PollingCenter::m_pollingstations) inverse(m_pollingcenter)

#endif
