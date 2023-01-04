/* -*-c++-*- */
#ifndef CATcgmdev_H_
#define CATcgmdev_H_
// COPYRIGHT DASSAULT SYSTEMES  2001
//============================================================================
//  Dynamic invokation of REGKillerTopologicalModel.tst framework
//============================================================================
#include "ExportedByGeometricObjects.h" 
#include "CATBaseUnknown.h" 
#include "CATBoolean.h"
#include "CATGemDumpLimits.h"
#include "CATListOfCATICGMObjects.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class istream;
#endif
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATGeoFactory;
class CATCGMQueryManager;
class CATDocument;


class ExportedByGeometricObjects CATcgmdev
{
public:

  inline static short IsAvailable();

  static  inline int cgmdev(istream &inputText, ostream &outputText, ostream &errorText);
  static  inline int limits(CATGeoFactory *Factory, ostream &outputText);
  
  // Dump a CATCGMQueryManager
  static inline void DumpQueryManager(CATGemDumpLimits     iShow,
                                      CATCGMQueryManager & iQuery,
                                      ostream            & outputText);

protected :

  CATcgmdev();
  virtual ~CATcgmdev();

  //---------------------------------------------------------------------------------
  // Pour implementation 
  //---------------------------------------------------------------------------------
  virtual int _cgmdev(istream &inputText, ostream &outputText, ostream &errorText) = 0;
  virtual int _limits(CATGeoFactory *Factory, ostream &outputText) = 0;
  virtual void _DumpQueryManager(CATGemDumpLimits iShow, CATCGMQueryManager & iQuery, ostream & outputText) = 0;

  //---------------------------------------------------------------------------
  // Acces a l'init
  //---------------------------------------------------------------------------
  static CATcgmdev *GetDebugOnly();
  static CATcgmdev *_Debug;
  static short      _Once;

  friend class CATCGMFactoryTransaction;
};

//-----------------------------------------------------------
// IsAvailable
//-----------------------------------------------------------
inline short CATcgmdev::IsAvailable()
{
  return ( (_Once || GetDebugOnly()) && _Debug ) ? 1 : 0;
}

//---------------------------------------------------------------------------
// cgmdev
//---------------------------------------------------------------------------
inline int  CATcgmdev::cgmdev(istream &inputText, ostream &outputText, ostream &errorText)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_cgmdev(inputText,outputText,errorText);
  return 0;
}

//---------------------------------------------------------------------------
// limits
//---------------------------------------------------------------------------
inline int  CATcgmdev::limits(CATGeoFactory *Factory, ostream &outputText)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) return _Debug->_limits(Factory,outputText);
  return 0;
}


//---------------------------------------------------------------------------
// DumpQueryManager
//---------------------------------------------------------------------------
inline void CATcgmdev::DumpQueryManager(CATGemDumpLimits iShow, CATCGMQueryManager & iQuery, ostream & outputText)
{
  if ( (_Once || GetDebugOnly()) && _Debug ) _Debug->_DumpQueryManager(iShow,iQuery,outputText);
}




#endif
