//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//==============================================================================================================
// CATPolyDumpable : CGR import - Utility class for debug
//==============================================================================================================
// Creation : CHU , 10 / 06 / 2003
//==============================================================================================================

#ifndef CATPolyDumpable_H
#define CATPolyDumpable_H

#include "PolyhedralUtilities.h"     // ExportedBy definition
#include "CATErrorDef.h"   // HRESULT definition

class CATCGMOutput;

class ExportedByPolyhedralUtilities CATPolyDumpable
{

public :

  // static name
  static char _DefaultName[2];

  // Tag management
  inline void SetTag(const int iTag);
  inline int GetTag() const;

  // Get class short-name
  virtual char * GetShortName() const;

  // Dump
  virtual HRESULT Dump( CATCGMOutput & s) const;
  friend ExportedByPolyhedralUtilities CATCGMOutput & operator << ( CATCGMOutput& s, const CATPolyDumpable & iObj);

protected:

  // Life cycle
  CATPolyDumpable();
  virtual ~CATPolyDumpable();

private:

  // -----------------------------------------------------------
  // Data

  int _Tag;
};

inline void CATPolyDumpable::SetTag(const int iTag) {
  _Tag = iTag; }

inline int CATPolyDumpable::GetTag() const {
  return _Tag; }

// Class dedicated to iostream (dump float or double value on imposed length)
#define POLYDNAME(lon,val) CATPolyDumpableName( lon , val )

class CATPolyDumpableName
{
public:

  inline CATPolyDumpableName(int iLength, const CATPolyDumpable * iObj);
  inline CATPolyDumpableName(int iLength, const void * iForeignObj, int (*iDump)(CATCGMOutput&,const void*,int));
  friend ExportedByPolyhedralUtilities CATCGMOutput& operator<< (CATCGMOutput& s, const CATPolyDumpableName & iObjNam);
  
private:

  const CATPolyDumpable * _Obj;
  const void *            _ForeignObj;
  int                   (*_ForeignDump)(CATCGMOutput & s, const void * iObj, int iDumpLength); // returns remaining length to fill with blanks
  int                     _Length;

};

inline CATPolyDumpableName::CATPolyDumpableName(int iLength, const CATPolyDumpable * iObj) :
_Obj(iObj), _Length(iLength), _ForeignObj(0), _ForeignDump(0) {
}

inline CATPolyDumpableName::CATPolyDumpableName(int iLength, const void * iForeignObj, int (*iDump)(CATCGMOutput&,const void*,int)) :
_Obj(0), _Length(iLength), _ForeignObj(iForeignObj), _ForeignDump(iDump) {
}

#endif
