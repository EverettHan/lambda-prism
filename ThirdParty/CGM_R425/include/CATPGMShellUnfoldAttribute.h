#ifndef CATPGMShellUnfoldAttribute_h_
#define CATPGMShellUnfoldAttribute_h_

// COPYRIGHT DASSAULT SYSTEMES 2016

#include "CATGMOperatorsInterfaces.h"
#include "CATCGMStreamClonableAttribute.h"

class CATMathSetOfLongs;
class CATMathSetOfPointsND;
class CATMathPoint;
class CATMathVector;
class CATExtClonableManager;
class CATICGMObject;

// Unfold type
typedef enum  { 
                CATShellFrFUnfold, 
								CATShellExpansion, 
								CATShellUndefined
              } 
CATShellUnfoldType;

//-----------------------------------------------------------------------
// CATPGMShellUnfoldAttribute
//-----------------------------------------------------------------------  
class ExportedByCATGMOperatorsInterfaces CATPGMShellUnfoldAttribute: public CATCGMStreamClonableAttribute
{
public:
  /**
   * Constructor
   */
  CATPGMShellUnfoldAttribute();

  /**
   * Destructor
   */
  virtual ~CATPGMShellUnfoldAttribute();

  // Streaming/Unstreaming of mesh atttributes
  virtual void UnStream(CATCGMStream &ioStream) = 0;

  virtual void Stream(CATCGMStream &ioStream) const = 0;

  // Get & Set methods for mesh attributes
  virtual void SetMeshAttributes(
    CATLONG32 iNbVertices,
    CATLONG32 iNbTriangles,
    CATMathSetOfLongs &ipTriangleIndices,
    CATMathSetOfPointsND &ipInputPoints,
    CATMathSetOfPointsND &ipOutputPoints) = 0;

  virtual void GetMeshAttributes(
    CATLONG32 &oNbVertices,
    CATLONG32 &oNbTriangles,
    CATMathSetOfLongs *&iopTriangleIndices,
    CATMathSetOfPointsND *&iopInputPoints,
    CATMathSetOfPointsND *&iopOutputPoints) const = 0;

  // Get & Set methods for Unfold type (0 : Free Form Unfold, 1: Shell Expansion)
  virtual void SetUnfoldType(CATShellUnfoldType iUnfoldType) = 0;

  virtual void GetUnfoldType(CATShellUnfoldType &ioUnfoldType) const = 0;

  // Get & Set methods for the reference origin 
  virtual void SetOrigin(const CATMathPoint & iReferenceOrigin) = 0;

  virtual void GetOrigin(CATMathPoint &ioReferenceOrigin) const = 0;

  // Get & Set methods for the first direction (Reference vector in Shell Expansion)
  virtual void SetFirstDirection(const CATMathVector & iFirstDirection) = 0;

  virtual void GetFirstDirection(CATMathVector &ioFirstDirection) const = 0;

  // Get & Set methods for the second diection (Symmetry plane normal in Shell Expansion)
  virtual void SetSecondDirection(const CATMathVector & iSecondDirection) = 0;

  virtual void GetSecondDirection(CATMathVector &ioSecondDirection) const = 0;

  // Report the clonable attributes from origin to destination
  virtual CATCGMAttribute *ReportClonableAttributes(
    CATExtClonableManager *ipClonableManager,
    CATICGMObject *ipOrigin,
    CATICGMObject *ipDestination) = 0;

};

ExportedByCATGMOperatorsInterfaces CATPGMShellUnfoldAttribute *CATPGMCreateShellUnfoldAttribute();

#endif /* CATPGMShellUnfoldAttribute_h_ */
