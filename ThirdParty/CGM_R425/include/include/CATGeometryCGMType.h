/* -*-c++-*- */
#ifndef CATGeometryCGMType_H
#define CATGeometryCGMType_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// Geometric type  definition
//
//=============================================================================
//  July,    2004 : RAQ : Ajout de CATSubdivMeshCGMGeoType
//  July,    2008 : RNO : Ajout de CATSubdivGridSurfaceCGMGeoType
//  Oct.     2009 : DNR : Suppression du #ifdef , sur CATCldVectorsType,
//                        aujourd'hui cette variable vaut toujours TRUE.
//  Nov.     2014 : DPS : add polyhedral types for the polyhedral modeler
//  Sept.    2015 : DPS : modification of poly types according to the new derived interfaces
//  Nov.     2015 : DPS : add PolySurfOnExactSurf type
//  Jan.     2019 : DPS : add PolyCurveOnPlane type
//  Jan.     2021 : DPS : add PolyCurveOnExactCurve & PolyCurve3DOnExactCurve types
//=============================================================================

#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"
#include "CATGeometryType.h"

#define CATRootContainerCGMGeoType                CATGeoFactoryType

#define CATCloudOfPointsCGMGeoType                CATCloudOfPointsType
#define CATSetOfPointsCGMGeoType                  CATSetOfPointsType

#define CATCircleCGMGeoType                       CATCircleType	
#define CATEllipseCGMGeoType                      CATEllipseType	

#define CATIntCurveCGMGeoType                     CATIntCurveType	
#define CATMergedCurveCGMGeoType                  CATMergedCurveType	
#define CATSimCurveCGMGeoType                     CATSimCurveType	
#define CATContactCurveCGMGeoType                 CATContactCurveType	

#define CATLineCGMGeoType                         CATLineType	
#define CATNurbsCurveCGMGeoType                   CATNurbsCurveType	
#define CATHelixCGMGeoType                        CATHelixType	

#define CATPCircleCGMGeoType                      CATPCircleType	
#define CATPCurveEquationCGMGeoType               CATPCurveEquationType	
#define CATPEllipseCGMGeoType                     CATPEllipseType	
#define CATNonLinearTransfoPCurveCGMGeoType       CATNonLinearTransfoPCurveType
#define CATPParabolaCGMGeoType                    CATPParabolaType
#define CATPHyperbolaCGMGeoType                   CATPHyperbolaType
#define CATPLineCGMGeoType                        CATPLineType	
#define CATPNurbsCGMGeoType		                    CATPNurbsType	
#define CATTrimmedPCurveCGMGeoType	              CATTrimmedPCurveType	


#define CATProcCurveCGMGeoType		                CATProcCurveType	

#define CATPSplineCGMGeoType                      CATPSplineType	
#define CATSplineCurveCGMGeoType                  CATSplineCurveType
	
#define CATCartesianPointCGMGeoType               CATCartesianPointType
#define CATMacroPointCGMGeoType                   CATMacroPointType	
#define CATPointOnCurveCGMGeoType                 CATPointOnCurveType	
#define CATPointOnEdgeCurveCGMGeoType             CATPointOnEdgeCurveType	
#define CATPointOnSurfaceCGMGeoType               CATPointOnSurfaceType	

#define CATSetOfSetOfPointsCGMGeoType             CATSetOfSetOfPointsType		

#define CATCircularSweepCGMGeoType                CATCircularSweepType
#define CATDraftSurfaceCGMGeoType                 CATDraftSurfaceType
#define CATGenericFilletCGMGeoType                CATGenericFilletType


