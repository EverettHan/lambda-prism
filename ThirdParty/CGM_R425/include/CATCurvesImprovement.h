//===================================================================
//   
// COPYRIGHT   : DASSAULT SYSTEMES 2000
//
// DESCRIPTION : CurvesImprovement
//
//
//===================================================================
#ifndef CATCurvesImprovement_H
#define CATCurvesImprovement_H

#include "CATIACGMLevel.h"

#include "CATGMOperatorsInterfaces.h"

#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "CATBoolean.h"

#include "CATListOfCATGeometries.h"
#include "CATListOfCATCurves.h"
#include "CATListOfCATCrvParams.h"
#include "CATListOfCATCrvLimits.h"
#include "CATLISTP_CATMathPlane.h"
#include "CATLISTP_CATMathVector.h"
#include "CATFreeFormDef.h"
#include "CATCurvesImprovementDefine.h"
#include "CATCGMVirtual.h"
#include "CATCreateCurvesImprovement.h"
#include "CATPGMCreateCurvesImprovement.h"

class CATLocalizer2DFrom3D;
class CATMathSetOfPoints;
class CATGeoFactory;
class CATSoftwareConfiguration;

// 
//  This operator allows to improve : 
//               1/ connections between CATCurves (geometrical corrections)
//               2/ reduce number of input CATCurves 
//  Each improvement could be requested independently.
//  Improvement is done in 3D space, or in 2D space or both (option hereafter).
//  In case of 2D space, the list of CATCurves must contain CATPcurves on required surface.
//  No ambiguity on supporting surface is allowed in this operator.
//
class ExportedByCATGMOperatorsInterfaces CATCurvesImprovement : public CATCGMVirtual
{
public:
   
   // Destructor
   //
   virtual ~CATCurvesImprovement(); 
   
   //
   // To complete the operator :
   //
   //                  GENERAL OPTION : 
   //                  ----------------
   //
   // In case of "curves on surfaces", to indicate if geometry to correct is 2D
   // representation or 3D representation.
   // The list of CATCurves to improve must been identified before this operator, 
   // according to this option.
   // For correcting 2D representation, a CATLocalizer2DFrom3D is mandatory (see 
   // CATLocalizer2DFrom3D.h)
   // For correcting 3D representation after a previous correction in 2D representation,
   // a NULL pointer is required
   // Default value : NULL pointer (3D Representation)
   //
   virtual void Set2DRepresentationToImprove (CATLocalizer2DFrom3D *iLocalizer) = 0;

   // In case of "curves on surfaces" and iPriority == Deformation. Otherwise, the
   // Run() method returns an error status.
   // Allows to have both 2D and 3D representation for the output curves that have been
   // corrected (fixed curves are unchanged through this mode). Output corrected curves are
   // of CATMergedCurve type where 3D curves are placed as reference curves.
   // Default value : 0 (2D Representation only)
   //
   virtual void SetHybridMode2D3D (int iHybridMode2D3D) = 0;
   
   // To indicate fixed points in the list of CATCurves (extremities only). 
   //
   virtual void SetFixedPoints (CATLISTP(CATCrvParam) *iFixedPoints) = 0;

   // To indicate fixed curves (no modification allowed). 
   //
   virtual void SetFixedCurves (CATLISTP(CATCurve) *iFixedCurves) = 0;
   
   // To fix Lines parts in the curve to clean 
   // Rules :
   // If iFixLevel == 0 no detection (default)
   // If iFixLevel == 1 
   //              one isolate line
   //                  => curve is FIXED
   //              several consecutive lines 
   //                  => NONE is FIXED
   //              one line + one fixed bordering curve 
   //                  => The line is NOT FIXED (except if it has been fixed by SetFixedCurves) 
   // If iFixLevel == 2 => All lines are FIXED
   //
   virtual void SetFixLines (int iFixLines) = 0;

   // To fix Canonics parts in the curve to clean (CANONICS = CURVES WITHOUT KNOTVECTOR, for instance
   // Lines and Circles)
   // Rules :
   // If iFixLevel == 0 no detection (default)
   // If iFixLevel == 1 
   //              one isolate canonic
   //                  => curve is FIXED
   //              several consecutive canonics 
   //                  => NONE is FIXED
   //              one canonic + one fixed bordering curve 
   //                  => The canonic is NOT FIXED (except if it has been fixed by SetFixedCurves) 
   // If iFixLevel == 2 => All canonics are FIXED
   //
   virtual void SetFixCanonics (int iFixLevel) = 0; 

