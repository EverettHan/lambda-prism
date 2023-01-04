#ifndef CATDynMassProperties1DOnEdge_H
#define CATDynMassProperties1DOnEdge_H
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 1997
//
// DESCRIPTION : CATDynMassProperties1DOnEdge  class declaration
//
//=============================================================================
#include "CATGMOperatorsInterfaces.h"

#include "CATEdge.h"
#include "CATCrvParam.h"
#include "CATMath3x3Matrix.h"
#include "CATMathAxis.h"
class CATTopData;

class ExportedByCATGMOperatorsInterfaces CATDynMassProperties1DOnEdge
{
    public :
    
     CATDynMassProperties1DOnEdge();
     virtual ~CATDynMassProperties1DOnEdge() ;

     virtual CATLength GetLengthFromParams(const CATCrvParam &iParam1,
					   const CATCrvParam &iParam2) const  = 0;
     
     virtual CATPositiveLength GetLength() const = 0; 

     /**
      * iParam       : reference parameter for iLength evaluation
      * iLength      : curvilinear distance between iParam and result parameter
      * oParam       : result parameter on edge
      * 
      * Return value : E_FAIL  if error or CATIA mode (Not yet implemented)
      *                S_FALSE if oParam has been defined outside of the CATEdge limits, it is relocated to the closest CATVertex.
      *                S_OK    if oParam has been successfully evaluated on edge
      */
     virtual HRESULT GetParamFromLength(const CATCrvParam &iParam, const CATLength & iLength, CATCrvParam & oParam) const;
};

ExportedByCATGMOperatorsInterfaces CATDynMassProperties1DOnEdge *CATDynCreateMassProperties1DOnEdge (const CATEdge*);  

ExportedByCATGMOperatorsInterfaces CATDynMassProperties1DOnEdge *CATDynCreateMassProperties1DOnEdge (CATTopData * iTopData, const CATEdge*);  

#endif
