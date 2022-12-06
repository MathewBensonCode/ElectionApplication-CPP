#pragma once

#include <memory>
#include <string>
#include <vector>
#include <odb/core.hxx>

class PollingStation;
class CandidateResult;

class ResultsForm34A {

  unsigned int m_id{};

  std::string m_imageUrl{};

  std::shared_ptr<PollingStation> m_pollingstation{};
  
  std::vector<std::weak_ptr<CandidateResult>> m_candidateresults{};

  friend odb::access;

public:
  [[nodiscard]] unsigned int Id() const;
  void Id(unsigned int);

  [[nodiscard]] const std::string &ImageUrl() const;
  void ImageUrl(const std::string &);

  [[nodiscard]] const std::shared_ptr<PollingStation> &Pollingstation() const;

  [[nodiscard]] const std::vector<std::weak_ptr<CandidateResult>> &Candidateresults() const;
};

#ifdef ODB_COMPILER

#include "CandidateResult.hxx"
#include "PollingStation.hxx"

#pragma db object(ResultsForm34A) table("ResultsForm34As")
#pragma db member(ResultsForm34A::m_id) id
#pragma db member(ResultsForm34A::m_pollingstation) column("PollingStationId") not_null
#pragma db member(ResultsForm34A::m_candidateresults) inverse(m_resultsform34A)

#endif
