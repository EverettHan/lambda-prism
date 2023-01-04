#ifndef __CATExplicitCheck_SetOfAnomalies__
#define __CATExplicitCheck_SetOfAnomalies__

//===========================================================================  
// COPYRIGHT DASSAULT SYSTEMES  2013
//===========================================================================  
//
//--------------------------------------------------------------------------- 
//  Class  CATExplicitCheck_SetOfAnomalies                 
//---------------------------------------------------------------------------  
//
//  Role :
//	   Store and Manage a collection of Specific Anomalies selected
//
//    
//  Services  
//        1 -  
//        2 -  
//        3 -  
//        4 -   
//            
//=============================================================================  
// 25 Jul 2013   Creation                                                  KY1
//
//  
//============================================================================= 

/* @nodoc @nocgmitf */
#include "CATPGMExplicitReport.h"
#include "CATCGMNewArray.h"
#include "CATExplicitLabelParameter.h"
#include "CATBoolean.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"

class CATExplicitCheck_AnomalyBase;
class CATExplicitCheck_HashTableOfAnomalyBase;

/** @nodoc @nocgmitf */
class CATExplicitCheck_SetOfAnomalies
{
public:

	CATCGMNewClassArrayDeclare;

	/** @nodoc @nocgmitf */
	CATExplicitCheck_SetOfAnomalies();

	/** @nodoc @nocgmitf */
	virtual ~CATExplicitCheck_SetOfAnomalies(); 

