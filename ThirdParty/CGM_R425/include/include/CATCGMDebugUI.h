/* -*-c++-*- */
#ifndef CATCGMDebugUI_H_
#define CATCGMDebugUI_H_
// COPYRIGHT DASSAULT SYSTEMES  2000
//============================================================================
//  Dedicated to NCGM Interactive debug, FOR INTERNAL CGM USE
//  **  BE CAREFUL, YOU MUST CHECK AVAILABITY OF INTERACTIVE DEBUG
//   with help of   CATCGMDebug.h 
//============================================================================
#include "ExportedByGeometricObjects.h"
#include <stddef.h>

#include "CATMathPointf.h"
#include "CATMathDirectionf.h"

class CATICGMObject;
class CATCGMAnnotation;
class CATCGMVisualObject;
class CATGeoFactory;

class ExportedByGeometricObjects CATCGMDebugUI
{
public:
  
  //---------------------------------------------------------------------------------
  // Association d'un Texte a un objet geometrique
  //  participant effectivement au graphisme, comme les  Vertex,Edge ou Face d'un Body
  //       CATCGMDebugUI::AddAnnotation("CHK",Edge,"Bad");
  //---------------------------------------------------------------------------------
  static inline CATCGMAnnotation *AddText(
    const char             iOperateur[4]       ,
    const CATICGMObject  * iObject             ,
    const char           * iTextToDisplay      ,
    const float         (* iCoord)[3]    = NULL ,
    const int           (* iColorRGB)[3] = NULL ,
    const int              iMustCommit  = 1,
    const int              ifNullCoordWhatAboutBoundingBox = 111);
  
  //---------------------------------------------------------------------------------
  // Association d'un Texte a un objet geometrique
  //  participant effectivement au graphisme, comme les  Vertex,Edge ou Face d'un Body
  //       CATCGMDebugUI::AddSymbol("CHK",Vertex,CATCGMDebugUI::CONCENTRIC);
  //---------------------------------------------------------------------------------
  enum SymbolType 
  { 
    NOTUSED,            
      CROSS,             
      PLUS,           
      CONCENTRIC,         
      COINCIDENT,        
      FULLCIRCLE,         
      FULLSQUARE,         
      STAR,
      DOT,
      SMALLDOT,
      MISC1,
      MISC2,
      FULLCIRCLE2,         
      FULLSQUARE2,         
      OPEN_ARROW,
      UNFILLED_ARROW,
      BLANKED_ARROW,
      FILLED_ARROW,
      UNFILLED_CIRCLE,
      BLANKED_CIRCLE,
      FILLED_CIRCLE,
      CROSSED_CIRCLE,
      BLANKED_SQUARE,
      FILLED_SQUARE,
      BLANKED_TRIANGLE,
      FILLED_TRIANGLE,
      MANIPULATOR_SQUARE,
      MANIPULATOR_DIAMOND,
      MANIPULATOR_CIRCLE,
      MANIPULATOR_TRIANGLE
  };
  
  static inline CATCGMAnnotation *AddSymbol(
    const char                         iOperateur[4]       ,
    const CATICGMObject             *  iObject             ,
    const CATCGMDebugUI::SymbolType    iSymbol             ,
    const float                     (* iCoord)[3]    = NULL ,
    const int                       (* iColorRGB)[3] = NULL ,
    const int                          iMustCommit  = 1,
    const int                          ifNullCoordWhatAboutBoundingBox = 111);

  
  //---------------------------------------------------------------------------------
  // Association d'une representation d'une Edge bords de Face
  //   iRGBA       :  (iRed << 24) | (iGreen << 16) | (iBlue << 8) | iAlpha  
  //   iLinetype   :  1=Solid, 2=Dotted, 3=Dashed, 4=Dot-dashed, 5=Phantom, 6=Small-dotted, 7=JIS Axis.
  //   iThickness  :  de 1 a 16.
  //---------------------------------------------------------------------------------
  static inline CATCGMVisualObject *AddFixedEdgeOnFace(
    const char               iOperateur[4]          ,
    const CATICGMObject     *iObject                ,
    const CATMathPointf     &iOriginOnEdge         ,
    const CATMathDirectionf &iTangentEdge          , 
    const CATMathDirectionf &iNormalFace           , 
    const int                iIsLeft               ,
    const int                iTangentPlaneLengthIn_mm  =  10,
    const int                iNormalLengthIn_mm        =  15,
    const int                iNormalHeadHeight         =   5,
    const int                iNormalBaseLength         =   0,
    const int                iRed                      =   0,
    const int                iGreen                    =   0,
    const int                iBlue                     =   0,
    const int                iAlpha                    = 255,
    const unsigned int       iLinetype                 =   1,
    const unsigned int       iThickness                =   1);

  //---------------------------------------------------------------------------------
  // Nettoyage des annotations
  //---------------------------------------------------------------------------------
  static inline void Remove(CATCGMAnnotation *iAnnotation);
  static inline void RemoveAll(CATGeoFactory *iFactory);

  //---------------------------------------------------------------------------------
  // Diverses magouilles pour l'implementation interne
  //---------------------------------------------------------------------------------  
protected :
  
  CATCGMDebugUI();
  virtual ~CATCGMDebugUI();  
  
