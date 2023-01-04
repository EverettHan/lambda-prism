#ifndef CATSkinOperatorExt_h
#define CATSkinOperatorExt_h

// COPYRIGHT DASSAULT SYSTEMES  1999

// 24/09/19 NLD Mise au propre
//              - detabulation
//              - reindentation
//              Ajout Init0()
//              Numérotation stable des constructeurs dans l'ordre du fichier header

#include "CATGeoToTopOperatorExt.h"
#include "CATMathDef.h"
#include "CATSurLimits.h"

class CATGeoFactory;
class CATBody;
class CATDomain;
class CATShell;
class CATLoop;
class CATFace;
class CATEdge;
class CATVertex;
class CATSurface;
class CATSimCurve;
class CATMacroPoint;
class CATPlane;
class CATPCurve;
class CATCrvParam;
class CATCrvLimits;
class CATMathLine;
class CATMathBox;
class CATCGMJournalList;
class CATListPtrCATPCurve;
class CATListPtrCATCrvLimits;
class CATListValShort;

class ExportedByCATTopologicalObjects CATSkinOperatorExt :public CATGeoToTopOperatorExt
{
public:

   /** @nodoc @nocgmitf */
   CATCGMNewClassArrayDeclare;

   //                                                                    N.B numerotation des constructeurs dans l'ordre initial du fichier header
   //                                                                        à ne JAMAIS changer, reportée de manière homogène dans le source
   //                                                                        NLD240919
   //                                                                    CATSkinOperatorExt_Constructor1
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      CATSurface         * iSurface        ,
                      CATBody            * iTargetBody     = NULL,
                      CATBodyFreezeMode    iBodyfreezemode = CATBodyFreezeOn,
                      CATCGMJournalList  * report          = NULL);

   //                                                                    CATSkinOperatorExt_Constructor2
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      CATTopData         * iTopData        ,
                      CATSurface         * iSurface        );

   //                                                                    CATSkinOperatorExt_Constructor3
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      int                  iNbPcurves      ,
                      CATPCurve         ** iPcurves        ,
                      CATCrvLimits       * iLimits         ,
                      short              * iOrientations   ,
                      CATBody            * iTargetBody     = NULL,
                      CATBodyFreezeMode    iBodyfreezemode = CATBodyFreezeOn,
                      CATCGMJournalList  * iReport         = NULL);

   //                                                                    CATSkinOperatorExt_Constructor4
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      CATTopData         * iTopData        ,
                      int                  iNbPcurves      ,
                      CATPCurve         ** iPcurves        ,
                      CATCrvLimits       * iLimits         ,
                      short              * iOrientations   );

   //                                                                    CATSkinOperatorExt_Constructor5
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      CATPlane           * plane           ,
                      CATMathBox         & iBox            ,
                      CATBody            * iTargetBody     = NULL,
                      CATBodyFreezeMode    iBodyfreezemode = CATBodyFreezeOn,
                      CATCGMJournalList  * iReport         = NULL);

   //                                                                    CATSkinOperatorExt_Constructor6
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      CATTopData         * iTopData        ,
                      CATPlane           * plane           ,
                      CATMathBox         & iBox            );

   //                                                                    CATSkinOperatorExt_Constructor7
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      int                  iNbPcurves      ,
                      CATPCurve         ** pcurves         ,
                      CATCrvLimits       * limits          ,
                      CATBody            * targetBody      = NULL,
                      CATBodyFreezeMode    iBodyfreezemode = CATBodyFreezeOn,
                      CATCGMJournalList  * report          = NULL);

   //                                                                    CATSkinOperatorExt_Constructor8
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      CATTopData         * iTopData        ,
                      int                  iNbPcurves      ,
                      CATPCurve         ** pcurves         ,
                      CATCrvLimits       * limits          );

   //                                                                    CATSkinOperatorExt_Constructor9
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      int                  iNbPcurves      ,
                      CATPCurve         ** pcurves         ,
                      CATBody            * targetBody      = NULL,
                      CATBodyFreezeMode    iBodyfreezemode = CATBodyFreezeOn,
                      CATCGMJournalList  * report          = NULL);

   //                                                                    CATSkinOperatorExt_Constructor10
   /** @nodoc @nocgmitf */
   CATSkinOperatorExt(CATGeoFactory      * iFactory        ,
                      int                  iNbPcurves      ,
                      CATPCurve         ** pcurves         ,
                      short              * orientations    ,
                      CATBody            * targetBody      = NULL,
                      CATBodyFreezeMode    iBodyfreezemode = CATBodyFreezeOn,
                      CATCGMJournalList  * report          = NULL);

   /** @nodoc @nocgmitf */
   ~CATSkinOperatorExt();

   /** @nodoc @nocgmitf */
   void  SetInternalLoop(int iNbPcurves, CATPCurve **iPcurves,
                         CATCrvLimits *iLimits, short *iOrientations);

   /** @nodoc @nocgmitf */
   void  AddInternalLoop(int iNbPcurves, CATPCurve **iPcurves,
                         CATCrvLimits *iLimits, short *iOrientations);

   /** @nodoc @nocgmitf */
   void  AddInternalLoop(int iNbPcurves, CATPCurve **pcurves);

   /** @nodoc @nocgmitf */
   void  AddInternalLoop(int iNbPcurves, CATPCurve **iPcurves,
                         CATCrvLimits *iLimits);

   /* @nodoc @nocgmitf */
   int   RunOperator();

   /** @nodoc @nocgmitf */
   void  ForceSkinClosureInU(); 

   /** @nodoc @nocgmitf */
   void  ForceSkinClosureInV(); 

   /** @nodoc @nocgmitf */
   CATShell* GetShell() const;

   /** @nodoc @nocgmitf */
   void GetLimits(CATSurLimits & iSurLim);

   /** @nodoc @nocgmitf */
   void SetLimits(const CATSurLimits & ioSurLim);

   /** @nodoc @nocgmitf */
   void GetCheck(int & oChecking);

   /** @nodoc @nocgmitf */
   void SetCheck(int iChecking);

   /** @nodoc @nocgmitf */
   void GetUseLims(int & oChecking);

   /** @nodoc @nocgmitf */
   void SetUseLims(int iChecking);

   /** @nodoc @nocgmitf */
   void SetResultInTargetBody(CATBody * iTB);

   /** @nodoc @nocgmitf */
   static void CreateArraysForSkinOperator(
                                           CATListPtrCATPCurve    & iPCurves,
                                           CATListPtrCATCrvLimits & iCrvLimits,
                                           CATListValShort        & iOriPCurvesVsLoop,
                                           int                    & oNbPCurves,
                                           CATPCurve            **& oPCurves,
                                           CATCrvLimits          *& oCrvLimits,
                                           short                 *& oOrientations);

   /** @nodoc @nocgmitf */
   static void DeleteArraysForSkinOperator(
                                           CATPCurve   **& oPCurves,
                                           CATCrvLimits *& oCrvLimits,
                                           short        *& oOrientations);