#define CATCylinderCGMGeoType                     CATCylinderType	
#define CATSphereCGMGeoType                       CATSphereType 	
#define CATConeCGMGeoType                         CATConeType
#define CATTorusCGMGeoType                        CATTorusType 		
#define CATFilletSurfaceCGMGeoType                CATFilletSurfaceType 
#define CATNurbsSurfaceCGMGeoType                 CATNurbsSurfaceType	
#define CATOffsetSurfaceCGMGeoType		            CATOffsetSurfaceType
#define CATProcOffsetSurfaceCGMGeoType	          CATProcOffsetSurfaceType
#define CATPlaneCGMGeoType                        CATPlaneType	
#define CATRevolutionSurfaceCGMGeoType            CATRevolutionSurfaceType	
#define CATRuledSurfaceCGMGeoType                 CATRuledSurfaceType
#define CATGenericRuledSurfaceCGMGeoType          CATGenericRuledSurfaceType
#define CATDirectionalSurfaceCGMGeoType           CATDirectionalSurfaceType
#define CATSweepSurfaceCGMGeoType                 CATSweepSurfaceType	
#define CATSweepSegmentSurfaceCGMGeoType          CATSweepSegmentSurfaceType	
#define CATTabulatedCylinderCGMGeoType            CATTabulatedCylinderType	
#define CATNonLinearTransfoSurfaceCGMGeoType      CATNonLinearTransfoSurfaceType
#define CATLinearTransfoSurfaceCGMGeoType         CATLinearTransfoSurfaceType

#define CATChamferSurfaceCGMGeoType               CATChamferSurfaceType 

#define CATSpecSurfaceCGMGeoType                  CATSpecSurfaceType 
#define CATProcSurfaceCGMGeoType                  CATProcSurfaceType 

#define CATUserGeometryCGMGeoType                 CATUserGeometryType
#define CATForeignSurfaceCGMGeoType               CATIForeignSurfaceType
#define CATForeignCurveCGMGeoType                 CATIForeignCurveType
#define CATForeignPCurveCGMGeoType                CATIForeignPCurveType

#define CATCXBodyGeoType                          CATBodyType	
	 
#define CATCXEdgeGeoType                          CATEdgeType	
#define CATCXFaceGeoType                          CATFaceType	
#define CATCXVertexGeoType                        CATVertexType	
#define CATCXVolumeGeoType                        CATVolumeType
	
#define CATCXLoopGeoType                          CATLoopType 
#define CATCXLumpGeoType                          CATLumpType	
#define CATCXShellGeoType                         CATShellType	
#define CATCXVertexInFaceGeoType                  CATVertexInFaceType	
#define CATCXVertexInVolumeGeoType                CATVertexInVolumeType	
#define CATCXWireGeoType                          CATWireType	
#define CATCellManifoldCGMGeoType                 CATCellManifoldType	
#define CATDatumManifoldCGMGeoType                CATDatumManifoldType	
#define CATSubdivisionManifoldCGMGeoType          CATSubdivisionManifoldType
#define CATPlaneManifoldCGMGeoType                CATPlaneManifoldType
#define CATCylinderManifoldCGMGeoType             CATCylinderManifoldType
#define CATSphereManifoldCGMGeoType               CATSphereManifoldType
#define CATConeManifoldCGMGeoType                 CATConeManifoldType
#define CATTorusManifoldCGMGeoType                CATTorusManifoldType
#define CATBoneFilletCGMGeoType                   CATBoneFilletType	
#define CATJointFilletCGMGeoType                  CATJointFilletType	
#define CATJointChamferCGMGeoType                 CATJointChamferType
#define CATBoneChamferCGMGeoType                  CATBoneChamferType	
#define CATHEdgeCGMGeoType                        CATHEdgeType
#define CATIntersectionHVertexCGMGeoType          CATIntersectionHVertexType
#define CATRatioHVertexCGMGeoType                 CATRatioHVertexType
#define CATDistanceHVertexCGMGeoType              CATDistanceHVertexType
#define CATDraftManifoldCGMGeoType                CATDraftManifoldType
#define CATButtonManifoldCGMGeoType               CATButtonManifoldType
#define CATManifoldCGMGeoType                     CATManifoldType

#define CATManifoldGroupCGMGeoType                CATManifoldGroupType
#define CATContextualManifoldGroupCGMGeoType      CATContextualManifoldGroupType
#define CATHierarchicalManifoldGroupCGMGeoType    CATHierarchicalManifoldGroupType
#define CATCellManifoldGroupCGMGeoType            CATCellManifoldGroupType

#define CATLawCGMGeoType                          CATLawType                	
#define CATCompositeLawCGMGeoType                 CATCompositeLawType       	
#define CATConstantLawCGMGeoType                  CATConstantLawType        	
#define CATLinearLawCGMGeoType                    CATLinearLawType          	
#define CATSTypeLawCGMGeoType                     CATSTypeLawType         
#define CATSplineLawCGMGeoType                    CATSplineLawType

