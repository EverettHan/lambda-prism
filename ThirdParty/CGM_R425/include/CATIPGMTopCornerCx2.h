#ifndef CATIPGMTopCornerCx2_h_
#define CATIPGMTopCornerCx2_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopCorner.h"
#include "CATTopCornerType.h"

class CATBody;
class CATCGMJournalList;
class CATCell;
class CATCurve;
class CATFace;
class CATGeoFactory;
class CATMathDirection;
class CATPlane;
class CATShell;
class CATSurLimits;
class CATCrvParam;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopCornerCx2;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATIPGMTopCornerCx2: public CATIPGMTopCorner
{
public:
  /**
   * Constructor
   */
  CATIPGMTopCornerCx2();

  virtual void InitDataCornerCx2() = 0;

  //
  //  Basic methods
  //
  virtual int Run() = 0;

  virtual int RunCornerByType() = 0;

  virtual CATLONG32 GetNumberOfCorners() const = 0;

  virtual void BeginningCorner() = 0;

  virtual CATBoolean NextCorner() = 0;

  virtual CATBody *GetCorner(CATCGMJournalList *CurJourn = NULL) = 0;

  /**
  * Creates a corner choose with conditions.
  * @param iCrvOr
  * The array of three orientations of the parallel to the first, second and third wire.
  * Acceptables values: 0,-1,1. Use 0 if you don't want to use this condition.
  * @param iTngOr
  * The array of three tangency orientations between the corner and the first, second and third wire.
  * Acceptables values: 0,-1,1. Use 0 if you don't want to use this condition.
  * @param iNumBeginWire
  * The number of input wire where the corner begin.
  * iNumBeginWire = 0,1,2,3 : The input wire where the corner begin. 0 : don't use this condition.
  * @iIndex 
  * iIndex = -1,0,1,2,... : The index of the wanted solution, Use -1 if you don't want to use this condition.
  * @param oUseOrientationCondition
  * Return TRUE if the corner solution use the orientation condition.
  * @param oUseBeginWireCondition
  * Return TRUE if the corner solution use the orientation condition.
  * @param oUseIndexCondition
  * Return TRUE if the corner solution use the orientation condition.
  * @param CurJourn
  * The pointer to the journal corresponding to the creation of the current corner.
  * If <tt>NULL</tt>, the journal is not written.
  * @return
  * The pointer to the created body, or NULL if we cannot find it. If you do not want to keep it,
  * use the @CATICGMContainer#Remove method to remove it from the geometric factory, after the deletion
  * of <tt>this</tt> operator.
  * Put the iterator of the resulting corners on the solution.
  */
  virtual CATBody *GetResultWithConditions(
    CATOrientation *iCrvOr,
    CATOrientation *iTngOr,
    int iNumBeginWire,
    int iIndex,
    CATBoolean &oUseOrientationCondition,
    CATBoolean &oUseBeginWireCondition,
    CATBoolean &oUseIndexCondition,
    CATCGMJournalList *CurJourn = NULL) = 0;

  // Set the direction 
  // To be used only in case of 3D corner definition 
  // ( by default if this service is not called a direction will be automatically calculated )
  virtual void SetDirection(const CATMathDirection &iDirectionFor3DCorner) = 0;

  // Get the direction 
  // To be used only in case of 3D corner definition  
  // ( by default a direction will be automatically calculated )
  virtual void GetDirection(
    CATMathDirection &oDirectionFor3DCorner,
    CATBoolean &oAutomaticModeForDirection) = 0;

  // SetTension
  // To be used only in case of 3D corner definition
  // Define the tension value at each extremity ( 1 by default )
  virtual void SetTension(const double iTension[2]) = 0;

  // Retourne tous les resultats dans le meme body
  virtual CATBody *GetResult() = 0;

  virtual void GetCurOrients(
    CATOrientation &Or1,
    CATOrientation &Or2,
    CATOrientation &Or3) const = 0;

  //
  //  Setting the Support Trimming Mode 
  //  iMode = 0 : Off  
  //  iMode = 1 : On
  //  valeur 0 par defaut
  //  
  virtual CATLONG32 SetSupportTrimmingMode(const CATLONG32 iTrimmingMode) = 0;

