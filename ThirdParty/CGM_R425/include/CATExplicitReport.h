
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2010
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	Class		  :		CATExplicitReport
//	Creation	:		18/08/2010
//
//
//	Synopsis	:	Header class of CATExplicitReport. It allows to Dump and consult
//					    the kind of anomalies 
//	
//
//
//	Authors		:  AAD + KY1 +TCX
//-----------------------------------------------------------------------------
//18/08/2010 Class creation
//-----------------------------------------------------------------------------

#ifndef CATExplicitReport_H
#define	CATExplicitReport_H


#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include <CATListOfCATICGMObjects.h>
#include "CATExplicitCheckSeverity.h"
#include "CATPGMExplicitReport.h"
#include "CATListOfDouble.h"
#include "CATCGMHashTable.h"
#include "CATListOfShort.h"
#include "CATCXExplicitCheckServices.h"
#include "CATCGMNewArray.h"

class CATICGMObject;
class CATCGMOutput;
class CATUnicodeString;
class CATCXReport;
class CATHTabCATICGMObjectByTag;
//class CATCGMHashTable;

//=========================================================================
// New   
//=========================================================================
/**
* CATCGMExplicitCheckAnomaly is an "Enumeration". It lists
*                            anomalies labels that can be selected
*
*     @param CATCGMAllInternalAnomalies               : 
*
*            Set of internal anomalies.
*
*     @param CATCGMAllSpecificAnomalies            :              
*
*           The "CATCGMAllSpecificAnomalies" label anomaly that allows you to select at once
*           all specific anomalies, see below for definition of each "Specific Anomaly".
*
*           Rmk: CATCGMInternalAnomalies is excluded.
*
*  Specific Anomalies Definitions
*  ==============================
*    - A Label of a specific Anomaly has the following prototype CATCGMEntity_Pathology where
*		  Entity    : is the kind of the master Object on which the anomaly has been detected
*       Pathology : key words that describe the anomaly
*
*    - A specific anomaly can take parameters. It allows the user to tune the behavior of the Check Algorithm
*      or its results. Tunning parameters of a specific anomaly will influence the Number of detected anomalies.
*      Some specific anomalies don't require currently parameters.
*      If a specific anomaly requires a parameter then user has to use the A.P.I : 
*	   CATPGMExplicitCheckOperator::SetParameter(...) to assign the desired parameter value.
*	   Each parameter of a specific anomaly is identified by a "specific Label" used with the "parameter valu"e and the "Anomaly label"
*	   to affect the desired parameter through the A.P.I CATPGMExplicitCheckOperator::SetParameter(...).
*	   Some Parameters (not all) have default values predefined and used if user doesn't tune those parameters.
*	   If a specific anomaly has all its parameters with no default value pre-defined thann this anomaly will no be checked. 
*	   Refer to documentation of each specific anomaly to know the label of the a given parameter and its default value if there is one.
*
*    - If a specific anomaly (also for Internal anomaly) is detected, it will be decribed by the 
*      following features :
*
*       1- Severity		       : it could be a warning (CATEXPLICITCHECK_WARNING_SEVERITY) 
*                                or an error(CATEXPLICITCHECK_ERROR_SEVERITY)
*
*       2- ListOfObjects[1..N] : a list of N Objects that are involved in the anomaly
*									- ListOfObjects[1]      : The first object, called the "master object",
*                                     is the object on which the anomaly has been detected.
*                                     In the label of a specific anomaly, the type of the master object 
*		                  			     corresponds the Entity.
*									- ListOfObjects[2..N]   : their types are specific to each anomaly
*                                     Refer to the definition of each specific anomaly to learn more about
*                                     the meaning of those objects.
*       3- ListOfValues[1..P]  : a list of P values (each value is a type of double) that describe 
*                                the anomaly.
*                                Available only for Specific anomalies.
*						               The formatting of the List of values is proper to each "specific anomaly".
*                                Refer to the definition of each specific anomaly to learn more about 
*                                the meaning of each value that describe the anomaly.
*
*       Below, for each specific anomaly, refer to the sub-section "Features" that presents its parameters if any, Severity, 
*		  the ListOfObjects[1..N] and the ListOfValues[1..P].
*

*
*     @param CATCGMVertex_GapXYZ                   : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Let V a vertex and suppose that V is bounded by N edges where each one is 
*           bounded by 2 faces. The Vertex V has N distinct 
*           potential points where each one is evaluated on a distinct PCurve.                                                                                                                                                                             
*
*           The "CATCGMVertex_GapXYZ" anomaly detects the max gap 
*           (greater than a fixed tolerance factory) between 2 Points Pi and Pj evaluated 
*           on their respective PCurves PC1 and PC2 (all configurations are taking into account)
*
*			- Parameters :
*			--------------
*				- Tolerance : specify the maximum distance allowed between points inside the Vertex. 
*					- Parameter Label			: CATExplicitLabelParameter_Tolerance
*					- Parameter Default value	: The default value is 100 times the factory resolution
*							         (100*FactoryResolution).
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Vertex on which the gap has been detected
*				   - ListOfObjects[2],ListOfObjects[3] : the two PCurves, on which 
*                the couple of points that has a maximum gap, have been 
*                evaluated:
*                             ListOfObjects[2]=PC1 
*                             ListOfObjects[3]=PC2
*           The List of values that describes this anomaly is :
*              - the value of the gap
*              - the tolerance value

*
*     @param CATCGMEdge_GapXYZ                     : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Let E be an edge and suppose that E is bounded by N faces.
*           The edge E has N distinct PCurves where each one is
*           rely on the surface of its bounded face.
*
*           The "CATCGMEdge_GapXYZ" anomaly detects if there is a gap 
*           (greater than a fixed tolerance) between PCurves PCi and PCj 
*           (all couples of PCurves within the Edge Curve of the edge under scope 
*	          are taking into account)
*
*			- Parameters :
*			--------------
*				- Tolerance : specify the maximum distance allowed between Curves inside the Edge. 
*					- Parameter Label			: CATExplicitLabelParameter_Tolerance
*					- Parameter Default value	: The default value is 100 times the factory resolution
*							         (100*FactoryResolution).
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Edge on which the gap has been detected
*				   - ListOfObjects[2],ListOfObjects[3] : the two PCurves, on which 
*                the mapping reveals the maximum gap:
*                             ListOfObjects[2]=PCi 
*                             ListOfObjects[3]=PCj
*              - ListOfObjects[4]=PC_Ref the parametrization of the Curve that is used                       
*                to compute equivalent parametrisation on the 2 previous curves               
*
*           The List of values that describes this anomaly is :
*              - the value of the gap
*              - the tolerance value
*
*     @param CATCGMEdge_LengthDegenerated     : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Let E be an edge that contains N Curves within its EdgeCurve.
*
*           The "CATCGMEdge_LengthDegenerated" anomaly detects if one of its 
*           curve has a degenerated length, i.e smaller than a given tolerance 
*			specified by the user through the Min Length parameter.
*
*			If user specifies both "Min Length" and a "Max Length" values, 
*			than check will retrieve Edges that have lengths bounded 
*			by these two values.
*
*			- Parameters :
*			--------------
*				- Min Length : specify the minimum length that an edge should has. 
*					- Parameter Label			: CATExplicitLabelParameter_MinLength
*					- Parameter Default value	: The default value is the length tolerance of the factory
*							under scope (0.001*FactoryScale).
*
*				- Max Length : specify the "Max Length" that an edge should not exceed. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxLength
*					- Parameter Default value	: no predifined default value.
*
*				- Check Wire Body	(DEPRECATED DO NOT USE): specify that the check is enabled for edges that  belong to Wire Body. 
*					- Parameter Label			: CATExplicitLabelParameter_Check_WireBody
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Skin Body	(DEPRECATED DO NOT USE): specify that the check is enabled for edges that  belong to Skin Body. 
*					- Parameter Label			: CATExplicitLabelParameter_Check_SkinBody
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Solid Body (DEPRECATED DO NOT USE): specify that the check is enabled for edges that  belong to Solid Body. 
*					- Parameter Label			: CATExplicitLabelParameter_Check_SolidBody
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the Edge that has a Curve with a degenerated 
*                length
*				   - ListOfObjects[i] :the i_th faulty Curve :
*           The List of values that describes this anomaly is :
*              - ListOfObjects[1] : the "Min Length" used to retrieve faulty Curve
*              - ListOfObjects[2] : the "Max Length" used to retrieve faulty Curve (-1 if not set by the user)
*              - ListOfObjects[i] : the length of the faulty edge.
*

*     @param CATCGMEdge_ArcLengthDegenerated     : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Let E be an edge that contains N Curves within its EdgeCurve.
*
*           The "CATCGMEdge_ArcLengthDegenerated" anomaly detects if one of its 
*           curve has arcs with degenerated length, i.e smaller than a given tolerance 
*			specified by the user through the Min Length parameter.
*
*			If user specifies both "Min Length" and a "Max Length" values, 
*			than check will retrieve Edges that have curves with arc lengths bounded 
*			by these two values.
*
*			- Parameters :
*			--------------
*				- Min Length : specify the minimum length that an Arc of a Curve should has. 
*					- Parameter Label			: CATExplicitLabelParameter_MinLength
*					- Parameter Default value	: The default value is the length tolerance of the factory
*							under scope (0.001*FactoryScale).
*
*				- Max Length : specify the "Max Length" that an Arc Curve should not exceed. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxLength
*					- Parameter Default value	: no predifined default value.
*
*				- Check Wire Body	(DEPRECATED DO NOT USE): specify that the check is enabled for edges that  belong to Wire Body. 
*					- Parameter Label			: CATExplicitLabelParameter_Check_WireBody
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Skin Body	(DEPRECATED DO NOT USE): specify that the check is enabled for edges that  belong to Skin Body. 
*					- Parameter Label			: CATExplicitLabelParameter_Check_SkinBody
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Solid Body (DEPRECATED DO NOT USE): specify that the check is enabled for edges that  belong to Solid Body. 
*					- Parameter Label			: CATExplicitLabelParameter_Check_SolidBody
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Only Ref Curve : specify that the check is only  done on the Ref Curve of the Edge. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckOnlyRefCurve
*					- Parameter Default value	: The default value is TRUE
*
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the Edge that has a Curve with a degenerated 
*                length
*				   - ListOfObjects[2] :the i_th faulty Curve :
*           The List of values that describes this anomaly is :
*              - ListOfObjects[1] : the "Min Length" used to retrieve faulty Curve
*              - ListOfObjects[2] : the "Max Length" used to retrieve faulty Curve (-1 if not set by the user)
*              - ListOfObjects[i], ListOfObjects[i+1] : the Idx of the faulty arc and its length.
*

*     @param CATCGMVolume_InnerShellOutsideOuterShell  : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Let Vol be a volume
*
*           The "CATCGMVolume_InnerShellOutsideOuterShell" anomaly detects 
*	         if there is an inner Shell not contained in the outer shell 
*           of the volume Vol
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Volume on which the anomaly has been detected
*				   - ListOfObjects[2] : the Inner Shell
*				   - ListOfObjects[3] : the Outer Shell
*
*           The List of values that describes this anomaly is :
*              - No value
*
*     @param CATCGMFace_InnerLoopOutsideOuterLoop  : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a face
*
*           The "CATCGMFace_InnerLoopOutsideOuterLoop" anomaly detects 
*	         if there is an inner loop not contained in the outer loop 
*           of the face
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*				   - ListOfObjects[2] : the Inner Loop
*				   - ListOfObjects[3] : the Outer Loop
*
*           The List of values that describes this anomaly is :
*              - No value
*
*     @param CATCGMEdgeDomain_AutoIntersection           : 
*		----------------------------------------------------
*
*			- Definition :
*			--------------	
*           Let E_D be an edge domain (Loop or Wire) that belongs to a given body B. 
*           Lets Ei and Ej edges that belongs to the Edge Domain E_D.
*
*           The "CATCGMEdgeDomain_AutoIntersection" anomaly detects 
*           if there are two intersected edges 
*
*			- Parameters :
*			--------------
*				- Check Wire Domain	: specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain	: specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : EdgeDomain on which auto intersection has been detected
*				   - ListOfObjects[2..N] : set of couples of intersected edges/vertex
*                          Example : if there are 2 intersected edges you can retrieve 
*                                    them from  ListOfObjects[2] and ListOfObjects[3]
*
*           The List of values that describes this anomaly is :
*              - No value	
*
*     @param CATCGMEdgeDomain_DisconnectedEdges  : 
*		--------------------------------------------------------
*
*			- Definition :
*			--------------	
*           Let E_D be an edge domain (Loop or Wire). Let Ei and Ei+1 two successive edges 
*           (w.r to the edge domain orientation) that belongs to the Edge Domain E_D.
*
*           The "CATCGMAdjacentEdges_DisjointVertices" anomaly checks if 
*           the end vertex of the edge Ei and the start vertex of the next edge Ei+1, 
*           in the edge domain E_D, are identical
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Edge Domain on which the anomaly has been detected
*				   - ListOfObjects[2],ListOfObjects[3] : the edges that are not connected 
*              - ListOfObjects[4],ListOfObjects[5] : vertices of the first and the second edge where connection test failed, 
*                                                    vertices expected same
*
*           The List of values that describes this anomaly is :
*              - No value
*     
*     @param CATCGMFace_IntersectionBetweenLoops  : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Let F be a a face and Lo its outer loop. Let Li1, Li2,..., Lin the internal loops
*           of the face F.
*
*           The "CATCGMFace_IntersectionBetweenLoops" anomaly checks that  
*           there is no couple of loops that intersect each other : [ Lo interesect Lij is empty 
*            (j=1,..,n) ] and [ Lik intersect Lij is empty (k,j=1,..,n), k not_equal to j ] 
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*				   - ListOfObjects[2],ListOfObjects[3] : the loops that are intersected
*              - ListOfObjects[4],ListOfObjects[5] : the loops that are intersected
*              - ... and so on. 
*
*           The List of values that describes this anomaly is :
*              - No value
*
*     @param CATCGMFace_IsoDegenerescence             : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face. 
*
*           The "CATCGMFace_IsoDegenerescence" anomaly detect  
*           if there is an degenerated IsoPar on the surface of the face
*	         within its Limits:
*   	      Lets (Umin,Vmin) and (Umax,Vmax) the Limits the 2D Bounding Box 
*           of the face.
*	         Denote by Pmm=(Umin,Vmin), PMm=(Umax,Vmin), PmM=(Umin,Vmax), PMM=(Umax,Vmax) 
*           the border points in (U,V) referential)
*
*           F is IsoDegenerescent if 
*                       ||Pmm,PmM|| <Tol                          or
*                       ||Pmm,PMm|| <Tol                          or
*                       ||PMm,PMM|| <Tol                          or
*                       ||PmM,PMM|| <Tol                          or
*                       ||dF/dU(Pmm)||<Tol or ||dF/dV(Pmm)||<Tol  or 
*	                     ||dF/dU(PmM)||<Tol or ||dF/dV(PmM)||<Tol  or 
*                       ||dF/dU(PMm)||<Tol or ||dF/dV(PMm)||<Tol  or 
*                       ||dF/dU(PMM)||<Tol or ||dF/dV(PMM)||<Tol
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*
*           The List of values that describes this anomaly is :
*              - for each point Pi (belongs to the set {Pmm,PMm,PmM,PMM}) 
*                that IsoDegenerescence has been detected 9 values are recorded :
*                  - ListValue[i*9+1] : UParam of Pi
*                  - ListValue[i*9+2] : VParam of Pi
*                  - ListValue[i*9+3] : XCoord of Pi
*                  - ListValue[i*9+4] : YCoord of Pi
*                  - ListValue[i*9+5] : ZCoord of Pi
*                  - ListValue[i*9+6] : UfirstDeriv of Pi
*                  - ListValue[i*9+7] : VfirstDeriv of Pi
*                  - ListValue[i*9+8] : Length of Degenerated IsoPar on Pi
*                  - ListValue[i*9+8] : Tolerance
*
*
*     @param CATCGMFace_Twisted                    : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face.
*
*           The "CATCGMFace_Twisted" anomaly detects
*           if the surface referenced by the face F is twisted
*	         within the Limits of the 2D BoundingBox of F:
*   	    
*	         A surface S is twisted within a given limits means that
*	         there is at least one twisted point.
*
*           A twisted point Pi=(ui,vi) [SurParam] is a point that 
*	         satisfies the following conditions :
*		         - Pi minimizes ||dF/dU^dF/dV||
*		         - One of the following condition is filled
*			         - ||dF/dU||<Tol or ||dF/dV||<Tol
*			         - ||dF/dU^dF/dV|| / ||dF/dU|| * ||dF/dV|| < Tol
*		               - Pi is interior to the face F
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*
*           The List of values that describes this anomaly is :
*              - N concatenated Set of 5 values that correspond 
*                to the N detected twisted point.
*                Each set correspond to (U,V), (X,Y,Z) coordinates
*                of the twisted point

*     @param CATCGMFace_NulCurvatureRadius                    : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face.
*
*           The "CATCGMFace_NulCurvatureRadius" anomaly detects
*           if the surface referenced by the face F has a nul 
*           curvature radius smaller than a fixed tolerance
*           within the Limits of the 2D BoundingBox 
*           of F. 
*
*			- Parameters :
*			--------------
*				- Min Curvature Radius : specify the minimum Curvature Radius. 
*					- Parameter Label			: CATExplicitLabelParameter_MinCurvatureRadius
*					- Parameter Default value	: The default value of the Curfvature "Radius" is equal to the factory resolution
*
*				- Check Only Face Area	: specify if the check should be done on the limits of the face or on the max limits 
*										  of its underlying surface.
*					- Parameter Label			: CATExplicitLabelParameter_CheckOnlyFaceArea
*					- Parameter Default value	: By default the Check is done on face limits.
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Surface federated by the Face on which the anomaly has been detected
*
*           The List of values that describes this anomaly is :
*                 
*              - If a point is detected as having a Nul Curvature Radius
*                the list of values supplies :
*                       - ListValue[i*6+1] : UParam of the point
*                       - ListValue[i*6+2] : VParam of the point
*                       - ListValue[i*6+3] : XCoord of the point
*                       - ListValue[i*6+4] : YCoord of the point
*                       - ListValue[i*6+5] : ZCoord of the point
*                       - ListValue[i*6+6] : Radius
*                After describing the coord of the point there is 
*                a last value that represents the tolerance
*

*     @param CATCGMEdge_HighNbArcs                    : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an Edge.
*
*           The "CATCGMEdge_HighNbArcs" anomaly detects
*           if the Ref Curve of the edge E has 
*				a number of arcs greater than a given limit.
*
*			- Parameters :
*			--------------
*				- Max Nb Arcs  : the maximum arc number allowed 
*					- Parameter Label : CATExplicitLabelParameter_Max_Nb_Arc
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			N.B : when select this specific anomaly, all parameters settings are mandatory, 
*					no default values definition are guaranteed
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2] : Ref Curve on which the arc number has been 
*												retrieved and compared to the given limit
*
*           The List of values that describes this anomaly is :
*              - the arc number of the Ref Curve of the Edge 
*              - the given parameter max arc number 
*

*     @param CATCGMEdge_HighPolynomialDegree       : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an Edge.
*
*           The "CATCGMEdge_HighPolynomialDegree" anomaly detects
*           if the Ref Curve (geometry) of the edge E has 
*				a polynomial degre greater than a given limit.
*
*			- Parameters :
*			--------------
*				- Max Degree  : the maximum allow polynomial degree
*					- Parameter Label : CATExplicitLabelParameter_Max_Polyn_Deg
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			N.B : when select this specific anomaly, all parameters settings are mandatory, 
*					no default values definition are guaranteed
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2] : Ref Curve on which the Polynomial Degree has been 
*												retrieved and compared to the given limit
*
*           The List of values that describes this anomaly is :
*              - the Polynomial Degree of the Ref Curve of the Edge 
*              - the given parameter max Polynomial Degree
*

*     @param CATCGMEdge_KnotsInSideRange       : 
*		-------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an Edge.
*
*           The "CATCGMEdge_KnotsInSideRange" anomaly detects,
*           on the Ref Curve (geometry) of the edge E, if the gap between 
*				two successive Knot points, coming from the knot vector 
*				of the Ref Curve, is inside a given range.
*				Not all geometries of edges (Ref Curves) have a Knot vector.
*				Examples of Geometry objects that have a Knot vector : 
*				CATNurbsCurve, CATPNurbs, ...
*				The Check stops when the it meets the 2 first succsssive Knot 
*				points with gap inside the given range 
*
*			- Parameters :
*			--------------
*				- Min Knot Gap   : the min limit of Knot gap
*					- Parameter Label : CATExplicitLabelParameter_Min_Gap_Knots
*				- Min Knot Gap   : the max limit of Knot gap
*					- Parameter Label : CATExplicitLabelParameter_Max_Gap_Knots
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			N.B : when select this specific anomaly, all parameters settings are mandatory, 
*					no default values definition are guaranteed
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2] : Ref Curve on which the knot vector is retrieved 
*												and gaps of between knot points were computed 
*
*           The List of values that describes this anomaly is : 
*              - the 1st Index (Idx1)of Knot point in the Knot Vector (KV)
*              - the 2nd Index of Knot point (Idx2 = Idx1-1) in the Knot Vector (KV)
*              - the 1st KnotPoint (KV[Idx1]) 
*              - the 2nd KnotPoint (KV[Idx2]) 
*              - the given parameter min limit of Knot gap
*              - the given parameter max limit of Knot gap
*

*     @param CATCGMFace_HighNbPatches              : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face.
*
*           The "CATCGMFace_HighNbPatches" anomaly detects
*           if the Surface referenced by the face F has 
*				a number of Patches greater than a given limit 
*				or if the Number of arcs in U or V direction is
*				greater than a given limit
*
*
*			- Parameters :
*			--------------
*				- Max Nb Patches  : the maximum patch number allowed.
*										  If set set to 0, the check of nb patches 
*										  will be turn off 	
*					- Parameter Label : CATExplicitLabelParameter_Max_Nb_Patches
*				- Max Nb Patches Dir  : the maximum arc number allowed in both 
*												direction U and V.
*										  If set set to 0, the check of nb patches 
*										  will be turn off 	
*					- Parameter Label : CATExplicitLabelParameter_Max_Nb_Patches_Dir
*
*			N.B : when select this specific anomaly, all parameters settings are mandatory, 
*					no default values definition are guaranteed
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Surface referenced by the Face F
*
*           The List of values that describes this anomaly is :
*              - the patch number of the underlying surface
*              - the max patch number given as parameter
*              - the arc number of the underlying surface if the U direction
*              - the arc number of the underlying surface if the V direction
*              - the max arc number given as parameter
*

*     @param CATCGMFace_HighPolynomialDegree       : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face.
*
*           The "CATCGMFace_HighPolynomialDegree" anomaly detects
*           if the surface (geometry) of the face F has 
*				a polynomial degree greater than a given limit.
*
*			- Parameters :
*			--------------
*				- Max Degree  : the maximum allow polynomial degree
*					- Parameter Label : CATExplicitLabelParameter_Max_Polyn_Deg
*
*			N.B : when select this specific anomaly, all parameters settings are mandatory, 
*					no default values definition are guaranteed
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Ref Curve on which the Polynomial Degree has been 
*												retrieved and compared to the given limit
*
*           The List of values that describes this anomaly is :
*              - the Minimum Polynomial Degree, retrieved from the Surface referenced 
*					  by the face F, that is greater than the given limit 
*              - the given Max Polynomial Degree parameter
*

*     @param CATCGMFace_KnotsInSideRange       : 
*		-------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face.
*
*           The "CATCGMFace_KnotsInSideRange" anomaly detects,
*           on the Surface of the face F, if the gap between 
*				two successive Knot points, coming from the U-Knot Vector
*				or V-Knot Vector, is inside a given range.
*				Not all surface have Knot vectors.
*				Examples of Geometry objects that have a Knot vector : 
*				CATNurbsSuface, ...
*				The Check stops when the it meets the 2 first succsssive Knot 
*				points with gap inside the given range 
*
*			- Parameters :
*			--------------
*				- Min Knot Gap   : the min limit of Knot gap
*					- Parameter Label : CATExplicitLabelParameter_Min_Gap_Knots
*				- Min Knot Gap   : the max limit of Knot gap
*					- Parameter Label : CATExplicitLabelParameter_Max_Gap_Knots
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Surface referenced by the the above face 
*
*           The List of values that describes this anomaly is : 
*              - the 1st Index (Idx1)of Knot point in the Knot Vector (KV)
*              - the 2nd Index of Knot point (Idx2 = Idx1-1) in the Knot Vector (KV)
*              - the 1st KnotPoint (KV[Idx1]) 
*              - the 2nd KnotPoint (KV[Idx2]) 
*              - the given min limit of Knot gap
*              - the given max limit of Knot gap
*

*     @param CATCGMBody_NonManifoldEdges       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets B be a body.
*
*           The "CATCGMBody_NonManifoldEdges" anomaly detects,
*           on a given body B, if it contains non manifold edges,
*				An Edge is considered as Non Manifold, in the context of a body, 
*				if it's bounded by more than two faces.
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Body on which the anomaly has been detected
*              - ListOfObjects[2] : first Non Manifold edge detected 
*              - ListOfObjects[3] : second Non Manifold edge detected
*              - ListOfObjects[..] : ....
*
*           The List of values that describes this anomaly is : 
*              - Number of bounded face for the first non manifold edge detected
*              - Number of bounded face for the second non manifold edge detected
*              - .....
*              - .....
*

*     @param CATCGMBody_VertexOverBounded       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets B be a body.
*
*           The "CATCGMBody_VertexOverBounded" anomaly detects,
*           on a given body B, if it contains vertices with number 
*				of bounded edges greater than a given limit
*
*			- Parameters :
*			--------------
*				- Max Nb Edges   : the max number of bounded edges allowed for a vertex.
*					- Parameter Label : CATExplicitLabelParameter_Max_Nb_Edges
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Body on which the anomaly has been detected
*              - ListOfObjects[2] : first over bounded vertex detected
*              - ListOfObjects[3] : second over bounded vertex detected
*              - ListOfObjects[..] : ....
*
*           The List of values that describes this anomaly is : 
*              - Number of bounded edges for the first over bounded vertex detected
*              - Number of bounded edges for the second over bounded vertex detected
*              - .....
*              - .....
*

*     @param CATCGMBody_MultiDomains       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets B be a body.
*
*           The "CATCGMBody_MultiDomains" anomaly detects,
*           on a given body B, if it federates directly more than one domain.
*				
*
*			- Parameters :
*			--------------
*				- Check Wire Body : Set to 1, enables to check, in case where B 
*										  is a Wire Body, if it contains more than 1 wire
*					- Parameter Label : CATExplicitLabelParameter_Check_WireBody
*				- Check Skin Body : Set to 1, enables to check, in case where B 
*										  is a Skin Body, if it contains more than 1 shell
*					- Parameter Label : CATExplicitLabelParameter_Check_SkinBody
*				- Check Solid Body : Set to 1, enables to check, in case where B 
*										  is a Solid Body, if it contains more than 1 Lump
*					- Parameter Label : CATExplicitLabelParameter_Check_SolidBody
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Body on which the anomaly has been detected
*              - ListOfObjects[2] : first domain federated by the body B
*              - ListOfObjects[3] : second domain federated by the body B
*              - ListOfObjects[..] : ....
*
*           The List of values that describes this anomaly is : 
*              - the given parameter Check Wire Body : 0 or 1 
*              - the given parameter Check Skin Body : 0 or 1 
*              - the given parameter Check Solid Body : 0 or 1 
*

*     @param CATCGMEdge_DiscontinuityG0       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an Edge.
*
*           The "CATCGMEdge_DiscontinuityG0" anomaly detects,
*           if the given edge E is discontinuous in point : G0-Discontinuity.
*			      The "G0-Discontinuity check" is done on the Ref Curve of the given edge
*           within its useful limits.
*	
*			- Parameters :
*			--------------
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2] : The reference Curve on which the "G0-Discontinuity" check has been done
*
*           The List of values that describe this anomaly are : 
*              - No values. 
*

*     @param CATCGMEdge_DiscontinuityG1       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an Edge.
*
*           The "CATCGMEdge_DiscontinuityG1" anomaly detects,
*           if the given edge E is discontinuous in tangent : G1-Discontinuity. 
*			      The "G1-Discontinuity" check is done on the Ref Curve of the given edge
*           within its useful limits.
*
*			- Parameters :
*			--------------
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2] : The reference Curve on which the G1-Discontinuity check has been done
*
*           The List of values that describe this anomaly are : 
*              - No values.
*

*     @param CATCGMEdge_DiscontinuityG2       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an Edge.
*
*           The "CATCGMEdge_DiscontinuityG2" anomaly detects,
*           if the given edge E is discontinuous in curvature : G2-Discontinuity. 
*			      The "G2-Discontinuity" check is done on the Ref Curve of the given edge
*           within its useful limits.
*
*			- Parameters :
*			--------------
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2] : The reference Curve on which the G2-Discontinuity has been done
*
*           The List of values that describe this anomaly are : 
*               No values.
*
*		@param CATCGMEdgeDomain_DiscontinuityG0   : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E_D be an Edge Domain (Wire or Loop domain).
*
*           The "CATCGMEdgeDomain_DiscontinuityG0" anomaly detects,
*           if the given edge domain E_D is discontinuous in point : G0-Discontinuity.
*			G0-Discontinuity is detected if the transition in point between 
*			two successive edges, is larger than the selected tolerance.
*			The tolerance (Max Gap) can be specified by the user otherwise the "G0-Discontinuity 
*			tolerance" of the factory (0.1*FactoryScale) will be used.
*	
*			- Parameters :
*			--------------
*				- Max Gap : specify the tolerance for the G0-Discontinuity. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxGap
*					- Parameter Default value	: The default value is the G0-Discontinuity tolerance of the factory
*							under scope (0.1*FactoryScale).
*
*				- Check Wire Domain	: specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain	: specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Edge Domain on which the anomaly has been detected
*              - ListOfObjects[i],ListOfObjects[i+1], ListOfObjects[i+2]: The i_th Edge, 
*					its adjacent edge and the Vertex that bound these edges on which G0-Discontinuity has been detected
*
*           The List of values that describe this anomaly are : 
*              - ListOfValues[1] : the Max Gap used to detect the G0-Discontinuity (set by the user or the default used if no setting done) 
*              - ListOfValues[i] : the detected Gap value.
*              - ...
*

*     @param CATCGMEdgeDomain_DiscontinuityG1       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E_D be an Edge Domain (Wire or Loop domain).
*
*           The "CATCGMEdgeDomain_DiscontinuityG1" anomaly detects,
*           if the given edge domain E_D is discontinuous in tangent : G1-Discontinuity. 
*			G1-Discontinuity is detected if the transition in tangent between 
*			two adjacent edges (taht belong to E_D) is larger than the selected tolerance.
*			The tolerance (Min Angle) can be specified by the user otherwise the "G1-Discontinuity" 
*			tolerance of the factory (0.5°) will be used.
*
*			If user specifies only the "Min Angle" parameter the check will detect "G1-Discontinuity" 
*			as described above.
*			If user specifies both "Min Angle" and "Max Angle" the check will detects "G1-Discontinuity"
*			between edges that have angular transition that exceed the specified "Min Angle" and doesn't 
*			exceed the given limit "Max Angle".
*
*			- Parameters :
*			--------------
*				- Min Angle (in Degree) : specify the tolerance for the G1-Discontinuity.
*					- Parameter Label			: CATExplicitLabelParameter_Min_Angle_Deg
*					- Parameter Default value	: The default value is the G1-Discontinuity tolerance of the factory
*							under scope (0.5°).
*
*				- Max Angle (in Degree) : specify the "Max Angle" transition allowed in case of G1-Discontinuity detection.
*							It allow to check that the detected G1-Discontinuity does not exceed the given value.
*					- Parameter Label			: CATExplicitLabelParameter_Max_Angle_Deg
*					- Parameter Default value	: no predifined default value.
*
*				- Check Wire Domain	: specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain	: specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Edge Domain on which the anomaly has been detected
*              - ListOfObjects[i],ListOfObjects[i+1], ListOfObjects[i+2]: The i_th Edge, 
*					its adjacent edge and the Vertex that bound these edges on which G1-Discontinuity has been detected
*
*           The List of values that describe this anomaly are : 
*              - ListOfValues[1] : the Min Angle used to detect the G1-Discontinuity (set by the user or the default used if no setting done) 
*              - ListOfValues[2] : the Max Angle used to check that detected G1-Discontinuity does not exceed the given value 
*				(if this parameter is not specified by the user, it will indicated by the value -1)
*              - ListOfValues[i] : the Angle transition detected on the faulty edges.
*			   - ...
*

*     @param CATCGMEdgeDomain_DiscontinuityG2       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E_D be an Edge Domain (Wire or Loop domain).
*
*           The "CATCGMEdgeDomain_DiscontinuityG2" anomaly detects,
*           if the given edge domain E_D is discontinuous in curvature : G2-Discontinuity. 
*			G2-Discontinuity is detected if the transition in curvature between 
*			two successive edges is larger than the selected tolerance.
*			The tolerance (Min Curvature Ratio) can be specified by the user otherwise the "G2-Discontinuity" 
*			tolerance of the factory (XXX) will be used.
*
*			If user specifies only the "Min Curvature  Ratio" parameter the check will detect "G2-Discontinuity" 
*			as described above.
*			If user specifies both "Min Curvature Ratio" and "Max Curvature Ratio" the check will detects "G2-Discontinuity"
*			between arcs that have curvature transition that exceed the specified "Min Curvature Ratio" and doesn't 
*			exceed the given limit "Max Curvature Ratio".
*
*			- Parameters :
*			--------------
*				- Min Curvature Ratio : specify the tolerance for the G2-Discontinuity. 
*							The default value is the G2-Discontinuity tolerance of the factory
*							under scope (XXX).
*					- Parameter Label			: CATExplicitLabelParameter_Min_CurvatureRatio
*					- Parameter Default value	: The default value is the G2-Discontinuity tolerance of the factory
*							under scope (XXXX).
*
*				- Max Curvature Ratio : specify the "Max Curvature Ratio" transition allowed in case of G2-Discontinuity detection.
*							It allow to check that the detected G2-Discontinuity does not exceed the given value
*							There is no default value predifined for this parameter.
*					- Parameter Label			: CATExplicitLabelParameter_Max_CurvatureRatio
*					- Parameter Default value	: no predifined default value.
*
*				- Check Wire Domain	: specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain	: specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Edge Domain on which the anomaly has been detected
*              - ListOfObjects[i],ListOfObjects[i+1], ListOfObjects[i+2]: The i_th Edge, 
*					its adjacent edge and the Vertex that bound these edges on which G2-Discontinuity has been detected
*
*           The List of values that describe this anomaly are : 
*              - ListOfValues[1] : the Min Curvature Ratio used to detect the G2-Discontinuity (set by the user or the default used if no setting done) 
*              - ListOfValues[2] : the Max Curvature Ratio used to check that detected G2-Discontinuity does not exceed the given value 
*				(if this parameter is not specified by the user, it will indicated by the value -1)
*              - ListOfValues[i] : the Curvature Ratio detected on the faulty edges.
*			   - ...
*

*     @param CATCGMFace_DiscontinuityG0       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face.
*
*           The "CATCGMFace_DiscontinuityG0" anomaly detects,
*           if the given face F is discontinuous in point : G0-Discontinuity.
*			      The "G0-Discontinuity check" is done on the Surface federated by the given face
*           within its useful 2D Bounding Box.
*	
*			- Parameters :
*			--------------
*           No parameters.				
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : The surface on which the check has been done
*
*           The List of values that describe this anomaly are : 
*               No values.

*     @param CATCGMFace_DiscontinuityG1       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           The "CATCGMFace_DiscontinuityG1" anomaly detects,
*           if the given face F is discontinuous in point : G1-Discontinuity.
*			      The "G1-Discontinuity check" is made on the Surface federated by the given face
*           within its useful 2D Bounding Box.
*
*			- Parameters :
*			--------------
*           No parameters.
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : The surface on which the check has been done
*
*           The List of values that describe this anomaly are : 
*               No values.
*
*     @param CATCGMFace_DiscontinuityG2       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           The "CATCGMFace_DiscontinuityG2" anomaly detects,
*           if the given face F is discontinuous in point : G2-Discontinuity.
*     			The "G2-Discontinuity check" is made on the Surface federated by the given face
*           within its useful 2D Bounding Box.
*
*			- Parameters :
*			--------------
*         No parameters.
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : The surface on which the check has been done
*
*           The List of values that describe this anomaly are : 
*              No values. 
*

*		@param CATCGMShell_DiscontinuityG0   : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets S_D be a Shell Domain.
*
*           The "CATCGMShell_DiscontinuityG0" anomaly detects,
*           if the given Shell S_D is discontinuous in point : G0-Discontinuity.
*			G0-Discontinuity is detected if the transition in point between 
*			two adjacent faces (which belong to the shell), is larger than the selected tolerance.
*			The tolerance (Max Gap) can be specified by the user otherwise the "G0-Discontinuity
*			tolerance" of the factory (0.1*FactoryScale) will be used.
*	
*			- Parameters :
*			--------------
*				- Max Gap : specify the tolerance for the G0-Discontinuity. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxGap
*					- Parameter Default value	: The default value is the G0-Discontinuity tolerance of the factory
*							under scope (0.1*FactoryScale).
*
*				- Point Sample Size : specify the size of the Point sample used to Check the G0-Discontinuity. 
*					- Parameter Label			: CATExplicitLabelParameter_Nb_Pts
*					- Parameter Default value	: The default value is choosen internally based on the geometry complexity.
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Shell on which the anomaly has been detected
*              - ListOfObjects[i], ListOfObjects[i+1], ListOfObjects[i+2]: The Edge and its 2 incident faces 
*					on which G0-Discontinuity has been detected
*
*           The List of values that describe this anomaly are : 
*              - ListOfValues[1] : the Max Gap used to detect the G0-Discontinuity (set by the user or the default used if no setting done) 
*              - ListOfValues[i] : the detected Gap value.
*              - ...
*

*     @param CATCGMShell_DiscontinuityG1       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets S_D be a Shell Domain.
*
*           The "CATCGMShell_DiscontinuityG1" anomaly detects,
*           if the given edge domain S_D is discontinuous in tangent : G1-Discontinuity. 
*			G1-Discontinuity is detected if the transition in tangent between 
*			twoo adjacent faces (which belong to the shell) is larger than the selected tolerance.
*			The tolerance (Min Angle) can be specified by the user otherwise the "G1-Discontinuity" 
*			tolerance of the factory (0.5°) will be used.
*
*			If user specifies only the "Min Angle" parameter the check will detect "G1-Discontinuity" 
*			as described above.
*			If user specifies both "Min Angle" and "Max Angle" the check will detects "G1-Discontinuity"
*			between faces that have angular transition that exceed the specified "Min Angle" and doesn't 
*			exceed the given limit "Max Angle".
*
*			- Parameters :
*			--------------
*				- Min Angle (in Degree) : specify the tolerance for the G1-Discontinuity.
*					- Parameter Label			: CATExplicitLabelParameter_Min_Angle_Deg
*					- Parameter Default value	: The default value is the G1-Discontinuity tolerance of the factory
*							under scope (0.5°).
*
*				- Max Angle (in Degree) : specify the "Max Angle" transition allowed in case of G1-Discontinuity detection.
*							It allow to check that the detected G1-Discontinuity does not exceed the given value.
*					- Parameter Label			: CATExplicitLabelParameter_Max_Angle_Deg
*					- Parameter Default value	: no predifined default value.
*
*				- Point Sample Size : specify the size of the Point sample used to Check the G1-Discontinuity. 
*					- Parameter Label			: CATExplicitLabelParameter_Nb_Pts
*					- Parameter Default value	: The default value is choosen internally based on the geometry complexity.
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Shell on which the anomaly has been detected
*              - ListOfObjects[i],ListOfObjects[i+1], ListOfObjects[i+2]: The Edge and its 2 incident faces 
*					on which G1-Discontinuity has been detected
*
*           The List of values that describe this anomaly are : 
*              - ListOfValues[1] : the Min Angle used to detect the G1-Discontinuity (set by the user or the default used if no setting done) 
*              - ListOfValues[2] : the Max Angle used to check that detected G1-Discontinuity does not exceed the given value 
*				(if this parameter is not specified by the user, it will indicated by the value -1)
*              - ListOfValues[i] : the Angle transition detected on the faulty faces.
*			   - ...
*

*     @param CATCGMShell_DiscontinuityG2       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets S_D be a Shell Domain.
*
*           The "CATCGMShell_DiscontinuityG2" anomaly detects,
*           if the given edge domain S_D is discontinuous in curvature : G2-Discontinuity. 
*			G2-Discontinuity is detected if the transition in curvature between 
*			two successive edges is larger than the selected tolerance.
*			The tolerance (Min Curvature Ratio) can be specified by the user otherwise the "G2-Discontinuity" 
*			tolerance of the factory (XXX) will be used.
*
*			If user specifies only the "Min Curvature  Radius" parameter the check will detect "G2-Discontinuity" 
*			as described above.
*			If user specifies both "Min Curvature Radius" and "Max Curvature Radius" the check will detects "G2-Discontinuity"
*			between arcs that have curvature transition that exceed the specified "Min Curvature Radius" and doesn't 
*			exceed the given limit "Max Curvature Radius".
*
*			- Parameters :
*			--------------
*				- Min Curvature Radius : specify the tolerance for the G2-Discontinuity. 
*							The default value is the G2-Discontinuity tolerance of the factory
*							under scope (XXX).
*					- Parameter Label			: CATExplicitLabelParameter_Min_CurvatureRatio
*					- Parameter Default value	: The default value is the G2-Discontinuity tolerance of the factory
*							under scope (XXXX).
*
*				- Max Curvature Radius : specify the "Max Curvature Radius" transition allowed in case of G2-Discontinuity detection.
*							It allow to check that the detected G2-Discontinuity does not exceed the given value
*							There is no default value predifined for this parameter.
*					- Parameter Label			: CATExplicitLabelParameter_Max_CurvatureRatio
*					- Parameter Default value	: no predifined default value.
*
*				- Point Sample Size : specify the size of the Point sample used to Check the G2-Discontinuity. 
*					- Parameter Label			: CATExplicitLabelParameter_Nb_Pts
*					- Parameter Default value	: The default value is choosen internally based on the geometry complexity.
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Shell on which the anomaly has been detected
*              - ListOfObjects[i],ListOfObjects[i+1], ListOfObjects[i+2]: The Edge and its 2 incident faces 
*					on which G2-Discontinuity has been detected
*
*           The List of values that describe this anomaly are : 
*              - ListOfValues[1] : the Min Curvature Radius used to detect the G2-Discontinuity (set by the user or the default used if no setting done) 
*              - ListOfValues[2] : the Max Curvature Radius used to check that detected G2-Discontinuity does not exceed the given value 
*				(if this parameter is not specified by the user, it will indicated by the value -1)
*              - ListOfValues[i] : the Curvature Ratio detected on the faulty faces.
*			   - ...
*

*     @param CATCGMVolume_WithInnerShell       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets V be a Volume.
*
*           The "CATCGMVolume_WithInnerShell" anomaly detects,
*           if the given volume V has inner shells. 
*
*			- Parameters :
*			--------------
*				Tis anomaly doesn't requests/needs parameters
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Volume on which the anomaly has been detected
*              - ListOfObjects[2] : The outer shell of the Volume under scope 
*              - ListOfObjects[i]: The i_th Inner Shell.
*
*           The List of values that describe this anomaly are : 
*				No numerical values needed.
*

*     @param CATCGMEdge_LinearEdgeCurveWithOverSizedPolDeg       : 
*		----------------------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an Edge.
*
*           The "CATCGMEdge_LinearEdgeCurveWithOverSizedPolDeg" anomaly detects,
*           if the given edge E has an Edge Curve (with Polynom Deg >1) 
*			that can be approximated by a Line within a given tolerance.
*			
*			The Check is done on the Ref Curve of the Edge Curve. 
*
*			- Parameters :
*			--------------
*				- Tolerance : specify the Maximal deviation tolerance accepted for Linear approximation
*					- Parameter Label			: CATExplicitLabelParameter_Tolerance
*					- Parameter Default value	: The default value is the tolerance of the factory
*							under scope (0.001*FactoryScale).
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2] : the Edge Curve federated of by the Edge and on which linearity has been detected 
*
*           The List of values that describe this anomaly are : 
*              - ListOfValues[1] : The maximal deviation tolerance used
*

*     @param CATCGMShell_AdjacentFacesSharpAngle       : (Not yet implemented)
*		----------------------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets S_D be a shell.
*
*           The "CATCGMShell_AdjacentFacesSharpAngle" anomaly detects,
*           if in the given shell S_D, there are pair of adjacent faces 
*			that have sharp angle at the edges that bound both  faces
*			
*
*			- Parameters :
*			--------------
*				- XXXXX : specify the XXXXXXXXXX XXXXXXXXXX
*					- Parameter Label			: CATExplicitLabelParameter_xxxxx
*					- Parameter Default value	: xxx default value xxxxx
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Shell on which the anomaly has been detected
*              - ListOfObjects[2] : XXXXXXXXXXXX
*
*           The List of values that describe this anomaly are : 
*              - ListOfValues[1] : XXXXXXXXXX
*

*     @param CATCGMFace_AreaDegenerated       : 
*		---------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a face.
*
*           The "CATCGMFace_AreaDegenerated" anomaly detects,
*           if the given face F, has an area smaller than a given tolerance 
*			specified by the user through the Min Area parameter.
*
*			If user specifies both "Min Area" and a "Max Area" values, 
*			than check will retrieve Faces that have areas bounded 
*			by these two values.
*			
*
*			- Parameters :
*			--------------
*				- Min Area : specify the minimum area that an edge should has. 
*					- Parameter Label			: CATExplicitLabelParameter_MinArea
*					- Parameter Default value	: The default value is ((0.001*FactoryScale)²).
*
*				- Max Area : specify the "Max Area" that an face should not exceed. 
*					- Parameter Label			: CATExplicitLabelParameter_MinArea
*					- Parameter Default value	: no predifined default value.
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the Face on which anoamly is detected
*				   - ListOfObjects[2] :the surface, federated by the Face, on which area has been computed.
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the "Min Area" used to retrieve faulty Face
*              - ListOfValues[2] : the "Max Area" used to retrieve faulty Face
*              - ListOfValues[3] : the area of the faulty Face
*

*     @param CATCGMLump_VolumeDegenerated       : 
*		---------------------------------------
*
*			- Definition :
*			--------------	
*           Lets L be a lump.
*
*           The "CATCGMLump_VolumeDegenerated" anomaly detects,
*           if the given lump L, has a volume smaller than a given tolerance 
*			specified by the user through the Min Volume parameter.
*
*			If user specifies both "Min volume" and a "Max volume" values, 
*			than check will retrieve Lumps that have volumes bounded 
*			by these two values.
*
*			- Parameters :
*			--------------
*				- Min Volume : specify the minimum volume that a lump should has. 
*					- Parameter Label			: CATExplicitLabelParameter_MinVolume
*					- Parameter Default value	: The default value is ((0.001*FactoryScale)^3).
*
*				- Max Volume : specify the "Max Volume" that a lump should not exceed. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxVolume
*					- Parameter Default value	: no predifined default value.
*
*				- Check Min Length Bounding Box : specify that the check will track Lumps with degenerated bounding box in one direction. 
*					This means Bounding box with length smaller lthan a given tolerance (Min BB Dim).
*					- Parameter Label			: CATExplicitLabelParameter_Check_MinLengthBB
*					- Parameter Default value	: default value is FALSE (not activated).
*
*				- Check Min Area Bounding Box : specify that the check will track Lumps with degenerated bounding box in 2 directions. 
*					This means Bounding box with at least one side area smaller than a given tolerance (Min BB Dim).
*					- Parameter Label			: CATExplicitLabelParameter_Check_MinAreaBB
*					- Parameter Default value	: default value is FALSE (not activated).
*
*				- Check Min Volume Bounding Box : specify that the check will track Lumps with degenerated bounding box in 3 directions. 
*					This means Bounding box with at least one side volume smaller than a given tolerance (Min BB Dim).
*					- Parameter Label			: CATExplicitLabelParameter_Check_MinVolumeBB
*					- Parameter Default value	: default value is FALSE (not activated).
*
*				- Min BB Dim : specify the minimum Dim that the Bounding Box should has.
*						 if "Check Min Length Bounding Box" is enabled the "Min BB Dim" is related to a length
*						 if "Check Min Area Bounding Box" is enabled the "Min BB Dim" is related to an area
*						 if "Check Min Volume Bounding Box" is enabled the "Min BB Dim" is related to an volume
*					- Parameter Label			: CATExplicitLabelParameter_Check_MinDimBB
*					- Parameter Default value	: default value is FALSE (not activated).
*
*				- Check per Volume : specify that the check has to be done on each volume that belong to the Lump under scope. 
*					This concern only the case when user activate the check of the dimension of the bounfding box in one, two or three direction.
*					- Parameter Label			: CATExplicitLabelParameter_Check_PerVolume
*					- Parameter Default value	: default value is FALSE (not activated).
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the Lump on which anoamly is detected
*				   - ListOfObjects[i] :the i_th faulty volume, federated by the Lump, (only if Check on Dim of BB and Check Per Volume are activated)
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the "Min Volume" used to retrieve faulty Lump
*              - ListOfValues[2] : the "Max Volume" used to retrieve faulty Lump
*              - ListOfValues[i] : the "Min Dim BB" used to retrieve faulty Lump
*

*     @param CATCGMFace_PatchAreaDegenerated     : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Let F be a face.
*
*           The "CATCGMFace_PatchAreaDegenerated" anomaly detects, 
*			on the Surface federated by the Face under scope, if one of its 
*           patch has a degenerated area, i.e smaller than a given tolerance 
*			specified by the user through the Min Area parameter.
*
*			If user specifies both "Min Area" and a "Max Area" values, 
*			than check will retrieve Faces that have Surface with at least 
*			one patch area bounded by these two values.
*
*			- Parameters :
*			--------------
*				- Min Area : specify the minimum area that a Patch of a Surface should has. 
*					- Parameter Label			: CATExplicitLabelParameter_MinArea
*					- Parameter Default value	: The default value is (0.001*FactoryScale)².
*
*				- Max Area : specify the "Max Area" that a Patch of a Surface should not exceed. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxArea
*					- Parameter Default value	: no predifined default value.
*
*				- Type of Measure (Area or Perimeter) : specify if the check has to compute the area or the perimeter of the Patch. 
*					- Parameter Label			: CATExplicitLabelParameter_TypeOfMeasure_AreaOrLength
*						Legal values : 0 (Area) / 1 (Perimeter)
*					- Parameter Default value	: The default value is 0 (Area).
*
*				- Check Narrow Patches	: specify that faces will be considered faulty if it's length in U or V direction fall in the given interval.
*					- Parameter Label			: CATExplicitLabelParameter_Check_NarrowPatch
*					- Parameter Default value	: The default value is FALSE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the Face that has a Surface with faulty patches
*				   - ListOfObjects[2] : the Surface on which faulty patches have been detected
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the value of the "Type of Measure (Area or Perimeter) " parameter
*              - ListOfValues[2] : the "Min Area" used to retrieve faulty Face
*              - ListOfValues[3] : the "Max Area" used to retrieve faulty Area (-1 if not set by the user)
*              - ListOfValues[4] : the value of the "Check of Narrow Patch" parameter
*              - ListOfValues[i], ListOfObjects[i+1], ListOfObjects[i+2] : the U_Idx and V_Idx of each faulty patch with its Area (perimeter, or U(V) extension)
*

*     @param CATCGMSetOfBody_EmbeddedWireBodies     : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Let B2, B2,...Bn be a set of bodies.
*
*           The "CATCGMSetOfBody_EmbeddedWireBodies" anomaly detects, 
*			if there are exactly or partially (optionally) embedded wire bodies among the bodies 
*			given to the CATIPGMExplicitCheckOperator operator. 
*
*			For every pair of overlapped wire bodies a report will be raised 
*			- Parameters :
*			--------------
*				- Tolerance (NOT YET AVAILABLE) : specify the tolerance used to detect the confusion between wires bodies. 
*					- Parameter Label			: CATExplicitLabelParameter_Tolerance
*					- Parameter Default value	: The default value is (0.001*FactoryScale).
*
*				- Check Partial Overlapping	: specify that partial embedded wires bodies will be considered faulty.
*					- Parameter Label			: CATExplicitLabelParameter_Check_PartialOverlaping
*					- Parameter Default value	: The default value is FALSE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the 1st Wire Body that has is embedded with another body
*				   - ListOfObjects[2] : the 2nd Wire Body embedded with the first one
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the "Tolerance" used to detect confusion.
*              - ListOfValues[2] : the "kind of overalapping" : Partial (1), Exact (2)
*

*     @param CATCGMSetOfBody_EmbeddedSkinBodies     : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Let B2, B2,...Bn be a set of bodies.
*
*           The "CATCGMSetOfBody_EmbeddedSkinBodies" anomaly detects, 
*			if there are exactly or partially (optionally) embedded skins bodies among the bodies 
*			given to the CATIPGMExplicitCheckOperator operator. 
*
*			For every pair of overlapped skin bodies a report will be raised 
*			- Parameters :
*			--------------
*				- Tolerance (NOT YET AVAILABLE) : specify the tolerance used to detect the confusion between Skins bodies. 
*					- Parameter Label			: CATExplicitLabelParameter_Tolerance
*					- Parameter Default value	: The default value is (0.001*FactoryScale).
*
*				- Check Partial Overlapping	: specify that partial embedded skins bodies will be considered faulty.
*					- Parameter Label			: CATExplicitLabelParameter_Check_PartialOverlaping
*					- Parameter Default value	: The default value is FALSE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the 1st Skin Body that has is embedded with another body
*				   - ListOfObjects[2] : the 2nd Skin Body embedded with the first one
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the "Tolerance" used to detect confusion.
*              - ListOfValues[2] : the "kind of overalapping" : Partial (1), Exact (2)
*

*     @param CATCGMSetOfBody_EmbeddedSolidBodies     : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Let B2, B2,...Bn be a set of bodies.
*
*           The "CATCGMSetOfBody_EmbeddedSolidBodies" anomaly detects, 
*			if there are exactly or partially (optionally) embedded solids bodies among the bodies 
*			given to the CATIPGMExplicitCheckOperator operator. 
*
*			For every pair of overlapped solids bodies a report will be raised 
*			- Parameters :
*			--------------
*				- Tolerance (NOT YET AVAILABLE) : specify the tolerance used to detect the confusion between Solids bodies. 
*					- Parameter Label			: CATExplicitLabelParameter_Tolerance
*					- Parameter Default value	: The default value is (0.001*FactoryScale).
*
*				- Check Narrow Patches	: specify that partial embedded solids bodies will be considered faulty.
*					- Parameter Label			: CATExplicitLabelParameter_Check_PartialOverlaping
*					- Parameter Default value	: The default value is FALSE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the 1st Soild Body that has is embedded with another body
*				   - ListOfObjects[2] : the 2nd Solid Body embedded with the first one
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the "Tolerance" used to detect confusion.
*              - ListOfValues[2] : the "kind of overalapping" : Partial (1), Exact (2)
*

*     @param CATCGMBody_EmbeddedFaces     : 
*		-----------------------------------
*
*			- Definition :
*			--------------	
*           Let B be a body.
*
*           The "CATCGMBody_EmbeddedFaces" anomaly detects, 
*			if there are exactly or partially (optionally) embedded faces in the selected Body B
*
*			- Parameters :
*			--------------
*				- Tolerance (NOT YET AVAILABLE) : specify the tolerance used to detect the confusion between faces. 
*					- Parameter Label			: CATExplicitLabelParameter_Tolerance
*					- Parameter Default value	: The default value is (0.001*FactoryScale).
*
*				- Check Partial Overlapping	: specify that partial embedded faces will be considered faulty.
*					- Parameter Label			: CATExplicitLabelParameter_Check_PartialOverlaping
*					- Parameter Default value	: The default value is FALSE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the 1st Soild Body that has is embedded with another body
*				   - ListOfObjects[2] : the 2nd Solid Body embedded with the first one
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the "Tolerance" used to detect confusion.
*              - ListOfValues[2] : the "kind of overalapping" : Partial (1), Exact (2)
*

*     @param CATCGMFace_Folded     : 
*		----------------------------
*
*			- Definition :
*			--------------	
*           Let F be a face.
*
*           The "CATCGMFace_Folded" anomaly detects if the angle between surface normals of two adjacent points
*			is greater then a given angular tolerance (Min Angle).
*			
*
*			- Parameters :
*			--------------
*				- Min Angle (Degree)  : specify the angular tolerance. If the Angle between two adjacent normal 
*					is below this tolerance then the face will considered as faulty. 
*					- Parameter Label			: CATExplicitLabelParameter_Min_Angle_Deg
*					- Parameter Default value	: no predefined default value.
*
*				- Nb Points Per Direction	: specify the point sample size in each direction of a patch (U-Direction & V-Direction).
*					- Parameter Label			: CATExplicitLabelParameter_NbPointsPerSegment
*					- Parameter Default value	: no predefined default value.
*
*				- Nb Adjacent Points 	: for each point "Pt" generated from the sampling, the number of adjacent points indicates 
*					the points that are used to check the angular deviation with the current point "Pt".
*					- Parameter Label			: CATExplicitLabelParameter_NbAdjacentPoints
*					- Parameter Default value	: no predefined default value.
*
*				- Check On Face Limits 	: the Check will be done on the limits of the face. If not enabled, the Check will be done 
*					on the max limits of the surface federated by the face under scope.
*					- Parameter Label			: CATExplicitLabelParameter_Check_OnFaceLimits
*					- Parameter Default value	: the default value is TRUE.
*
*				- Check Only on Boundaries 	: the Check will be done on the boundary of the Face. 
*					on the max limits of the surface federated by the face under scope.
*					- Parameter Label			: CATExplicitLabelParameter_Check_OnlyBoundaries
*					- Parameter Default value	: the default value is FALSE.
*
*				- Check On Neighbor Segments	:  (NOT YET AVAILABLE)
*					
*					- Parameter Label			: CATExplicitLabelParameter_Check_NeighborSegments
*					- Parameter Default value	: the default value is FALSE.
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the Face on which anomaly is detected 
*				   - ListOfObjects[2] : the surface federated by the Face under scope
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the "Angular Tolerance" used to detect angular deviation.
*              - ListOfValues[i],ListOfValues[i+1],ListOfValues[i+2],ListOfValues[i+3],ListOfValues[i+4] : 
*						the detected faulty angle between the surface normals of the points with folowing params : (U_Param, V_Param) and (U_Param', V_Param').  
*

*     @param CATCGMShell_ConfusedFreeEdges     : 
*		----------------------------
*
*			- Definition :
*			--------------	
*           Let S_D be a Shell.
*
*           The "CATCGMShell_ConfusedFreeEdges" anomaly detects if the shell S_D contains holes within a given tolerance.
*			It checks if in the shell S_D there is a narrow "ring of free edges" i.e where the distance between its free edges smaller than a given tolerance.
*			Detection of this kind of configuration might highlight that possible errors during design process result in faces not joined.
*			
*
*			- Parameters :
*			--------------
*				- Narrow Tolerance : specify the tolerance used to detect holes in the shell. 
*					- Parameter Label			: CATExplicitLabelParameter_NarrowTolerance
*					- Parameter Default value	: The default value is (0.001*FactoryScale).
*
*				- Nb Points Per Segment	: specify the point sample size for each arc of curve federated by a free edge.
*					- Parameter Label			: CATExplicitLabelParameter_NbPointsPerSegment
*					- Parameter Default value	: no predefined default value.
*
*				- Check on Partially narrow 	: the Check will also détects if there are ring of free edges partially narrow
*					on the max limits of the surface federated by the face under scope.
*					- Parameter Label			: CATExplicitLabelParameter_Check_IfClosedBoundariesIsPartiallyNarrow
*					- Parameter Default value	: the default value is FALSE.
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the Shell on which anomaly is detected 
*				   - ListOfObjects[i],ListOfObjects[i+1],... : detected free edges that represent sets of holes 
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the "Narrow Tolerance" used to detect holes in the shell.
*              - ListOfValues[i]:  the size of the  group of edges that represent hooles, i.e narrow ring of free edges.
*


*     @param CATCGMWire_DiscontinuityG0       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets W be a wire domain.
*
*           The "CATCGMWire_DiscontinuityG0" anomaly detects,
*           on a given body B, if it federates directly more than one domain.
*				
*
*			- Parameters :
*			--------------
*				- Check Wire Body : Set to 1, enables to check, in case where B 
*										  is a Wire Body, if it contains more than 1 wire
*					- Parameter Label : CATExplicitLabelParameter_Check_WireBody
*				- Check Skin Body : Set to 1, enables to check, in case where B 
*										  is a Skin Body, if it contains more than 1 shell
*					- Parameter Label : CATExplicitLabelParameter_Check_SkinBody
*				- Check Solid Body : Set to 1, enables to check, in case where B 
*										  is a Solid Body, if it contains more than 1 Lump
*					- Parameter Label : CATExplicitLabelParameter_Check_SolidBody
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Body on which the anomaly has been detected
*              - ListOfObjects[2] : first domain federated by the body B
*              - ListOfObjects[3] : second domain federated by the body B
*              - ListOfObjects[..] : ....
*
*           The List of values that describes this anomaly is : 
*              - the given parameter Check Wire Body : 0 or 1 
*              - the given parameter Check Skin Body : 0 or 1 
*              - the given parameter Check Solid Body : 0 or 1 
*

*    @param CATCGMEdge_NulCurvatureRadius       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an Edge.
*
*           The "CATCGMEdge_NulCurvatureRadius" anomaly detects,
*           if the Ref Curve of the edge E has 
*				    a curvature radius smaller than a given limit.
*
*			- Parameters :
*			--------------
*				- Min Curvature Radius  : the minimun radius allowed 
*					- Parameter Label : CATExplicitLabelParameter_MinCurvatureRadius
*					- Parameter Default value	: The default value of the Curfvature "Radius" is equal to the factory resolution
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			N.B : when select this specific anomaly, default parameter is factory tolerance 
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2] : Ref Curve on which the Curvature Radius has been computed
*
*           The List of values that describes this anomaly is :
*              - the value of the faulty Curvature radius of the Ref Curve of the Edge
*              - the parameter of the Ref Curve where faulty Curv Radius is located
*			   - the XCoord, YCoord, ZCoord of the point on the Ref Curve  where faulty Curv Radius is located
*			   - the Min Curvature Radius used
*

*     @param CATCGMFace_PatchLengthDegenerated              : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face.
*
*           The "CATCGMFace_PatchLengthDegenerated" anomaly detects
*           if the Surface referenced by the face F has 
*				    Patches smaller than a given limit in U or V direction
*
*			- Parameters :
*			--------------
*				- Min Patch length  : the minimun patch length allowed.
*					- Parameter Label : CATExplicitLabelParameter_MinLength
*				
*			N.B : when select this specific anomaly, default parameter is factory tolerance
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Surface referenced by the Face F
*
*           The List of values that describes this anomaly is :
*              - the min length patch given as parameter
*              - the patch number of the underlying surface in the U direction
*              - the patch number of the underlying surface in the V direction
*              - the length of the patch
*

*     @param CATCGMEdgeDomain_LengthDegenerated     : 
*		---------------------------------------------
*
*			- Definition :
*			--------------	
*           Let E_D be an edge domain (wire or loop).
*
*           The "CATCGMEdgeDomain_LengthDegenerated" anomaly detects if the length
*           of the edge domaine E_D  is smaller than a given tolerance 
*			specified by the user through the Min Length parameter.
*
*			If user specifies both "Min Length" and a "Max Length" values, 
*			than check will retrieve Edge Domain that have lengths bounded 
*			by these two values.
*
*			- Parameters :
*			--------------
*				- Min Length : specify the minimum length that an edge should has. 
*					- Parameter Label			: CATExplicitLabelParameter_MinLength
*					- Parameter Default value	: The default value is the length tolerance of the factory
*							under scope (0.001*FactoryScale).
*
*				- Max Length : specify the "Max Length" that an edge should not exceed. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxLength
*					- Parameter Default value	: no predifined default value.
*
*				- Check Wire Domain	: specify that the check is enabled for wire domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain	: specify that the check is enabled for loop domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				   - ListOfObjects[1] : the Edge Domain on which anomaly is detected
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the "Min Length" used to retrieve faulty Curve
*              - ListOfValues[2] : the "Max Length" used to retrieve faulty Curve (-1 if not set by the user)
*              - ListOfValues[3] : the length of the faulty edge domain.
*

*     @param CATCGMPOEC_GapXYZ                   : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Let POEC a Point on Edge Curve and suppose that POEC reference the Edge Curve E_C that contains N Curves.
*           potential points where each one is evaluated on a distinct PCurve.                                                                                                                                                                             
*
*           The "CATCGMPOEC_GapXYZ" anomaly detects if there is a gap between the Point on the Ref Curve 
*			and Point on the Comp Curve (other Curves that the Ref Curve federated by the E_C).
*           The Tolerance of the factory is used.
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				- ListOfObjects[1] : POEC on which the gap has been detected
*				- ListOfObjects[2] : the Ref Curve of the Edge Curve reference by the POEC under scope
*				- ListOfObjects[i] : the curve on which the evaluated Point has a distance to The Ref point 
*									(evaluated on the Ref Curve) greater than a Tolerance 
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the used tolerance for gap detection
*              - ListOfValues[i] : the i-th detected gap.
*

*     @param CATCGMFace_WithAnalyticalOrProceduralSurface                   : 
*		---------------------------------------------------------------------
*
*			- Definition :
*			--------------	
*           Let F be a Face with the surface S as its underlying geometry.
*
*           The "CATCGMFace_WithAnalyticalOrProceduralSurface" anomaly detects if the Surface S is of Analytical type or Procedural Type. 
*			Analytical Surface is a canonical surface, surface that can be described by a mathematical Equation as Ellipsoid, Sphere, ... 
*			Procedural Surface is a surface that its definition rely on another surface, as exemple we can mention : 
*			Ruled Surface, Revolution Surface, ... 
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				- ListOfObjects[1] : Face on which the anomaly has been detected
*				- ListOfObjects[2] : the underlying surface of the face under scope
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the type of the surface (1 : Analytical, 2: Procedural)
*

*     @param CATCGMEdge_WithAnalyticalOrProceduralCurve                   : 
*		---------------------------------------------------------------------
*
*			- Definition :
*			--------------	
*           Let E be an Edge with the Edge Curve E_C as its underlying geometry, that contain N Curves {C_i}
*
*           The "CATCGMEdge_WithAnalyticalOrProceduralCurve" anomaly detects if on of its Curve C_i is of Analytical type or Procedural Type. 
*			Analytical Curve is a canonical curve, surface that can be described by a mathematical Equation as Ellipse, Parabol, ... 
*			Procedural Curve is a curve that its definition rely on another curve, as exemple we can mention : 
*			NonLinear Transfo PCurve, Trimmed PCurve, ... 
*
*			- Parameters :
*			--------------
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				- ListOfObjects[1] : Edge on which the anomaly has been detected
*				- ListOfObjects[i] : the detected Anlaytical of Procedural Curve 
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the type of the Curve (1 : Analytical, 2: Procedural)
*

*     @param CATCGMFace_SurfaceWithHighNumberOfCtrlPoints     : 
*		-------------------------------------------------------
*
*			- Definition :
*			--------------	
*           Let F be a face with a Nubs Surface surface S as its underlying geometry.
*
*           The "CATCGMFace_SurfaceWithHighNumberOfCtrlPoints" anomaly detects whether the Number of Conrol Point 
*			of a Nurbs Surface does not exceed a given limit given by the user.
*
*			- Parameters :
*			--------------
*				- Max Nb Of Ctrl Pts : specify the maximum allowed number of Control Points in The Nurbs Surface.
*					- Parameter Label			: CATExplicitLabelParameter_MaxNumberOfCtrlPoints
*					- Parameter Default value	: no predifined default value.
*
*				- Max Nb Of Ctrl Pts in U or V direction : specify the maximum allowed number of Control Points 
*							in The Nurbs Surface in U or V direction
*					- Parameter Label			: CATExplicitLabelParameter_MaxNumberOfCtrlPointsInParamDir
*					- Parameter Default value	: no predifined default value.
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				- ListOfObjects[1] : Face on which the anomaly has been detected
*				- ListOfObjects[2] : the underlying surface of the face under scope
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[1] : the Nb of Ctrl Points of the Nurbs Surface (0 means that user does not set the Max Number of Cotnrol Points allowed)
*              - ListOfValues[2] : the Max Nb of Ctrl Points of the Nurbs Surface set by the User 
*              - ListOfValues[3] : the Nb of Ctrl Points of the Nurbs Surface in U direction (0 means that user does not set the Max Number of Cotnrol Points in U or V direction allowed)
*              - ListOfValues[4] : the Max Nb of Ctrl Points of the Nurbs Surface in U or V direction set by the User 
*              - ListOfValues[5] : the Nb of Ctrl Points of the Nurbs Surface in V direction (0 means that user does not set the Max Number of Cotnrol Points in U or V direction allowed)
*              - ListOfValues[6] : the Max Nb of Ctrl Points of the Nurbs Surface in U or V direction set by the User 
*

*     @param CATCGMSurface_MultiFaces     : 
*		-------------------------------------------------------
*
*			- Definition :
*			--------------	
*           Let S be a surface.
*
*           The "CATCGMSurface_MultiFaces" anomaly detects whether the surface under scope is referenced by more than one Faces 
*			among the selected bodies given to the CATIPGMExplicitCheckOperator operator.
*
*			- Parameters :
*			--------------
*				- Check Skin Body	: specify that the check is enabled for objects that are Skin Bodies. 
*					- Parameter Label			: CATExplicitLabelParameter_Check_SkinBody
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Solid Body	: specify that the check is enabled for objects that are Solid Bodies. 
*					- Parameter Label			: CATExplicitLabelParameter_Check_SolidBody
*					- Parameter Default value	: The default value is TRUE
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*				- ListOfObjects[1] : Surface on which the anomaly has been detected
*				- ListOfObjects[i] : the faces that share the surface under scope, grouped by their belonging to the same body 
*
*           The List of values that describes this anomaly is :
*              - ListOfValues[i] : the size of each group of faces that share the surface and belong to the same body 
*

*     @param CATCGMFace_PlanarSurfaceWithOverSizedPolDeg       : 
*		----------------------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face with the surface S its underlying geometry.
*
*           The "CATCGMFace_PlanarSurfaceWithOverSizedPolDeg" anomaly detects,
*           if the surface of the given face F has Patches that can be 
*			approximated by a Plane within a given tolerance.
*
*			- Parameters :
*			--------------
*				- Tolerance : specify the Maximal deviation tolerance accepted for Planar approximation
*					- Parameter Label			: CATExplicitLabelParameter_Tolerance
*					- Parameter Default value	: The default value is the tolerance of the factory
*							under scope (0.001*FactoryScale).
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : the surface federated of by the face and on which patch planarity has been detected 
*
*           The List of values that describe this anomaly are : 
*				- ListOfValues[1] : The maximal deviation tolerance used        
*				- ListOfValues[i], ListOfValues[i+1]: The (U_Idx,V_Idx) of the detected planar patch.
*		
*

*     @param CATCGMSurface_UnusedPatches :
*		---------------------------------
*
*			- Definition :
*			--------------	
*           Lets S be a Surface.
*
*           The "CATCGMSurface_UnusedPatches" anomaly detects,
*           patches of surface that are not used by faces of the factory.
*
*			- Parameters :
*			--------------
*				Currently no parameters required to tunes this anomaly
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : the surface federated of by the face under scope
*
*           The List of values that describe this anomaly are : 
*				- The U-IDx of the faulty patch.
*				- The V-IDx of the faulty patch.
*

*     @param CATCGMEdgeDomain_SharpAngleOnAdjacentEdges       : 
*		----------------------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E_D be an Edge Domain that contains {E_i}i edges.
*
*           The "CATCGMEdgeDomain_SharpAngleOnAdjacentEdges" anomaly detects,
*           if there is adjacent edges (E_i, E_j) with sharp angle at their bounded vertex.
*
*
*			- Parameters :
*			--------------
*				- Min Angle (Degree) : The max angle tolerated below which adjacent edges will be considered sharp 
*					- Parameter Label			: CATExplicitLabelParameter_Min_Angle_Deg
*					- Parameter Default value	: The default value is the G1-Discontinuity tolerance of the factory
*							under scope (0.5°).
*					
*				- Check Wire Domain	: specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain	: specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Edge Domain on which the anomaly has been detected
*              - ListOfObjects[i], ListOfObjects[i+1] : pair of adjacent edges where sharpnes has been detected
*
*           The List of values that describe this anomaly are : 
*				- ListOfValues[1] : The Min Angle below which the sharpness is detected
*				- ListOfValues[i] : The sharpness angle computed on the faultyi_th  pair of adjacent edges.
*

*     @param CATCGMEdge_ConfusedExtremities       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an Edge with Vs and Ve as its vertices extremities.
*
*           The "CATCGMEdge_ConfusedExtremities" anomaly detects,
*           if there Vs and Ve are confused, i.e if the distance between them
*			are below a given tolerance.
*
*
*			- Parameters :
*			--------------
*				- Tolerance : The min distance tolerated between the vertices. 
*					- Parameter Label			: CATExplicitLabelParameter_Tolerance
*					- Parameter Default value	: The default value is the G0-Discontinuity tolerance of the factory
*							under scope (0.001*FactoryScale).
*
*				- Check Wire Domain	: specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain	: specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*					
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2], ListOfObjects[3] : the vertices of the edge
*
*           The List of values that describe this anomaly are : 
*				- ListOfValues[1] : The used tolerance below which the confusion is detected.
*				- ListOfValues[2] : The distance between the confused vertices of the edge
*

*     @param CATCGMFace_DegeneratedBoundaryPatchLength : 
*		----------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a face with the surface S as its undelying geometry.
*
*           The "CATCGMFace_DegeneratedBoundaryPatchLength" anomaly detects,
*           if there is a patch is narrow with a length boundary less than a given tolerance 
*			or outside a given interval.
*
*			- Parameters :
*			--------------
*				- Min Length : specify the minimum length that a boundary patch should has. 
*					- Parameter Label			: CATExplicitLabelParameter_MinLength
*					- Parameter Default value	: The default value is the length tolerance of the factory
*							under scope (0.001*FactoryScale).
*
*				- Max Length : specify the maximum length that a boundary patch should not exceed. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxLength
*					- Parameter Default value	: no predifined default value.
*
*				- Check Only Patch Boundary Length	: if FALSE the criteria will retrieve patches 
*													  that have isopar length  (in u or v direction)  
*													  less a given tolerance or outside a given interval.
*													  	
*					- Parameter Label			: CATExplicitLabelParameter_CheckOnlyPatchBoundaryLength
*					- Parameter Default value	: The default value is TRUE
*				
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Surface referenced by the Face F
*
*           The List of values that describes this anomaly is :
*              - the min length patch given as parameter
*              - the max length patch given as parameter
*              - the u-idx of the faulty patch
*              - the v-idx of the faulty patch
*              - the faulty length of the patch

*     @param CATCGMEdge_WavyPlanarCurve : 
*		-------------------------------
*
*			- Definition :
*			--------------	
*           Lets E be an edge with the Curve C as its undelying geometry (Ref. Curve).
*
*           The "CATCGMEdge_WavyPlanarCurve" anomaly detects,
*           if there the Curve C is planar and has a number of inflection points greater than given limit.
*			User has to fix the number of allowed inflection points for a given adjacent arcs number
*
*			- Parameters :
*			--------------
*				- Number of arcs : specify the size of arc group to take into account. If not set the
*								   the criteria will take into account all the arcs of the curve.	
*					- Parameter Label			: CATExplicitLabelParameter_NbArcsPerGroup
*					- Parameter Default value	: no predifined default value. 
*
*				- Max Nb Inflection Pts : specify the maximum inflection point allowed for a group of adj. arcs. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxNbInflectionPts
*					- Parameter Default value	: no predifined default value.
*
*				- Infinite Curvature Radius	: threshold value for an “infinite” curvature radius. Any curvature
*											  radius greater than this value will be considered infinite .
*					- Parameter Label			: CATExplicitLabelParameter_InfiniteCurvatureRadius
*					- Parameter Default value	: no predifined default value.
*
*				- Check Wire Domain : specify that the check is enabled for Wire Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckWireDomain
*					- Parameter Default value	: The default value is TRUE
*
*				- Check Loop Domain : specify that the check is enabled for Loop Domain. 
*					- Parameter Label			: CATExplicitLabelParameter_CheckLoopDomain
*					- Parameter Default value	: The default value is TRUE
*					
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Edge on which the anomaly has been detected
*              - ListOfObjects[2] : Ref Curve referenced by the Edge E
*
*           The List of values that describes this anomaly is :
*              - the Infinite Curvature Radius given as parameter
*              - the number of faulty arc groups
*			For each faulty arc group
*              - the start idx of the the arc 
*              - the end idx of the arcs
*              - the number of inflection pts for the faulty arc group
*			   - coordinates X, Y, Z of each inflection point
*

*     @param CATCGMFace_WavySurface : 
*		---------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a face with the surface S as its undelying geometry.
*
*           The "CATCGMFace_WavySurface" anomaly detects,
*           if there the Surface S has isopars with number of inflection points greater than a given limit.
*			User has to fix the number of allowed inflection points for a given adjacent arcs number
*
*			- Parameters :
*			--------------
*				- Check On Arc Or IsoParam Crv : specify if the check of maximunm allowed inflection points 
*											     will be done of the arc of the isopar or on the entire arcs 
*												 of the isopar.
*					- Parameter Label			: CATExplicitLabelParameter_CheckOnArcOrIsoParamCrv
*					- Parameter Default value	: no predifined default value. 
*
*				- Max Nb Inflection Pts : specify the maximum inflection point allowed for a group of adj. arcs. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxNbInflectionPts
*					- Parameter Default value	: no predifined default value.
*
*				- Infinite Curvature Radius	: threshold value for an “infinite” curvature radius. Any curvature
*											  radius greater than this value will be considered infinite .
*					- Parameter Label			: CATExplicitLabelParameter_InfiniteCurvatureRadius
*					- Parameter Default value	: no predifined default value.
*					
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Surface referenced by the Face F
*
*           The List of values that describes this anomaly is :
*              - the Infinite Curvature Radius given as parameter
*              - the max inflection pts allowed (given as parameter)
*              - the number faulty isopars if U-Direction
*			For each faulty IsoPar 
*              - the U-Param of the IsoPar
*              - the number of Inflection Pts
*              - the number of inflection pts for the faulty arc group
*			   - coordinates X, Y, Z of each inflection point
*              - the number faulty isopars if V-Direction
*			For each faulty IsoPar 
*              - the V-Param of the IsoPar
*              - the number of Inflection Pts
*              - the number of inflection pts for the faulty arc group
*			   - coordinates X, Y, Z of each inflection point
*

*     @param CATCGMFace_BigCurvatureRadius : 
*		----------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a Face.
*
*           The "CATCGMFace_BigCurvatureRadius" anomaly detects
*           if the surface referenced by the curvature radius at each ppoint 
*			of the face F is greater than a fixed tolerance.
*
*			- Parameters :
*			--------------
*				- Max Curvature Radius : specify the maximum curvature radius allowed 
*					- Parameter Label			: CATExplicitLabelParameter_MaxCurvatureRadius
*					- Parameter Default value	: no predifined default value.
*
*				- Min Length Of Normal	: tolerance for the minimal length of the normals.
*					- Parameter Label			: CATExplicitLabelParameter_MinLengthOfNormal
*					- Parameter Default value	: no predifined default value.
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Surface federated by the Face on which the anomaly has been detected
*
*           The List of values that describes this anomaly is :
*              - the maximum curvature radius allowed given as parameter
*              - the Max Curvature Radius computed of the face
*

*     @param CATCGMFace_PatchSurfaceSharpnessAngle : 
*	  ------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a face with the surface S as its undelying geometry.
*
*           The "CATCGMFace_PatchSurfaceSharpnessAngle" anomaly detects,
*           if there is an angle (Pseudo) corner patch below outside a given interval.
*			Pseudo corner  : When length of a boundary patch is less a given tolerance than the angle is computed between the boudaries
*			that bounds the degenerated boundary patch.
*
*			- Parameters :
*			--------------
*				- Min Angle Corner : specify the minimum angle allowed for a corner of a Patch. 
*					- Parameter Label			: CATExplicitLabelParameter_MinAngleCorner
*					- Parameter Default value	: no predifined default value.
*
*				- Max Angle Corner : specify the maximum angle allowed for a corner of a Patch. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxAngleCorner
*					- Parameter Default value	: no predifined default value.
*
*				- Min Angle Pseudo Corner : specify the minimum angle allowed for a pseudo corner of a Patch. 
*					- Parameter Label			: CATExplicitLabelParameter_MinAnglePseudoCorner
*					- Parameter Default value	: no predifined default value.
*
*				- Max Angle Pseudo Corner : specify the maximum angle allowed for a pseudo corner of a Patch. 
*					- Parameter Label			: CATExplicitLabelParameter_MaxAnglePseudoCorner
*					- Parameter Default value	: no predifined default value.
*
*				- Min Length Patch Boundary	: the tolerance length below which the boundary patch is considered degenerated.
*					- Parameter Label			: CATExplicitLabelParameter_MinLengthPatchBoundary
*					- Parameter Default value	: no predifined default value.
*
*				- Check Only Face Area	: specify if the check should be done on the limits of the face or on the max limits 
*										  of its underlying surface.
*					- Parameter Label			: CATExplicitLabelParameter_CheckOnlyFaceArea
*					- Parameter Default value	: no predifined default value.
*				
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Surface referenced by the Face F
*
*           The List of values that describes this anomaly is :
*              - the min angle corner patch given as parameter
*              - the max angle corner patch given as parameter
*              - the min angle pseudo corner patch given as parameter
*              - the max angle pseudo corner patch given as parameter
*              - the min length patch boundary patch given as parameter
*              - the u-idx of the faulty patch
*              - the v-idx of the faulty patch
*              - the type of the corner (normal = 0, Pseudo = 1)
*              - the computed angle of the (pseudo) corner
*

*     @param CATCGMFace_PatchSurfaceUndefinedNormal : 
*	  ------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets F be a face with the surface S as its undelying geometry.
*
*           The "CATCGMFace_PatchSurfaceUndefinedNormal" anomaly detects,
*           if there is a Patch with an undifined surface normal at its extremities 
*
*			- Parameters :
*			--------------
*				- Min Length Of Normal : specify the minimum length of Normal allowed for a corner of a Patch. 
*					- Parameter Label			: CATExplicitLabelParameter_MinLengthOfNormal
*					- Parameter Default value	: no predifined default value.
*
*				- Min Length Patch Boundary	: the tolerance length below which the boundary patch is considered degenerated.
*											  In this case, the extremities will be ignored.   	
*					- Parameter Label			: CATExplicitLabelParameter_MinLengthPatchBoundary
*					- Parameter Default value	: no predifined default value.
*				
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Face on which the anomaly has been detected
*              - ListOfObjects[2] : Surface referenced by the Face F
*
*           The List of values that describes this anomaly is :
*              - the min length Of normal allowed given as parameter
*              - the min length patch boundary patch given as parameter
*              - the u-idx of the faulty patch
*              - the v-idx of the faulty patch
*			   - the U-Param of the point at which degenerated normal has been detectetd
*			   - the V-Param of the point at which degenerated normal has been detectetd
*              - the computed normal surface
*
*     @param CATCGMEdgeDomain_InvalidEdgeOrientation       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMEdgeDomain_AdjacentEdgesImproperlyConnected       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMEdgeDomain_WithoutEdges       :
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMVertex_WithoutMacroPoint       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMBody_VertexOutsideBoundingBox       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMEdge_BoundingBoxEmpty       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMBody_IncorrectDomainType       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMBody_InvalidDomainLocation       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMBody_OverlappingEdges       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMEdge_EdgeCurveInvalid       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMPOEC_OutsideEdgeCurveMaxLimitsComplex       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMPOEC_OutsideEdgeCurveMaxLimitsHigh       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMPOEC_OutsideEdgeCurveMaxLimitsLow       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMShell_AdjacentFacesInconsistentOrientation       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMShell_NonManifoldEdge       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMVolume_FreeEdge       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMShell_WithoutFaces       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMShell_FaceOverReferenced       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_POECOutsideUFaceBoundingBox       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_POECOutsideVFaceBoundingBox       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_PCurvesOfEdgesLieOnDifferentSurfaces       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_MatterSideInvalid       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMDomain_CellsDisconnected       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMMacroPoint_WithoutPoints       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMEdge_WithoutPOEC       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMEdge_WithoutVertex       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLump_WithoutVolumes       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMFace_WithoutLoops       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMFace_FirstLoopNotOuter       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMFace_NonFirstLoopNotInner       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_UVBoundingBoxEmpty       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_POECOutsideUBoundingBox       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_POECOutsideVBoundingBox       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_POECOutsideMaxLimitsU       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_POECOutsideMaxLimitsV       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMDomain_MultipleOwnersInsideBody       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMPOEC_OutsidePCurveMaxLimitsComplex       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMPOEC_OutsidePCurveMaxLimitsHigh       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMPOEC_OutsidePCurveMaxLimitsLow       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMLoop_PCurveAndFaceSupportDistinct       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsComplex       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsHigh       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMPOEC_ImageOnRefCurveOutsideMaxLimitsLow       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMEdge_WrongPOECOrientation       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMEdge_CachedMaxGapIncorrect       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMBody_OverlappingVertices       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMVertexInFace_WithoutVertex       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMVertexInFace_InvalidLocation       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMVertexInVolume_WithoutVertex       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*     @param CATCGMVolume_WithoutShell       : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*
*			- Parameters :
*			--------------
*
*			- Features :
*			------------
*           The List of objects that describe this anomaly are :
*
*           The List of values that describe this anomaly are : 
*
*

*     @param CATCGMBody_MixedConvexityEdges      : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets B be a body.
*
*           The "CATCGMBody_MixedConvexityEdges" anomaly detects,
*           on a given body B, if it contains edges that have mixed
*           convexity.  The convexity of the edge on a shell tells
*           which side of the faces adjacent to the edge the volume is on.
*
*			- Parameters :
*			--------------
*				- no parameters.
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Body on which the anomaly has been detected
*              - ListOfObjects[2] : first mixed convexity edge
*              - ListOfObjects[3] : second mixed convexity edge
*              - ListOfObjects[..] : ....
*
*           The List of values that describes this anomaly is : 
*              - No values. 
*

*     @param CATCGMBody_InnerIntersectionBetweenFaces     : 
*		------------------------------------------
*
*			- Definition :
*			--------------	
*           Lets B be a body.
*
*           The "CATCGMBody_InnerIntersectionBetweenFaces" anomaly detects,
*           on a given body B, if it contains inner intersecting faces. In other
*           words faces that intersect in the interrior. 
*
*			- Parameters :
*			--------------
*				- Tolerance : specify the tolerance used to detect the intersection between faces. 
*
*			- Features :
*			------------
*           The List of objects that describes this anomaly is :
*              - ListOfObjects[1] : Body on which the anomaly has been detected
*              - ListOfObjects[2] : first  inner intersecting face
*              - ListOfObjects[3] : second inner intersecting face
*              - ListOfObjects[..] : ....
*
*           The List of values that describes this anomaly is : 
*              - ListOfValues[1] : the "Tolerance" used to detect intersection
*              - ListOfValues[2] : the "kind of intersection" : direct(3)
*
*/
//=========================================================================


