//====================================================================
// Copyright Dassault Systemes Provence 1998-2006, all rights reserved 
//====================================================================
//======================================================================
//
// Compute Gcontinuity of a list of CATCurve.
//
//======================================================================
//  27/07/2006 : RNO ; Derivation CGMVirtual + Abstraction
//  21/05/2003 : RNO ; Versionning CATMassProperties1D (2 appels)
//  07-01-2003 : RNO ; Messages d'erreurs + cas ou retour run non teste
//  02-12-2002 : RNO ; Methode inline staic Getcurvature -> inline de classe sinon pbm R9 ?!
//  19-11-2002 : RNO ; Ajout des methodes de masquages, calcul des longueurs,
//                     Restructuration du code
//  18-05-2001 : HLN ; (RI301455A) Add _NullCurvatureThreshold et Set/Get 
//                     corresponding methods
//  06-02-2001 : MWE ; ajout de GetG2Delta
//  17-01-2001 : JCV ; prise en compte de la fermeture (IsClosed)
//  14-01-2001 : JEL : Add 'int GetGorder(int iConnexion)' with iConnexion <=> vertex index
//                        'int GetCorder(int iConnexion)' with iConnexion <=> vertex index
//  11-01-2001 : MMO ; Add 'double GetGiThreshold()' i = 0,1,2
//  26-10-2000 : JFI ; Creation 
//======================================================================
#ifndef CATCurveGContinuity_H
#define CATCurveGContinuity_H
//----------------------------------------------------------------------
#include "CATCGMVirtual.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATListOfCATCurves.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "CATListOfCATCrvLimits.h"
#include "CATBoolean.h"
class CATSoftwareConfiguration;
class CATFrFCompositeCurve;
class CATMathPoint;
class CATMathVector;
class CATGeoFactory;
class CATCurveGContinuityCx2;


class ExportedByCATGMOperatorsInterfaces CATCurveGContinuity  : public CATCGMVirtual
{
public :
 
   // defini (set) si la liste de courbes est fermee
   virtual void IsClosed () = 0 ;
   //
   // En cas de vecteur nul, de division par zero on considere que 
   // l'ordre n'est pas respecte
   //
   // Seuil G0 (mm) -Distance entre deux courbes successives-
   virtual void SetThresholdG0 (double iG0) = 0 ;
   //
   // Seuil G1 (radians) - Angle entre 2 tangente successives rad-
   virtual void SetThresholdG1 (double iG1) = 0 ;
   //
   // Seuil G2 (valeur comprise entre ]0 et 1]) 
   // Valeur par defaut : 0.98 (pour 1e-3 dans la factory)
   //                                c' ^c''        c'
   // soit R le vecteur courbure R= --------  ^   ------
   //                               | C'|**3       |c'|
   //
   // c'est G2 ssi : |R1-R2|/|R2| < (1-seuilG2)/seuilG2 
   virtual void SetThresholdG2 (double iG2) = 0 ;
   //
   // Carré du Seuil de courbure nulle (mm-2) defaut = 1.e-12/(Scale*Scale);
   ////// Seuil de courbure nulle (mm-1) - Valeur de courbure en deca de laquelle une
   ////// courbure est consideree comme nulle -
   ////// Valeur par defaut : 8.e-9 = (8.*ResolutionC0)/((0.01*ModelSize)**2) qui correspond
   ////// a la courbure d'un cercle pour lequel une corde de 1m donne une fleche de 0.001mm
   // Remarque : c'est une valeur securitaire d'un point de vue numerique. Choisir une
   // valeur plus faible risque de provoquer de faux diagnostics a partir de courbes issues
   // de droites a l'origines a cause des pertes de precision numeriques.
   virtual void SetNullCurvatureThreshold(double iNullCurvature) = 0 ;
   //
   virtual double GetG0Threshold() = 0 ;
   virtual double GetG1Threshold() = 0 ;
   virtual double GetG2Threshold() = 0 ; 
   virtual double GetNullCurvatureThreshold() = 0 ;
   

   

