//===================================================================
// COPYRIGHT Dassault Systemes 2017/01/13
//===================================================================

#ifndef CATPolyBodyFuzzyOffset_H
#define CATPolyBodyFuzzyOffset_H

#include "CATSysErrorDef.h"

class CATPolyBody;
class CATMathTransformation;

/**
*	Interface to by pass packaging problems over CATFuzzyOperators
*/
class CATPolyBodyFuzzyOffset
{
public:

    virtual ~CATPolyBodyFuzzyOffset() {}

    /**
     * @brief Initialize will parse each PolyBody and aggregate all the geometry into a PolyMesh to performs the fuzzy offset
     * Match CATPolyMeshOffset interfaces
     *
     * @param iPolyBodies             pointers over polybodies to process
     * @param iTransfos               pointers to possible positions (may be null)
     * @param iNPolyBodies            
     * @param iOffsetValue            offset value
     * @param iClientMaxDeviation     deviation to compute the offset
     * @param oDepth                  expected depth of the octree, high values could lead to serious computation overhead
     * @param iBothSide
     * @param iRoundedBorder
     * @param iTol
     *
     */
    virtual HRESULT Initialize( CATPolyBody** iPolyBodies, const CATMathTransformation ** iTransfos, unsigned iNPolyBodies, double iOffsetValue, double iClientMaxDeviation, int& oDepth, int iBothSide = 0, int iRoundedBorder = 0 ) = 0;

    /**
     * @brief Run
     *
     * @param oPolyBody
     *
     */
    virtual HRESULT Run( CATPolyBody*& oPolyBody ) = 0;

};

#endif
