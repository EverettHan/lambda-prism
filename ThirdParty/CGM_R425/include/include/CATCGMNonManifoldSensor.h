/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//-----------------------------------------------------------------------------
// Usage : detect and decorate non manifold  topology (pre-analyse)
//=============================================================================
#ifndef CATCGMNonManifoldSensor_H
#define CATCGMNonManifoldSensor_H
#include "CATCGMStreamAttribute.h"                                 
#include "CATDataType.h"
#include "CATTopOperator.h"
#include "CATBody.h"
#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATCell.h"
#include "CATListOfCATICGMObjects.h"
#include "CATListOfInt.h"
#include "CATechSet.h"

#include "CATListOfCATCGMArrayOfOrientedObjects.h"
#include "CATCGMArrayOfOrientedObjects.h"
#include "CATechAttribute.h"


class ExportedByCATTopologicalObjects CATCGMNonManifoldSensor : public CATCGMStreamAttribute
{
public :
  // Definition of the attribute (constructor, destructor, stream etc...)
  CATCGMNonManifoldSensor();
  CATCGMNonManifoldSensor(CATechSet  * iNumberOfBounded);
  ~CATCGMNonManifoldSensor();

  CATCGMNewClassArrayDeclare;

  CATCGMDeclareAttribute (CATCGMNonManifoldSensor,CATCGMStreamAttribute);

  static CATCGMNonManifoldSensor * ComputeNonManifold( CATBody  *iBodyToAnalyse  );

  virtual void Stream   (CATCGMStream&) const;
  virtual void UnStream (CATCGMStream&);
  virtual int  IsPersistent();


  void GetBoundedSignature( CATLONG32 oBounded[3] );


  /** @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput & os ); // For Debug Purpose

    /** @nodoc @nocgmitf   internal DATA */
  CATBoolean                 _Frozen;
  CATLONG32                  _SensorVersion;
  CATechSet               *  _NonManifoldSet;

  /** @nodoc @nocgmitf */
  static CATechAttribute *  Cell_BuildAttribute(CATBody    * iBodyInterface,  CATICGMObject             * iMyInterface,    const CATLISTP(CATCGMArrayOfOrientedObjects) & iPaths );
  static void               GetNonTrivialCells( CATechSet  * iNonManifoldSet, CATLISTP(CATICGMObject)   & oNonManifoldCells );

    /** @nodoc  CheckBRepServices  */
  CATLONG64 CheckBRepServices();



  /** @nodoc @nocgmitf */
  static const CATechMeta     &  NonManifold_Holder(); 
  static const CATechMeta     &  NonManifold_Path(); 
  static const CATechMeta     &  NonManifold_Body(); 
 

private :
  CATCGMNonManifoldSensor(const CATCGMNonManifoldSensor&);
  CATCGMNonManifoldSensor& operator = (const CATCGMNonManifoldSensor&);

};



#endif
