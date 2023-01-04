#ifndef CATEdgeOperatorExt_h
#define CATEdgeOperatorExt_h

#include "CATGeoToTopOperatorExt.h"
#include "CATCrvLimits.h"

class CATDomain;
class CATEdge;
class CATLoop;
class CATVertex;
class CATCurve;
class CATSurface;
class CATGeoFactory;
class CATBody;
class CATCGMJournalList;

//-------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATEdgeOperatorExt :public CATGeoToTopOperatorExt
{
public:

  CATCGMNewClassArrayDeclare;

  // Creates a face bounded by pcurves
  CATEdgeOperatorExt(CATGeoFactory*    factory,
                  CATCurve*	    curve,
                  CATBody*          bodyforcellcreation=NULL,
                  CATBodyFreezeMode bodyfreezemode=CATBodyFreezeOn,
                  CATCGMJournalList *report=NULL);
  CATEdgeOperatorExt(CATGeoFactory*    factory,
    CATTopData * iData,
                  CATCurve*	    curve,
                  CATBody*          bodyforcellcreation=NULL);

  CATEdgeOperatorExt(CATGeoFactory*    iFactory,
									CATTopData *  iData,
                  CATCurve*	    iCurve, const CATCrvLimits & iLims);
  
  ~CATEdgeOperatorExt();

  // return the edge matching the last added curve
  CATEdge*	GetEdge()   const;

		//KY1 : 10-12-2010

	//KY1 : 10-12-2010
	/**	@nodoc @nocgmitf */
	int RunOperator();

	/**  @nodoc @nocgmitf */
	void   RDOIAOO(CATTopOperator & iOperator);

protected:
  // Methods for CGMReplay recording.  We need to use the Ext naming because we've used that in CATGeoToTopOperatorExt.
  // If more of these methods are implemented, they should also use the new naming convention.
  virtual void WriteInputExt(CATCGMStream  & ioStream);
  virtual void WriteOutputExt(CATCGMStream &ioStream);

  virtual CATCGMOperator::CATCheckDiagnostic CheckOutputExt(CATCGMOutput & os);
  virtual CATBoolean                         ValidateOutputExt(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);

  virtual void DumpExt(CATCGMOutput& os);
  virtual void DumpOutputExt(CATCGMOutput& os);

private:

  void		MakeEdge();

  CATEdge        *  _edge;
  CATCurve       *  _curve;
  int               _makeedgedone;
  int               _infiniteline;
  CATCrvLimits      _lims;
  
};

#endif
//-------------------------------------------------------------------------


