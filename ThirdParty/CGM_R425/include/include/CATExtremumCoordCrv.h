// COPYRIGHT DASSAULT SYSTEMES 1999
//===================================================================
//
// CATExtremumCoordCrv : operator which gives for a geometric element
// the exact box with (xmin,ymin,zmin) and (xmax,ymax,zmax).
//
//===================================================================
// Aug 99  FBZ
//===================================================================

#ifndef CATExtremumCoordCrv_H
#define CATExtremumCoordCrv_H

#include "Y30A3HGG.h"

class CATGeometry;
class CATGeoFactory;
class CATCurve;
class CATCrvLimits;
class CATSoftwareConfiguration;

#include "CATCrvParam.h"
#include "CATCGMVirtual.h"
#include "CATExtremumCoordCrvDef.h"

class ExportedByY30A3HGG CATExtremumCoordCrv   : public CATCGMVirtual
{  
  
private:
  CATCurve ** _Crv;
  CATSoftwareConfiguration *_Config;
  double _Xsol;
  CATCrvParam _Paramsol;
  CATLONG32 _NumberOfCurveSolution;
  CATGeoFactory * _Factory;
  CATCrvLimits *_CrvLim;
  CATLONG32 _nbCrv;
  Direction _Dir;
  MinMax _Minmax;

public:

  //-----------------------------------------------------------------------
  //- Constructor
  //
  //-prend en entree un tableau de nbCrv courbes avec des limites associees
  //
  //-precise si on cherche xmin, xmax, ymin, ymax, zmin ou zmax
  // par defaut, on cherche xmin
  //-----------------------------------------------------------------------  
  CATExtremumCoordCrv(CATGeoFactory *iFactory,CATSoftwareConfiguration *iConfig,
    CATCurve ** iCrv, CATLONG32 nbCrv,
    CATCrvLimits *iLim,  Direction iDirection = XDirection,
    MinMax iMinMax = Min);  

  //-----------------------------------------------------------------------
  //- Destructor
  //-----------------------------------------------------------------------  
  ~CATExtremumCoordCrv();

  //-----------------------------------------------------------------------
  //- Reading the results
  //-----------------------------------------------------------------------
  
  //-----------------------------------------------------------------------
  //  GetExtremum 
  //  renvoie un des extremums de la courbe suivant un axe ( X, Y ou Z )
  //-----------------------------------------------------------------------
  double GetExtremum();

  //-----------------------------------------------------------------------
  //  GetPointSolution
  //  renvoie le numero de la courbe sur laquelle est trouve 
  //  l'extremum ainsi que le CrvParam associe
  //-----------------------------------------------------------------------
  void GetPointSolution(CATLONG32 &oNumberCrv, CATCrvParam &oParam);

  //-----------------------------------------------------------------------
  //- Set Method
  //----------------------------------------------------------------------- 
  
  //-----------------------------------------------------------------------
  // SetSearch
  // permet de specifier quel extremum on souhaite chercher 
  //
  // iDir indique dans quelle direction : XDirection, YDirection ou ZDirection 
  //
  // iMinMax indique si c'est la valeur maximale ou minimale dans cette direction 
  //------------------------------------------------------------------------
  void SetSearch(Direction iDir, MinMax iMinMax);   
   
  //-----------------------------------------------------------------------
  //- Execution
  //-----------------------------------------------------------------------  
  int Run() ;  
};

#endif
