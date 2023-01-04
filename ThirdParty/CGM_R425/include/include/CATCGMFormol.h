/* -*-c++-*- */
#ifndef CATCGMFormol_h_
#define CATCGMFormol_h_
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 1998
//-----------------------------------------------------------------------------
// class CATCGMFormol : Temporary lock of geometric objects 
//     to avoid deletion of implicit objects
//-----------------------------------------------------------------------------
// Usage Notes: Geometric and Topological Operators 
//    during
//-----------------------------------------------------------------------------
// Creation 23/11/98                                                  tcx
//-----------------------------------------------------------------------------
#include "YP00IMPL.h"
#include "CATCGMVirtual.h"

// new method based on CATSysSimpleHashTable
class CATSysSimpleHashTable;
class CATGeometry;


class ExportedByYP00IMPL CATCGMFormol : public CATCGMVirtual
{
public:
  CATCGMFormol();
  CATCGMFormol(int itype);
  virtual ~CATCGMFormol();


  /** 
   * To avoid premature deletion of Objects 
   */
  void lock(CATGeometry *geometry);
  
  
  /**
    * If You do not want to wait the death of CATCGMFormol object
	*   to release all objects locked
	*/
  void unlockAll();

private:
  CATSysSimpleHashTable * _locked;
  int _withLock;
};


#endif