/**
* Class designed to describe a detected anomaly on a given object 
* (have a look to CATExplicitCheck)
*<br>
* The CATExplicitReport class store usefull information which describe
* an anomaly occured on a CATICGMObject or a group of CATICGMObject. 
* The class allows only to view information about an anomaly.
* You cannot create, modify or delete an object of type CATExplicitReport
* N.B : An anomaly has degree of severity which could be a Warning or an Error.
* 
* To use a CATExplicitCheck class:
*<ul>
* <li>Retrieve the list of objects concerned by the anomaly <tt>GetListOfObjectInAnomalies</tt>
* <li>Get the severity level of the anomaly (warning or an error) <tt>GetSeverity</tt>
* <li>Retrieve the anomaly message <tt>GetAnomalyMessage</tt>
*</ul> 
*/
class ExportedByCATTopologicalObjects CATExplicitReport: public CATPGMExplicitReport
{

public:

   /** @nodoc @nocgmitf */
   static CATExplicitReport *CATCreateCATExplicitReport(CATLISTP(CATICGMObject)& iListOfCATICGMObject,CATUnicodeString &iMsgErrorOrWarning,CATExplicitCheckSeverity iDegreeOfAnomaly, CATUnicodeString &iDetailedAnomalyMessage);

   /**
   * Get the list of object concerned by the anomaly <tt>ioListOfCATICGMObject</tt>
   * @param ioListOfCATICGMObject 
   *   List of Object implicated by the anomaly. 
   */
   void GetListOfObjectInAnomalies(CATLISTP(CATICGMObject)& ioListOfCATICGMObject);

