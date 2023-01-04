/* -*-c++-*- */
#ifndef CATCGMBreakPoint_H_
#define CATCGMBreakPoint_H_
// COPYRIGHT DASSAULT SYSTEMES  2001
//============================================================================
//  INTERNAL USE ONLY 
//============================================================================
#include "ExportedByCATMathStream.h"
#include "catcxbreakpoints.h" 
#include "CATBaseUnknown.h" 

class CATActivateDebug;
class CATCommand;
class CATCGMObject;
class CATICGMObject;
class CATTime;

class CATDlgMultiList;
class CATDlgEditor;
class CATUnicodeString;


//----------------------------------------------------------
// Les BreakPoints interactifs de CGM
//----------------------------------------------------------

class ExportedByCATMathStream CATCGMBreakPoint
{
public:
  // Positionnement CheckPoint
  static inline CATActivateDebug* InitBreakPoints(char* iCGPGroupName);
  static inline void DeleteBreakPoints(CATActivateDebug*& ioDbg);

  // Positionnement CheckPoint
  static inline int BreakPoint(CATActivateDebug* iDebug, char* iCPName, CATCommand* iCommand);
  
  // utilitaire de mise en Show/NoShow
  static inline int CGMSwapVisibleMode(CATActivateDebug* iDebug, void* obj, int  mod);
  
  static inline int CGMColorVisibleMode(CATActivateDebug* iDebug,void* obj, int  r, int g , int b);
  
  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  virtual ~CATCGMBreakPoint();
  
  


  //-------------------------------------------------------------------------------------
  //  Pour Gestion CGMDebugLife : INTERNAL USE Only
  //-------------------------------------------------------------------------------------
  static int GetDebugLifeStatus(); // permets de savoir si le debug est actif

  static void  AddReference( CATCGMObject *pointed, CATICGMObject *pointedItf, 
                             CATCGMObject *pointing, CATICGMObject *pointingItf);
  
  static void  ReleaseReference( CATCGMObject *pointed, CATICGMObject *pointedItf, 
                                 CATCGMObject *pointing, CATICGMObject *pointingItf);

  static short StillReferenced(CATICGMObject *itf);
  
  //-------------------------------------------------------------------------------------
  //  Pour Gestion CGMBuildVersion : INTERNAL USE Only
  //-------------------------------------------------------------------------------------
  static const CATULONG32   CurrentBuild;

  static inline void ConvertToTime(const CATULONG32  version, CATTime &from, CATTime &before);

  //---------------------------------------------------------------------------------
  // Pour gestion interne Fw CATGem
  //---------------------------------------------------------------------------------
  static inline void DefineColumns( CATDlgMultiList *iPanel, int iArraySize , CATUnicodeString *iTitleArray );
  static inline int  AddColumnItem( CATDlgMultiList *iPanel, int iColumnIndex, const CATUnicodeString& iString, int iRowIndex );
  static inline int  SetColumnPixelWidth( CATDlgMultiList *iPanel, int iColumnIndex,  int iPixelWidth );
  static inline int  SetColumnEditable( CATDlgMultiList *iPanel, int iColumnIndex,  int iEditable );
  static inline void SetText( CATDlgEditor  *iEditor, const CATUnicodeString& iString );


protected :
  // Positionnement CheckPoint
  virtual CATActivateDebug* _InitBreakPoints(char* iCGPGroupName) = 0;
  // delete
  virtual void _DeleteBreakPoints(CATActivateDebug*& ioDbg) = 0;

  // Positionnement CheckPoint
  virtual int _BreakPoint(CATActivateDebug* iDebug, char* iCPName, CATCommand* iCommand) = 0;
  
  // utilitaire de mise en Show/NoShow
  virtual int _CGMSwapVisibleMode(CATActivateDebug* iDebug, void* obj, int  mod) = 0;
  
  virtual int _CGMColorVisibleMode(CATActivateDebug* iDebug, void* obj, int  r, int g , int b) = 0;

  
  //-------------------------------------------------------------------------------------
  //  Pour Gestion CGMDebugLife : INTERNAL USE Only
  //-------------------------------------------------------------------------------------
  virtual void  _AddReference( CATCGMObject *pointed, CATICGMObject *pointedItf, 
                             CATCGMObject *pointing, CATICGMObject *pointingItf)= 0;
  
  virtual void  _ReleaseReference( CATCGMObject *pointed, CATICGMObject *pointedItf, 
                                 CATCGMObject *pointing, CATICGMObject *pointingItf)= 0;

  virtual short _StillReferenced(CATICGMObject *itf)= 0;

  //-------------------------------------------------------------------------------------
  //  Pour Gestion CGMBuildVersion : INTERNAL USE Only
  //-------------------------------------------------------------------------------------