  //
  //  Getting the Support Trimming Mode 
  //  iMode = 0 : Off  
  //  iMode = 1 : On
  //  valeur 0 par defaut
  //  
  virtual CATLONG32 GetSupportTrimmingMode(CATLONG32 &oTrimmingMode) = 0;

  //
  //  Setting the Support Trimming Side
  //  iTrimmingSide = 0 : Trim whith all input wires 
  //  iTrimmingSide = 1 : Trim whith first input wires 
  //  iTrimmingSide = 2 : Trim whith last input wires 
  //  valeur 0 par defaut
  //  And setting the Support Trimming Mode 
  //  iMode = 0 : Off  
  //  iMode = 1 : On
  //  valeur 0 par defaut
  //
  virtual CATLONG32 SetSupportTrimmingSideAndMode(
    const CATLONG32 iTrimmingSide,
    const CATLONG32 iTrimmingMode) = 0;

  //
  //  Getting the Support Trimming Side 
  //  oTrimmingSide = 0 : Trim whith all input wires 
  //  oTrimmingSide = 1 : Trim whith first input wires 
  //  oTrimmingSide = 2 : Trim whith last input wires 
  //  valeur 0 par defaut
  //  And getting the Support Trimming Mode 
  //  iMode = 0 : Off  
  //  iMode = 1 : On
  //  valeur 0 par defaut
  //  
  virtual CATLONG32 GetSupportTrimmingSideAndMode(
    CATLONG32 &oTrimmingSide,
    CATLONG32 &oTrimmingMode) = 0;

  //
  //  Setting the Support Trimming Side
  //  iTrimmingSide = 1 : Trim whith first input wires 
  //  iTrimmingSide = 2 : Trim whith last input wires 
  //  And setting the Support Trimming Mode 
  //  iMode = 0 : Off  
  //  iMode = 1 : Smooth Side
  //  iMode = -1 : Reverse smooth side
  //  valeur 0 par defaut
  //
  virtual CATLONG32 SetSupportTrim(
    const CATLONG32 iTrimmingSide,
    const CATLONG32 iTrimmingMode) = 0;

  //
  //  Getting the Support Trimming Side 
  //  oTrimmingSide = 1 : Trim whith first input wires 
  //  oTrimmingSide = 2 : Trim whith last input wires 
  //  And getting the Support Trimming Mode 
  //  iMode = 0 : Off  
  //  iMode = 1 : Smooth Side
  //  iMode = -1 : ReverseSmoothSide
  //  valeur 0 par defaut
  //  
  virtual CATLONG32 GetSupportTrim(
    CATLONG32 iTrimmingSide,
    CATLONG32 &oTrimmingMode) = 0;

  //
  // initialisation du mode corner :
  // corner complet, corner relimite ou corner complementaire
  // le corner par defaut est le corner complet. ce mode n'autorise pas le
  // le mode trim
  // le corner relimite est le plus petit corner joignant les points de contact
  // aux appuis
  // le corner complementaire est l'autre corner.
  // nous ne fournissons pas de mode angle pour les corners sur support
  // quelconque. Ce mode n'est valide que pour les supports plans monofaces
  //
  virtual CATLONG32 SetCircleMode(
    CATCircleMode iCircleMode,
    double iStart,
    double iEnd) = 0;

  virtual void GetCircleMode(
    CATCircleMode &iCircleMode,
    double &iStart,
    double &iEnd) = 0;

  virtual CATBoolean GetCircularData(
    CATMathPoint &oCenter,
    CATAngle &oRadius,
    CATMathDirection &oFirst,
    CATMathDirection &oSecond,
    CATAngle &oStartAngle,
    CATAngle &oEndAngle) const = 0;

  // methodes générales utilisé dans le create les constructeurs ou dans le Run global:
  virtual CATLONG32 CheckModeCompatibility(CATBoolean iWithError) = 0;

  virtual void SetCornerType(CATTopCornerType iCornerType) = 0;

  virtual CATTopCornerType GetCornerType() = 0;