   // In case of "curves on surfaces", to fix transition points between faces.
   // Default value : 0
   //
   virtual void SetFixedTransitions (int iFixTrans) = 0;

   // To indicate curves to delete. 
   //
   // 20062006 Removed 
   // virtual void SetDeletedCurves (CATLISTP(CATCurve) *iDeletedCurves) = 0;
   //
   // To indicate what is the priority if the continuity is too hard to respect with the 
   // MaxDeformationTreshold data.
   // Value in : Deformation, Continuity, NoPriority
   //
   // o Deformation : Priority is to the continuity with taking into account the
   //                 MaxDeformationThreshold. To check whether MaxDeformationThreshold is
   //                 or is not respected by the computation, compare it with GetMaxDeformation.
   // o Continuity  : Priority is to the continuity only: MaxDeformationTreshold is not taken
   //                 into account.
   // o NoPriority  : Not yet implemented. 
   //  
   // Default value : Continuity // New Version : Default Mode : Deformation
   //
   virtual void SetPriorityMode (CATCrvImprvPriority iPriority) = 0;

   //
   //
   //                  CONCERNING GEOMETRICAL CORRECTIONS :
   //                  ------------------------------------
   //
   // Allowed maximum deformation. 
   // It corresponds to the maximum 3D deformation on the list of curves.
   // Default value : G0 resolution = 0.001 
   //
   virtual void SetMaxDeformationThreshold (double iMaxDeformation) = 0;

   // To indicate the continuity level to improve, default value : CATFrFTangentCont 
   // It could be also : CATFrFPointCont, CATFrFCurvatureCont
   //
   virtual void SetLevelContinuityToImprove (CATFrFContinuity iLevel) = 0; 

   // Threshold below which the G0 correction is applied. It is an distance.
   // If the distance between two consecutives curves  < iMaxG0, then G0 correction is applied.
   //
   // Default value : G0 resolution = 0.001 
   //
   virtual void SetG0Threshold (double iMaxG0) = 0;

   // Threshold below which the G0 correction is not applied. It is an distance.
   // If the distance between two consecutives curves  < iMinG0, then G0 correction is not applied.
   //
   // Default value : 0.
   //
   //             +------------+---------------------+------------------> G0 Gap
   //             0          iMinG0                iMaxG0
   // Correction  :     NO               YES                   NO         
   //
   virtual void SetG0MinThreshold (double iMinG0) = 0;

   // Threshold below which the G1 correction is applied. It is an angle in degree.
   // If angle(Tgt1,Tgt2) < iMaxG1, then G1 correction is applied
   // (Tgt1, and Tgt2 are tangent vectors : on extremity of curve1 and origin of curve2).
   //
   // Default value : C1Resolution = 0.5 degree
   //
   virtual void SetG1Threshold (double iMaxG1) = 0;

   // Threshold below which the G1 correction is not applied. It is an angle in degree.
   // If angle(Tgt1,Tgt2) < iMinG1, then G1 correction is not applied
   // (Tgt1, and Tgt2 are tangent vectors : on extremity of curve1 and origin of curve2).
   //
   // Default value : 0. degree
   //
   //
   //             +------------+---------------------+------------------> G1 Gap
   //             0          iMinG1                iMaxG1
   // Correction  :     NO               YES                   NO         
   //
   virtual void SetG1MinThreshold (double iMinG1) = 0;

   // Threshold above which the G2 correction is applied. It is a percentage (in [0,1]).
   // Default value : 0.98
   // If  || Rho1-Rho2|| / ||Rho2|| < (1-percent)/percent, then correction is applied
   // (Rho1, and Rho2 are curvature vectors, where ||Rho1|| < ||Rho2||)
   //
   virtual void SetG2Threshold (double iMinG2) = 0; 

   // Threshold above which the G2 correction is NOT applied. It is a percentage (in [0,1]).
   // Default value : 1.0
   // If  || Rho1-Rho2|| / ||Rho2|| < (1-percent)/percent, then correction is NOT applied
   // (Rho1, and Rho2 are curvature vectors, where ||Rho1|| < ||Rho2||)
   // 
   //             +------------+---------------------+------------------+ G2 Gap
   //             0          iMinG2                iMaxG2
   // Correction  :     NO               YES                   NO       1 
   //
   virtual void SetG2MaxThreshold (double iMaxG2) = 0; 

