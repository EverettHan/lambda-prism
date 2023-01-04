
//#define AFFICHE_DEBUG

#ifndef CATBoxUVFrom3DLoop_H
#define CATBoxUVFrom3DLoop_H

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATMathBox2D.h"
#include "CATSurParam.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATCrvLimits.h"
#include "CATFrFNurbsBipar.h"
#include "CATCreateBoxUVFrom3DLoop.h"

class CATMathBox;
class CATCurve;
class CATCrvLimits;
class CATSurface;
class CATSurLimits;
class CATSoftwareConfiguration;
#include "CATGeoFactory.h"

/* Le but de cet operateur est, etant donne une liste de courbes (2D et 3D) et une surface, de determiner quels 
 * patchs de la surface sont interceptes par les courbes. 
 * Les resultats sont fournis sous la forme d'une CATMathBox2D contenant les bornes inferieures et superieures des 
 * parametres U et V, ou bien sous formes de 4 entiers qui sont les limites des numeros de patchs qui interceptent 
 * les courbes.
 * Si les courbes en entree sont toutes des PCurves posees sur la surface l'interception est prise au sens stricte,
 * sinon on regarde si les CATMathBox 3D qui contiennent les patchs et les courbes s'interceptent.
 * Le parametre _Tolerance permet de definir la tolerance pour l'intersection des boites (cf CATMathBox::IsIntersecting).
 */


class ExportedByY30UIUTI  CATBoxUVFrom3DLoop : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATBoxUVFrom3DLoop);
public:
  // 1er Constructeur
  CATBoxUVFrom3DLoop(CATGeoFactory * iFactory,CATSoftwareConfiguration * iConfig, CATSurface * iSurface);
  /*
   * iFactory : Factory,
   *
   * iCurveList : liste de courbes (Curves ou PCurves),
   *
   * iCrvLimitsList : liste des limites des courbes de iCurveList,
   *
   * iSurface : surface multipatches.
   */

  // 2eme Constructeur
  CATBoxUVFrom3DLoop(CATGeoFactory * iFactory,CATSoftwareConfiguration * iConfig, CATFrFNurbsBipar * iSurface);

  // AddCurve
  void AddCurve(CATCurve * iCurve, const CATCrvLimits & iLimit);


  ~CATBoxUVFrom3DLoop();
    
private:
  CATBoolean CheckI(CATBoolean * array, CATLONG32 I, CATLONG32 NbU, CATLONG32 NbV);
  CATBoolean CheckJ(CATBoolean * array, CATLONG32 J, CATLONG32 NbU, CATLONG32 Imin, CATLONG32 Imax);
  
public:
  // int Run() : Operateur de Run, permet d'initialiser les variables privees de la classe,
  // doit etre lance avant les methodes GetBoxUV, GetParams et GetPatchesNumber.
  int Run();

  // CATBoolean GetRunned() : renvoie 1 si la methode Run a deja ete lancee, renvoie 0 sinon
  CATBoolean GetRunned();

  // CATBoolean GetDiagnostic() : renvoie 0 si il n'y a eu aucune intersection, renvoie 1 sinon.
  CATBoolean GetDiagnostic();

  // CATBoolean GetTypeOfCurves() : renvoie 1 si toutes les courbes sont des PCurves posee sur la surface iSurface, 0 sinon
  CATBoolean GetTypeOfCurves();
  
  // void GetBoxUV(CATMathBox2D &ioCATBoxUV) : si l'operateur Run a deja tourne et si GetDiagnostic renvoie la boite 2D
  // des parametres U et V utiles.
  void GetBoxUV(CATMathBox2D &ioCATBoxUV);

  // void GetParams(CATSurParam &ioLowParam, CATSurParam &ioHighParam) : si l'operateur Run a deja tourne et si 
  // GetDiagnostic renvoie les deux extremites de la boite 2D des parametres U et V utiles.
  //void GetParams(CATSurParam &ioLowParam, CATSurParam &ioHighParam);

  // void GetPatchesNumber(CATLONG32 oUmin, CATLONG32 oUmax, CATLONG32 oVmin, CATLONG32 oVmax) : si l'operateur Run a deja tourne et si 
  // GetDiagnostic renvoie les numeros inferieurs et superieurs des patches utiles.
  void GetPatchesNumber(CATLONG32 oUmin, CATLONG32 oUmax, CATLONG32 oVmin, CATLONG32 oVmax);

  // void SetTolerance(double iTol) : permet de definir la tolerance pour l'intersection des boites 3D : 
  // methode IsIntersecting de CATMathBox.
  void SetTolerance(double iTol);
  
private:  
  CATLONG32                     _UMinUsefull, _UMaxUsefull, _VMinUsefull, _VMaxUsefull;
  CATLISTP(CATCurve)      *_CurveList;
  CATLISTP(CATCrvLimits)  *_CrvLimitsList;
  CATSurface              *_Surface;
  double                   _Tolerance;
  CATMathBox2D             _CATBoxUV;
  CATSurParam              _LowParam,_HighParam;
  short                    _WhichConstructor;
  CATBoolean               _AlreadyRunned;
  CATBoolean               _Diagnostic;
  CATBoolean               _AllPCurves;
  CATSoftwareConfiguration * _Config;
   
#ifdef AFFICHE_DEBUG
public:
  CATMathBox              *_BoxCurveArray;
  CATMathBox              *_BoxSurfArray;
  CATLONG32 _NbCurves;
  CATLONG32 _NbPatches;
#endif

};

#endif

