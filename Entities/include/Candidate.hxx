#pragma once

#include <odb/core.hxx>
#include <string>
#include <vector>
#include <memory>

class CandidateResult;

class Candidate {

  unsigned int m_id{};
  std::string m_name{};

  std::vector<std::weak_ptr<CandidateResult>> m_candidateresults;

  friend odb::access;

public:
  [[nodiscard]] unsigned int Id() const;
  void Id(unsigned int);

  [[nodiscard]] const std::string &Name() const;
  void Name(const std::string &);

  [[nodiscard]] const std::vector<std::weak_ptr<CandidateResult>> &CandidateResults() const;
};

#ifdef ODB_COMPILER

#include "CandidateResult.hxx"

#pragma db object(Candidate) table("Candidates")
#pragma db member(Candidate::m_id) id
#pragma db member(Candidate::m_candidateresults) inverse(m_candidate)

#endif