   /**
   * Get the the anomaly message <tt>ioAnomalyMessage</tt>
   * @param ioAnomalyMessage 
   *   A string which summarize the anomaly kind. 
   */
   void GetAnomalyMessage(CATUnicodeString &ioAnomalyMessage);

   /**
   * Get the severity level of the anomaly (warning or error)
   * @return
   *   The severity level of the anomaly
   */
   CATExplicitCheckSeverity GetSeverity();

   /**
   * Get the anomaly label, the label belongs to the set of labels "CATCGMExplicitCheckAnomaly".
   * The label can be either "CATCGMInternalAnomalies" that correspond to an internal anomaly
   * or one of specific labels that corresponds to a selected specific anomaly
   *   
   * Refer to the CATCGMExplicitCheckAnomaly documentation for details about Specific Anomalies 
   * and their labels
   * @return
   *   the anomaly label
   */
   CATCGMExplicitCheckAnomaly GetType() const;

   /**
   * Get the list of values described the anomaly <tt>ioListOfValues</tt>
   *
   *   Each Anomaly (except Internal_Anomalies) has a List of values that described it.
   *   For example Gap, Number of Elements, Coordinates, Parameters, and so on.
   *   The List of values of a given Anomaly is specifically fomatted and each value
   *   has a specific meaning
   *   Refer to definition of each specific anomaly (Embedded in CATCGMExplicitCheckAnomaly 
   *   definition) for further details about values that describe each specific anomaly
   *
   * @param ioListOfValues 
   *   List of Values described the anomaly. 
   *     
   */
   void GetListOfValues(CATListOfDouble &ioListOfValues);


