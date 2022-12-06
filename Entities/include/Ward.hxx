#pragma once

#include <memory>
#include <odb/core.hxx>
#include <string>
#include <vector>

class Constituency;
class PollingCenter;

class Ward {

  unsigned int m_id{};
  std::string m_name{};

  std::shared_ptr<Constituency> m_constituency{};
  std::vector<std::weak_ptr<PollingCenter>> m_pollingcenters;

  friend odb::access;

public:
  [[nodiscard]] unsigned int Id() const;
  void Id(unsigned int);

  [[nodiscard]] const std::string &Name() const;
  void Name(const std::string &);

  [[nodiscard]] const std::shared_ptr<Constituency> &WardConstituency() const;
  [[nodiscard]] const std::vector<std::weak_ptr<PollingCenter>> &
  PollingCenters() const;
};

#ifdef ODB_COMPILER

#include "Constituency.hxx"
#include "PollingCenter.hxx"

#pragma db object(Ward) table("Wards")
#pragma db member(Ward::m_id) id
#pragma db member(Ward::m_constituency) not_null column("ConstituencyId")
#pragma db member(Ward::m_pollingcenters) inverse(m_ward)


#endif
