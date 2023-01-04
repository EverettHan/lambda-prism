/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

/* -*-C++-*-*/

#ifndef CATCGMDbgPoseSur_H
#define CATCGMDbgPoseSur_H

//=============================================================================
// Nov. 03 _pPrivateData, GetPrivateData()                                HCN
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMNewArray.h"
#include "CATHashTabCATCGMDbgPoseSur.h"
#include "CATBoolean.h"
#include "CATMathInline.h"

class CATCell;
class CATTopology;
class CATGeometry;
class CATCGMOutput;

//---------------------------------------------------
// Pour Validation stabilite des liens poses Sur
//---------------------------------------------------
class  ExportedByCATTopologicalObjects CATCGMDbgPoseSur
{
public:
  CATCGMDbgPoseSur(CATCell *iFrom, CATCell *iTo, CATTopology *iContext, CATGeometry *iWith, void* ipPrivateData = NULL);
  virtual ~CATCGMDbgPoseSur();
  CATCGMDbgPoseSur(const CATCGMDbgPoseSur &iCopie);
  CATCGMDbgPoseSur& operator= (const CATCGMDbgPoseSur &iCopie);

  CATCGMNewClassArrayDeclare;  
  
  INLINE CATCell      *From() const ;
  INLINE CATCell      *To()   const ;
  INLINE CATGeometry  *With() const ;
  INLINE CATTopology  *Context() const ;

  INLINE short      NumberOfDuplicate() const ;
  INLINE CATBoolean WasNoMoreModifiable() const ;

  INLINE void  IncDuplicate();

  void       Dump( CATCGMOutput& os );
  CATBoolean IsExpectedAlive() const ;


private :
  void Set(CATCell *iFrom, CATCell *iTo, CATTopology *iContext, CATGeometry *iWith, void* ipPrivateData);
  INLINE void* GetPrivateData() const; 

  CATCell     *_From;
  CATCell     *_To;
  CATTopology *_Context;
  CATGeometry *_With;
  void        *_pPrivateData;

  short        _NumberOfDuplicate;
  CATBoolean   _NoMoreModifiable;

  friend ExportedByCATTopologicalObjects unsigned int HashKeyCATCGMDbgPoseSur(CATCGMDbgPoseSur* inew);
  friend ExportedByCATTopologicalObjects int CompareCATCGMDbgPoseSur(CATCGMDbgPoseSur* i1, CATCGMDbgPoseSur *i2);

  friend class CATCGMTopoCXMODEL;

};


INLINE CATCell      *CATCGMDbgPoseSur::From()           const { return _From;    }
INLINE CATCell      *CATCGMDbgPoseSur::To()             const { return _To;      }
INLINE CATGeometry  *CATCGMDbgPoseSur::With()           const { return _With;    }
INLINE CATTopology  *CATCGMDbgPoseSur::Context()        const { return _Context; }
INLINE void         *CATCGMDbgPoseSur::GetPrivateData() const { return _pPrivateData; }        

INLINE short       CATCGMDbgPoseSur::NumberOfDuplicate() const   { return _NumberOfDuplicate; }
INLINE CATBoolean  CATCGMDbgPoseSur::WasNoMoreModifiable() const { return _NoMoreModifiable; }

INLINE void        CATCGMDbgPoseSur::IncDuplicate() { _NumberOfDuplicate++; }

#endif