   virtual int Run () = 0 ;
   //+JEL20010112 int GetContinuity(int)
   virtual int GetContinuity(int iConnexion) = 0 ; // iConnexion = index connexion curve/curve = [1..ncurve-1]
   // Lecture de la continuiute generale (-1, 0, 1, 2)
   virtual int GetGlobalContinuity () = 0 ;
   // Lecture de l'erreur Max G0, G1, G2 sour toute les courbes
   // Pour les endroits ou il n'y a pas de PB.
   virtual double GetGlobalG0Error () = 0 ;  // en mm
   virtual double GetGlobalG1Error () = 0 ;  // en radian
   virtual double GetGlobalG2Error () = 0 ;  // Valeur du seuil
   // Lecture des debuts des intervalles G0
   virtual void GetStartG0Interval (CATListOfInt & iInterval) = 0 ;
   // Lecture des debuts des intervalles G0 et G1
   virtual void GetStartG1Interval (CATListOfInt & iInterval) = 0 ;
   // Lecture des debuts des intervalles G0, G1 et G2
   virtual void GetStartG2Interval (CATListOfInt & iInterval) = 0 ;
   //
   // Lecture des erreurs maxi par intervalle G0
   virtual void GetMaxG0ErreurInterval ( CATListOfDouble & oGoError) = 0 ;
   // Lecture des erreurs maxi par intervalle G1
   virtual void GetMaxG1ErreurInterval ( CATListOfDouble & oG1Error) = 0 ;
   // Lecture des erreurs maxi par intervalle G2
   virtual void GetMaxG2ErreurInterval ( CATListOfDouble & oG2Error) = 0 ;
   //
   // Lecture des trous G0 G1, et G2 entre chaque transition 
   virtual void GetGorder ( CATListOfInt    & oGorder) = 0 ;
   virtual void GetG0Error( CATListOfDouble & oDeltaGoError) = 0 ;
   virtual void GetG1Error( CATListOfDouble & oDeltaG1Error) = 0 ;
   virtual void GetG2Error( CATListOfDouble & oG2Error) = 0 ;
   virtual void GetG2Delta( CATListOfDouble & oDeltaG2) = 0 ;
   
   // Return an estimation of the Minimal Normal deviation for the curves
   // in order to reach the absolute G0 Continuity...
   // also gives at each connexion the pseudo-normal G0 Gap...
   virtual double GetG0NormalDeviations(CATListOfDouble & oGoNormalDev) = 0 ;

   //===================================================
   //Number of connexion considering masked edges ...
   virtual int GetNbVisibleConnexion (int & oNbOfVisibleConnexion) = 0 ;
   // Length curve below which curve is considered as "small" curve.
   //  
   virtual int  SetLengthThreshold(double iSmallLength) = 0 ;//0 = 0 ;
   
   // Get Edges' positions considered as small
    virtual  int  GetSmallEdgesPositions(CATListOfInt    & oSmallPositions) = 0 ;//ok
   
   // Allow Add More Edges to Mask ie Edges that will be considered as a gap
   virtual int  SetEdgesToMask( CATListOfInt    & iEdgesToMaskPositions) = 0 ;//OK

   // Get Small and edges masked by SetEdgesToMask method
   virtual int  GetAllMaskedEdges(CATListOfInt    & iEdgesToMaskPositions) = 0 ;//OK

   // 
   virtual int  GetAllEdgesLength(CATListOfDouble & oLengths ) = 0 ;//ok

    
   virtual int GetContinuityWithMask(int iConnexion) = 0 ; // iConnexion = index connexion curve/curve = [1..ncurve-1]
   // Lecture de la continuiute generale (-1, 0, 1, 2)
   virtual int GetGlobalContinuityWithMask () = 0 ;
   // Lecture de l'erreur Max G0, G1, G2 sour toute les courbes
   // Pour les endroits ou il n'y a pas de PB.
   virtual double GetGlobalG0ErrorWithMask () = 0 ;  // en mm
   virtual double GetGlobalG1ErrorWithMask () = 0 ;  // en radian
   virtual double GetGlobalG2ErrorWithMask () = 0 ;  // Valeur du seuil
   
   //
   // Lecture des trous G0 G1, et G2 entre chaque transition visibles
   virtual void GetGorderWithMask ( CATListOfInt    & oGorder) = 0 ;
   virtual void GetG0ErrorWithMask( CATListOfDouble & oDeltaGoError) = 0 ;
   virtual void GetG1ErrorWithMask( CATListOfDouble & oDeltaG1Error) = 0 ;
   virtual void GetG2ErrorWithMask( CATListOfDouble & oG2Error) = 0 ;
   virtual void GetG2DeltaWithMask( CATListOfDouble & oDeltaG2) = 0 ;

};


//FOR CREATION
ExportedByCATGMOperatorsInterfaces
CATCurveGContinuity  * CATCreateCurveGContinuity(
      CATGeoFactory * iFactory,
      const CATLISTP(CATCurve) & iCurvesToImprove, 
      const CATListOfInt & iSens, 
      const CATLISTP(CATCrvLimits) &iLimits,
      CATSoftwareConfiguration * iSoftConfig);

ExportedByCATGMOperatorsInterfaces
   CATCurveGContinuity * CATCreateCurveGContinuity(CATGeoFactory * iFactory,CATFrFCompositeCurve * iCCV,
                    CATSoftwareConfiguration * iSoftConfig);
#endif
