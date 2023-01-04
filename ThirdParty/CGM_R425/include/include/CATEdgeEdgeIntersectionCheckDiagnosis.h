#ifndef CATEdgeEdgeIntersectionCheckDiagnosis_h_
#define CATEdgeEdgeIntersectionCheckDiagnosis_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
//===========================================================================================
// 24/07/2015  G5S  Create read, write and validate functions so we can have a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker.
//===========================================================================================

#include "CATGMModelInterfaces.h"
#include "CATIntersectionCheckDiagnosis.h"

class CATCXEdge;
class CATCell;
class CATDomain;
class CATEdge;
class CATWire;

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class ExportedByCATGMModelInterfaces CATEdgeEdgeIntersectionCheckDiagnosis: public CATIntersectionCheckDiagnosis
{
public:
  /**
   * Constructor
   */
  CATEdgeEdgeIntersectionCheckDiagnosis();

  /**
   * Destructor
   */
  virtual ~CATEdgeEdgeIntersectionCheckDiagnosis();

  //==========================
  // Acces aux donnees membres
  //==========================
  // Retourne les deux edges dont la confrontation a donné naissance au diagnostic
  virtual void GetIntersectedEdges(CATEdge *&oFirstEdge, CATEdge *&oSecondEdge) const = 0;

  //=================================
  // Methodes virtuelles
  //=================================
  // Retourne les deux topologies dont la confrontation a donné naissance au diagnostic
  virtual void GetIntersectedCells(
    CATCell *&oFirstCell,
    CATCell *&oSecondCell) const = 0;

  virtual void Dump(CATCGMOutput &iOutput) const = 0;

  virtual const char *ClassName() const = 0;

  virtual unsigned int GetType() const = 0;

  virtual int IsATypeOf(unsigned int iTypeReference) const = 0;
};

#endif /* CATEdgeEdgeIntersectionCheckDiagnosis_h_ */
