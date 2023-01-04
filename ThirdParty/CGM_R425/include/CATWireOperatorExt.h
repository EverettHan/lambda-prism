#ifndef CATWireOperatorExt_h
#define CATWireOperatorExt_h

#include "CATGeoToTopOperatorExt.h"
#include "CATTopDef.h"

class CATEdge;
class CATVertex;
class CATCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATGeoFactory;
class CATBody;
class CATCGMJournalList;
class CATWire;
class CATMacroPoint;
class CATPointOnEdgeCurve;
class CATCrvLimits;

class ExportedByCATTopologicalObjects CATWireOperatorExt :public CATGeoToTopOperatorExt
{
public:

  /**	@nodoc @nocgmitf */
  CATCGMNewClassArrayDeclare;

	/**	@nodoc @nocgmitf */
	CATWireOperatorExt(CATGeoFactory      *iFactory,
		int                 iNbCurves,
		CATCurve          **iCurves,
		CATCrvLimits       *iLimits,
		short              *iOrientations,
		CATBody            *iTargetBody=NULL,
		CATBodyFreezeMode   iBodyfreezemode=CATBodyFreezeOn,
		CATCGMJournalList  *iReport=NULL);

  /**	@nodoc @nocgmitf */
	CATWireOperatorExt(CATGeoFactory      *iFactory,
		CATTopData * iData,
		int                 iNbCurves,
		CATCurve          **iCurves,
		CATCrvLimits       *iLimits,
		short              *iOrientations);
	
	/**	@nodoc @nocgmitf */
	CATWireOperatorExt(CATGeoFactory      *iFactory,
		CATCurve           *iCurve,
		const CATCrvLimits &iLimits,
		short               iOrientation,
		CATBody            *iTargetBody=NULL,
		CATBodyFreezeMode   iBodyfreezemode=CATBodyFreezeOn,
		CATCGMJournalList  *report=NULL);
	
	/**	@nodoc @nocgmitf */
  CATWireOperatorExt(CATGeoFactory*    factory,
		int               inbcurves,
		CATCurve**        icurves,
		CATBody*          iTargetBody=NULL,
		CATBodyFreezeMode bodyfreezemode=CATBodyFreezeOn,
		CATCGMJournalList *report=NULL);
		
  /**	@nodoc @nocgmitf */
  CATWireOperatorExt(CATGeoFactory*    factory,
		CATCurve*         icurve,
		CATBody*          iTargetBody=NULL,
		CATBodyFreezeMode bodyfreezemode=CATBodyFreezeOn,
		CATCGMJournalList *report=NULL);
		
  /**	@nodoc @nocgmitf */
  CATWireOperatorExt(CATGeoFactory*    iFactory,
		int               inbcurves,
		CATCurve**        icurves,
		short*            iorientations,
		CATBody*          iTargetBody=NULL,
		CATBodyFreezeMode bodyfreezemode=CATBodyFreezeOn,
		CATCGMJournalList *report=NULL);
	
	
	/**	@nodoc @nocgmitf */
  CATWireOperatorExt(CATGeoFactory*    factory,
		CATBody*          iBody,
		CATVertex*        iEndVertex,
		CATCurve*         iExtrapolationCurve,
		CATBodyFreezeMode iBodyfreezemode=CATBodyFreezeOn,
		CATCGMJournalList *report=NULL);

  /**	@nodoc @nocgmitf */
  CATWireOperatorExt(CATGeoFactory*    factory,
    CATTopData *      iData,
		CATBody*          iBody,
		CATVertex*        iEndVertex,
		CATCurve*         iExtrapolationCurve);
	
	/**	@nodoc @nocgmitf */
  CATWireOperatorExt(CATGeoFactory*    factory,
		CATBody*          iBody,
		CATCurve*         iExtrapolationCurve,
		CATOrientation    iOriNewEdgeVsWire,
		CATBodyFreezeMode iBodyfreezemode=CATBodyFreezeOn,
		CATCGMJournalList *iReport=NULL);
	
  /**	@nodoc @nocgmitf */
	~CATWireOperatorExt();

  /* @nodoc @nocgmitf */
  int RunOperator();
	
	/**	@nodoc @nocgmitf */
	void ForceWireClosure();

   /**	@nodoc @nocgmitf */
	void MakeWireInfinite();
	
	/**	@nodoc @nocgmitf */
	CATWire* GetWire() const;
	
  /**	@nodoc @nocgmitf */
  virtual void SetResultInTargetBody(CATBody * iTB);

  /**	@nodoc @nocgmitf */
  virtual void GetSemiClosureParam(CATCrvParam & Param);

  /**	@nodoc @nocgmitf */
  virtual void SetSemiClosureParam(const CATCrvParam &Param);

  /**	@nodoc @nocgmitf */
  void StoneAgeCode(CATBody * iBody);

  //***************************************************************************************
  // CGMReplay
  //***************************************************************************************

  /**	@nodoc @nocgmitf */
  void RDOIAOO(CATTopOperator & iOperator);

protected:
  // Methods for CGMReplay recording.  We need to use the Ext naming because we've used that in CATGeoToTopOperatorExt.
  // If more of these methods are implemented, they should also use the new naming convention.
  virtual void WriteInputExt(CATCGMStream &ioStream);
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutputExt(CATCGMOutput & os);
  virtual void DumpExt(CATCGMOutput & os);

private:

  /**	@nodoc @nocgmitf */
	void Init();
	
  /**	@nodoc @nocgmitf */
	void MakeWire();

  /**	@nodoc @nocgmitf */
	void MakeWireClosure();

  /**	@nodoc @nocgmitf */
	void CreateNewEdge(CATCurve     *iNewCurve,
		CATCrvLimits *iLimits,
		short        *iOrientations,
    int indexcurve=0);

  /**	@nodoc @nocgmitf */
	void CreateEdgeOnSingleCurve(CATCurve     *iNewCurve,
		CATCrvLimits *iLimits,
		short        *iOrientation);

  /**	@nodoc @nocgmitf */
	void CreateEdgeOnCurves(int            iNbCurves,
		CATCurve     **iCurves,
		CATCrvLimits  *iLimits,
		short         *iOrientaions);

  /**	@nodoc @nocgmitf */
	CATLONG32 GetCurveClosure(CATCurve *iCurve, const CATCrvLimits & CurLims);

  /**	@nodoc @nocgmitf */
	int  GetCurvesOrientation(int            iNbCurves,
		CATCurve     **iCurves,
		CATCrvLimits  *iLimits,
		short         *&oOrientations);

  /**	@nodoc @nocgmitf */
  CATLONG32 GetWireClosure(CATCurve * iCurve1,const CATCrvLimits & CurLim1,
                      CATCurve * iCurve2,const CATCrvLimits & CurLim2);
     
  /**	@nodoc @nocgmitf */
  void CreateCleaner();
	
	CATEdge             *  _edge;
	CATVertex           *  _vertexs;
	CATMacroPoint       *  _mps;
	CATPointOnEdgeCurve *  _poecs; 
	CATVertex           *  _vertexe;
	CATMacroPoint       *  _mpe;
	CATPointOnEdgeCurve *  _poece; 
	CATCurve            ** _curves;
	int                    _nbcurves;
	CATCrvLimits        *  _limits;
	short               *  _orientations;
  CATCrvParam         *  _SemiClosureParam;
	int                    _makewiredone;
	int                    _curveisclosed;
	int                    _forcewireclosure;
   int                    _makewireinfinite;

//	int                    _reportOnWireExtremities;
	int                    _infiniteline;
  int                    _IsALine;
  int                    _wireisclosed;
};
#endif
