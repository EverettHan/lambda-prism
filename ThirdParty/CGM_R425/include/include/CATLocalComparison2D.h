#ifndef CATLocalComparison2D_H
#define CATLocalComparison2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 

#include "Y30UIUTI.h"
#include "Y300IINT.h"

class CATSurface;
class CATMathDirection2D;
#include "CATSurParam.h"
#include "CATMathVector.h"

#include "CATCGMVirtual.h"
#include "CATCreateLocalComparison2D.h"

class CATSoftwareConfiguration;
class CATLocalAnalysis2D;


/**
* Class defining the local Comparison on a point of a two CATSurfaces.
* The two surfaces have to haeve the same parametrization/
*<br>It performs deformation in length on a point of a CATSurface. This class is not streamable.
* The point where the analysis is done can be changed by @href CATLocalComparison2D#SetParam.
*/
class ExportedByY30UIUTI CATLocalComparison2D : public CATCGMVirtual
  {
  CATCGMVirtualDeclareClass(CATLocalComparison2D);

  public :
    /**
    * Creates a local Comparison on two points of CATSurfaces.
    * @param iConfig
    * The level of code (Versionning).
    * @param iSupport
    * The surface on which the Comparison is done.
    * @param iPointToCompare
    * The parameter on <tt>iSupport</tt> of the point to Compare.
    */   
    CATLocalComparison2D (CATSoftwareConfiguration * iConfig,
      const CATSurface *iRefSurface, 
      const CATSurface *iSurface, 
      const CATSurParam &iPointToAnalyze);

    /**
    * Destructor.
    */
    virtual ~CATLocalComparison2D () ;

    /**
    * Copy Constructor.
    */
    CATLocalComparison2D (const CATLocalComparison2D &iComparisonToCopy ) ;

    /**
    * Assignment operator.
    */
    CATLocalComparison2D& operator=(const CATLocalComparison2D &iComparisonToAffect) ;

    /**
    * Modifies the point where <tt>this</tt> CATLocalComparison2D is performed.
    *<br>The comparison is automatically done.
    * @param iNewParamToAnalyze
    * The parameter of the new point to analyze.
    */
    virtual void SetParam (const CATSurParam &iNewParamToAnalyze) ;

    /**
    * @nodoc
    */
    void SetReferenceSurface(CATSurface* iRefSurface) ;

    /**
    * @nodoc
    */
    double GetDeformation() ;

    //Data
  public:
  protected :
  private:
    CATSoftwareConfiguration * _Config;
    const CATSurface *   _Surface;
    const CATSurface *_RefSurface;

    CATSurParam _Param;
    CATSurParam _RefParam;

  };

#endif 