  virtual void _ConvertToTime(const CATULONG32  version, CATTime &from, CATTime &before) = 0;


  virtual void _DefineColumns( CATDlgMultiList *iPanel, int iArraySize , CATUnicodeString *iTitleArray ) = 0;
  virtual int  _AddColumnItem( CATDlgMultiList *iPanel, int iColumnIndex, const CATUnicodeString& iString, int iRowIndex ) = 0;
  virtual int  _SetColumnPixelWidth( CATDlgMultiList *iPanel, int iColumnIndex,  int iPixelWidth ) = 0;
  virtual int  _SetColumnEditable(   CATDlgMultiList *iPanel, int iColumnIndex,  int iEditable ) = 0;
  virtual void _SetText( CATDlgEditor  *iEditor, const CATUnicodeString& iString ) = 0;

  //---------------------------------------------------------------------------------
  // Pour gestion interne 
  //---------------------------------------------------------------------------------
  CATCGMBreakPoint();
  static inline CATCGMBreakPoint *GetCGMImplement();
  static CATCGMBreakPoint *       FindCGMImplement();

  static int _DebugLifeStatus;

private :
  static CATCGMBreakPoint *_Gateway;
  static int               _alreadyInitialised;
};


//=================================================================
//  L'utilisation des fonctionnalites de BreakPoint
//=================================================================
inline CATCGMBreakPoint * CATCGMBreakPoint::GetCGMImplement()   
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway )
     return CATCGMBreakPoint::_Gateway;
  return NULL;
}

//=================================================================
//  L'utilisation des fonctionnalites de BreakPoint
//=================================================================
inline CATActivateDebug* CATCGMBreakPoint::InitBreakPoints(char* iCGPGroupName)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway )
    return _Gateway->_InitBreakPoints(iCGPGroupName);
  return NULL;
}

inline void CATCGMBreakPoint::DeleteBreakPoints(CATActivateDebug*& ioDbg)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway )
    _Gateway->_DeleteBreakPoints(ioDbg);
}

inline int CATCGMBreakPoint::BreakPoint(CATActivateDebug* iDebug, char* iCPName, CATCommand* iCommand)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway )
    return _Gateway->_BreakPoint(iDebug,iCPName,iCommand);
  return 1;
}

//=================================================================
//  L'utilisation des fonctionnalites de Show/NoShow
//=================================================================
inline int CATCGMBreakPoint::CGMSwapVisibleMode(CATActivateDebug* iDebug,void* obj, int  mod)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway )
    return _Gateway->_CGMSwapVisibleMode(iDebug,obj,mod);
  return 1;
}

inline int CATCGMBreakPoint::CGMColorVisibleMode(CATActivateDebug* iDebug,void* obj, int  r, int g , int b)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway )
    return _Gateway->_CGMColorVisibleMode(iDebug,obj,r,g,b);
  return 1;
}


//=================================================================
//  Decryptage interne de la Version de Build du Modeleur
//=================================================================
inline void CATCGMBreakPoint::ConvertToTime(const CATULONG32  version, CATTime &from, CATTime &before)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway )
     _Gateway->_ConvertToTime(version,from,before);
}



//=================================================================
// Usage interne CATGem
//=================================================================
inline void CATCGMBreakPoint::DefineColumns( CATDlgMultiList  *iPanel, int iArraySize , CATUnicodeString *iTitleArray  )
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway && iPanel )
    _Gateway->_DefineColumns(iPanel,iArraySize,iTitleArray);
}


inline int CATCGMBreakPoint::AddColumnItem( CATDlgMultiList *iPanel, int iColumnIndex, const CATUnicodeString& iString, int iRowIndex )
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway && iPanel )
    return _Gateway->_AddColumnItem(iPanel,iColumnIndex,iString,iRowIndex);
  return iColumnIndex;
}

inline int CATCGMBreakPoint::SetColumnPixelWidth( CATDlgMultiList *iPanel, int iColumnIndex, int iPixelWidth)
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway && iPanel )
    return _Gateway->_SetColumnPixelWidth(iPanel,iColumnIndex,iPixelWidth);
  return -1;
}

inline int CATCGMBreakPoint::SetColumnEditable( CATDlgMultiList *iPanel, int iColumnIndex, int iEditable )
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway && iPanel )
    return _Gateway->_SetColumnEditable(iPanel,iColumnIndex,iEditable);
  return  -1;
}

inline void CATCGMBreakPoint::SetText( CATDlgEditor  *iEditor, const CATUnicodeString& iString )
{
  if ( (_alreadyInitialised || FindCGMImplement()) && _Gateway && iEditor )
    _Gateway->_SetText(iEditor,iString);
}

#endif