   /** LifeCycle protection  
   * @return 
   *    Counter value after incrementation
   */
   unsigned int							AddRef();

   /** LifeCycle protection  
   * @return 
   *    Counter value after decrementation
   */
   unsigned int							Release();


   /**
   * @nodoc
   */
   void Dump(CATCGMOutput& os);

   /**
   * @nodoc
   */
   CATUnicodeString & GetDetailedAnomalyMessage();

   /**
   * @nodoc
   * Get a short description of the anomaly.
   * @return
   * A string which contains a short description of the anomaly. 
   */
   virtual CATUnicodeString GetAnomalyDescription() const;

   /**
   * @nodoc
   * Get a detailed description of the anomaly.
   * @return
   * A string which contains a detailed description of the anomaly and how it is formed. 
   */
   virtual CATUnicodeString GetAnomalyDetailedDescription() const;

   /**
   * @nodoc
   * Get a list of anomaly value infos.
   * @param oValueInfos 
   * A list of anomaly value info objects. 
   */
   virtual void GetValueInfo(CATLISTV(CATCGMCheckAnomalyValueInfo) &oValueInfos) const;

   /** @nodoc @nocgmitf */
   void SetType(CATCGMExplicitCheckAnomaly iAnomalyLabel);

   /** @nodoc @nocgmitf */
   void SetListOfValues(CATListOfDouble& iListOfValues);

