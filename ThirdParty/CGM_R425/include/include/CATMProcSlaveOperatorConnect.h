// COPYRIGHT DASSAULT SYSTEMES 2009
//=============================================================================
// May. 09  Creation                                                    SOU
//=============================================================================



#ifndef CATMProcSlaveOperatorConnect_H
#define CATMProcSlaveOperatorConnect_H

#include "IUnknown.h"

#include "CATMProcSlaveOperatorCGM.h"
#include "ConnectInt.h"
#include "CATCrvParam.h"
#include "CATIntersectionSign.h"

class CATConnectComputer;
class CATConnectSupport;
class CATConnectTool;
class CATMathSetOfPointsND;
class CATEdgeCurve;
class CATPCurve;
class CATCrvLimits;

//	This class manages the connect computation on the slave part
//	basically unstream of the input, Create Connect and Run it, stream Result

class ExportedByConnectInt CATMProcSlaveOperatorConnect : public CATMProcSlaveOperatorCGM
{
public:

	CATMProcSlaveOperatorConnect();

	virtual ~CATMProcSlaveOperatorConnect();

	CATMProcSlaveOperatorConnect& operator =(const CATMProcSlaveOperatorConnect& iOneOf);

	HRESULT Run(void*& ioBuffer,unsigned int& ioLgAllocated,unsigned int &ioLgData);

	static CATMProcSlaveOperatorConnect* GetOperator();

protected:
	//clean the factory to avoid conflicts on reception of new objects
	void EraseLocal();

	HRESULT RunComputer(CATCGMStream* StreamResults);

	//unstream the other non cgm input and by the way separate the listinput in the two listsurfaces
	void UnStreamOtherInput(CATCGMStream& Stream,CATLISTP(CATICGMObject) &iListInput);

	//void WriteTrace(char* iMessage);

  CATConnectComputer* _Computer;

  //data required for creating Computer
  CATConnectSupport*  _Supports[2];//to do: make generic
  const CATConnectTool* _Profile;
  CATMathSetOfPointsND* _InitPoints;
  CATIntersectionSign _StartingSignOn1;

  short _CommonCurveOrient1, _CommonCurveOrient2;
  CATEdgeCurve* _CommonCurve;
  CATCrvParam _CommonPoint;
  CATBoolean _LoopSearch;

  //settings on Computer
  double *_PointingPoint;

  CATBoolean _OnlyInitHomotopic;
  CATLONG32              _PCrvSize;
  CATLONG32           *  _PCrvID;
  CATPCurve           ** _PCrvTable;
  CATCrvLimits        *  _PCrvLim;
  short               *  _PCrvSide;

  CATLONG32 _Dimension;

  //debug
  static CATLONG32 _NumRun;

};

//Slave function : function dynamically called by the slaves process
extern "C" HRESULT ExportedByConnectInt ExecuteConnectComputer(void*& ioBuffer,unsigned int& ioLgBuffer,unsigned int& oLgData);


#endif

