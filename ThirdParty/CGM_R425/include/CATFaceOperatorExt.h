#ifndef CATFaceOperatorExt_h
#define CATFaceOperatorExt_h

#include "CATGeoToTopOperatorExt.h"
#include "ListPOfListPOfCATPCurve.h"

class CATDomain;
class CATFace;
class CATLoop;
class CATEdge;
class CATVertex;
class CATPCurve;
class CATPlane;
class CATSurface;
class CATGeoFactory;
class CATBody;
class CATCGMJournalList;
class CATMathLine;
class CATMathBox;

class ExportedByCATTopologicalObjects CATFaceOperatorExt :public CATGeoToTopOperatorExt
{
public:

  /**	@nodoc @nocgmitf */ 
  CATCGMNewClassArrayDeclare;

  /**	@nodoc @nocgmitf */ 
  CATFaceOperatorExt(CATGeoFactory*     factory, 
                  CATSurface*        surface,
                  CATBody*           targetBody=NULL,
                  CATBodyFreezeMode  bodyfreezemode=CATBodyFreezeOn,
                  CATCGMJournalList* report=NULL);

  /**	@nodoc @nocgmitf */ 
  CATFaceOperatorExt(CATGeoFactory * iFactory, 
                   CATTopData    * iTopData,
                   CATSurface     * iSurface);

  /**	@nodoc @nocgmitf */ 
  CATFaceOperatorExt(CATGeoFactory*     factory,
                  int                iNbCurves,
                  CATPCurve * const ipCurveArray[],
                  CATBody*           targetBody=NULL,
                  CATBodyFreezeMode  bodyfreezemode=CATBodyFreezeOn,
                  CATCGMJournalList *report=NULL);

  /**	@nodoc @nocgmitf */ 
  CATFaceOperatorExt(CATGeoFactory  * factory, 
                      CATTopData    * iData,
                      int                iNbCurves,
                      CATPCurve * const ipCurveArray[]);
  
  /**	@nodoc @nocgmitf */ 
	void AddInternalLoop(int nbpcurves, CATPCurve ** ipCurveArray);

  /**	@nodoc @nocgmitf */ 
	~CATFaceOperatorExt();

  /**	@nodoc @nocgmitf */ 
	CATFace* GetFace() const;

	/**	@nodoc @nocgmitf */
	int RunOperator();

	/**  @nodoc @nocgmitf */
	void   RDOIAOO(CATTopOperator & iOperator);

  static const CATString *GetDefaultOperatorId() { return &_OperatorId; };

protected:
  const  CATString *GetOperatorId();

  // Methods for CGMReplay recording.
  CATExtCGMReplay  *IsRecordableExt(short &LevelOfRuntime, short &VersionOfStream);

  virtual void WriteInputExt(CATCGMStream  & ioStream);

  virtual CATCGMOperator::CATCheckDiagnostic CheckOutputExt(CATCGMOutput & os);

  virtual void DumpExt(CATCGMOutput& os);

private:
  CATLoop * BuildInternalLoop(int nbpcurves, CATPCurve **pcurves);

  /**	@nodoc @nocgmitf */ 
  int  GetSurfaceBoundaries(CATSurface* Surface, CATPCurve**& pcurves);

  /**	@nodoc @nocgmitf */ 
  void MakeFace();

  /**	@nodoc @nocgmitf */ 
  void Init(CATSurface*);

  /**	@nodoc @nocgmitf */ 
  void FillLoop(CATLoop*, int, CATPCurve**);

  /**	@nodoc @nocgmitf */ 
  void FillLoopAuto(CATLoop*, int, CATPCurve**);

  /**	@nodoc @nocgmitf */ 
  void FillClosedLoop(CATLoop*,CATPCurve*);

  CATLoop        *  _externalloop;       
  CATFace        *  _face;
  CATSurface     *  _surface;

  // PCurves on outside of face.
  CATPCurve     **  _pcurves; 
  int               _nbpcurves;

  // Internal loops and PCurves for them.
  ListPOfCATDomain        _InternalLoopList; // List of internal loops created.
  ListPOfListPOfCATPCurve _PCurveListInternalLoopList;

  int               _makefacedone;
  int               _infiniteface;
  int               _autosurf;

  static CATString  _OperatorId;

  // Whether calculation to get surface from PCurves or vice versa has been done.
  CATBoolean        _SurfaceAndPCurvesCalculated; 


};
#endif

