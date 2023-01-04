#ifndef CATIPGMFrFCheckGeometricContinuity_h_
#define CATIPGMFrFCheckGeometricContinuity_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"

class CATCartesianPoint;
class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATSoftwareConfiguration;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFrFCheckGeometricContinuity;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMFrFCheckGeometricContinuity: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMFrFCheckGeometricContinuity();

  //------------------- Data Access Methods -------------------  
  // Recuperation des resultats ; la methode Run doit avoir ete appelee
  // auparavent et le double Results doit DEJA etre alloue.
  // Results[0] = distance maximale entre 2 points (carre de la distance)
  // Results[1] = angle maximal entre les normales 
  // Results[2] = angle maximal entre les tangentes a la surface dans la 
  //              direction orthogonale a la tgt a la courbe (la continuite
  //              C0 donnant deja linfo pour la direction de la tgt a la 
  //              courbe).
  // Results[3] = difference maximale entre les courbures gaussiennes 
  // Results[4] = difference maximale entre les courbures gaussiennes 
  //              rapportee a la somme des valeurs absolues des courbures.
  virtual void GetResults(double *Results) const = 0;

  // Recuperation des resultats ; la methode Run doit etre appelee apres
  // et le retour est alloue par la methode (a detruire donc).
  // Point[0] et Point[1] = distance maximale entre 2 points (carre de la distance)
  // Point[2] et Point[3] = angle maximal entre les normales 
  // Point[4] et Point[5] =  difference maximale entre les courbures gaussiennes 
  virtual CATCartesianPoint **GetPoints() = 0;

  // impose les courbes et leur crvlimits
  virtual void SetCurveOne(const CATCurve *C1, const CATCrvLimits &CL1) = 0;

  virtual void SetCurveTwo(const CATCurve *C2, const CATCrvLimits &CL2) = 0;

  // impose le type de continuite
  // 1  : C0                        DEFAULT  
  // 2  : Colinear normals (G1)    
  // 3  : Colinear tangents (C1)  (dans la direction ortho a la tgte a la courbe)
  // 4  : Curvature continuity (C2) 
  virtual void SetContinuityMode(int ContinuityMode) = 0;

  // Impose le nombre de points discretises (equisdistants en parametre)
  // ou se feront les tests de continuite (10 par defaut).
  virtual void SetNbOfDiscretizedPoints(int NbOfDiscretizedPoints) = 0;

  // Impose le type de coupling :
  // 1 = a isoparametre (a la reorientation pres) DEFAULT
  // 2 = par projection sur la courbe opposee
  virtual void SetCouplingType(int iCType) = 0;

  // Impose l orientation relative des courbes 
  // a un sens seulement pour coupling isoparameter 
  // 1  : orientees dans le meme sens
  // -1 : orientees de maniere inverse
  virtual void SetOrientation(int iOrientation) = 0;

  // Affiche les resultats
  // 1 == oui, 0 == non (DEFAUT)
  virtual void SetDisplay(int iDisplay) = 0;

  // Rend symetrique le calcul (uniquement avec report par min distance).
  // Par defaut non symetrique : La courbe 1 est discretisee et une distance min est faite avec la courbe 2.
  virtual void SetSymetricComputation() = 0;

  // Permet de mettre des plafonds au dessus desquels, on ne souhaite pas poursuivre l'analyse
  virtual void SetMaxValues(double *iMaxPt, double *iMaxNormal = 0, double *iMaxCurvature = 0) = 0;

  //------------------- Compute Methods -------------------  
  virtual void Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFrFCheckGeometricContinuity(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFrFCheckGeometricContinuity *CATPGMCreateFrFCheckGeometricContinuity(
  CATGeoFactory *iFactory,
  const CATCurve *C1,
  const CATCurve *C2,
  CATCrvLimits & CL1,
  CATCrvLimits & CL2,
  CATSoftwareConfiguration *iSoftwareConfiguration = NULL);

#endif /* CATIPGMFrFCheckGeometricContinuity_h_ */