   // Define if the list of curve is closed
   // Default value : FALSE
   //
   virtual void SetClosure (CATBoolean) = 0;
   
   //
   // Management of "small" curves :
   // ------------------------------
   //
   // Length curve below which curve is considered as "small" curve. Two measurements are
   // available :
   // absolute (iAbsoluteMeasure is TRUE) or 
   // relative (iAbsoluteMeasure is FALSE).
   // (iAbsoluteMeasure wad previously and historically names iKindOfMeasurement, before July 2019)
   // Default value 0.01 (10*G0Resolution), absolute measurement.
   //
   virtual void SetLengthThreshold (double     iSmallLength      ,
                                    CATBoolean iAbsoluteMeasure) = 0;
   
   // How to manage "small" curves : 
   // Value in : NotModified, Modified, Concatenated
   //
   // o NotModified  : "small" curves are kept, the geometrical corrections are made on 
   //                   adjacent curves.
   // o Modified     : "small" curves are geometrically corrected, and adjacent curves
   //                   are kept.
   // o Concatenated : "small" curves are concatenated by smoothing, adjacent curves give
   //                   tangent and curvature on extremities.
   //
   // Default value : Concatenated
   //
   virtual void SetSmallCurvesManagement (CATCrvImprvSmallCurve iChoice) = 0;

   // In case of "curves on surfaces" with previous option value "Concatenated", allows to suppress
   // "small" curves that are isolated on one support on value 1.
   // Default value : 0
   //
   virtual void SetForceSuppressSmall2D (int iForceSuppressSmall2D) = 0;


   // Imposed Ratio on Tangent Norm on discontinuities; By default there is no ratio.
   // The Ratio on the Tangents Between the i_th and the (i+1)_th curves 
   // (ie vertex i) is  
   // r(i) = NormOfTgt(i)/NormOfTgt(i+1)
   // If _ListOfTgtRatios == 0 then there is no imposed ratio.
   // If _ListOfTgtRatios(i) == -1 there is no imposed ratio on this vertex (should be default)
   // Else _ListOfTgtRatios(i) = r(i)
   // Rem : 
   // First & Last Ratios are respectively the Starting and the Ending Point of the Curve to Clean.
   // They Should be set to -1 but for Closed Curve those Two ratios should be equal and positive  
   // Rem2 : The Number of ratios must be equal to the (Number of curves +1)  
   //
   virtual int  SetConnectingTgtRatio ( CATListOfDouble * iListOfTgtRatios) = 0;
   
   // To use local optimization . ONLY AVAILABLE WITH "Deformation" OPTION AND 3D REPRESENTATION
   // Local optimization means : new connections are computed to minimize the 3rd derivative of 
   // the curves (3rd order energy). The goal is to reduce oscillations of curvature combs.
   // The result could be close to we picture.
   // iOptimization = 1 = ON, iOptimization = 0 = OFF;
   //
   // New Version : Default Mode : local optimization : ON
   //
   virtual void SetLocalOptimization (int iOptimization) = 0;

   // Restricted and temporary use. Forbidden. Linked to SetLocalOptimization()
   virtual void SetForceLocalOpti3   (int iForceLocalOpti3Level) = 0;

   // To use global optimization .
   // The aim is to improve the general look of the curves.
   // iOptimization = 1 = ON, iOptimization = 0 = OFF;
   //
   // New Version : Default Mode : Global optimization : ON
   // The GlobalOptimization starts working with a MaxDeformationThreshold higher than 0.005
   // and gives better results with a MaxDeformationThreshold higher than 0.01
   //
   virtual void SetGlobalOptimization (int iOptimization) = 0;

   // Allow the activation of the mapping of the input vertices to the output vertices.
   // @param iApplyMapping
   // If TRUE AND SetContinuityLevel(CATFrFCurvatureCont) AND SetGlobalOptimization(TRUE) AND SetCellReduction(FALSE) 
   // the mapping could be activated then the quality of the wire is very similar to the quality obtained 
   // when the SetCellReduction is to TRUE (Smoother result).
   // but the vertices are kept. After deletion of small edges the position of the remained vertices are saved with their
   // global curvilinear adimensional param (eg Pos(Vi)=Total_Length_From_The_Starting_Extremity_To_Vi/Total_Length_Of_Wire)
   // then a a global smoothing is applyied on a reduced wire and the vertices are reinserted at 
   // New_Pos(Vi)=Pos(Vi)*New_Total_Length_Of_Wire.
   //
   virtual void SetApplyMappingOfInitialVertices (const int iApplyMapping = 0) = 0;

