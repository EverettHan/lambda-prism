#ifndef CATCGMStreamIncrementalOpen_H
#define CATCGMStreamIncrementalOpen_H
// COPYRIGHT DASSAULT SYSTEMES 2001
//=====================================================================================
//
// Incremental Open dedicated to light Design Mode
// Auteurs: TCX   
// Date: 1 st April 2002 (don't know if it will work)
//
//=====================================================================================
#include "CATGeometricObjects.h"
#include "CATCGMListOfCATULONGPTR.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATStreamArea;

class ExportedByCATGeometricObjects CATCGMStreamIncrementalOpen
{
public:
  //=================================================================
  // Find if it is available (NCGM / CATPart Unit Tests)
  //=================================================================
  static CATCGMStreamIncrementalOpen * Create(const char iFilename[]);

  //=================================================================
  // Find if For second Time or many times After
  //=================================================================
  static CATCGMStreamIncrementalOpen * Create(CATGeoFactory *iReadFactory);

  //=================================================================
  // If available, do not forget to free temporary allocation
  //=================================================================
  virtual ~CATCGMStreamIncrementalOpen();

  //=================================================================
  // The Functionality (First Time, creation of the CATGeoFactory)
  //=================================================================
  virtual void Open( CATGeoFactory* &ioFactory, CATCGMListOfCATULONGPTR &ioObjects )  = 0;

  //=================================================================
  // The Functionality (Other Times, completion of the CATGeoFactory)
  //=================================================================
  virtual void Append( CATGeoFactory* iFactory, CATCGMListOfCATULONGPTR &ioObjects )  = 0;

  //=================================================================
  // Analysis
  //=================================================================
  INLINE const char        *IsFilename()   const;
  INLINE CATStreamArea     *IsStreamArea() const;
  INLINE CATGeoFactory     *IsReadFactory() const;

protected :

  //=================================================================
  // Constructeurs
  //=================================================================
  CATCGMStreamIncrementalOpen(CATStreamArea *iStreamArea, const char iFilename[], CATGeoFactory *iReadFactory);

  void SetFactory(CATGeoFactory *iReadFactory);


private :
  char            *_Filename;
  CATStreamArea   *_StreamArea;
  CATGeoFactory   *_ReadFactory;
};

//=================================================================
// IsFilename 
//=================================================================
INLINE const char  *CATCGMStreamIncrementalOpen::IsFilename() const
{
  return _Filename;
}

//=================================================================
// IsReadFactory 
//=================================================================
INLINE CATGeoFactory     *CATCGMStreamIncrementalOpen::IsReadFactory() const
{
  return _ReadFactory;
}

//=================================================================
// IsStreamArea 
//=================================================================
INLINE CATStreamArea  *CATCGMStreamIncrementalOpen::IsStreamArea() const
{
  return _StreamArea;
}

//=================================================================
// Internal Use 
//=================================================================
extern "C" { typedef CATCGMStreamIncrementalOpen * CATCGMLOADStreamIncrementalOpenFilename(const char iFilename[]); }  


#endif