  //
  // methodes permettant l'indexation des solutions: a appeler a la fin du Run()
  //
  virtual void SetNumberOfInputWires(int iNbInputWires) = 0;

  virtual void InitPt(
    int iNbCornerOpe,
    CATLONG32 *iNbSol,
    CATBody ***ioPtCenter,
    CATBody ***ioPtContact1,
    CATBody ***ioPtContact2,
    CATBody ***ioPtContact3 = NULL) = 0;

  virtual void InitArraysOfLocalisation(
    int iNbSol,
    int *iaIndCrv,
    CATCrvParam *iaCrvParam,
    CATOrientation *iaOri) = 0;

  virtual void ClearIndexData() = 0;

  virtual void InitIndexData() = 0;

  virtual void InitAllCornerDataWhithoutPtContact(
    CATLONG32 nbcorn = 0,
    CATLONG32 *IndiceDebut = NULL) = 0;

  virtual int ComputeTangencyOrientation(
    CATBody *iCorner,
    int iNumInWire,
    int iIndCorner,
    CATBody *PtContact = NULL,
    CATBoolean WithPtContact = FALSE) = 0;

  virtual int ComputeDataWireCornerWithPtContact(
    CATBody *iCurCorner,
    int iIndCorner,
    int iIndWire,
    int &oNumCrv,
    CATCrvParam &oCrvParam,
    CATOrientation &oCurveOnWireOri,
    CATBody *iPtContact = NULL) = 0;

  virtual int ComputeDataWireCornerWithIntersectionAndProjection(
    CATBody *iCurInputBody,
    int iIndInWire,
    int iIndCorner,
    CATBody *iCurCorner,
    CATOrientation iCurOrient,
    int &oInWireNumCrv,
    CATCrvParam &oInWireCrvP,
    CATOrientation &oCurveOnWireOri) = 0;

  virtual void RemovePtAndLocalisationsArrayWithBadTangency(
    int iNbCorner,
    CATBoolean *iaAcceptedBody) = 0;

  virtual void ComputeIndexOfCorner() = 0;

  virtual void DeletePt() = 0;

  //Si les CurCornerData sont nulle et qu'il y a des corners solution on prend les cornerData du iRattrapCorner comme
  //curCornerData(à lancer après le Run)
  virtual void UseRattrapCornerInfo(CATIPGMTopCornerCx2 *iRattrapCorner, int iNbCorner) = 0;

  //
  // Surcharge des methodes d'indexations de CATTopTangentCurveOperator:
  //
  virtual void GetOrientationOnWire(
    int &oTngtOrientation,
    int &oCrvtOrientation,
    int &oIdem,
    int iIndWire) = 0;

  virtual CATLONG32 GetIndCurCorner() = 0;

  virtual void GetDiscriminationIndex(int &oIndex) = 0;

  //
  // Surcharge des methodes d'indexations de CATTopCorner:
  //
  virtual void GetCurBeginOfCorner(int &oNumWire) = 0;

  virtual void SetBeginOfCorner(int iNumWire) = 0;

  virtual void GetBeginOfCorner(int &oNumWire) = 0;

  //
  // Gestion des confusions entre les wires inputs ou entre les parallels
  // A appeler après le Run().
  //
  //debug  int   GetNbConfusionsIni(); // Nombre de Cells en confusions pour les wires initiaux.
  //debug  int   GetConfusionsIniCells(ListPOfCATCell& oListOfCells); //listes de ces cells
  virtual int AddConfusionsIniCells(
    CATCell *iIniCell1,
    int NumCell1,
    CATCell *iIniCell2,
    int NumCell2) = 0;

  virtual void ClearConfusionIni() = 0;

  //
  // Gestion des warnings Issus du calcul des corners.(Inclu les confusions ente wires inputs)
  // A appeler après le Run().
  //
  //  int         GetNbWarning(); //Nombres de warnings.
  //  CATError *  GetWarning(int iNumWarning); //Warning numero iNumWarning(entre 1 et NbWarning)
  virtual void AddWarning(CATError *iNewWarning) = 0;

  virtual void DeleteWarning() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopCornerCx2(); // -> delete can't be called
};

#endif /* CATIPGMTopCornerCx2_h_ */