   // Special Case of Use : There is onlyOne Curve in input 
   // Smoothing the curve with the globaloptimization integrated tool
   // if not set the output curve would be the same as input (Default) 
   //
   virtual void SetForceCleanOneCurve() = 0;

   //  o  DefaultC1ToC2Management   :   By default only the C1-curves that need a modification to reach
   //                                    the SetLevelContinuityToImprove continuity becomes C2 ;
   //  o  AllCurvesC1ToC2Management :   if this option is set ALL C1 curves becomes  C2 (exceptions 
   //                                                for fixed curves that are stil untouched) ;
   //  o  NoC1ToC2Management         :   No Special Management are made WARNING with this option,
   //                                                            ouput curves could be C1 Only
   virtual void SetC1ToC2Management (CATCrvImprvC1ToC2Management iChoice) = 0;

   // To impose a target (point,line,or plane) for location of each new vertex.
   // By default there are no G0 targets.
   // If iListOfG0Target == 0 then new vertices are computed by the operator.
   // If iListOfG0Target(i) == 0 there is no target for this vertex (should be default)
   // Else iListOfG0Target(i) = CATGeometry, new vertex is on this geometry
   // Rem : 
   // First & Last targets are respectively for the Starting and the Ending Point.
   // They must be set to 0, but for a Closed Curve those Two geometries should be different to 0, and equal  
   // Rem2 : The Number of geometries must be equal to the (Number of curves +1)  
   //
   virtual int SetConnectingG0Target (CATLISTP(CATGeometry) * iListOfG0Target) = 0;

   // To impose a G1 target (vector,or plane) with possibly G0 target point
   // (see the above method "SetConnectingG0Target" to get details on G0Targets)
   // Priority to G0, first G0 is done on G0 target if it exists else it is done automatically
   // Then the G1 target is moved to the connecting point (ie G0 target) and the connection is tangent to
   // this target. If both a plane and a vector is defined as a G1 target, then the vector is projected on 
   // the G1plane target.
   // Rem1 : All lists must be Null OR must have the same size equal to  (Number of curves +1). 
   //        First & Last targets are respectively for the Starting and the Ending Point.
   //        They must be set to 0, but for a Closed Curve these Two targets could be different to 0 and equal  
   // Rem2 : Lists can contain null pointer eg iPlanes(i)==NULL means no G1Plane target on the i-th vertex.
   // Rem3 : Pointers must be allocated and deleted by the caller. 
   //
   virtual int SetConnectingG0G1Target (CATLISTP(CATGeometry)   * iListOfG0Target,
                                        CATLISTP(CATMathPlane)  * iPlanes        = 0,
                                        CATLISTP(CATMathVector) * iTgtDirections = 0) = 0;
   //
   // 
   //                  CONCERNING DATA REDUCTION :
   //                  ---------------------------
   //
   // Allows to reduce the number of curves
   // Default value : FALSE
   //
   virtual void SetDataReduction (CATBoolean iChoice) = 0;

   // Allowed maximum degree to reduce data
   // Default value : 5
   //
   virtual void SetMaxDegree (int iMaxDegree) = 0;

   // Allows to cut on C3 discontinuies of the result
   // Default value : FALSE
   //
   virtual void SetC3Cutting (CATBoolean) = 0;  

   // Threshold above which cut is effective
   // If the norm of difference vector is greater than iC3Threshold, 2 different edges are created
   // Default value : 0.0001    
   //
   virtual void SetC3Threshold (double iC3Threshold) = 0; 

   // Defines the highest continuity level at the START extremity between the input and the result.
   // Default value : CATFrFCurvatureCont
   //
   virtual void SetStartExtremityContinuityLevel(CATFrFContinuity iStartContLevel) = 0;

   // Defines the highest continuity level at the END extremity between the input and the result.
   // Default value : CATFrFCurvatureCont
   //
   virtual void SetEndExtremityContinuityLevel(CATFrFContinuity iEndContLevel) = 0;

   //
   // Computation :
   // -------------
   //
   // returns 0 if Ok.
   // 
   virtual int Run() = 0;

