// ==================================================================================
//
// 12/10/2016 Integration of the Parametrization of the specific anomalies 
//			  CATCGMEdge_GapXYZ and CATCGMVrtex_GapXYZ						KY1   
//
// ==================================================================================
#ifndef __CATExplicitCheck_AnomalyBase__
#define __CATExplicitCheck_AnomalyBase__

#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATPGMExplicitReport.h"
#include "CATExplicitLabelParameter.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"
#include "CATCGMHashTable.h"
//class CATCGMHashTable;

enum CATExplicitAnomaly_Category
{
	CATExplicitAnomaly_Category_Unknown,
	CATExplicitAnomaly_OnlyInternal,
	CATExplicitAnomaly_OnlySpecific,
	CATExplicitAnomaly_InternalAndSpecific
};


/** @nodoc @nocgmitf */
/**
* Class representing the base class of an explicit anomaly.
* Cannot be instanciated
* <br><b>Role</b>: Provide generic services to handle an explicit anomaly. 
*							-	Setting Parameters,
*							-	Getting Labels
*							-	Setting ....
*							-	Getting ....
*
* @example
*  // example is optional
*/
class CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	static CATExplicitCheck_AnomalyBase *CATCreateExplicitCheck_AnomalyBase(CATCGMExplicitCheckAnomaly iAnomalyLabel);

	/** @nodoc @nocgmitf */
	/**
	* set the Scale Factor
	* @param iScaleFactor
	*	 the scale factor
	*/
	static void SetScaleFactor(double iScaleFactor);

	/** @nodoc @nocgmitf */
	CATExplicitCheck_AnomalyBase();

	/** @nodoc @nocgmitf */
	virtual ~CATExplicitCheck_AnomalyBase();

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	virtual void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	virtual void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	virtual void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	virtual CATCGMExplicitCheckAnomaly GetLabel() = 0;

	/** @nodoc @nocgmitf */
	CATExplicitAnomaly_Category GetCategory();

	/** @nodoc @nocgmitf */
	CATBoolean GetContextConceptFeature();

	/** @nodoc @nocgmitf */
	CATExplicitCheck_AnomalyBase *CastTo(CATCGMExplicitCheckAnomaly iAnomalyLabel);
		
	/** @nodoc @nocgmitf */
	//INLINE void SetStatus(CATBoolean iStatus) { _Status = iStatus;};

	/** @nodoc @nocgmitf */
	//INLINE CATBoolean GetStatus() { return _Status; };

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	CATULONG32 HashKey();

	/** @nodoc @nocgmitf */
	CATLONG32 IsEqual(CATExplicitCheck_AnomalyBase *pExplicitCheck_AnomalyBase);

	/** @nodoc @nocgmitf */
	virtual void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	unsigned int AddRef();

	/** @nodoc @nocgmitf */
	unsigned int Release();

	/** @nodoc @nocgmitf */
	unsigned int						_Counter;	

	/** @nodoc @nocgmitf */
	//CATBoolean							_Status;

	/** @nodoc @nocgmitf */
	CATExplicitAnomaly_Category	_ExplicitAnomaly_Category;

	/** @nodoc @nocgmitf */
	CATBoolean						 	_ContextConceptFeature;

protected:
	/** @nodoc @nocgmitf */
	//virtual CATExplicitCheck_AnomalyBase *SecureCastTo() = 0;

	/** @nodoc @nocgmitf */
	static double _ScaleFactor;

private:
	/** @nodoc @nocgmitf */
	CATExplicitCheck_AnomalyBase(const CATExplicitCheck_AnomalyBase& iExplicitCheck_AnomalyBase);

	/** @nodoc @nocgmitf */
	CATExplicitCheck_AnomalyBase&  operator = (const CATExplicitCheck_AnomalyBase& iExplicitCheck_AnomalyBase);
};


/** @nodoc @nocgmitf */
class CATCGMEdge_AnomalyBase : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_AnomalyBase();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_AnomalyBase();
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	//void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireDomain();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckLoopDomain();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATBoolean _CheckWireDomain;
		/** @nodoc @nocgmitf */
	CATBoolean _CheckLoopDomain;
	/** @nodoc @nocgmitf */
	CATCGMEdge_AnomalyBase(const CATCGMEdge_AnomalyBase& iCGMEdge_AnomalyBase);

	/** @nodoc @nocgmitf */
	CATCGMEdge_AnomalyBase&  operator = (const CATCGMEdge_AnomalyBase& iCGMEdge_AnomalyBase);
};


/** @nodoc @nocgmitf */
/**
* Class to representing a Hash Table of @href CATExplicitCheck_AnomalyBase.
*
* <br><b>Role</b>: store a collection of @href CATExplicitCheck_AnomalyBase
* <p>
* Do not use the @href CATCGMUnsmartList constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*/
class CATExplicitCheck_HashTableOfAnomalyBase  : public CATCGMHashTable
{
public:
	/** @nodoc @nocgmitf */
	CATExplicitCheck_HashTableOfAnomalyBase(int iEstimatedSize = 0);  

	/** @nodoc @nocgmitf */
  virtual ~CATExplicitCheck_HashTableOfAnomalyBase();

  CATCGMNewClassArrayDeclare;
  /** @nodoc @nocgmitf */
  int                 Insert(CATExplicitCheck_AnomalyBase* piExplicitCheck_AnomalyBase);

  /** @nodoc @nocgmitf */
  CATExplicitCheck_AnomalyBase*		Locate(CATExplicitCheck_AnomalyBase* piExplicitCheck_AnomalyBase) const;

  /** @nodoc @nocgmitf */
  CATExplicitCheck_AnomalyBase*		KeyLocate(unsigned int iKey) const;

  CATExplicitCheck_AnomalyBase*     Next(CATExplicitCheck_AnomalyBase* piExplicitCheck_AnomalyBase) const;

  /** @nodoc @nocgmitf */
  CATExplicitCheck_AnomalyBase*  Get(int iPos) const;
};


