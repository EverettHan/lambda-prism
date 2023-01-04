/* -*-c++-*- */
#ifndef CATTopCutting_h
#define CATTopCutting_h
// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//
// CATTopCutting :
// 
/**
 *  Management of Cutting Objects For Boolean Operations.
 */
//=============================================================================
// Usage Notes:
//
//=============================================================================
// Fev. 99 Delivery                                  lly, rad
// Aout 99 Ajout de iExclusive                       lly
//=============================================================================

#include "BOOPER.h"
#include "CATBoolean.h"
#include "ListPOfCATCell.h"
#include "CATTopDef.h"

class CATCell;
class CATDomain;
class CATBody;
class CATGeometry;

class ExportedByBOOPER CATTopCutting
{
public:
  /**
   *  Conversions From LyingOn to Cutting
   * 
   *  Si iBodyToCut est value et iExclusive vaut 1, 
   *  les coupantes modifiables sur les autres Bodies sont detruites.
   *  A revisiter avec rad.
   */
  static void ActivateCutting(CATCell*   iLyingCell,   CATBody* iBodyToCut, int iExclusive = 0);
  static void ActivateCutting(CATDomain* iLyingDomain, CATBody* iBodyToCut, int iExclusive = 0);
  static void ActivateCutting(CATBody*   iLyingBody,   CATBody* iBodyToCut, int iExclusive = 0);

  /**
   *  Conversions From Cutting to LyingOn
   */
  static void DesactivateCutting(CATCell*   iCuttingCell);
  static void DesactivateCutting(CATDomain* iCuttingDomain);
  static void DesactivateCutting(CATBody*   iCuttingBody);

  /**
   *  Destruction Of Cutting 
   *
   *  Seules les coupantes sur le Body specifie sont detruites.
   */
  static void DestroyCutting(CATCell*   iCuttingCell,   CATBody* iCutBody);
  static void DestroyCutting(CATDomain* iCuttingDomain, CATBody* iCutBody);
  static void DestroyCutting(CATBody*   iCuttingBody,   CATBody* iCutBody);

  /**
   *  Old management (LyionOn and Cutting)
   *
   * ...
   */
   static void         GetCuttingOrLyingOn         (CATCell * iCell, CATLISTP(CATCell)& ioSupports,CATBody* iInBody=NULL);
   static CATGeometry* GetCuttingOrLyingGeometryOn (CATCell * iCell, CATCell* iSupportingCell);
   static CATBoolean   IsCuttingOrLyingOn          (CATCell * iCell, CATCell* iSupportingCell);

   static CATTopLyingOnDiagnostic IsCuttingOrLyingOn(CATBody* iBody, CATBody* iSuppport);
   static CATTopLyingOnDiagnostic IsCuttingOrLyingOn(CATDomain* iBody, CATDomain* iSuppport);

};

#endif
