#pragma once

#include <string>
#include <memory>
#include <vector>
#include <odb/core.hxx>


class County;
class Ward;

class Constituency
{
  unsigned int m_id {};
  std::string m_name{};

  std::shared_ptr<County> m_county{};
  std::vector<std::weak_ptr<Ward>> m_wards{};

  friend class odb::access;

public:
  [[nodiscard]] unsigned int Id() const;
  void Id(unsigned int);

  [[nodiscard]] const std::string& Name() const;
  void Name(const std::string&);

  [[nodiscard]] const std::shared_ptr<County>& ConstituencyCounty() const;

  [[nodiscard]] const std::vector<std::weak_ptr<Ward>> &Wards() const;
};

#ifdef ODB_COMPILER
#include "County.hxx"
#include "Ward.hxx"
#pragma db object(Constituency) table("Constituencies")
#pragma db member(Constituency::m_id) id
#pragma db member(Constituency::m_county) column("CountyId") not_null
#pragma db member(Constituency::m_wards) inverse(m_constituency)

#endif
