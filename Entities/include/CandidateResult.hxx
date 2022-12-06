#pragma once

#include <memory>
#include <odb/core.hxx>

class Candidate;
class ResultsForm34A;
   
class CandidateResult
{
  unsigned int m_id{};

  std::shared_ptr<Candidate> m_candidate{};

  std::shared_ptr<ResultsForm34A> m_resultsform34A{};

  unsigned int m_votes{};

  friend odb::access;

public:

  [[nodiscard]] unsigned int Id() const;
  void Id(unsigned int);

  [[nodiscard]] const std::shared_ptr<Candidate> &ElectionCandidate() const;

  [[nodiscard]] const std::shared_ptr<ResultsForm34A> &ResultsForm() const;

  [[nodiscard]] unsigned int Votes() const;

};

#ifdef ODB_COMPILER

#include "Candidate.hxx"
#include "ResultsForm34A.hxx"

#pragma db object(CandidateResult) table("CandidateResults")
#pragma db member(CandidateResult::m_id) id
#pragma db member(CandidateResult::m_candidate) not_null column("CandidateId")
#pragma db member(CandidateResult::m_resultsform34A) not_null column("ResultsForm34AId")

#endif