#define CATCloudCGMGeoType                        CATCloudType
#define CATTessCloudCGMGeoType                    CATTessCloudType
#define CATScanCGMGeoType                         CATScanType
#define CATTessScanCGMGeoType                     CATTessScanType

#define CATCldBodyCGMGeoType                      CATCldBodyType
#define CATCldCloudCGMGeoType                     CATCldCloudType
#define CATCldScanCGMGeoType                      CATCldScanType
#define CATCldGridCGMGeoType                      CATCldGridType
#define CATCldPolygonCGMGeoType                   CATCldPolygonType
#define CATCldVectorsCGMGeoType                   CATCldVectorsType
#define CATCldSetOfScansCGMGeoType                CATCldSetOfScansType
#define CATCldSetOfGridsCGMGeoType                CATCldSetOfGridsType
#define CATCldScanOnPolygonCGMGeoType             CATCldScanOnPolygonType
#define CATCldSubPolygonCGMGeoType                CATCldSubPolygonType
#define CATCldSetOfPointsFCGMGeoType              CATCldSetOfPointsFType
#define CATCldSetOfPointsDCGMGeoType              CATCldSetOfPointsDType

#define CATSubdivMeshCGMGeoType                   CATSubdivMeshType

#define CATSubdivCellSurfaceCGMGeoType            CATSubdivCellSurfaceType
#define CATSubdivGridSurfaceCGMGeoType            CATSubdivGridSurfaceType
#define CATSubdivMeshGeoCGMGeoType                CATSubdivMeshGeoType

#define CATGeoPolyPointImplGeoType                CATGeoPolyPointType
#define CATGeoPolyCurveImplGeoType                CATGeoPolyCurveType
#define CATGeoPolySurfaceImplGeoType              CATGeoPolySurfaceType

#define CATGeoPolyBodyImplGeoType                 CATGeoPolyBodyType

#define CATGMPolyGeoPolyBodyGeoType               CATGeoPolyBodyType

#define CATGMPolyBodyGeoType                      CATBodyType		 
#define CATGMPolyVertexGeoType                    CATVertexType	
#define CATGMPolyEdgeGeoType                      CATEdgeType	
#define CATGMPolyFaceGeoType                      CATFaceType	
#define CATGMPolyVolumeGeoType                    CATVolumeType	
#define CATGMPolyVertexInFaceGeoType              CATVertexInFaceType	
#define CATGMPolyVertexInVolumeGeoType            CATVertexInVolumeType	
#define CATGMPolyWireGeoType                      CATWireType	
#define CATGMPolyLoopGeoType                      CATLoopType 
#define CATGMPolyShellGeoType                     CATShellType	
#define CATGMPolyLumpGeoType                      CATLumpType	

#define CATGMPolyPointGeoType                     CATGeoPolyPointType
#define CATGMPolyPointOnCurveGeoType              CATGeoPolyPointOnCurveType
#define CATGMPolyPointOnSurfaceGeoType            CATGeoPolyPointOnSurfaceType
#define CATGMPolySingleCurveGeoType               CATGeoPolyCurveType
#define CATGMPolyCurve3DGeoType                   CATGeoPolyCurveType
#define CATGMPolyCurveOnExactCurveGeoType         CATGeoPolyCurveType
#define CATGMPolyCurve3DOnExactCurveGeoType       CATGeoPolyCurveType
#define CATGMPolyCurveOnCurveGeoType              CATGeoPolyCurveOnCurveType
#define CATGMPolyCurveOnSurfaceGeoType            CATGeoPolyCurveOnSurfaceType
#define CATGMPolyCurveOnDirSurfGeoType            CATGeoPolyCurveOnSurfaceType
#define CATGMPolyCurveOnPlaneGeoType              CATGeoPolyCurveOnPlaneType
#define CATGMPolyCouplingCurveGeoType             CATGeoPolyCouplingCurveType
#define CATGMPolySurfaceGeoType                   CATGeoPolySurfaceType
#define CATGMPolySurfOnExactSurfGeoType           CATGeoPolySurfaceType

#define CATGMImplicitSurfaceGeoType               CATGeoImplicitSurfaceType

#include "CATCGMBOAObject.h"
#if defined ( CATCGMBOAObject )
#define CATGeoFactoryCGMGeoType                   CATGeoFactoryType
#define CATSubdConfusedLoopGeoType                CATLoopType
#endif

#endif
