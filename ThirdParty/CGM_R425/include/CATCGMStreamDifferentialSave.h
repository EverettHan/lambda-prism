#ifndef CATCGMStreamDifferentialSave_H
#define CATCGMStreamDifferentialSave_H
// COPYRIGHT DASSAULT SYSTEMES 2001
//=====================================================================================
//
// Differential Save dedicated to Roll (automatic Save)
// Auteurs: TCX   
// Date: 1 st April 2002 (don't know if it will work)
//
//=====================================================================================
#include "CATGeometricObjects.h"
#include "CATMathInline.h"

class CATGeoFactory;
class CATStreamArea;

class ExportedByCATGeometricObjects CATCGMStreamDifferentialSave
{
public:
  //=================================================================
  // Find if it is available (CATPart integration)
  //=================================================================
  static CATCGMStreamDifferentialSave * Create(CATGeoFactory* iFactory, CATStreamArea *iStreamArea);

  //=================================================================
  // Find if it is available (NCGM Unit Tests)
  //=================================================================
  static CATCGMStreamDifferentialSave * Create(CATGeoFactory* iFactory, const char iFilename[]);

  //=================================================================
  // If available, do not forget to  
  //=================================================================
  virtual ~CATCGMStreamDifferentialSave();

  //=================================================================
  // The Functionality
  //=================================================================
  virtual void Save() = 0;

  //=================================================================
  // Analysis
  //=================================================================
  INLINE CATGeoFactory     *Factory()    const;
  INLINE const char        *IsFilename() const;
  INLINE CATStreamArea     *IsStreamArea() const;

protected :

  //=================================================================
  // Constructeurs
  //=================================================================
  CATCGMStreamDifferentialSave(CATGeoFactory* iFactory, CATStreamArea *iStreamArea, const char iFilename[]);

private :

  CATGeoFactory   *_Factory;
  char            *_Filename;
  CATStreamArea   *_StreamArea;

};


//=================================================================
// Factory 
//=================================================================
INLINE CATGeoFactory  *CATCGMStreamDifferentialSave::Factory() const
{
  return _Factory;
}

//=================================================================
// IsFilename 
//=================================================================
INLINE const char  *CATCGMStreamDifferentialSave::IsFilename() const
{
  return _Filename;
}

//=================================================================
// IsStreamArea 
//=================================================================
INLINE CATStreamArea  *CATCGMStreamDifferentialSave::IsStreamArea() const
{
  return _StreamArea;
}

//=================================================================
// Internal Use 
//=================================================================
extern "C" { typedef CATCGMStreamDifferentialSave * CATCGMLOADStreamDifferentialSaveFilename(CATGeoFactory* iFactory, const char iFilename[]); }  

#endif