private:

   void  GetSurfaceClosureInUV     ( CATSurLimits & iMaxSurLimits, CATBoolean &oClosedInU, CATBoolean &oClosedInV);
   int   GetSurfaceBoundaries      ( CATSurface* Surface, CATPCurve**& pcurves);
   void  GetCurvesOrientation      ( int nbpcurves, CATPCurve **pcurves,
                                     CATCrvLimits *iLimits, short *& oOrientations);
   void  Init0                     ( CATGeoFactory* iFactory);
   void  Init                      ( CATSurface*);
   void  MakeSingleFace            ();
   void  MakeMultiFaces            ();
   void  CreateNewEdgeAtFaceBorder ( CATFace * iFace , 
                                     CATMacroPoint * iMP1 , CATMacroPoint * iMP2 ,
                                     CATVertex * iVertex1 , CATVertex * iVertex2,
                                     CATPCurve * iPLine1 , CATPCurve * iPLine2,
                                     CATEdge  *& oNewEdge , CATSimCurve *& oNewSimCurve );
   void  VerifyLoopOrientation      ( CATLoop  * iLoop );
   void  AddInternalLoopMultiFaces  ( int nbpcurves, CATPCurve **pcurves,
                                      CATCrvLimits *iLimits);
   void  FillLoop                   ( CATLoop*, int, CATPCurve**, CATCrvLimits*);
   void  FillClosedLoop             ( CATLoop*, CATPCurve*, CATCrvLimits*);
   void  InvertInnerLoops           ();

   void BuildInternalLoops          ();
   void DraftDeletion               ();

   void MergeVertices               ( CATVertex * iVertex1 , CATVertex * iVertex2 );

   void CreateCleaner               ();

   //***************************************************************************************
   // CGMReplay
   //***************************************************************************************

public:

   /* @nodoc @nocgmitf */
   void SetConstructorType(short iConstructorType) {_ConstructorType = iConstructorType;}

   /* @nodoc @nocgmitf */
   short GetConstructorType() {return _ConstructorType;}

   void  RDOIAOO(CATTopOperator & iOperator);

protected:


   // Methods for CGMReplay recording.  We need to use the Ext naming because we've used that in CATGeoToTopOperatorExt.
   // If more of these methods are implemented, they should also use the new naming convention.
   void               WriteInputExt(CATCGMStream &ioStream);

   short           _ConstructorType;

private:
   CATLoop      *  _externalloop;
   CATFace      *  _face;
   CATSurLimits    _surflim;
   CATSurface   *  _surface;
   CATPCurve   **  _pcurves;
   CATCrvLimits *  _limits;
   short        *  _orientations;
   int             _nbpcurves;
   int             _makefacedone;
   int             _surfisclosedU;
   int             _surfisclosedV;
   int             _forceskinclosureU;
   int             _forceskinclosureV;
   int             _infiniteface;
   int             _outer_loop_given;
   int             _good_constructor; 
   int             _check_discontinuity;
   int             _UseLims;
   int             _PCurvesInput;
   int             _surfaceExplicit;
   int             _DraftToResultAuthorised;
   CATBoolean      _MustCreatePCurvesFromSurfaceAndLimits;

   //***************************************************************************************
   // New InternalLoops management
   //***************************************************************************************

   int              _nbinternloops;
   int           *  _nbcurvesinloop;
   CATPCurve   ***  _interncurves;
   CATCrvLimits **  _interncrvlim;
   short        **  _internorient;
};
#endif