  virtual CATCGMAnnotation *_AddText(
    const char            operateur[4]       ,
    const CATICGMObject * Object             ,
    const char          * TextToDisplay      ,
    const float         (* Coord)[3]           ,
    const int           (* ColorRGB)[3]        ,
    const int             MustCommit ,
    const int             ifNullCoordWhatAboutBoundingBox ) = 0;
  
  virtual CATCGMAnnotation *_AddSymbol(
    const char                        operateur[4]       ,
    const CATICGMObject             * Object             ,
    const CATCGMDebugUI::SymbolType   symbol             ,
    const float                     (* Coord)[3]           ,
    const int                       (* ColorRGB)[3]        ,
    const int                         MustCommit,
    const int                         ifNullCoordWhatAboutBoundingBox ) = 0;

  virtual CATCGMVisualObject *_AddFixedEdgeOnFace(
    const char               operateur[4]          ,
    const CATICGMObject     *Object                ,
    const CATMathPointf     &iOriginOnEdge         ,
    const CATMathDirectionf &iTangentEdge          , 
    const CATMathDirectionf &iNormalFace           , 
    const int                iIsLeft               ,
    const int                iTangentPlaneLengthIn_mm,
    const int                iNormalLengthIn_mm,
    const int                iNormalHeadHeight,
    const int                iNormalBaseLength,
    const int                iRed,
    const int                iGreen,
    const int                iBlue,
    const int                iAlpha,
    const unsigned int       iLinetype,
    const unsigned int       iThickness) = 0;


  virtual void _Remove(CATCGMAnnotation *iAnnotation) = 0;
  virtual void _RemoveAll(CATGeoFactory *iFactory) = 0;

private :
  
  static CATCGMDebugUI *GetCGMImplement();
  
  static CATCGMDebugUI *_FirstInstance;
  static int            _IsInitialised;
};

//---------------------------------------------------------------------------------
// Rajout de Texte
//---------------------------------------------------------------------------------
inline CATCGMAnnotation *CATCGMDebugUI::AddText(
    const char            operateur[4]       ,
    const CATICGMObject * Object             ,
    const char          * TextToDisplay      ,
    const float         (* Coord)[3]           ,
    const int           (* ColorRGB)[3]        ,
    const int             MustCommit,
    const int            ifNullCoordWhatAboutBoundingBox )
{
  CATCGMDebugUI *debug = GetCGMImplement();
  if ( debug )
    return debug->_AddText(operateur,Object,TextToDisplay,Coord,ColorRGB,MustCommit,ifNullCoordWhatAboutBoundingBox);
  return NULL;
}

//---------------------------------------------------------------------------------
// Rajout de Symbole
//---------------------------------------------------------------------------------
inline CATCGMAnnotation *CATCGMDebugUI::AddSymbol(
    const char            operateur[4]       ,
    const CATICGMObject * Object             ,
    const CATCGMDebugUI::SymbolType   symbol ,
    const float         (* Coord)[3]           ,
    const int           (* ColorRGB)[3]        ,
    const int             MustCommit,
    const int             ifNullCoordWhatAboutBoundingBox )
{
  CATCGMDebugUI *debug = GetCGMImplement();
  if ( debug )
    return debug->_AddSymbol(operateur,Object,symbol,Coord,ColorRGB,MustCommit,ifNullCoordWhatAboutBoundingBox);
  return NULL;
}


//---------------------------------------------------------------------------------
// Rajout de FixedEdgeOnFace
//---------------------------------------------------------------------------------
inline CATCGMVisualObject *CATCGMDebugUI::AddFixedEdgeOnFace(
    const char               operateur[4]          ,
    const CATICGMObject     *Object                ,
    const CATMathPointf     &iOriginOnEdge         ,
    const CATMathDirectionf &iTangentEdge          , 
    const CATMathDirectionf &iNormalFace           , 
    const int                iIsLeft               ,
    const int                iTangentPlaneLengthIn_mm,
    const int                iNormalLengthIn_mm,
    const int                iNormalHeadHeight,
    const int                iNormalBaseLength,
    const int                iRed,
    const int                iGreen,
    const int                iBlue,
    const int                iAlpha,
    const unsigned int       iLinetype,
    const unsigned int       iThickness)
{
  CATCGMDebugUI *debug = GetCGMImplement();
  if ( debug )
    return debug->_AddFixedEdgeOnFace(operateur,Object,iOriginOnEdge,iTangentEdge,iNormalFace,iIsLeft,
                                      iTangentPlaneLengthIn_mm,iNormalLengthIn_mm,iNormalHeadHeight,iNormalBaseLength,
                                      iRed,iGreen,iBlue,iAlpha,iLinetype,iThickness);
  return NULL;
}

//---------------------------------------------------------------------------------
// Nettoyage des annotations et symboles
//---------------------------------------------------------------------------------
inline void CATCGMDebugUI::Remove(CATCGMAnnotation *annotation)
{
  CATCGMDebugUI *debug = GetCGMImplement();
  if ( debug )
    debug->_Remove(annotation);
}

inline void CATCGMDebugUI::RemoveAll(CATGeoFactory *factory)
{
  CATCGMDebugUI *debug = GetCGMImplement();
  if ( debug )
    debug->_RemoveAll(factory);
}
  
//---------------------------------------------------------------
// Pour Gestion interne
//---------------------------------------------------------------
extern "C" 
{
  typedef void INIT_CATCGMDebugUI(); 
}  


#endif