   /** @nodoc @nocgmitf */
   void SetListOfValueTypes(CATListOfShort& iListOfValueTypes);

   /** @nodoc @nocgmitf */
   void SetListOfObjectsOfAnomaly(CATLISTP(CATICGMObject)& iListOfCATICGMObject);

   /** @nodoc @nocgmitf */
   void ApplyScale(double iScaleFactor);
   /** @nodoc @nocgmitf */
   CATULONG32    HashKey();

   /** @nodoc @nocgmitf */
   int    IsEqual(CATPGMExplicitReport *piExplicitReport);

private:
   CATCGMNewClassArrayDeclare;

   /** @nodoc @nocgmitf */
   HRESULT ComputeListOfValueTypes();

   /** @nodoc @nocgmitf */
   void GetTypeOfValueInStr(CATCXExplicitCheckValueType iValueType,CATUnicodeString& ioStrTypeOfValue);

   /* Data */
   CATLISTP(CATICGMObject)                   _ListOfCATICGMObject;
   CATUnicodeString                          _MsgErrorOrWarning;
   CATUnicodeString                          _DetailedAnomalyMessage;
   CATCGMExplicitCheckAnomaly                _AnomalyLabel;
   CATListOfDouble                           _ListOfValues;
   CATListOfShort                            _ListOfValueTypes;
   CATExplicitCheckSeverity                  _DegreeOfAnomaly;

