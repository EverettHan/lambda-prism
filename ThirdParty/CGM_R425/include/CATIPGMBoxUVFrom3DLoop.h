#ifndef CATIPGMBoxUVFrom3DLoop_h_
#define CATIPGMBoxUVFrom3DLoop_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATCrvLimits;
class CATCurve;
class CATMathBox;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATMathBox2D;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMBoxUVFrom3DLoop;

/* Le but de cet operateur est, etant donne une liste de courbes (2D et 3D) et une surface, de determiner quels 
 * patchs de la surface sont interceptes par les courbes. 
 * Les resultats sont fournis sous la forme d'une CATMathBox2D contenant les bornes inferieures et superieures des 
 * parametres U et V, ou bien sous formes de 4 entiers qui sont les limites des numeros de patchs qui interceptent 
 * les courbes.
 * Si les courbes en entree sont toutes des PCurves posees sur la surface l'interception est prise au sens stricte,
 * sinon on regarde si les CATMathBox 3D qui contiennent les patchs et les courbes s'interceptent.
 * Le parametre _Tolerance permet de definir la tolerance pour l'intersection des boites (cf CATMathBox::IsIntersecting).
 */
class ExportedByCATGMModelInterfaces CATIPGMBoxUVFrom3DLoop: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBoxUVFrom3DLoop();

  // AddCurve
  virtual void AddCurve(CATCurve *iCurve, const CATCrvLimits &iLimit) = 0;

  // int Run() : Operateur de Run, permet d'initialiser les variables privees de la classe,
  // doit etre lance avant les methodes GetBoxUV, GetParams et GetPatchesNumber.
  virtual int Run() = 0;

  // CATBoolean GetRunned() : renvoie 1 si la methode Run a deja ete lancee, renvoie 0 sinon
  virtual CATBoolean GetRunned() = 0;

  // CATBoolean GetDiagnostic() : renvoie 0 si il n'y a eu aucune intersection, renvoie 1 sinon.
  virtual CATBoolean GetDiagnostic() = 0;

  // CATBoolean GetTypeOfCurves() : renvoie 1 si toutes les courbes sont des PCurves posee sur la surface iSurface, 0 sinon
  virtual CATBoolean GetTypeOfCurves() = 0;

  // void GetBoxUV(CATMathBox2D &ioCATBoxUV) : si l'operateur Run a deja tourne et si GetDiagnostic renvoie la boite 2D
  // des parametres U et V utiles.
  virtual void GetBoxUV(CATMathBox2D &ioCATBoxUV) = 0;

  // void GetParams(CATSurParam &ioLowParam, CATSurParam &ioHighParam) : si l'operateur Run a deja tourne et si 
  // GetDiagnostic renvoie les deux extremites de la boite 2D des parametres U et V utiles.
  //void GetParams(CATSurParam &ioLowParam, CATSurParam &ioHighParam);
  // void GetPatchesNumber(CATLONG32 oUmin, CATLONG32 oUmax, CATLONG32 oVmin, CATLONG32 oVmax) : si l'operateur Run a deja tourne et si 
  // GetDiagnostic renvoie les numeros inferieurs et superieurs des patches utiles.
  virtual void GetPatchesNumber(
    CATLONG32 oUmin,
    CATLONG32 oUmax,
    CATLONG32 oVmin,
    CATLONG32 oVmax) = 0;

  // void SetTolerance(double iTol) : permet de definir la tolerance pour l'intersection des boites 3D : 
  // methode IsIntersecting de CATMathBox.
  virtual void SetTolerance(double iTol) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBoxUVFrom3DLoop(); // -> delete can't be called
};

#endif /* CATIPGMBoxUVFrom3DLoop_h_ */
