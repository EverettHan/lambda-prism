/* -*-c++-*- */
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004
//-----------------------------------------------------------------------------
// Usage :Simulate rough overweigth disk size for PCS criteria
// November 2009 : TCX
//=============================================================================
#ifndef CATCGMRecycleRate_H
#define CATCGMRecycleRate_H
#include "CATCGMStreamAttribute.h"                                 
#include "CATDataType.h"
#include "CATTopOperator.h"
#include "CATBody.h"
#include "ExportedByCATTopologicalObjects.h"


class ExportedByCATTopologicalObjects CATCGMRecycleRate : public CATCGMStreamAttribute
{
public :
  // Definition of the attribute (constructor, destructor, stream etc...)
  CATCGMRecycleRate();
  ~CATCGMRecycleRate();

  CATCGMNewClassArrayDeclare;

  CATCGMDeclareAttribute (CATCGMRecycleRate,CATCGMStreamAttribute);


   static void ComputeRecycleRate( CATCGMOperator * iOperator , CATLISTP(CATBody) & iListOfInputBodies, CATBody *pResultBody );

   static CATBoolean ValidateRecyclingRateIndicator( CATCGMOperator * iOperator ,  CATBody  *iBodyComputed,  CATBody  *iBodyExpected, CATCGMOutput& os );   


  virtual void Stream   (CATCGMStream&) const;
  virtual void UnStream (CATCGMStream&);
 
private :
  CATCGMRecycleRate(const CATCGMRecycleRate&);
  CATCGMRecycleRate& operator = (const CATCGMRecycleRate&);
 
};

#endif
