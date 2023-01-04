#ifndef CATFaceFaceIntersectionCheckDiagnosis_h_
#define CATFaceFaceIntersectionCheckDiagnosis_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
//===========================================================================================
// 24/07/2015  G5S  Create read, write and validate functions so we can have a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker, which uses diagnosis objects.
//===========================================================================================

#include "CATGMModelInterfaces.h"
#include "CATIntersectionCheckDiagnosis.h"

class CATCXFace;
class CATCell;
class CATFace;
class CATLISTP(CATCGMObject);
class CATShell;
class CATTopology;

class ExportedByCATGMModelInterfaces CATFaceFaceIntersectionCheckDiagnosis: public CATIntersectionCheckDiagnosis
{
public:
  /**
   * Constructor
   */
  CATFaceFaceIntersectionCheckDiagnosis();

  /**
   * Destructor
   */
  virtual ~CATFaceFaceIntersectionCheckDiagnosis();

  //==========================
  // Acces aux donnees membres
  //==========================
  // Retourne les deux faces dont la confrontation a donné naissance au diagnostic
  virtual void GetIntersectedFaces(CATFace *&oFirstFace, CATFace *&oSecondFace) const = 0;

  virtual int GetAssociatedObjects(CATLISTP(CATGeometry) &ioAssociatedObjects) const = 0;

  virtual CATFaceFaceIntersectionCheckDiagnosis *Clone() const = 0;

  //=================================
  // Methodes virtuelles
  //=================================
  // Retourne les deux topologies dont la confrontation a donné naissance au diagnostic
  virtual void GetIntersectedCells(
    CATCell *&oFirstCell,
    CATCell *&oSecondCell) const = 0;

  virtual CATGeometry *GetAssociatedObject() const = 0;

  virtual void Dump(CATCGMOutput &iOutput) const = 0;

  virtual const char *ClassName() const = 0;

  virtual unsigned int GetType() const = 0;

  virtual int IsATypeOf(unsigned int iTypeReference) const = 0;
};

#endif /* CATFaceFaceIntersectionCheckDiagnosis_h_ */
