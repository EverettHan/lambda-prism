// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// Class designed to handle mapping between two Curves 
// The Mapping is realised using a projection Points with direction on each Curve..
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Jan. 00 Creation                                                  R. HAMZA
// Aug. 11 Added the functions GetType() and GetDir().                    R1Y
//=============================================================================
#ifndef CATProjectInDirectionCrvSurMapX_H
#define CATProjectInDirectionCrvSurMapX_H


#include "CATSetOfPointsMapX.h"
#include "CATMathVector.h"
class CATCurve;
class CATSoftwareConfiguration;

class ExportedByYP00IMPL CATProjectInDirectionCrvSurMapX : public CATSetOfPointsMapX  {
public:
   /** @nodoc */
  CATCGMNewClassArrayDeclare;
	//-------------------------------------------------------------------------
  // Constructors(Vide pour l'instant)
  //-------------------------------------------------------------------------
  CATProjectInDirectionCrvSurMapX (const CATCurve* iCurveToProject, const CATCrvLimits & iLimitsToProject,
                                   const CATCurve* iCurveProjected, const CATCrvLimits & iLimitsProjected,
                                   const CATMathVector* iDir,
                                   const double    iMaxGap,
                                   const CATLONG32      iNbPoints=0,
                                   const double*   iParamsToProject=0,
                                   const double*   iParamsProjected=0,
                                   const short     iDuplicate=1,
                                   CATSoftwareConfiguration * iConfig = NULL);

  CATProjectInDirectionCrvSurMapX(const CATCurve* iCurveToProject, 
                                  const double iRefLow, const double iRefHigh,
                                  const CATCurve* iCurveProjected,
                                  const double iLow, const double iHigh,
                                  const CATMathVector* iDir,
                                  const double    iMaxGap,
                                  const CATLONG32      iNbPoints=0,
                                  const double*   iParamsToProject=0,
                                  const double*   iParamsProjected=0,
                                  const short     iDuplicate=1,
                                  CATSoftwareConfiguration * iConfig = NULL);

  CATProjectInDirectionCrvSurMapX(const CATProjectInDirectionCrvSurMapX* iMapX);

  ~CATProjectInDirectionCrvSurMapX();
  
  virtual CATMapX* Duplicate()const;

  virtual CATMapX::Type GetType()const;

  const CATMathVector * GetDir() const;

  void SetDir( double iDir[]);

  void SetConfig(CATSoftwareConfiguration * iConfig);

  virtual void Dump(CATCGMOutput & os)const;

protected:
  //----------------------------------------------------------------------------------------------------------------
  // CATMapX methods (Reconverge depend de la fonctionnelle de projection PT/CRV par rapport a une direction donnee)
  //----------------------------------------------------------------------------------------------------------------
  void  Reconverge (const CATCurve * iCurveToProject, const double iPointToProject, 
                    const CATCurve * iCurveProjected, double & oPointProjected,
                    const double iLowProjected, const double iHighProjected,
                    const CATPositiveLength iApproximateResolution = 0.0) const;

  // INTERNAL ONLY 
  virtual size_t  GetDynamicMemoryBytes() const;   
  virtual size_t  GetStaticMemoryBytes() const; 

  //==============================================
  //  DATA
  //==============================================
protected:
  CATMathVector* _Dir;

private:
  CATSoftwareConfiguration * _Config;

};

#endif
