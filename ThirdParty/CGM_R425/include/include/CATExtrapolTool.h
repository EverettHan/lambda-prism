#ifndef CATExtrapolTool_H
#define CATExtrapolTool_H

// COPYRIGHT DASSAULT SYSTEMES 2000

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATTopOperator.h"
#include "CATTopData.h"
#include "CATDataType.h"
#include "ExportedByCATTopologicalObjects.h"

class CATBody;
class CATDistanceTool;
class CATGeoFactory;
class CATLaw;
class CATCGMJournalList;
class CATListPtrCATVertex;

//
//--------------------------------------------------------------------------
//
/**
 * Class defining the extrapol computation.
 */
class ExportedByCATTopologicalObjects CATExtrapolTool : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATExtrapolTool);
 public:
/**
 * @nodoc
 */
  CATExtrapolTool(	CATGeoFactory * iGeoFactory, 
							CATTopData * iData);

  virtual ~CATExtrapolTool();

/** @nodoc */
  virtual CATBody * ComputeExtrapolation( CATBody * Wire,CATCGMJournalList * JournalOfReturn, CATLONG32 iForceCode = 0)=0;
    /**
     * Retrieves the skin body on which the extrapolation is computed.
     * @param oSupport
     * The pointer to the skin body. 
     */
	virtual void GetSupport(CATBody *& oSupport) = 0;
	
	virtual CATExtrapolTool * Duplicate() = 0;
	
	virtual void SetSupport(CATBody * oSupport) = 0;
  /* inactive implementation */
  int Run ();

  CATBody * GetResult();

  /** @nodoc @nocgmitf */
  virtual void SetVerticesToExtrapolate(CATListPtrCATVertex & iVertexList) = 0;
  
  // On arrete l'extrapolation au bord de la Face
  // possible (1 pour oui, 0 pour non).
  virtual void SetPartialExtrapol(short iOnOff) = 0;

};

#endif
