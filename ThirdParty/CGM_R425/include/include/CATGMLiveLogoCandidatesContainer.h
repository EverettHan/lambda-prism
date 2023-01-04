#ifndef CATGMLiveLogoCandidatesContainer_H
#define CATGMLiveLogoCandidatesContainer_H

#include "CATIACGMLevel.h"

#ifdef CATIACGMV5R20
#include "CATGMModelInterfaces.h"
#else
#include "PersistentCell.h"
#endif

#include "ListPOfCATGMLiveLogoCandidate.h"
#include "CATDRepSeedsContainer.h"

#ifdef CATIACGMV5R20
class ExportedByCATGMModelInterfaces CATGMLiveLogoCandidatesContainer: public CATDRepSeedsContainer
#else
class ExportedByPersistentCell CATGMLiveLogoCandidatesContainer: public CATDRepSeedsContainer
#endif 
{
public: 
  CATGMLiveLogoCandidatesContainer(); 
  virtual ~CATGMLiveLogoCandidatesContainer();

  void AddLogoCandidate(CATGMLiveLogoCandidate * iLogoCandidate);
  void FilterLogoCandidates(ListPOfCATGMLiveLogoCandidate & iLogoCandidatesToKeep);
  void GetLogoCandidates(ListPOfCATGMLiveLogoCandidate & oLogoCandidates);

private:
  ListPOfCATGMLiveLogoCandidate _LogoCandidates;
};


#endif

