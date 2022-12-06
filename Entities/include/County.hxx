#pragma once

#include <memory>
#include <vector>

#include <odb/core.hxx>


class Constituency;

class County {
  unsigned int m_id{};
  std::string m_name{};
  std::vector<std::weak_ptr<Constituency>> m_constituencies;

  friend odb::access;

public:
  [[nodiscard]] unsigned int Id() const;
  void Id(unsigned int);

  [[nodiscard]] const std::string &Name() const;
  void Name(const std::string &);

  [[nodiscard]] const std::vector<std::weak_ptr<Constituency>> &
  Constituencies() const;
};

#ifdef ODB_COMPILER

#pragma db object(County) table("Counties")
#pragma db member(County::m_id) id
#pragma db member(County::m_constituencies) inverse(m_county)

#include "Constituency.hxx"

#endif

