#ifndef CATPositionPtFaceOperatorPro_h
#define CATPositionPtFaceOperatorPro_h

// COPYRIGHT DASSAULT SYSTEMES  2009

// Interface en  Protected Pour Methodes Particulieres
//
// Aout2009 JSX Ajout IsOnBoundary

#include "CATPositionPtFaceOperator.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATEdge;
class CATFace;
class CATSurParam;
class CATTopPositionPtFaceOperator;
class CATPositionPtFaceOperatorPro : public CATPositionPtFaceOperator
  {
  CATCGMVirtualDeclareClass(CATPositionPtFaceOperatorPro);

 public :
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
  virtual void SetSurParam(const CATSurParam& iPoint);
  virtual void SetSurParams(int             iNbPoints,
                            CATSurParam     iPoints[]);
  virtual void SetToleranceOnBoundary(double iTol);
  virtual void        Run();
  virtual CATLocation   GetOneResult();
  virtual const CATLocation*    GetResults() const;






  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


     /** @nodoc */
/*  CATPositionPtFaceOperatorPro(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATSurParam   & iPoint,
    CATFace       * iFace);*/

  CATPositionPtFaceOperatorPro(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    int             iNbPoints,
    CATSurParam     iPoints[], 
    CATFace       * iFace);

  virtual ~CATPositionPtFaceOperatorPro();
  public :
    virtual void SetLockCrvEq();
    virtual void IsOnBoundary(const CATSurParam & iParam, CATFace * iFace, CATEdge *& oEdge);
  protected :

    CATPositionPtFaceOperatorPro() {_TopoPositionOperator=0;};
    CATTopPositionPtFaceOperator * _TopoPositionOperator ;

  };

ExportedByCATTopologicalObjects CATPositionPtFaceOperatorPro * GetProtectedPositionPtFaceOperator(CATPositionPtFaceOperator *Ope);

ExportedByCATTopologicalObjects CATPositionPtFaceOperatorPro * CATCreatePositionPtFaceOperatorPro(CATGeoFactory * iFactory,
                                                                                                  CATSoftwareConfiguration * iConfig,
                                                                                                  int             iNbPoints,
                                                                                                  CATSurParam     *iPoints, 
                                                                                                  CATFace         *iFace,
                                                                                                  CATBoolean      iLockCrvEquation);

#endif