	/** @nodoc @nocgmitf */
	/**
	* Set parameter for a selected anomaly
	* @param iLabelAnomaly 
	*   the Anomaly unde scope.
	* @param iParam
	*   the parameter value to set.
	* @param iExplicitLabelParam
	*   the label of parameter to set.
	*/
	void SetParameter(CATCGMExplicitCheckAnomaly iLabelAnomaly, CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

	/** @nodoc @nocgmitf */
	/**
	* Set parameter for a selected anomaly
	* @param iLabelAnomaly 
	*   the Anomaly unde scope.
	* @param iParam
	*   the parameter value to set.
	* @param iExplicitLabelParam
	*   the label of parameter to set.
	*/
	void SetParameter(CATCGMExplicitCheckAnomaly iLabelAnomaly, CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

	/** @nodoc @nocgmitf */
	/**
	* Set parameter for a selected anomaly
	* @param iLabelAnomaly 
	*   the Anomaly unde scope.
	* @param iParam
	*   the parameter value to set.
	* @param iExplicitLabelParam
	*   the label of parameter to set.
	*/
	void SetParameter(CATCGMExplicitCheckAnomaly iLabelAnomaly, CATExplicitLabelParameter iExplicitLabelParam, double iParam);

	/** @nodoc @nocgmitf */
	/**
	* return nb of selected anomalies
	* @return 
	*   nb of selected anomalies
	*/
	int Size();

	/**
	* Add an anomaly to the list of anomalies to be checked
	* @param iLabelAnomaly 
	*   an additional Anomaly to be Checked.
	*
	* Rmk :  If no anomalies have been specified via the AddAnomaly service,
	*        the default behavior is to check the "CATCGMInternalAnomalies" 
	*        set of anomaly
	*/
	void AddAnomaly(CATCGMExplicitCheckAnomaly iLabelAnomaly);

	/** @nodoc @nocgmitf */
	/**
	* return next selected anomaly
	* @param piExplicitCheck_AnomalyBase
	*	 the Current Anomaly 
	* @return 
	*   return next selected anomaly
	*/
	CATExplicitCheck_AnomalyBase *Next(CATExplicitCheck_AnomalyBase *piExplicitCheck_AnomalyBase = NULL);

	/** @nodoc @nocgmitf */
	/**
	* Activate and Init Parameters of the given Specific Anomaly 
	* @param iLabelAnomaly 
	*   the Anomaly Label under scope.
	* @return
	*   the requested Anomaly 
	*/
	CATExplicitCheck_AnomalyBase *Locate(CATCGMExplicitCheckAnomaly iLabelAnomaly);

	/** @nodoc @nocgmitf */
	/**
	* insert the selected anomaly
	* @param piExplicitCheck_AnomalyBase
	*	 the Anomaly to be inserted 
	* @return 
	* @return
	*	<br><b>Legal values</b>:
	*		<dl><dt><tt>1</tt><dd> if insertion succeeded.
	*     <dt><tt>0</tt><dd> otherwise.</dl>
	*/
	int Insert(CATExplicitCheck_AnomalyBase *piExplicitCheck_AnomalyBase);

   /** @nodoc @nocgmitf */
	/**
	* ..........................................................
	* @return
	@param iScaleFactor
	*	 ..........................................................
	*/
   static void SetScaleFactor(double iScaleFactor);

	/** @nodoc @nocgmitf */
	/**
	* Check if there is at least a Specific Anomaly
	* @return
	*	<br><b>Legal values</b>:
	*		<dl><dt><tt>TRUE</tt><dd> at least one specific anomaly found.
	*     <dt><tt>FALSE</tt><dd> otherwise.</dl>
	*/
	CATBoolean							IsThereSpecificAnomaly(); 

	/** @nodoc @nocgmitf */
	/**
	* Check if there is at least a Specific and Internal Anomaly
	* @return
	*	<br><b>Legal values</b>:
	*		<dl><dt><tt>TRUE</tt><dd> at least one specific and internal anomaly found.
	*     <dt><tt>FALSE</tt><dd> otherwise.</dl>
	*/
	CATBoolean							IsThereSpecificAndInternalAnomaly(); 

	/** @nodoc @nocgmitf */
	/**
	* Activate and Init Parameters of the given Specific Anomaly 
	* @param iLabelAnomaly 
	*   the Anomaly under scope.
	*/
	//void InitParametersExplicitAnomaly(CATCGMExplicitCheckAnomaly iLabelAnomaly);

	/** @nodoc @nocgmitf */
	/**
	* Dump Parameters of the given Specific Anomaly 
	* @param ioCGMStr 
	*   the output stream.
	* @param iLabelAnomaly 
	*   the Anomaly under scope.
	*/
	//void Dump(CATCGMOutput& ioCGMStr,CATCGMExplicitCheckAnomaly iLabelAnomaly);

   /** @nodoc @nocgmitf */
   /**
	* Dump Parameters Specific Anomalies 
	* @param ioCGMStr 
	*   the output stream.
	*/
	void Dump(CATCGMOutput& ioCGMStr);
	
	/** @nodoc @nocgmitf */
	void Write(CATCGMStream& ioStr,short iVersion);

	/** @nodoc @nocgmitf */
	void Read(CATCGMStream& ioStr,short iVersion);

	//void ReadLabels(CATCGMStream& ioStr,short iVersion,int iNbLabels,CATListOfInt &ListOfLabels);
	//void ReadParams(CATCGMStream& ioStr,short iVersion,int iNbLabels,CATListOfInt &ListOfLabels);

	/** @nodoc @nocgmitf */
	int AddRef();

	/** @nodoc @nocgmitf */
	int Release();

	
	//CATCGMEdge_HighNArcs_Parameters									_CGMEdge_HighNArcs_Params;
	//CATCGMEdge_HighPolynomialDegree_Parameters					_CGMEdge_HighPolynomialDegree_Params;
	//CATCGMEdge_KnotsInSideRange_Parameters						_CGMEdge_KnotsInSideRange_Params;
	//CATCGMFace_HighNbPatches_Parameters								_CGMFace_HighNbPatches_Params;
	//CATCGMFace_HighPolynomialDegree_Parameters					_CGMFace_HighPolynomialDegree_Params;
	//CATCGMFace_KnotsInSideRange_Parameters						_CGMFace_KnotsInSideRange_Params;
	//CATCGMBody_NonManifoldEdges_Parameters							_CGMBody_NonManifoldEdges_Params;
	//CATCGMBody_MixedConvexityEdges_Parameters							_CGMBody_MixedConvexityEdges_Params;
	//CATCGMBody_VertexOverBounded_Parameters						_CGMBody_VertexOverBounded_Params;
	//CATCGMShell_AdjacentFacesSharpAngle_Parameters   			_CGMShell_AdjacentFacesSharpAngle_Params;
	//CATCGMBody_MultiDomains_Parameters								_CGMBody_MultiDomains_Params;

private:
	// private methods 
	CATExplicitCheck_SetOfAnomalies(const CATExplicitCheck_SetOfAnomalies& iExplicitAnomaly_SetOfAnomalies);
	CATExplicitCheck_SetOfAnomalies& operator =(const CATExplicitCheck_SetOfAnomalies& iExplicitAnomaly_SetOfAnomalies);

	// Set Of Anomalies
	CATExplicitCheck_HashTableOfAnomalyBase*	_pHashTableOfAnomalies;

	// Life Cycle Mngt
	int					_Counter;
};

#endif