/** @nodoc @nocgmitf */
class CATCGMInternalAnomalies_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMInternalAnomalies_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMInternalAnomalies_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	////CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMInternalAnomalies_Anomaly(const CATCGMInternalAnomalies_Anomaly& iCGMInternalAnomalies_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMInternalAnomalies_Anomaly&  operator = (const CATCGMInternalAnomalies_Anomaly& iCGMInternalAnomalies_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMVertex_GapXYZ_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMVertex_GapXYZ_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMVertex_GapXYZ_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

   /** @nodoc @nocgmitf */
   void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

   /** @nodoc @nocgmitf */
   double Get_Tolerance();

   /** @nodoc @nocgmitf */
   virtual void Write(CATCGMStream& Str,short iVersion);

   /** @nodoc @nocgmitf */
   virtual void Read(CATCGMStream& Str,short iVersion);

   /** @nodoc @nocgmitf */
   void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
   /** @nodoc @nocgmitf */
   double _Tolerance;
	/** @nodoc @nocgmitf */
	CATCGMVertex_GapXYZ_Anomaly(const CATCGMVertex_GapXYZ_Anomaly& iCGMVertex_GapXYZ_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMVertex_GapXYZ_Anomaly&  operator = (const CATCGMVertex_GapXYZ_Anomaly& iCGMVertex_GapXYZ_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_GapXYZ_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_GapXYZ_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_GapXYZ_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

   /** @nodoc @nocgmitf */
   void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

   /** @nodoc @nocgmitf */
   double Get_Tolerance();

   /** @nodoc @nocgmitf */
   virtual void Write(CATCGMStream& Str,short iVersion);

   /** @nodoc @nocgmitf */
   virtual void Read(CATCGMStream& Str,short iVersion);

   /** @nodoc @nocgmitf */
   void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
   /** @nodoc @nocgmitf */
   double _Tolerance;
	/** @nodoc @nocgmitf */
	CATCGMEdge_GapXYZ_Anomaly(const CATCGMEdge_GapXYZ_Anomaly& iCGMEdge_GapXYZ_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_GapXYZ_Anomaly&  operator = (const CATCGMEdge_GapXYZ_Anomaly& iCGMEdge_GapXYZ_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_LengthDegenerated_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_LengthDegenerated_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_LengthDegenerated_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinLength();

	/** @nodoc @nocgmitf */
	double Get_MaxLength();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireBody();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckSkinBody();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckSolidBody();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _MinLength;
	/** @nodoc @nocgmitf */
	double _MaxLength;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckWireBody;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckSkinBody;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckSolidBody;
	/** @nodoc @nocgmitf */
	CATCGMEdge_LengthDegenerated_Anomaly(const CATCGMEdge_LengthDegenerated_Anomaly& iCGMEdge_LengthDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_LengthDegenerated_Anomaly&  operator = (const CATCGMEdge_LengthDegenerated_Anomaly& iCGMEdge_LengthDegenerated_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_NulCurvatureRadius_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_NulCurvatureRadius_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_NulCurvatureRadius_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);	

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
	
	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	double Get_MinCurvatureRadius();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	double _MinCurvatureRadius;

	/** @nodoc @nocgmitf */
	CATCGMEdge_NulCurvatureRadius_Anomaly(const CATCGMEdge_NulCurvatureRadius_Anomaly& iCGMEdge_NulCurvatureRadius_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_NulCurvatureRadius_Anomaly&  operator = (const CATCGMEdge_NulCurvatureRadius_Anomaly& iCGMEdge_NulCurvatureRadius_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_ArcLengthDegenerated_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_ArcLengthDegenerated_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_ArcLengthDegenerated_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	//void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinLength();

	/** @nodoc @nocgmitf */
	double Get_MaxLength();
	
	/** @nodoc @nocgmitf */
	//CATLONG32 Get_CurveLimitsMode();

	/** @nodoc @nocgmitf */
	//CATLONG32 Get_ComputationMethod();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireBody();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckSkinBody();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckSolidBody();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckOnlyRefCurve();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _MinLength;
	/** @nodoc @nocgmitf */
	double _MaxLength;
	/** @nodoc @nocgmitf */
	//CATLONG32 _CurveLimitsMode; // 0 : MaxLimits of Arcs limited by the limit of the edge (params of start and end POEC of the edge), 1 : Max Limits of arcs, 2 : MaxLimits of the Curve
	/** @nodoc @nocgmitf */
	//CATLONG32 _ComputationMethod; // 0 : compute the real length of the arc (default beha) / 1 : compute approximate length by sampling the arc in three pts
	/** @nodoc @nocgmitf */
	CATBoolean _CheckWireBody;
		/** @nodoc @nocgmitf */
	CATBoolean _CheckSkinBody;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckSolidBody;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckOnlyRefCurve;
	
	/** @nodoc @nocgmitf */
	CATCGMEdge_ArcLengthDegenerated_Anomaly(const CATCGMEdge_ArcLengthDegenerated_Anomaly& iCGMEdge_ArcLengthDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_ArcLengthDegenerated_Anomaly&  operator = (const CATCGMEdge_ArcLengthDegenerated_Anomaly& iCGMEdge_ArcLengthDegenerated_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMVolume_InnerShellOutsideOuterShell_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMVolume_InnerShellOutsideOuterShell_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMVolume_InnerShellOutsideOuterShell_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMVolume_InnerShellOutsideOuterShell_Anomaly(const CATCGMVolume_InnerShellOutsideOuterShell_Anomaly& iCGMVolume_InnerShellOutsideOuterShell_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMVolume_InnerShellOutsideOuterShell_Anomaly&  operator = (const CATCGMVolume_InnerShellOutsideOuterShell_Anomaly& iCGMVolume_InnerShellOutsideOuterShell_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_AutoIntersection_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_AutoIntersection_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_AutoIntersection_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireDomain();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckLoopDomain();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATBoolean _CheckWireDomain;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckLoopDomain;
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_AutoIntersection_Anomaly(const CATCGMEdgeDomain_AutoIntersection_Anomaly& iCGMEdgeDomain_AutoIntersection_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_AutoIntersection_Anomaly&  operator = (const CATCGMEdgeDomain_AutoIntersection_Anomaly& iCGMEdgeDomain_AutoIntersection_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_DisconnectedEdges_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_DisconnectedEdges_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_DisconnectedEdges_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_DisconnectedEdges_Anomaly(const CATCGMEdgeDomain_DisconnectedEdges_Anomaly& iCGMEdgeDomain_DisconnectedEdges_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_DisconnectedEdges_Anomaly&  operator = (const CATCGMEdgeDomain_DisconnectedEdges_Anomaly& iCGMEdgeDomain_DisconnectedEdges_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_InnerLoopOutsideOuterLoop_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_InnerLoopOutsideOuterLoop_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_InnerLoopOutsideOuterLoop_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_InnerLoopOutsideOuterLoop_Anomaly(const CATCGMFace_InnerLoopOutsideOuterLoop_Anomaly& iCGMFace_InnerLoopOutsideOuterLoop_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_InnerLoopOutsideOuterLoop_Anomaly&  operator = (const CATCGMFace_InnerLoopOutsideOuterLoop_Anomaly& iCGMFace_InnerLoopOutsideOuterLoop_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_IntersectionBetweenLoops_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_IntersectionBetweenLoops_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_IntersectionBetweenLoops_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_IntersectionBetweenLoops_Anomaly(const CATCGMFace_IntersectionBetweenLoops_Anomaly& iCGMFace_IntersectionBetweenLoops_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_IntersectionBetweenLoops_Anomaly&  operator = (const CATCGMFace_IntersectionBetweenLoops_Anomaly& iCGMFace_IntersectionBetweenLoops_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_IsoDegenerescence_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_IsoDegenerescence_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_IsoDegenerescence_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_IsoDegenerescence_Anomaly(const CATCGMFace_IsoDegenerescence_Anomaly& iCGMFace_IsoDegenerescence_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_IsoDegenerescence_Anomaly&  operator = (const CATCGMFace_IsoDegenerescence_Anomaly& iCGMFace_IsoDegenerescence_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_Twisted_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_Twisted_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_Twisted_Anomaly(){};
	
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_Twisted_Anomaly(const CATCGMFace_Twisted_Anomaly& iCGMFace_Twisted_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_Twisted_Anomaly&  operator = (const CATCGMFace_Twisted_Anomaly& iCGMFace_Twisted_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_NulCurvatureRadius_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_NulCurvatureRadius_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_NulCurvatureRadius_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;
		
	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	//void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);	

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
	
	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	double Get_MinCurvatureRadius();

	/** @nodoc @nocgmitf */
	//double Get_MaxCurvatureRadius();

	/** @nodoc @nocgmitf */
	//double Get_TolMinLengthNormal();
	
	/** @nodoc @nocgmitf */
	//CATLONG32 Get_NbPointsPerSegment();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckOnlyFaceArea();
	
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	double _MinCurvatureRadius;
	/** @nodoc @nocgmitf */
	//double _MaxCurvatureRadius;
	/** @nodoc @nocgmitf */
	//double _TolMinLengthNormal;	
	/** @nodoc @nocgmitf */
	//CATLONG32 _NbPointsPerSegment;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckOnlyFaceArea;

	/** @nodoc @nocgmitf */
	CATCGMFace_NulCurvatureRadius_Anomaly(const CATCGMFace_NulCurvatureRadius_Anomaly& iCGMFace_NulCurvatureRadius_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_NulCurvatureRadius_Anomaly&  operator = (const CATCGMFace_NulCurvatureRadius_Anomaly& iCGMFace_NulCurvatureRadius_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_HighNbArcs_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_HighNbArcs_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_HighNbArcs_Anomaly(){};
	
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	CATLONG32 GetMaxNbArcs();

protected:
	/** @nodoc @nocgmitf */
	CATLONG32 _MaxNbArcs;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();	
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_HighNbArcs_Anomaly(const CATCGMEdge_HighNbArcs_Anomaly& iCGMEdge_HighNbArcs_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_HighNbArcs_Anomaly&  operator = (const CATCGMEdge_HighNbArcs_Anomaly& iCGMEdge_HighNbArcs_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_HighPolynomialDegree_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_HighPolynomialDegree_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_HighPolynomialDegree_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	CATLONG32 GetMaxDegree();

protected:
	/** @nodoc @nocgmitf */
	CATLONG32 _MaxDegree;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_HighPolynomialDegree_Anomaly(const CATCGMEdge_HighPolynomialDegree_Anomaly& iCGMEdge_HighPolynomialDegree_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_HighPolynomialDegree_Anomaly&  operator = (const CATCGMEdge_HighPolynomialDegree_Anomaly& iCGMEdge_HighPolynomialDegree_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMCell_KnotsInSideRange_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMCell_KnotsInSideRange_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMCell_KnotsInSideRange_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	virtual CATCGMExplicitCheckAnomaly GetLabel() = 0;

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	double Get_Min_Gap_Knots();

	/** @nodoc @nocgmitf */
	double Get_Max_Gap_Knots();

protected:
	/** @nodoc @nocgmitf */
	double _Min_Gap_Knots;
	/** @nodoc @nocgmitf */
	double _Max_Gap_Knots;
	/** @nodoc @nocgmitf */
	//virtual CATExplicitCheck_AnomalyBase *SecureCastTo() = 0;
};


/** @nodoc @nocgmitf */
class CATCGMEdge_KnotsInSideRange_Anomaly : public CATCGMCell_KnotsInSideRange_Anomaly
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_KnotsInSideRange_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_KnotsInSideRange_Anomaly(){};

	CATCGMNewClassArrayDeclare;

   /** @nodoc @nocgmitf */
   void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

   /** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

   /** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
   
   /** @nodoc @nocgmitf */
   CATBoolean Get_CheckWireDomain();

   /** @nodoc @nocgmitf */
   CATBoolean Get_CheckLoopDomain();
	
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_KnotsInSideRange_Anomaly(const CATCGMEdge_KnotsInSideRange_Anomaly& iCGMEdge_KnotsInSideRange_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_KnotsInSideRange_Anomaly&  operator = (const CATCGMEdge_KnotsInSideRange_Anomaly& iCGMEdge_KnotsInSideRange_Anomaly);

   /** @nodoc @nocgmitf */
	CATBoolean _CheckWireDomain;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckLoopDomain;	
};

/** @nodoc @nocgmitf */
class CATCGMFace_HighNbPatches_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMFace_HighNbPatches_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_HighNbPatches_Anomaly(){};
	
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	CATLONG32 Get_Max_NbPatches();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_Max_NbPatches_Dir();

protected:
	/** @nodoc @nocgmitf */
	CATLONG32 _Max_NbPatches;
	/** @nodoc @nocgmitf */
	CATLONG32 _Max_NbPatches_Dir;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_HighNbPatches_Anomaly(const CATCGMFace_HighNbPatches_Anomaly& iCGMFace_HighNbPatches_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_HighNbPatches_Anomaly&  operator = (const CATCGMFace_HighNbPatches_Anomaly& iCGMFace_HighNbPatches_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_HighPolynomialDegree_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_HighPolynomialDegree_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_HighPolynomialDegree_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	CATLONG32	Get_MaxDegree();

	/** @nodoc @nocgmitf */
	CATBoolean	Get_CheckCanonicalSurfaces();
	protected:
		/** @nodoc @nocgmitf */
		CATLONG32	_MaxDegree;
		/** @nodoc @nocgmitf */
	CATBoolean	_CheckCanonicalSurfaces;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_HighPolynomialDegree_Anomaly(const CATCGMFace_HighPolynomialDegree_Anomaly& iCGMFace_HighPolynomialDegree_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_HighPolynomialDegree_Anomaly&  operator = (const CATCGMFace_HighPolynomialDegree_Anomaly& iCGMFace_HighPolynomialDegree_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_KnotsInSideRange_Anomaly : public CATCGMCell_KnotsInSideRange_Anomaly
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_KnotsInSideRange_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_KnotsInSideRange_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
	
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_KnotsInSideRange_Anomaly(const CATCGMFace_KnotsInSideRange_Anomaly& iCGMFace_KnotsInSideRange_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_KnotsInSideRange_Anomaly&  operator = (const CATCGMFace_KnotsInSideRange_Anomaly& iCGMFace_KnotsInSideRange_Anomaly);
};


/** @nodoc @nocgmitf */
class CATCGMBody_NonManifoldEdges_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_NonManifoldEdges_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_NonManifoldEdges_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
		
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMBody_NonManifoldEdges_Anomaly(const CATCGMBody_NonManifoldEdges_Anomaly& iCGMBody_NonManifoldEdges_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_NonManifoldEdges_Anomaly&  operator = (const CATCGMBody_NonManifoldEdges_Anomaly& iCGMBody_NonManifoldEdges_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_MixedConvexityEdges_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_MixedConvexityEdges_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_MixedConvexityEdges_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
		
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMBody_MixedConvexityEdges_Anomaly(const CATCGMBody_MixedConvexityEdges_Anomaly& iCGMBody_MixedConvexityEdges_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_MixedConvexityEdges_Anomaly&  operator = (const CATCGMBody_MixedConvexityEdges_Anomaly& iCGMBody_MixedConvexityEdges_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_VertexOverBounded_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMBody_VertexOverBounded_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_VertexOverBounded_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
	
	/** @nodoc @nocgmitf */
	CATLONG32 Get_MaxNbIncidEdges();

protected:
	/** @nodoc @nocgmitf */
	CATLONG32 _MaxNbIncidEdges;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMBody_VertexOverBounded_Anomaly(const CATCGMBody_VertexOverBounded_Anomaly& iCGMBody_VertexOverBounded_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_VertexOverBounded_Anomaly&  operator = (const CATCGMBody_VertexOverBounded_Anomaly& iCGMBody_VertexOverBounded_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMShell_AdjacentFacesSharpAngle_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMShell_AdjacentFacesSharpAngle_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMShell_AdjacentFacesSharpAngle_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion) ;
	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);
	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
  
	/** @nodoc @nocgmitf */
	double			Get_MaxAngle();

	/** @nodoc @nocgmitf */
	CATLONG32		Get_SampleKind();

	/** @nodoc @nocgmitf */
	CATLONG32		Get_SizeSamplePt();

	/** @nodoc @nocgmitf */
	CATLONG32		Get_CheckModeForLimitPts();
protected:
	/** @nodoc @nocgmitf */
	double			_MaxAngle;

	/** @nodoc @nocgmitf */
	CATLONG32		_SampleKind;				//(legal values 0,1)

	/** @nodoc @nocgmitf */
	CATLONG32		_SizeSamplePt;

	/** @nodoc @nocgmitf */
	CATLONG32		_CheckModeForLimitPts;	//(legal values 0,1,2,3)
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMShell_AdjacentFacesSharpAngle_Anomaly(const CATCGMShell_AdjacentFacesSharpAngle_Anomaly& iCGMShell_AdjacentFacesSharpAngle_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMShell_AdjacentFacesSharpAngle_Anomaly&  operator = (const CATCGMShell_AdjacentFacesSharpAngle_Anomaly& iCGMShell_AdjacentFacesSharpAngle_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_MultiDomains_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_MultiDomains_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_MultiDomains_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);
	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireBody();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckSkinBody();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckSolidBody();

	protected:
		/** @nodoc @nocgmitf */
		CATBoolean _CheckWireBody;
		/** @nodoc @nocgmitf */
		CATBoolean _CheckSkinBody;
		/** @nodoc @nocgmitf */
		CATBoolean _CheckSolidBody;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMBody_MultiDomains_Anomaly(const CATCGMBody_MultiDomains_Anomaly& iCGMBody_MultiDomains_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_MultiDomains_Anomaly&  operator = (const CATCGMBody_MultiDomains_Anomaly& iCGMBody_MultiDomains_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_DiscontinuityG0_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	CATCGMEdge_DiscontinuityG0_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_DiscontinuityG0_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
	
	/** @nodoc @nocgmitf */
	double Get_MaxGap();

protected:
	/** @nodoc @nocgmitf */
	double _MaxGap;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_DiscontinuityG0_Anomaly(const CATCGMEdge_DiscontinuityG0_Anomaly& iCGMEdge_DiscontinuityG0_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_DiscontinuityG0_Anomaly&  operator = (const CATCGMEdge_DiscontinuityG0_Anomaly& iCGMEdge_DiscontinuityG0_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_DiscontinuityG1_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	CATCGMEdge_DiscontinuityG1_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_DiscontinuityG1_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	double Get_MaxAngleDeg();

	/** @nodoc @nocgmitf */
	double Get_MinAngleDeg();

protected:
	/** @nodoc @nocgmitf */
	double _MaxAngleDeg;
		/** @nodoc @nocgmitf */
	double _MinAngleDeg;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_DiscontinuityG1_Anomaly(const CATCGMEdge_DiscontinuityG1_Anomaly& iCGMEdge_DiscontinuityG1_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_DiscontinuityG1_Anomaly&  operator = (const CATCGMEdge_DiscontinuityG1_Anomaly& iCGMEdge_DiscontinuityG1_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_DiscontinuityG2_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	CATCGMEdge_DiscontinuityG2_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_DiscontinuityG2_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	double Get_MaxCurvatureRatio();

	/** @nodoc @nocgmitf */
	double Get_MinCurvatureRatio();

	/** @nodoc @nocgmitf */
	double Get_InfiniteCurvatureRatio();

protected:
	/** @nodoc @nocgmitf */
	double _MaxCurvatureRatio;
	/** @nodoc @nocgmitf */
	double _MinCurvatureRatio;
	/** @nodoc @nocgmitf */
	double _InfiniteCurvatureRatio;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_DiscontinuityG2_Anomaly(const CATCGMEdge_DiscontinuityG2_Anomaly& iCGMEdge_DiscontinuityG2_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_DiscontinuityG2_Anomaly&  operator = (const CATCGMEdge_DiscontinuityG2_Anomaly& iCGMEdge_DiscontinuityG2_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_DiscontinuityG0_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMEdgeDomain_DiscontinuityG0_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_DiscontinuityG0_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireDomain();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckLoopDomain();

	/** @nodoc @nocgmitf */
	double Get_MaxGap();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
protected:
	/** @nodoc @nocgmitf */
	double _MaxGap;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckWireDomain;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckLoopDomain;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_DiscontinuityG0_Anomaly(const CATCGMEdgeDomain_DiscontinuityG0_Anomaly& iCGMEdgeDomain_DiscontinuityG0_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_DiscontinuityG0_Anomaly&  operator = (const CATCGMEdgeDomain_DiscontinuityG0_Anomaly& iCGMEdgeDomain_DiscontinuityG0_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_DiscontinuityG1_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMEdgeDomain_DiscontinuityG1_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_DiscontinuityG1_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireDomain();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckLoopDomain();

	/** @nodoc @nocgmitf */
	double Get_MaxAngleDeg();

	/** @nodoc @nocgmitf */
	double Get_MinAngleDeg();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
protected:
	/** @nodoc @nocgmitf */
	double _MinAngleDeg;
	/** @nodoc @nocgmitf */
	double _MaxAngleDeg;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckWireDomain;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckLoopDomain;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_DiscontinuityG1_Anomaly(const CATCGMEdgeDomain_DiscontinuityG1_Anomaly& iCGMEdgeDomain_DiscontinuityG1_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_DiscontinuityG1_Anomaly&  operator = (const CATCGMEdgeDomain_DiscontinuityG1_Anomaly& iCGMEdgeDomain_DiscontinuityG1_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_DiscontinuityG2_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMEdgeDomain_DiscontinuityG2_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_DiscontinuityG2_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireDomain();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckLoopDomain();

	/** @nodoc @nocgmitf */
	double Get_MaxCurvatureRatio();

	/** @nodoc @nocgmitf */
	double Get_MinCurvatureRatio();

	/** @nodoc @nocgmitf */
	double Get_InfiniteCurvatureRatio();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
protected:
	/** @nodoc @nocgmitf */
	double _MaxCurvatureRatio;
	/** @nodoc @nocgmitf */
	double _MinCurvatureRatio;
	/** @nodoc @nocgmitf */
	double _InfiniteCurvatureRatio;
	/** @nodoc @nocgmitf */
	double _MaxAngleDeg;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckWireDomain;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckLoopDomain;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_DiscontinuityG2_Anomaly(const CATCGMEdgeDomain_DiscontinuityG2_Anomaly& iCGMEdgeDomain_DiscontinuityG2_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_DiscontinuityG2_Anomaly&  operator = (const CATCGMEdgeDomain_DiscontinuityG2_Anomaly& iCGMEdgeDomain_DiscontinuityG2_Anomaly);
};


/** @nodoc @nocgmitf */
class CATCGMVolume_WithInnerShell_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMVolume_WithInnerShell_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMVolume_WithInnerShell_Anomaly(){};

	CATCGMNewClassArrayDeclare;
		
	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);
	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
	protected:		
		//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMVolume_WithInnerShell_Anomaly(const CATCGMVolume_WithInnerShell_Anomaly& iCGMVolume_WithInnerShell_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMVolume_WithInnerShell_Anomaly&  operator = (const CATCGMVolume_WithInnerShell_Anomaly& iCGMVolume_WithInnerShell_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_LinearEdgeCurveWithOverSizedPolDeg_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_LinearEdgeCurveWithOverSizedPolDeg_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_LinearEdgeCurveWithOverSizedPolDeg_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);
	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	double Get_Tolerance();

	protected:
		/** @nodoc @nocgmitf */
		double _Tolerance;
		/** @nodoc @nocgmitf */
		//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_LinearEdgeCurveWithOverSizedPolDeg_Anomaly(const CATCGMEdge_LinearEdgeCurveWithOverSizedPolDeg_Anomaly& iCGMEdge_LinearEdgeCurveWithOverSizedPolDeg_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_LinearEdgeCurveWithOverSizedPolDeg_Anomaly&  operator = (const CATCGMEdge_LinearEdgeCurveWithOverSizedPolDeg_Anomaly& iCGMEdge_LinearEdgeCurveWithOverSizedPolDeg_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_AreaDegenerated_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_AreaDegenerated_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_AreaDegenerated_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinArea();

	/** @nodoc @nocgmitf */
	double Get_MaxArea();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _MinArea;
	/** @nodoc @nocgmitf */
	double _MaxArea;
	/** @nodoc @nocgmitf */
	CATCGMFace_AreaDegenerated_Anomaly(const CATCGMFace_AreaDegenerated_Anomaly& iCGMFace_AreaDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_AreaDegenerated_Anomaly&  operator = (const CATCGMFace_AreaDegenerated_Anomaly& iCGMFace_AreaDegenerated_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLump_VolumeDegenerated_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLump_VolumeDegenerated_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLump_VolumeDegenerated_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinVolume();

	/** @nodoc @nocgmitf */
	double Get_MaxVolume();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_MinLengthBB();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_MinAreaBB();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_MinVolumeBB();
	
	/** @nodoc @nocgmitf */
	double Get_MinDimBB();
	
	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_PerVolume();
	
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _MinVolume;
	/** @nodoc @nocgmitf */
	double _MaxVolume;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_MinLengthBB;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_MinAreaBB;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_MinVolumeBB;
	/** @nodoc @nocgmitf */
	double _MinDimBB;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_PerVolume;
	/** @nodoc @nocgmitf */
	CATCGMLump_VolumeDegenerated_Anomaly(const CATCGMLump_VolumeDegenerated_Anomaly& iCGMLump_VolumeDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLump_VolumeDegenerated_Anomaly&  operator = (const CATCGMLump_VolumeDegenerated_Anomaly& iCGMLump_VolumeDegenerated_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMShell_DiscontinuityG0_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMShell_DiscontinuityG0_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMShell_DiscontinuityG0_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
		
	/** @nodoc @nocgmitf */
	double Get_MaxGap();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_PointSampleSize();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
protected:
	/** @nodoc @nocgmitf */
	double _MaxGap;
	/** @nodoc @nocgmitf */
	CATLONG32 _PointSampleSize;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMShell_DiscontinuityG0_Anomaly(const CATCGMShell_DiscontinuityG0_Anomaly& iCGMShell_DiscontinuityG0_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMShell_DiscontinuityG0_Anomaly&  operator = (const CATCGMShell_DiscontinuityG0_Anomaly& iCGMShell_DiscontinuityG0_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMShell_DiscontinuityG1_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMShell_DiscontinuityG1_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMShell_DiscontinuityG1_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MaxAngleDeg();

	/** @nodoc @nocgmitf */
	double Get_MinAngleDeg();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_PointSampleSize();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_DiscG1Mode();
	
	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
protected:
	/** @nodoc @nocgmitf */
	double _MinAngleDeg;
	/** @nodoc @nocgmitf */
	double _MaxAngleDeg;
	/** @nodoc @nocgmitf */
	CATLONG32 _PointSampleSize;
	/** @nodoc @nocgmitf */
	CATLONG32 _DiscG1Mode;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMShell_DiscontinuityG1_Anomaly(const CATCGMShell_DiscontinuityG1_Anomaly& iCGMShell_DiscontinuityG1_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMShell_DiscontinuityG1_Anomaly&  operator = (const CATCGMShell_DiscontinuityG1_Anomaly& iCGMShell_DiscontinuityG1_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMShell_DiscontinuityG2_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMShell_DiscontinuityG2_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMShell_DiscontinuityG2_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MaxCurvatureRatio();

	/** @nodoc @nocgmitf */
	double Get_MinCurvatureRatio();

	/** @nodoc @nocgmitf */
	double Get_InfiniteCurvatureRatio();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_PointSampleSize();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
protected:
	/** @nodoc @nocgmitf */
	double _MaxCurvatureRatio;
	/** @nodoc @nocgmitf */
	double _MinCurvatureRatio;
	/** @nodoc @nocgmitf */
	double _InfiniteCurvatureRatio;
	/** @nodoc @nocgmitf */
	CATLONG32 _PointSampleSize;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMShell_DiscontinuityG2_Anomaly(const CATCGMShell_DiscontinuityG2_Anomaly& iCGMShell_DiscontinuityG2_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMShell_DiscontinuityG2_Anomaly&  operator = (const CATCGMShell_DiscontinuityG2_Anomaly& iCGMShell_DiscontinuityG2_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_DiscontinuityG0_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMFace_DiscontinuityG0_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_DiscontinuityG0_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
		
	/** @nodoc @nocgmitf */
	double Get_MaxGap();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_PointSampleSize();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
protected:
	/** @nodoc @nocgmitf */
	double _MaxGap;
	/** @nodoc @nocgmitf */
	CATLONG32 _PointSampleSize;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_DiscontinuityG0_Anomaly(const CATCGMFace_DiscontinuityG0_Anomaly& iCGMFace_DiscontinuityG0_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_DiscontinuityG0_Anomaly&  operator = (const CATCGMFace_DiscontinuityG0_Anomaly& iCGMFace_DiscontinuityG0_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_DiscontinuityG1_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMFace_DiscontinuityG1_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_DiscontinuityG1_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MaxAngleDeg();

	/** @nodoc @nocgmitf */
	double Get_MinAngleDeg();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_PointSampleSize();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckIsoParamTgtDev();
	
	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
protected:
	/** @nodoc @nocgmitf */
	double _MinAngleDeg;
	/** @nodoc @nocgmitf */
	double _MaxAngleDeg;
	/** @nodoc @nocgmitf */
	CATLONG32 _PointSampleSize;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckIsoParamTgtDev;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_DiscontinuityG1_Anomaly(const CATCGMFace_DiscontinuityG1_Anomaly& iCGMFace_DiscontinuityG1_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_DiscontinuityG1_Anomaly&  operator = (const CATCGMFace_DiscontinuityG1_Anomaly& iCGMFace_DiscontinuityG1_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_DiscontinuityG2_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	CATCGMFace_DiscontinuityG2_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_DiscontinuityG2_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MaxCurvatureRatio();

	/** @nodoc @nocgmitf */
	double Get_MinCurvatureRatio();

	/** @nodoc @nocgmitf */
	double Get_InfiniteCurvatureRatio();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_PointSampleSize();

	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
		
protected:
	/** @nodoc @nocgmitf */
	double _MaxCurvatureRatio;
	/** @nodoc @nocgmitf */
	double _MinCurvatureRatio;
	/** @nodoc @nocgmitf */
	double _InfiniteCurvatureRatio;
	/** @nodoc @nocgmitf */
	CATLONG32 _PointSampleSize;
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_DiscontinuityG2_Anomaly(const CATCGMFace_DiscontinuityG2_Anomaly& iCGMFace_DiscontinuityG2_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_DiscontinuityG2_Anomaly&  operator = (const CATCGMFace_DiscontinuityG2_Anomaly& iCGMFace_DiscontinuityG2_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_PatchAreaDegenerated_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_PatchAreaDegenerated_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_PatchAreaDegenerated_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinArea();

	/** @nodoc @nocgmitf */
	double Get_MaxArea();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_TypeOfMeasure_AreaOrLength();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_NarrowPatch();
		
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _MinArea;
	/** @nodoc @nocgmitf */
	double _MaxArea;
	/** @nodoc @nocgmitf */
	CATLONG32 _TypeOfMeasure_AreaOrLength;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_NarrowPatch;

	/** @nodoc @nocgmitf */
	CATCGMFace_PatchAreaDegenerated_Anomaly(const CATCGMFace_PatchAreaDegenerated_Anomaly& iCGMFace_PatchAreaDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_PatchAreaDegenerated_Anomaly&  operator = (const CATCGMFace_PatchAreaDegenerated_Anomaly& iFace_PatchAreaDegenerated_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_PatchLengthDegenerated_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_PatchLengthDegenerated_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_PatchLengthDegenerated_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;
		
	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinLength();

	/** @nodoc @nocgmitf */
	double Get_DenomLenghtRatioOfAdjacentPatches();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckLengthRatioOfAdjacentPatches();
	
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

private:
	/** @nodoc @nocgmitf */
	double		_MinLength;
	/** @nodoc @nocgmitf */
	double		_DenomLenghtRatioOfAdjacentPatches;
	/** @nodoc @nocgmitf */
	CATBoolean	_CheckLengthRatioOfAdjacentPatches;	
	/** @nodoc @nocgmitf */
	CATCGMFace_PatchLengthDegenerated_Anomaly(const CATCGMFace_PatchLengthDegenerated_Anomaly& iCGMFace_LengthAreaDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_PatchLengthDegenerated_Anomaly&  operator = (const CATCGMFace_PatchLengthDegenerated_Anomaly& iFace_PatchLengthDegenerated_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMSetOfBody_EmbeddedWireBodies_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMSetOfBody_EmbeddedWireBodies_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMSetOfBody_EmbeddedWireBodies_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_Tolerance();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_NbPointsPerSegment();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_PartialOverlaping();
		
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _Tolerance;
	/** @nodoc @nocgmitf */
	CATLONG32 _NbPointsPerSegment;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_PartialOverlaping;

	/** @nodoc @nocgmitf */
	CATCGMSetOfBody_EmbeddedWireBodies_Anomaly(const CATCGMSetOfBody_EmbeddedWireBodies_Anomaly& iCGMSetOfBody_EmbeddedWireBodies_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMSetOfBody_EmbeddedWireBodies_Anomaly&  operator = (const CATCGMSetOfBody_EmbeddedWireBodies_Anomaly& iCGMSetOfBody_EmbeddedWireBodies_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMSetOfBody_EmbeddedSkinBodies_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMSetOfBody_EmbeddedSkinBodies_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMSetOfBody_EmbeddedSkinBodies_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_Tolerance();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_PartialOverlaping();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_InnerPtsOfFaces();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_NbInnerPtsPerFace();
			
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _Tolerance;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_PartialOverlaping;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_InnerPtsOfFaces;
	/** @nodoc @nocgmitf */
	CATLONG32 _NbInnerPtsPerFace;

	/** @nodoc @nocgmitf */
	CATCGMSetOfBody_EmbeddedSkinBodies_Anomaly(const CATCGMSetOfBody_EmbeddedSkinBodies_Anomaly& iCGMSetOfBody_EmbeddedSkinBodies_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMSetOfBody_EmbeddedSkinBodies_Anomaly&  operator = (const CATCGMSetOfBody_EmbeddedSkinBodies_Anomaly& iCGMSetOfBody_EmbeddedSkinBodies_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMSetOfBody_EmbeddedSolidBodies_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMSetOfBody_EmbeddedSolidBodies_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMSetOfBody_EmbeddedSolidBodies_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_Tolerance();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_PartialOverlaping();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_InnerPtsOfFaces();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_NbInnerPtsPerFace();
			
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _Tolerance;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_PartialOverlaping;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_InnerPtsOfFaces;
	/** @nodoc @nocgmitf */
	CATLONG32 _NbInnerPtsPerFace;

	/** @nodoc @nocgmitf */
	CATCGMSetOfBody_EmbeddedSolidBodies_Anomaly(const CATCGMSetOfBody_EmbeddedSolidBodies_Anomaly& iCGMSetOfBody_EmbeddedSolidBodies_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMSetOfBody_EmbeddedSolidBodies_Anomaly&  operator = (const CATCGMSetOfBody_EmbeddedSolidBodies_Anomaly& iCGMSetOfBody_EmbeddedSolidBodies_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_EmbeddedFaces_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_EmbeddedFaces_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_EmbeddedFaces_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_Tolerance();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_PartialOverlaping();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_NbPointsPerSegment();
		
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _Tolerance;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_PartialOverlaping;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_InnerPtsOfFaces;
	/** @nodoc @nocgmitf */
	CATLONG32 _NbPointsPerSegment;

	/** @nodoc @nocgmitf */
	CATCGMBody_EmbeddedFaces_Anomaly(const CATCGMBody_EmbeddedFaces_Anomaly& iCGMBody_EmbeddedFaces_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_EmbeddedFaces_Anomaly&  operator = (const CATCGMBody_EmbeddedFaces_Anomaly& iCGMBody_EmbeddedFaces_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_InnerIntersectionBetweenFaces_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_InnerIntersectionBetweenFaces_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_InnerIntersectionBetweenFaces_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_Tolerance();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _Tolerance;

	/** @nodoc @nocgmitf */
	CATCGMBody_InnerIntersectionBetweenFaces_Anomaly(const CATCGMBody_InnerIntersectionBetweenFaces_Anomaly& iCGMBody_InnerIntersectionBetweenFaces_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_InnerIntersectionBetweenFaces_Anomaly&  operator = (const CATCGMBody_InnerIntersectionBetweenFaces_Anomaly& iCGMBody_InnerIntersectionBetweenFaces_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMShell_ConfusedFreeEdges_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMShell_ConfusedFreeEdges_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMShell_ConfusedFreeEdges_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_NarrowTolerance();

	/** @nodoc @nocgmitf */
	double Get_MinAngleDeg();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_NbPointsPerSegment();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_IfClosedBoundariesIsNarrow();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_G1Discontinuity();	

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_IfClosedBoundariesIsPartiallyNarrow();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _NarrowTolerance;
	/** @nodoc @nocgmitf */
	double _MinAngleDeg;
	/** @nodoc @nocgmitf */
	CATLONG32 _NbPointsPerSegment;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_IfClosedBoundariesIsNarrow;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_G1Discontinuity;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_IfClosedBoundariesIsPartiallyNarrow;
	

	/** @nodoc @nocgmitf */
	CATCGMShell_ConfusedFreeEdges_Anomaly(const CATCGMShell_ConfusedFreeEdges_Anomaly& iCGMShell_ConfusedFreeEdges_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMShell_ConfusedFreeEdges_Anomaly&  operator = (const CATCGMShell_ConfusedFreeEdges_Anomaly& iCGMShell_ConfusedFreeEdges_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_Folded_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_Folded_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_Folded_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinAngleDeg();
		
	/** @nodoc @nocgmitf */
	CATLONG32 Get_NbPointsPerSegment();
	
	/** @nodoc @nocgmitf */
	CATLONG32 Get_NbAdjacentPoints();
	
	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_NeighborSegments();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_OnFaceLimits();

	/** @nodoc @nocgmitf */
	CATBoolean Get_Check_OnlyBoundaries();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _MinAngleDeg;
	/** @nodoc @nocgmitf */
	CATLONG32 _NbPointsPerSegment;
		/** @nodoc @nocgmitf */
	CATLONG32 _NbAdjacentPoints;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_NeighborSegments;
		/** @nodoc @nocgmitf */
	CATBoolean _Check_OnlyBoundaries;
	/** @nodoc @nocgmitf */
	CATBoolean _Check_OnFaceLimits;
	

	/** @nodoc @nocgmitf */
	CATCGMFace_Folded_Anomaly(const CATCGMFace_Folded_Anomaly& iCGMFace_Folded_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_Folded_Anomaly&  operator = (const CATCGMFace_Folded_Anomaly& iCGMFace_Folded_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_LengthDegenerated_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_LengthDegenerated_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_LengthDegenerated_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinLength();

	/** @nodoc @nocgmitf */
	double Get_MaxLength();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireDomain();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckLoopDomain();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _MinLength;
	/** @nodoc @nocgmitf */
	double _MaxLength;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckWireDomain;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckLoopDomain;
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_LengthDegenerated_Anomaly(const CATCGMEdgeDomain_LengthDegenerated_Anomaly& iCGMEdgeDomain_LengthDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_LengthDegenerated_Anomaly&  operator = (const CATCGMEdgeDomain_LengthDegenerated_Anomaly& iCGMEdgeDomain_LengthDegenerated_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_GapXYZ_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_GapXYZ_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_GapXYZ_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	//void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

		/** @nodoc @nocgmitf */
	//void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	//double Get_Tolerance();

	/** @nodoc @nocgmitf */
	//CATBoolean Get_CheckOnlyRelativelyToRefCurve();

	/** @nodoc @nocgmitf */
	//virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	//virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	//void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	//CATBoolean _CheckOnlyRelativelyToRefCurve;

	/** @nodoc @nocgmitf */
	//double _Tolerance;

	/** @nodoc @nocgmitf */
	CATCGMPOEC_GapXYZ_Anomaly(const CATCGMPOEC_GapXYZ_Anomaly& iCGMPOEC_GapXYZ_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_GapXYZ_Anomaly&  operator = (const CATCGMPOEC_GapXYZ_Anomaly& iCGMPOEC_GapXYZ_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_WithAnalyticalOrProceduralSurface_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_WithAnalyticalOrProceduralSurface_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_WithAnalyticalOrProceduralSurface_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_WithAnalyticalOrProceduralSurface_Anomaly(const CATCGMFace_WithAnalyticalOrProceduralSurface_Anomaly& iCGMFace_WithAnalyticalOrProceduralSurface_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_WithAnalyticalOrProceduralSurface_Anomaly&  operator = (const CATCGMFace_WithAnalyticalOrProceduralSurface_Anomaly& iFace_WithAnalyticalOrProceduralSurface_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_WithAnalyticalOrProceduralCurve_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_WithAnalyticalOrProceduralCurve_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_WithAnalyticalOrProceduralCurve_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_WithAnalyticalOrProceduralCurve_Anomaly(const CATCGMEdge_WithAnalyticalOrProceduralCurve_Anomaly& iCGMEdge_WithAnalyticalOrProceduralCurve_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_WithAnalyticalOrProceduralCurve_Anomaly&  operator = (const CATCGMEdge_WithAnalyticalOrProceduralCurve_Anomaly& iEdge_WithAnalyticalOrProceduralCurve_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_SurfaceWithHighNumberOfCtrlPoints_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_SurfaceWithHighNumberOfCtrlPoints_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_SurfaceWithHighNumberOfCtrlPoints_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	//void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	CATLONG32  Get_MaxNumberOfCtrlPoints();

	/** @nodoc @nocgmitf */
	CATLONG32  Get_MaxNumberOfCtrlPointsInParamDir();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATLONG32 _MaxNumberOfCtrlPoints;

	/** @nodoc @nocgmitf */
	CATLONG32 _MaxNumberOfCtrlPointsInParamDir;

	/** @nodoc @nocgmitf */
	//CATBoolean _DoCheckInParameterDirection;

	/** @nodoc @nocgmitf */
	CATCGMFace_SurfaceWithHighNumberOfCtrlPoints_Anomaly(const CATCGMFace_SurfaceWithHighNumberOfCtrlPoints_Anomaly& iCGMFace_SurfaceWithHighNumberOfCtrlPoints_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_SurfaceWithHighNumberOfCtrlPoints_Anomaly&  operator = (const CATCGMFace_SurfaceWithHighNumberOfCtrlPoints_Anomaly& iFace_SurfaceWithHighNumberOfCtrlPoints_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMSurface_MultiFaces_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMSurface_MultiFaces_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMSurface_MultiFaces_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckSkinBody();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckSolidBody();

		/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATBoolean _CheckSkinBody;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckSolidBody;
	/** @nodoc @nocgmitf */
	CATCGMSurface_MultiFaces_Anomaly(const CATCGMSurface_MultiFaces_Anomaly& iCGMSurface_MultiFaces_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMSurface_MultiFaces_Anomaly&  operator = (const CATCGMSurface_MultiFaces_Anomaly& iSurface_MultiFaces_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_Tolerance();
	
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _Tolerance;
	/** @nodoc @nocgmitf */
	CATCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly(const CATCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly& iCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly&  operator = (const CATCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly& iFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMSurface_UnusedPatches_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMSurface_UnusedPatches_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMSurface_UnusedPatches_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMSurface_UnusedPatches_Anomaly(const CATCGMSurface_UnusedPatches_Anomaly& iCGMEdge_WithAnalyticalOrProceduralCurve_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMSurface_UnusedPatches_Anomaly&  operator = (const CATCGMSurface_UnusedPatches_Anomaly& iEdge_WithAnalyticalOrProceduralCurve_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_SharpAngleOnAdjacentEdges_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_SharpAngleOnAdjacentEdges_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_SharpAngleOnAdjacentEdges_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinAngleDeg();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckWireDomain();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckLoopDomain();
	
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _MinAngleDeg;	
	/** @nodoc @nocgmitf */
	CATBoolean _CheckWireDomain;
		/** @nodoc @nocgmitf */
	CATBoolean _CheckLoopDomain;
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_SharpAngleOnAdjacentEdges_Anomaly(const CATCGMEdgeDomain_SharpAngleOnAdjacentEdges_Anomaly& iCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_SharpAngleOnAdjacentEdges_Anomaly&  operator = (const CATCGMEdgeDomain_SharpAngleOnAdjacentEdges_Anomaly& iFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_ConfusedExtremities_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_ConfusedExtremities_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_ConfusedExtremities_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_Tolerance();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	double _Tolerance;
	/** @nodoc @nocgmitf */
	CATCGMEdge_ConfusedExtremities_Anomaly(const CATCGMEdge_ConfusedExtremities_Anomaly& iCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_ConfusedExtremities_Anomaly&  operator = (const CATCGMEdge_ConfusedExtremities_Anomaly& iFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_WavyPlanarCurve_Anomaly : public CATCGMEdge_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_WavyPlanarCurve_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_WavyPlanarCurve_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);
		
	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
		
	/** @nodoc @nocgmitf */
	CATLONG32 Get_NbArcsPerGroup();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_MaxNbInflectionPts();

	/** @nodoc @nocgmitf */
	double Get_InfiniteCurvatureRadius();
	
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATLONG32 _NbArcsPerGroup;
	/** @nodoc @nocgmitf */
	CATLONG32 _MaxNbInflectionPts;
	/** @nodoc @nocgmitf */
	double _InfiniteCurvatureRadius;
	/** @nodoc @nocgmitf */
	CATCGMEdge_WavyPlanarCurve_Anomaly(const CATCGMEdge_WavyPlanarCurve_Anomaly& iCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_WavyPlanarCurve_Anomaly&  operator = (const CATCGMEdge_WavyPlanarCurve_Anomaly& iFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_DegeneratedBoundaryPatchLength_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_DegeneratedBoundaryPatchLength_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_DegeneratedBoundaryPatchLength_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;
		
	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinLength();

	/** @nodoc @nocgmitf */
	double Get_MaxLength();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckOnlyPatchBoundaryLength();	

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

private:
	/** @nodoc @nocgmitf */
	double		_MinLength;
	/** @nodoc @nocgmitf */
	double		_MaxLength;
	/** @nodoc @nocgmitf */
	CATBoolean	_CheckOnlyPatchBoundaryLength;
	/** @nodoc @nocgmitf */
	CATCGMFace_DegeneratedBoundaryPatchLength_Anomaly(const CATCGMFace_DegeneratedBoundaryPatchLength_Anomaly& iCGMFace_LengthAreaDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_DegeneratedBoundaryPatchLength_Anomaly&  operator = (const CATCGMFace_DegeneratedBoundaryPatchLength_Anomaly& iFace_DegeneratedBoundaryPatchLength_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_PatchSurfaceSharpnessAngle_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_PatchSurfaceSharpnessAngle_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_PatchSurfaceSharpnessAngle_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;
		
	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinAngleCorner();

	/** @nodoc @nocgmitf */
	double Get_MaxAngleCorner();

	/** @nodoc @nocgmitf */
	double Get_MinAnglePseudoCorner();

	/** @nodoc @nocgmitf */
	double Get_MaxAnglePseudoCorner();

	/** @nodoc @nocgmitf */
	double Get_MinLengthPatchBoundary();

	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckOnlyFaceArea();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

private:
	/** @nodoc @nocgmitf */
	double _MinAngleCorner;
	/** @nodoc @nocgmitf */
	double _MaxAngleCorner;
	/** @nodoc @nocgmitf */
	double _MinAnglePseudoCorner;
	/** @nodoc @nocgmitf */
	double _MaxAnglePseudoCorner;
	/** @nodoc @nocgmitf */
	double _MinLengthPatchBoundary;
	/** @nodoc @nocgmitf */
	CATBoolean _CheckOnlyFaceArea;
	/** @nodoc @nocgmitf */
	CATCGMFace_PatchSurfaceSharpnessAngle_Anomaly(const CATCGMFace_PatchSurfaceSharpnessAngle_Anomaly& iCGMFace_LengthAreaDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_PatchSurfaceSharpnessAngle_Anomaly&  operator = (const CATCGMFace_PatchSurfaceSharpnessAngle_Anomaly& iFace_PatchSurfaceSharpnessAngle_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_PatchSurfaceUndefinedNormal_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_PatchSurfaceUndefinedNormal_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_PatchSurfaceUndefinedNormal_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;
		
	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

	/** @nodoc @nocgmitf */
	double Get_MinLengthOfNormal();

	/** @nodoc @nocgmitf */
	double Get_MinLengthPatchBoundary();

	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

private:
	/** @nodoc @nocgmitf */
	double _MinLengthOfNormal;
	/** @nodoc @nocgmitf */
	double _MinLengthPatchBoundary;
	/** @nodoc @nocgmitf */
	CATCGMFace_PatchSurfaceUndefinedNormal_Anomaly(const CATCGMFace_PatchSurfaceUndefinedNormal_Anomaly& iCGMFace_LengthAreaDegenerated_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_PatchSurfaceUndefinedNormal_Anomaly&  operator = (const CATCGMFace_PatchSurfaceUndefinedNormal_Anomaly& iFace_PatchSurfaceUndefinedNormal_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_BigCurvatureRadius_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_BigCurvatureRadius_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_BigCurvatureRadius_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;
	
	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);	

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
	
	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

	/** @nodoc @nocgmitf */
	double Get_MaxCurvatureRadius();

	/** @nodoc @nocgmitf */
	double Get_MinLengthOfNormal();
	
protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	double _MaxCurvatureRadius;
	double _MinLengthOfNormal;

	/** @nodoc @nocgmitf */
	CATCGMFace_BigCurvatureRadius_Anomaly(const CATCGMFace_BigCurvatureRadius_Anomaly& iCGMFace_MaxCurvatureRadius_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_BigCurvatureRadius_Anomaly&  operator = (const CATCGMFace_BigCurvatureRadius_Anomaly& iCGMFace_MaxCurvatureRadius_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_WavySurface_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_WavySurface_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_WavySurface_Anomaly(){};

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	void SetParameter(CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);
		
	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();
		
	/** @nodoc @nocgmitf */
	CATBoolean Get_CheckOnArcOrIsoParamCrv();

	/** @nodoc @nocgmitf */
	CATLONG32 Get_MaxNbInflectionPts();

	/** @nodoc @nocgmitf */
	double Get_InfiniteCurvatureRadius();
	
	/** @nodoc @nocgmitf */
	virtual void Write(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	virtual void Read(CATCGMStream& Str,short iVersion);

	/** @nodoc @nocgmitf */
	void Dump(CATCGMOutput& ioCGMStr);

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATBoolean _CheckOnArcOrIsoParamCrv;
	/** @nodoc @nocgmitf */
	CATLONG32 _MaxNbInflectionPts;
	/** @nodoc @nocgmitf */
	double _InfiniteCurvatureRadius;
	/** @nodoc @nocgmitf */
	CATCGMFace_WavySurface_Anomaly(const CATCGMFace_WavySurface_Anomaly& iCGMFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_WavySurface_Anomaly&  operator = (const CATCGMFace_WavySurface_Anomaly& iFace_PlanarSurfaceWithOverSizedPolDeg_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_SelfIntersection_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_SelfIntersection_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_SelfIntersection_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_SelfIntersection_Anomaly(const CATCGMFace_SelfIntersection_Anomaly& iCGMFace_SelfIntersection_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_SelfIntersection_Anomaly&  operator = (const CATCGMFace_SelfIntersection_Anomaly& iCGMFace_SelfIntersection_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_InvalidEdgeOrientation_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_InvalidEdgeOrientation_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_InvalidEdgeOrientation_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_InvalidEdgeOrientation_Anomaly(const CATCGMEdgeDomain_InvalidEdgeOrientation_Anomaly& iCGMEdgeDomain_InvalidEdgeOrientation_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_InvalidEdgeOrientation_Anomaly&  operator = (const CATCGMEdgeDomain_InvalidEdgeOrientation_Anomaly& iCGMEdgeDomain_InvalidEdgeOrientation_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_InconsistentEdgeOrientation_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
  /** @nodoc @nocgmitf */
  CATCGMEdgeDomain_InconsistentEdgeOrientation_Anomaly();

  /** @nodoc @nocgmitf */
  virtual ~CATCGMEdgeDomain_InconsistentEdgeOrientation_Anomaly() {};

  CATCGMNewClassArrayDeclare;

  /** @nodoc @nocgmitf */
  CATCGMExplicitCheckAnomaly GetLabel();

protected:
  /** @nodoc @nocgmitf */
  //CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
  /** @nodoc @nocgmitf */
  CATCGMEdgeDomain_InconsistentEdgeOrientation_Anomaly(const CATCGMEdgeDomain_InconsistentEdgeOrientation_Anomaly& iCGMEdgeDomain_InconsistentEdgeOrientation_Anomaly);

  /** @nodoc @nocgmitf */
  CATCGMEdgeDomain_InconsistentEdgeOrientation_Anomaly&  operator = (const CATCGMEdgeDomain_InconsistentEdgeOrientation_Anomaly& iCGMEdgeDomain_InconsistentEdgeOrientation_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_AdjacentEdgesImproperlyConnected_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_AdjacentEdgesImproperlyConnected_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_AdjacentEdgesImproperlyConnected_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_AdjacentEdgesImproperlyConnected_Anomaly(const CATCGMEdgeDomain_AdjacentEdgesImproperlyConnected_Anomaly& iCGMEdgeDomain_AdjacentEdgesImproperlyConnected_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_AdjacentEdgesImproperlyConnected_Anomaly&  operator = (const CATCGMEdgeDomain_AdjacentEdgesImproperlyConnected_Anomaly& iCGMEdgeDomain_AdjacentEdgesImproperlyConnected_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdgeDomain_WithoutEdges_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_WithoutEdges_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdgeDomain_WithoutEdges_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_WithoutEdges_Anomaly(const CATCGMEdgeDomain_WithoutEdges_Anomaly& iCGMEdgeDomain_WithoutEdges_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdgeDomain_WithoutEdges_Anomaly&  operator = (const CATCGMEdgeDomain_WithoutEdges_Anomaly& iCGMEdgeDomain_WithoutEdges_Anomaly);
};

///** @nodoc @nocgmitf */
//class CATCGMEdgeDomain_CellsDisconnected_Anomaly : public CATExplicitCheck_AnomalyBase
//{
//public:
//  /** @nodoc @nocgmitf */
//  CATCGMEdgeDomain_CellsDisconnected_Anomaly();
//
//  /** @nodoc @nocgmitf */
//  virtual ~CATCGMEdgeDomain_CellsDisconnected_Anomaly(){};
//
//  CATCGMNewClassArrayDeclare;
//
//  /** @nodoc @nocgmitf */
//  CATCGMExplicitCheckAnomaly GetLabel();
//
//protected:
//  /** @nodoc @nocgmitf */
//  //CATExplicitCheck_AnomalyBase *SecureCastTo();
//private:
//  /** @nodoc @nocgmitf */
//  CATCGMEdgeDomain_CellsDisconnected_Anomaly(const CATCGMEdgeDomain_CellsDisconnected_Anomaly& iCGMEdgeDomain_CellsDisconnected_Anomaly);
//
//  /** @nodoc @nocgmitf */
//  CATCGMEdgeDomain_CellsDisconnected_Anomaly&  operator = (const CATCGMEdgeDomain_CellsDisconnected_Anomaly& iCGMEdgeDomain_CellsDisconnected_Anomaly);
//};

/** @nodoc @nocgmitf */
class CATCGMVertex_WithoutMacroPoint_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMVertex_WithoutMacroPoint_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMVertex_WithoutMacroPoint_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMVertex_WithoutMacroPoint_Anomaly(const CATCGMVertex_WithoutMacroPoint_Anomaly& iCGMVertex_WithoutMacroPoint_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMVertex_WithoutMacroPoint_Anomaly&  operator = (const CATCGMVertex_WithoutMacroPoint_Anomaly& iCGMVertex_WithoutMacroPoint_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_VertexOutsideBoundingBox_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_VertexOutsideBoundingBox_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_VertexOutsideBoundingBox_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMBody_VertexOutsideBoundingBox_Anomaly(const CATCGMBody_VertexOutsideBoundingBox_Anomaly& iCGMBody_VertexOutsideBoundingBox_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_VertexOutsideBoundingBox_Anomaly&  operator = (const CATCGMBody_VertexOutsideBoundingBox_Anomaly& iCGMBody_VertexOutsideBoundingBox_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_BoundingBoxEmpty_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_BoundingBoxEmpty_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_BoundingBoxEmpty_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_BoundingBoxEmpty_Anomaly(const CATCGMEdge_BoundingBoxEmpty_Anomaly& iCGMEdge_BoundingBoxEmpty_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_BoundingBoxEmpty_Anomaly&  operator = (const CATCGMEdge_BoundingBoxEmpty_Anomaly& iCGMEdge_BoundingBoxEmpty_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_IncorrectDomainType_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_IncorrectDomainType_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_IncorrectDomainType_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMBody_IncorrectDomainType_Anomaly(const CATCGMBody_IncorrectDomainType_Anomaly& iCGMBody_IncorrectDomainType_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_IncorrectDomainType_Anomaly&  operator = (const CATCGMBody_IncorrectDomainType_Anomaly& iCGMBody_IncorrectDomainType_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_InvalidDomainLocation_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_InvalidDomainLocation_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_InvalidDomainLocation_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMBody_InvalidDomainLocation_Anomaly(const CATCGMBody_InvalidDomainLocation_Anomaly& iCGMBody_InvalidDomainLocation_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_InvalidDomainLocation_Anomaly&  operator = (const CATCGMBody_InvalidDomainLocation_Anomaly& iCGMBody_InvalidDomainLocation_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_OverlappingEdges_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_OverlappingEdges_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_OverlappingEdges_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMBody_OverlappingEdges_Anomaly(const CATCGMBody_OverlappingEdges_Anomaly& iCGMBody_OverlappingEdges_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_OverlappingEdges_Anomaly&  operator = (const CATCGMBody_OverlappingEdges_Anomaly& iCGMBody_OverlappingEdges_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_EdgeCurveInvalid_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_EdgeCurveInvalid_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_EdgeCurveInvalid_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_EdgeCurveInvalid_Anomaly(const CATCGMEdge_EdgeCurveInvalid_Anomaly& iCGMEdge_EdgeCurveInvalid_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_EdgeCurveInvalid_Anomaly&  operator = (const CATCGMEdge_EdgeCurveInvalid_Anomaly& iCGMEdge_EdgeCurveInvalid_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_OutsideEdgeCurveMaxLimitsComplex_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsideEdgeCurveMaxLimitsComplex_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_OutsideEdgeCurveMaxLimitsComplex_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsideEdgeCurveMaxLimitsComplex_Anomaly(const CATCGMPOEC_OutsideEdgeCurveMaxLimitsComplex_Anomaly& iCGMPOEC_OutsideEdgeCurveMaxLimitsComplex_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsideEdgeCurveMaxLimitsComplex_Anomaly&  operator = (const CATCGMPOEC_OutsideEdgeCurveMaxLimitsComplex_Anomaly& iCGMPOEC_OutsideEdgeCurveMaxLimitsComplex_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_OutsideEdgeCurveMaxLimitsHigh_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsideEdgeCurveMaxLimitsHigh_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_OutsideEdgeCurveMaxLimitsHigh_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsideEdgeCurveMaxLimitsHigh_Anomaly(const CATCGMPOEC_OutsideEdgeCurveMaxLimitsHigh_Anomaly& iCGMPOEC_OutsideEdgeCurveMaxLimitsHigh_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsideEdgeCurveMaxLimitsHigh_Anomaly&  operator = (const CATCGMPOEC_OutsideEdgeCurveMaxLimitsHigh_Anomaly& iCGMPOEC_OutsideEdgeCurveMaxLimitsHigh_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_OutsideEdgeCurveMaxLimitsLow_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsideEdgeCurveMaxLimitsLow_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_OutsideEdgeCurveMaxLimitsLow_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsideEdgeCurveMaxLimitsLow_Anomaly(const CATCGMPOEC_OutsideEdgeCurveMaxLimitsLow_Anomaly& iCGMPOEC_OutsideEdgeCurveMaxLimitsLow_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsideEdgeCurveMaxLimitsLow_Anomaly&  operator = (const CATCGMPOEC_OutsideEdgeCurveMaxLimitsLow_Anomaly& iCGMPOEC_OutsideEdgeCurveMaxLimitsLow_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMShell_AdjacentFacesInconsistentOrientation_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMShell_AdjacentFacesInconsistentOrientation_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMShell_AdjacentFacesInconsistentOrientation_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMShell_AdjacentFacesInconsistentOrientation_Anomaly(const CATCGMShell_AdjacentFacesInconsistentOrientation_Anomaly& iCGMShell_AdjacentFacesInconsistentOrientation_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMShell_AdjacentFacesInconsistentOrientation_Anomaly&  operator = (const CATCGMShell_AdjacentFacesInconsistentOrientation_Anomaly& iCGMShell_AdjacentFacesInconsistentOrientation_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMShell_NonManifoldEdge_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMShell_NonManifoldEdge_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMShell_NonManifoldEdge_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMShell_NonManifoldEdge_Anomaly(const CATCGMShell_NonManifoldEdge_Anomaly& iCGMShell_NonManifoldEdge_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMShell_NonManifoldEdge_Anomaly&  operator = (const CATCGMShell_NonManifoldEdge_Anomaly& iCGMShell_NonManifoldEdge_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMVolume_FreeEdge_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMVolume_FreeEdge_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMVolume_FreeEdge_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMVolume_FreeEdge_Anomaly(const CATCGMVolume_FreeEdge_Anomaly& iCGMVolume_FreeEdge_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMVolume_FreeEdge_Anomaly&  operator = (const CATCGMVolume_FreeEdge_Anomaly& iCGMVolume_FreeEdge_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMShell_WithoutFaces_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMShell_WithoutFaces_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMShell_WithoutFaces_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMShell_WithoutFaces_Anomaly(const CATCGMShell_WithoutFaces_Anomaly& iCGMShell_WithoutFaces_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMShell_WithoutFaces_Anomaly&  operator = (const CATCGMShell_WithoutFaces_Anomaly& iCGMShell_WithoutFaces_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMShell_FaceOverReferenced_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMShell_FaceOverReferenced_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMShell_FaceOverReferenced_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMShell_FaceOverReferenced_Anomaly(const CATCGMShell_FaceOverReferenced_Anomaly& iCGMShell_FaceOverReferenced_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMShell_FaceOverReferenced_Anomaly&  operator = (const CATCGMShell_FaceOverReferenced_Anomaly& iCGMShell_FaceOverReferenced_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_POECOutsideUFaceBoundingBox_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideUFaceBoundingBox_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_POECOutsideUFaceBoundingBox_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideUFaceBoundingBox_Anomaly(const CATCGMLoop_POECOutsideUFaceBoundingBox_Anomaly& iCGMLoop_POECOutsideUFaceBoundingBox_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideUFaceBoundingBox_Anomaly&  operator = (const CATCGMLoop_POECOutsideUFaceBoundingBox_Anomaly& iCGMLoop_POECOutsideUFaceBoundingBox_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_POECOutsideVFaceBoundingBox_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideVFaceBoundingBox_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_POECOutsideVFaceBoundingBox_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideVFaceBoundingBox_Anomaly(const CATCGMLoop_POECOutsideVFaceBoundingBox_Anomaly& iCGMLoop_POECOutsideVFaceBoundingBox_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideVFaceBoundingBox_Anomaly&  operator = (const CATCGMLoop_POECOutsideVFaceBoundingBox_Anomaly& iCGMLoop_POECOutsideVFaceBoundingBox_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces_Anomaly(const CATCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces_Anomaly& iCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces_Anomaly&  operator = (const CATCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces_Anomaly& iCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_MatterSideInvalid_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_MatterSideInvalid_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_MatterSideInvalid_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_MatterSideInvalid_Anomaly(const CATCGMLoop_MatterSideInvalid_Anomaly& iCGMLoop_MatterSideInvalid_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_MatterSideInvalid_Anomaly&  operator = (const CATCGMLoop_MatterSideInvalid_Anomaly& iCGMLoop_MatterSideInvalid_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMDomain_CellsDisconnected_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMDomain_CellsDisconnected_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMDomain_CellsDisconnected_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMDomain_CellsDisconnected_Anomaly(const CATCGMDomain_CellsDisconnected_Anomaly& iCGMDomain_CellsDisconnected_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMDomain_CellsDisconnected_Anomaly&  operator = (const CATCGMDomain_CellsDisconnected_Anomaly& iCGMDomain_CellsDisconnected_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMMacroPoint_WithoutPoints_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMMacroPoint_WithoutPoints_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMMacroPoint_WithoutPoints_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMMacroPoint_WithoutPoints_Anomaly(const CATCGMMacroPoint_WithoutPoints_Anomaly& iCGMMacroPoint_WithoutPoints_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMMacroPoint_WithoutPoints_Anomaly&  operator = (const CATCGMMacroPoint_WithoutPoints_Anomaly& iCGMMacroPoint_WithoutPoints_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_WithoutPOEC_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_WithoutPOEC_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_WithoutPOEC_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_WithoutPOEC_Anomaly(const CATCGMEdge_WithoutPOEC_Anomaly& iCGMEdge_WithoutPOEC_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_WithoutPOEC_Anomaly&  operator = (const CATCGMEdge_WithoutPOEC_Anomaly& iCGMEdge_WithoutPOEC_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_WithoutVertex_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_WithoutVertex_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_WithoutVertex_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_WithoutVertex_Anomaly(const CATCGMEdge_WithoutVertex_Anomaly& iCGMEdge_WithoutVertex_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_WithoutVertex_Anomaly&  operator = (const CATCGMEdge_WithoutVertex_Anomaly& iCGMEdge_WithoutVertex_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLump_WithoutVolumes_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLump_WithoutVolumes_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLump_WithoutVolumes_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLump_WithoutVolumes_Anomaly(const CATCGMLump_WithoutVolumes_Anomaly& iCGMLump_WithoutVolumes_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLump_WithoutVolumes_Anomaly&  operator = (const CATCGMLump_WithoutVolumes_Anomaly& iCGMLump_WithoutVolumes_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_WithoutLoops_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_WithoutLoops_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_WithoutLoops_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_WithoutLoops_Anomaly(const CATCGMFace_WithoutLoops_Anomaly& iCGMFace_WithoutLoops_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_WithoutLoops_Anomaly&  operator = (const CATCGMFace_WithoutLoops_Anomaly& iCGMFace_WithoutLoops_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_FirstLoopNotOuter_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_FirstLoopNotOuter_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_FirstLoopNotOuter_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_FirstLoopNotOuter_Anomaly(const CATCGMFace_FirstLoopNotOuter_Anomaly& iCGMFace_FirstLoopNotOuter_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_FirstLoopNotOuter_Anomaly&  operator = (const CATCGMFace_FirstLoopNotOuter_Anomaly& iCGMFace_FirstLoopNotOuter_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_NonFirstLoopNotInner_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMFace_NonFirstLoopNotInner_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMFace_NonFirstLoopNotInner_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMFace_NonFirstLoopNotInner_Anomaly(const CATCGMFace_NonFirstLoopNotInner_Anomaly& iCGMFace_NonFirstLoopNotInner_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMFace_NonFirstLoopNotInner_Anomaly&  operator = (const CATCGMFace_NonFirstLoopNotInner_Anomaly& iCGMFace_NonFirstLoopNotInner_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_Closed_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
  /** @nodoc @nocgmitf */
  CATCGMFace_Closed_Anomaly();

  /** @nodoc @nocgmitf */
  virtual ~CATCGMFace_Closed_Anomaly() {};

  CATCGMNewClassArrayDeclare;

  /** @nodoc @nocgmitf */
  CATCGMExplicitCheckAnomaly GetLabel();

protected:
  /** @nodoc @nocgmitf */
  //CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
  /** @nodoc @nocgmitf */
  CATCGMFace_Closed_Anomaly(const CATCGMFace_Closed_Anomaly& iCGMFace_Closed_Anomaly);

  /** @nodoc @nocgmitf */
  CATCGMFace_Closed_Anomaly&  operator = (const CATCGMFace_Closed_Anomaly& iCGMFace_Closed_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMFace_InconsistentOrientationOnSurface_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
  /** @nodoc @nocgmitf */
  CATCGMFace_InconsistentOrientationOnSurface_Anomaly();

  /** @nodoc @nocgmitf */
  virtual ~CATCGMFace_InconsistentOrientationOnSurface_Anomaly() {};

  CATCGMNewClassArrayDeclare;

  /** @nodoc @nocgmitf */
  CATCGMExplicitCheckAnomaly GetLabel();

protected:
  /** @nodoc @nocgmitf */
  //CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
  /** @nodoc @nocgmitf */
  CATCGMFace_InconsistentOrientationOnSurface_Anomaly(const CATCGMFace_InconsistentOrientationOnSurface_Anomaly& iCGMFace_InconsistentOrientationOnSurface_Anomaly);

  /** @nodoc @nocgmitf */
  CATCGMFace_InconsistentOrientationOnSurface_Anomaly&  operator = (const CATCGMFace_InconsistentOrientationOnSurface_Anomaly& iCGMFace_InconsistentOrientationOnSurface_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_UVBoundingBoxEmpty_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_UVBoundingBoxEmpty_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_UVBoundingBoxEmpty_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_UVBoundingBoxEmpty_Anomaly(const CATCGMLoop_UVBoundingBoxEmpty_Anomaly& iCGMLoop_UVBoundingBoxEmpty_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_UVBoundingBoxEmpty_Anomaly&  operator = (const CATCGMLoop_UVBoundingBoxEmpty_Anomaly& iCGMLoop_UVBoundingBoxEmpty_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_POECOutsideUBoundingBox_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideUBoundingBox_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_POECOutsideUBoundingBox_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideUBoundingBox_Anomaly(const CATCGMLoop_POECOutsideUBoundingBox_Anomaly& iCGMLoop_POECOutsideUBoundingBox_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideUBoundingBox_Anomaly&  operator = (const CATCGMLoop_POECOutsideUBoundingBox_Anomaly& iCGMLoop_POECOutsideUBoundingBox_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_POECOutsideVBoundingBox_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideVBoundingBox_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_POECOutsideVBoundingBox_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideVBoundingBox_Anomaly(const CATCGMLoop_POECOutsideVBoundingBox_Anomaly& iCGMLoop_POECOutsideVBoundingBox_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideVBoundingBox_Anomaly&  operator = (const CATCGMLoop_POECOutsideVBoundingBox_Anomaly& iCGMLoop_POECOutsideVBoundingBox_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_POECUVGap_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECUVGap_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_POECUVGap_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECUVGap_Anomaly(const CATCGMLoop_POECUVGap_Anomaly& iCGMLoop_POECUVGap_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_POECUVGap_Anomaly&  operator = (const CATCGMLoop_POECUVGap_Anomaly& iCGMLoop_POECUVGap_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_POECOutsideMaxLimitsU_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideMaxLimitsU_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_POECOutsideMaxLimitsU_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideMaxLimitsU_Anomaly(const CATCGMLoop_POECOutsideMaxLimitsU_Anomaly& iCGMLoop_POECOutsideMaxLimitsU_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideMaxLimitsU_Anomaly&  operator = (const CATCGMLoop_POECOutsideMaxLimitsU_Anomaly& iCGMLoop_POECOutsideMaxLimitsU_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_POECOutsideMaxLimitsV_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideMaxLimitsV_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_POECOutsideMaxLimitsV_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideMaxLimitsV_Anomaly(const CATCGMLoop_POECOutsideMaxLimitsV_Anomaly& iCGMLoop_POECOutsideMaxLimitsV_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_POECOutsideMaxLimitsV_Anomaly&  operator = (const CATCGMLoop_POECOutsideMaxLimitsV_Anomaly& iCGMLoop_POECOutsideMaxLimitsV_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMDomain_MultipleOwnersInsideBody_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMDomain_MultipleOwnersInsideBody_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMDomain_MultipleOwnersInsideBody_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMDomain_MultipleOwnersInsideBody_Anomaly(const CATCGMDomain_MultipleOwnersInsideBody_Anomaly& iCGMDomain_MultipleOwnersInsideBody_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMDomain_MultipleOwnersInsideBody_Anomaly&  operator = (const CATCGMDomain_MultipleOwnersInsideBody_Anomaly& iCGMDomain_MultipleOwnersInsideBody_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_OutsidePCurveMaxLimitsComplex_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsidePCurveMaxLimitsComplex_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_OutsidePCurveMaxLimitsComplex_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsidePCurveMaxLimitsComplex_Anomaly(const CATCGMPOEC_OutsidePCurveMaxLimitsComplex_Anomaly& iCGMPOEC_OutsidePCurveMaxLimitsComplex_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsidePCurveMaxLimitsComplex_Anomaly&  operator = (const CATCGMPOEC_OutsidePCurveMaxLimitsComplex_Anomaly& iCGMPOEC_OutsidePCurveMaxLimitsComplex_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_OutsidePCurveMaxLimitsHigh_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsidePCurveMaxLimitsHigh_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_OutsidePCurveMaxLimitsHigh_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsidePCurveMaxLimitsHigh_Anomaly(const CATCGMPOEC_OutsidePCurveMaxLimitsHigh_Anomaly& iCGMPOEC_OutsidePCurveMaxLimitsHigh_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsidePCurveMaxLimitsHigh_Anomaly&  operator = (const CATCGMPOEC_OutsidePCurveMaxLimitsHigh_Anomaly& iCGMPOEC_OutsidePCurveMaxLimits_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_OutsidePCurveMaxLimitsLow_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsidePCurveMaxLimitsLow_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_OutsidePCurveMaxLimitsLow_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsidePCurveMaxLimitsLow_Anomaly(const CATCGMPOEC_OutsidePCurveMaxLimitsLow_Anomaly& iCGMPOEC_OutsidePCurveMaxLimitsLow_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_OutsidePCurveMaxLimitsLow_Anomaly&  operator = (const CATCGMPOEC_OutsidePCurveMaxLimitsLow_Anomaly& iCGMPOEC_OutsidePCurveMaxLimitsLow_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMLoop_PCurveAndFaceSupportDistinct_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMLoop_PCurveAndFaceSupportDistinct_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMLoop_PCurveAndFaceSupportDistinct_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMLoop_PCurveAndFaceSupportDistinct_Anomaly(const CATCGMLoop_PCurveAndFaceSupportDistinct_Anomaly& iCGMLoop_PCurveAndFaceSupportDistinct_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMLoop_PCurveAndFaceSupportDistinct_Anomaly&  operator = (const CATCGMLoop_PCurveAndFaceSupportDistinct_Anomaly& iCGMLoop_PCurveAndFaceSupportDistinct_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex_Anomaly(const CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex_Anomaly& iCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex_Anomaly&  operator = (const CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex_Anomaly& iCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh_Anomaly(const CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh_Anomaly& iCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh_Anomaly&  operator = (const CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh_Anomaly& iCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow_Anomaly(const CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow_Anomaly& iCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow_Anomaly&  operator = (const CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow_Anomaly& iCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_WrongPOECOrientation_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_WrongPOECOrientation_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_WrongPOECOrientation_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_WrongPOECOrientation_Anomaly(const CATCGMEdge_WrongPOECOrientation_Anomaly& iCGMEdge_WrongPOECOrientation_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_WrongPOECOrientation_Anomaly&  operator = (const CATCGMEdge_WrongPOECOrientation_Anomaly& iCGMEdge_WrongPOECOrientation_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMEdge_CachedMaxGapIncorrect_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMEdge_CachedMaxGapIncorrect_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMEdge_CachedMaxGapIncorrect_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMEdge_CachedMaxGapIncorrect_Anomaly(const CATCGMEdge_CachedMaxGapIncorrect_Anomaly& iCGMEdge_CachedMaxGapIncorrect_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMEdge_CachedMaxGapIncorrect_Anomaly&  operator = (const CATCGMEdge_CachedMaxGapIncorrect_Anomaly& iCGMEdge_CachedMaxGapIncorrect_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMBody_OverlappingVertices_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMBody_OverlappingVertices_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMBody_OverlappingVertices_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMBody_OverlappingVertices_Anomaly(const CATCGMBody_OverlappingVertices_Anomaly& iCGMBody_OverlappingVertices_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMBody_OverlappingVertices_Anomaly&  operator = (const CATCGMBody_OverlappingVertices_Anomaly& iCGMBody_OverlappingVertices_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMVertexInFace_WithoutVertex_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMVertexInFace_WithoutVertex_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMVertexInFace_WithoutVertex_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMVertexInFace_WithoutVertex_Anomaly(const CATCGMVertexInFace_WithoutVertex_Anomaly& iCGMVertexInFace_WithoutVertex_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMVertexInFace_WithoutVertex_Anomaly&  operator = (const CATCGMVertexInFace_WithoutVertex_Anomaly& iCGMVertexInFace_WithoutVertex_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMVertexInFace_InvalidLocation_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMVertexInFace_InvalidLocation_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMVertexInFace_InvalidLocation_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMVertexInFace_InvalidLocation_Anomaly(const CATCGMVertexInFace_InvalidLocation_Anomaly& iCGMVertexInFace_InvalidLocation_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMVertexInFace_InvalidLocation_Anomaly&  operator = (const CATCGMVertexInFace_InvalidLocation_Anomaly& iCGMVertexInFace_InvalidLocation_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMVertexInVolume_WithoutVertex_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMVertexInVolume_WithoutVertex_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMVertexInVolume_WithoutVertex_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMVertexInVolume_WithoutVertex_Anomaly(const CATCGMVertexInVolume_WithoutVertex_Anomaly& iCGMVertexInVolume_WithoutVertex_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMVertexInVolume_WithoutVertex_Anomaly&  operator = (const CATCGMVertexInVolume_WithoutVertex_Anomaly& iCGMVertexInVolume_WithoutVertex_Anomaly);
};

/** @nodoc @nocgmitf */
class CATCGMVolume_WithoutShell_Anomaly : public CATExplicitCheck_AnomalyBase
{
public:
	/** @nodoc @nocgmitf */
	CATCGMVolume_WithoutShell_Anomaly();

	/** @nodoc @nocgmitf */
	virtual ~CATCGMVolume_WithoutShell_Anomaly(){};
		
	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATCGMExplicitCheckAnomaly GetLabel();

protected:
	/** @nodoc @nocgmitf */
	//CATExplicitCheck_AnomalyBase *SecureCastTo();
private:
	/** @nodoc @nocgmitf */
	CATCGMVolume_WithoutShell_Anomaly(const CATCGMVolume_WithoutShell_Anomaly& iCGMVolume_WithoutShell_Anomaly);

	/** @nodoc @nocgmitf */
	CATCGMVolume_WithoutShell_Anomaly&  operator = (const CATCGMVolume_WithoutShell_Anomaly& iCGMVolume_WithoutShell_Anomaly);
};

#endif