   //
   // Result :
   // --------
   //
   // Output curves will be 3D curves if 3D representation correction has been requested
   // Output curves will be Pcurves if 2D representation correction has been requested
   //
   // Raises if "run" has not been done
   // If no improvement output list of CATCurves is equal to input list of CATCurves
   //
   // oIsModified and oIsConcatened lists are given to construct the topological journal
   // Ex :                          oIsModified ! oIsConcatenated 
   // curve 1 modified      : 1 (rank of curve) ! 0
   // curve 2 unmodified    : 0                 ! 0
   // curve 3 deleted       :-1                 ! 0
   // curves 4 and 5 merged : 4 (rank of first  ! 4
   //                       : 4  curve merged)  ! 4
   //
   virtual void   GetResult (CATLISTP(CATCurve)     &oListCurve, 
                             CATLISTP(CATCrvLimits) &oListOfLimits,
                             CATListOfInt           &oListOfOrientations,
                             CATListOfInt           &oIsModified,
                             CATListOfInt           &oIsConcatened) = 0;

   // Output maximum G0,G1 and minimum G2 on INPUT curves
   // MaxG0 is given in mm
   // MaxG1 is given in degree
   // MinG2 is a percent ||R2-R1||/R1
   // returns -1,-1,-1 if input curves have not been given
   // WARNING : If the list of input curves is closed, the SetClosure method should be
   // used before.
   //
   virtual void   GetMaxG0G1MinG2InputCurves (double &oMaxG0,double &oMaxG1, double &oMinG2) = 0;

   // Output maximum G0,G1 and minimum G2 on OUTPUT curves
   // MaxG0 is given in mm
   // MaxG1 is given in degree
   // MinG2 is a percent ||R2-R1||/R1
   // returns -1,-1,-1 if Run has not be done
   //
   virtual void   GetMaxG0G1MinG2OutputCurves (double &oMaxG0,double &oMaxG1, double &oMinG2) = 0;

   //
   // Further computation informations :
   // ----------------------------------
   //
   // Returns maximum 3D geometrical deformation with regard to the input list of curves
   // (the greater minimum distance between one position on one list of curves and the
   // other list of curves).
   //
   virtual double GetMaxDeformation () = 0; 

   // Returns list of 3D points where the maximum deformation is reached.
   //
   virtual void   GetMaxDeformationLocation (CATMathSetOfPoints & ioSetOfPoints) = 0; 

   // Returns maximum 3D deformation between input and output list of curves at places
   // having the same parameter (the greater 3D distance between two positions of same
   // parameter on each list of curves).
   // Warning : Not available with Data Reduction. Returns negative value in this case.
   //
   //virtual double GetMaxDeformationAtIsoParameter () = 0; 

   //
   // Various Get functions :
   // -----------------------
   //
   virtual CATLONG32               GetCgmLevel                      () = 0;
   virtual CATLocalizer2DFrom3D  * Get2DRepresentationToImprove     () = 0;
   virtual int                     GetHybridMode2D3D                () = 0;
   virtual double                  GetMaxDeformationThreshold       () = 0; 
   virtual CATLISTP(CATCrvParam) * GetFixedPoints                   () = 0; 
   virtual CATLISTP(CATCurve)    * GetFixedCurves                   () = 0; 
   virtual int                     GetFixedTransitions              () = 0;
   virtual CATCrvImprvPriority     GetPriorityMode                  () = 0; 
   virtual CATFrFContinuity        GetLevelContinuityToImprove      () = 0; 
   virtual double                  GetG0Threshold                   () = 0;
   virtual double                  GetG1Threshold                   () = 0;
   virtual double                  GetG2Threshold                   () = 0;
   virtual double                  GetG0MinThreshold                () = 0;
   virtual double                  GetG1MinThreshold                () = 0;
   virtual double                  GetLengthThreshold               (CATBoolean * oAbsoluteMeasure) = 0;
   virtual CATCrvImprvSmallCurve   GetSmallCurvesManagement         () = 0; 
   virtual CATBoolean              GetDataReduction                 () = 0;
   virtual int                     GetMaxDegree                     () = 0;
   virtual int                     GetLocalOptimization             () = 0;
   virtual int                     GetGlobalOptimization            () = 0;
   virtual int                     GetClosure                       () = 0;
   virtual CATFrFContinuity        GetStartExtremityContinuityLevel () = 0;
   virtual CATFrFContinuity        GetEndExtremityContinuityLevel   () = 0;
};

// To create an instance of the operator: see CATPGMCreateCurvesImprovement.h

#endif
