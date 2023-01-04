//================================================
// COPYRIGHT Dassault Systemes 2012/07/09
//===================================================================
// Header definition of class CATOptTools
//===================================================================
//
// Usage notes:
//
//===================================================================
//   22/03/17 KJD Creation 
//===================================================================

#ifndef CATOptTools_H
#define CATOptTools_H

#include "YN000OPT.h"
#include "CATDataType.h"
#include "CATMathDef.h"
#include "CATOptTypes.h"
#include "CATString.h"
#include "CATLib.h"

class CATMathOptimizer;
class CATMathInterval;
class CATMathOptFunction;
class CATCGMOutput;
class CATSoftwareConfiguration;
class CATTolerance;
class CATOptAlgo_Penalty;
class CATOptAlgo_Unconstrained;

class ExportedByYN000OPT  CATOptTools
{

public:
    CATOptTools(CATSoftwareConfiguration     * iConfig, const CATTolerance  & iTolObject);
    ~CATOptTools();


    static CATString  GetMethodName (CATOptMethodId );
    static CATString  GetShortMethodName (CATOptMethodId );
    static CATOptParamLabel   GetParamLabel (CATString iName);    
    static CATOptDescription  GetDescription(CATOptMethodId  iName);
    static CATOptMethodId     GetMethodFromDescription(CATOptDescription iDescription);


    /**
    * GRAPHIC DEBUG 
    */
    //*Dump the 1D function whose unknown is the iVarIdx-th one of the CATMathOption and which is equal to the CATMathOptFunction at iX
    void Dump(CATCGMOutput & os, CATMathOptFunction * ipF, const CATMathOption & iOptionEval, const CATLONG32 & iVarIdx,
              const CATOptReal * iX, const CATMathInterval & iD, int iSampling);

    void Dump(CATCGMOutput & os, CATMathOptimizer * ipOptimizer,  CATOptExprType S, CATULONG32 iIdxFunction,
              const CATMathOption & iOptionEval, const CATLONG32 & iVarIdx,
              const CATOptReal * iX, const CATMathInterval & iD, int iSampling);

    void DumpObjective(CATCGMOutput & os, CATMathOptimizer * ipOptimizer,
                      const CATMathOption & iOptionEval, const CATLONG32 & iVarIdx,
                      const CATOptReal * iX, const CATMathInterval & iD, int iSampling);


    /**
    * STAT
    */
    FILE * OpenStatFile(int iNbRun,  CATOptMethodId iMethodId, CATBoolean iUnconstr, CATULONG32 ConstrNb[4]);
    //record of the final result of Penalty Methods 
    void RecordStatData(CATULONG32 FuncNb[5], CATListOfInt & StatIntData, CATLISTV_CATOptReal & StatRealData, const CATULONG32 &IterNb, FILE *fp);
    //record of the result for every iteration  of LM algo
    void RecordStatData(const CATOptReal & iLambda,  const CATOptReal & ivalue, int iEqNb, const CATOptReal * iVa, FILE *fp);

private :
    CATOptTools(const CATOptTools &);
    void operator = (const CATOptTools &);

private:
  CATSoftwareConfiguration              *  _Config;
  const CATTolerance                    &  _TolObject;

};

#endif
