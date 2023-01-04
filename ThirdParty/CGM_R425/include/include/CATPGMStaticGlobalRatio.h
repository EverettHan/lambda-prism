#ifndef CATPGMStaticGlobalRatio_h_
#define CATPGMStaticGlobalRatio_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATBody;
class CATEdge;
class CATMathPoint;
class CATTopData;

// parametre d'un point sur un wire
typedef double CATGlobalRatio;
// parametre d'un point sur une edge. ce parametre ne depad pas du wire dans lequel
// l edge est incluse
typedef double CATLocalRatio;

//
// pour toutes les methodes statiques de cette classe,
// le retour 0 signifie que tout s'est bien passe 
// et qu'on a pu realiser le calcul demande.
// retour <> 0 alors quelque chose a cloche
// se reporter qux commentaires pour plus de precision
//
class ExportedByCATGMModelInterfaces CATPGMStaticGlobalRatio
{
public:
  //
  //
  // calculs du global ratio
  //
  // a partir du point 3D
  static int CATGRFromMathPoint(
    CATBody *Wire,
    const CATMathPoint &MathPoint,
    CATGlobalRatio &GR);

  static int CATGRFromMathPoint(
    CATBody *Wire,
    CATTopData *iData,
    const CATMathPoint &MathPoint,
    CATGlobalRatio &GR);

  // a partir de l'edge local et du ratio local
  static int CATGRFromLocale(
    CATBody *Wire,
    CATEdge *LocalEdge,
    const CATLocalRatio &LR,
    CATGlobalRatio &GR,
    CATTopData *iData = 0);

  //
  // calculs a partir du ratio global
  //
  // calcul de l'edge et du ratio local sur l'edge
  static int CATLocaleFromGR(
    CATBody *Wire,
    const CATGlobalRatio &GR,
    CATEdge *&LocalEdge,
    CATLocalRatio &LR,
    CATTopData *iData = 0);

  // calcul du point 3D equivalent
  //renvoie 0 qd tout va bien
  //renvoie 1 qd c'est ferme ... mais tout va bien aussi en principe ! (attention, eventuel pb stabilite)
  //renvoie 2 si erreur
  static int CATMathPointFromGR(
    CATBody *Wire,
    const CATGlobalRatio &GR,
    CATMathPoint &PointXYZ);

  static int CATMathPointFromGR(
    CATBody *Wire,
    CATTopData *iData,
    const CATGlobalRatio &GR,
    CATMathPoint &PointXYZ);

};

#endif /* CATPGMStaticGlobalRatio_h_ */