   CATHTabCATICGMObjectByTag                *_pHashTabOfCATICGMObject;

   /** LifeCycle */
   unsigned int							_Counter;

   //Ctors 
   /** @nodoc @nocgmitf */
   CATExplicitReport(CATLISTP(CATICGMObject)& iListOfCATICGMObject,CATUnicodeString &iMsgErrorOrWarning,CATExplicitCheckSeverity iDegreeOfAnomaly, CATUnicodeString &iDetailedAnomalyMessage);
   /** @nodoc @nocgmitf */
   CATExplicitReport(const CATExplicitReport& iExplicitReport);
   /** @nodoc @nocgmitf */
   CATExplicitReport();
   //Dtors
   /** @nodoc @nocgmitf */
   virtual ~CATExplicitReport();
};

/**
* @nodoc
*/
/**
* Class representing a Hast Table of CATExplicitReport Objects.
*
* <br><b>Role</b>: Provide the basic class function...
* <p>
* Do not use the @href CATCGMUnsmartList constructor to
* do such and such but instead...
*
* @example
*  // example is optional
*  pHT_ExplicitReport = new CATCGMHashTableOfExplicitReport(33);
*
* @href ClassReference, Class#MethodReference, #InternalMethod...
*/

//class ExportedByCATTopologicalObjects CATCGMHashTableOfExplicitReport : public CATCGMHashTable
//{
//public :
//   CATCGMHashTableOfExplicitReport(int iEstimatedSize = 0);  
//   ~CATCGMHashTableOfExplicitReport();
//   CATCGMNewClassArrayDeclare;
//
//   int                  Insert(CATExplicitReport* piExplicitReport);
//   CATExplicitReport*   Locate(CATExplicitReport* piExplicitReport) const;
//   int                  Remove(CATExplicitReport* piExplicitReport);
//};

/** @nodoc @nocgmitf */
ExportedByCATTopologicalObjects
   int TrivialIndexSortCATExplicitReport(CATPGMExplicitReport *left, CATPGMExplicitReport *right);
#endif

