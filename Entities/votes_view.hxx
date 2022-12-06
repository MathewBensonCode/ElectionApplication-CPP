#pragma once

#include "Candidate.hxx"
#include "CandidateResult.hxx"

#pragma db view object(Candidate) object(CandidateResult)
struct votes_view {

  std::string name;

#pragma db column("sum(" + CandidateResult::m_votes + ")")
  unsigned int votes;
};
