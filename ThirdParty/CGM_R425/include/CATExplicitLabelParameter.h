//

//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2010
//-----------------------------------------------------------------------------
#ifndef CATExplicitLabelParameter_H
#define	CATExplicitLabelParameter_H
enum CATExplicitLabelParameter
{
	CATExplicitLabelParameter_Unknown_Label								=			0,
	CATExplicitLabelParameter_Max_Nb_Arc									=			1,		//	maximum number of fragment in each curve
	CATExplicitLabelParameter_Max_Polyn_Deg								=			2,		//	maximum allowed polynomial degree
	CATExplicitLabelParameter_Min_Gap_Knots								=			3,		//	minimal gap between internl knots
	CATExplicitLabelParameter_Max_Gap_Knots								=			4,		//	maximal gap between internl knots
	CATExplicitLabelParameter_Check_SolidBody								=			5,
	CATExplicitLabelParameter_Check_SkinBody								=			6,
	CATExplicitLabelParameter_Check_WireBody								=			7,
	CATExplicitLabelParameter_Check_Canonical_Surf						=			8,		//	check or not canonical surfaces
	CATExplicitLabelParameter_Min_Nb_Edges									=			9,		// minimum allowed number of edges.
	CATExplicitLabelParameter_Max_Nb_Edges									=			10,	// maximum allowed number of edges.
	CATExplicitLabelParameter_Max_Nb_Patches								=			11,	//	maximum number of patches (segemnt row) per surface
	CATExplicitLabelParameter_Max_Nb_Patches_Dir							=			12,	//	maximum number of patches per surface
	CATExplicitLabelParameter_Sampling_Pts_Mode							=			13,	//	Sampling mode
	CATExplicitLabelParameter_Nb_Pts											=			14,	//	Sample Size
	CATExplicitLabelParameter_Check_Mode_LimitPts						=			15,	// Check for continuity in the corresponding limit points. 
																											//This option only makes sense if the tolerance for the calculation 
																											//of the topology is less than or equal to the value specified in 1. 
																											//		• Check for continuity in the projectable limit points. 
																											//		• Limit points will be ignored in this check.   
   CATExplicitLabelParameter_Max_Angle_Deg								=			16,	//	minimum angle degree
	CATExplicitLabelParameter_Min_Angle_Deg								=			17,	//	maximum angle degree
	CATExplicitLabelParameter_MaxGap											=			18,	//	maximum gap
	CATExplicitLabelParameter_CheckWireDomain								=			19,
	CATExplicitLabelParameter_CheckLoopDomain								=			20,
	CATExplicitLabelParameter_MinLength										=			21,
	CATExplicitLabelParameter_MaxLength										=			22,
	CATExplicitLabelParameter_Tolerance										=			23,
	CATExplicitLabelParameter_Max_CurvatureRatio							=			24,
	CATExplicitLabelParameter_Min_CurvatureRatio							=			25,
	CATExplicitLabelParameter_Infinite_CurvatureRatio					=			26,
	CATExplicitLabelParameter_Length											=			27,
	CATExplicitLabelParameter_MinArea									=			28,
	CATExplicitLabelParameter_MaxArea									=			29,
	CATExplicitLabelParameter_MinVolume									=			30,
	CATExplicitLabelParameter_MaxVolume									=			31,
	CATExplicitLabelParameter_Check_MinLengthBB						=			33,
	CATExplicitLabelParameter_Check_MinAreaBB							=			34,
	CATExplicitLabelParameter_Check_MinVolumeBB						=			35,
	CATExplicitLabelParameter_MinDimBB									=			36,
	CATExplicitLabelParameter_Check_PerVolume							=			37,
	CATExplicitLabelParameter_G1_DiscMode								=			38,
	CATExplicitLabelParameter_CheckIsoParamTgtDev					=			39,
	CATExplicitLabelParameter_TypeOfMeasure_AreaOrLength			=			40,
	CATExplicitLabelParameter_Check_NarrowPatch						=			41,
	CATExplicitLabelParameter_NbPointsPerSegment						=			42,
	CATExplicitLabelParameter_Check_PartialOverlaping				=			43,
	CATExplicitLabelParameter_Check_InnerPtsOfFaces					=			44,
	CATExplicitLabelParameter_NbInnerPtsPerFace						=			45,
	CATExplicitLabelParameter_CheckOnlyFaceArea						=			46,
	CATExplicitLabelParameter_MinCurvatureRadius						=			47,
	CATExplicitLabelParameter_MaxCurvatureRadius						=			48,
	CATExplicitLabelParameter_TolMinLengthNormal						=			49,
	CATExplicitLabelParameter_NbAdjacentPoints						=			50,
	CATExplicitLabelParameter_Check_NeighborSegments				=			51,
	CATExplicitLabelParameter_Check_OnlyBoundaries					=			52,
	CATExplicitLabelParameter_Check_OnFaceLimits						=			53,
	CATExplicitLabelParameter_Check_IfClosedBoundariesIsNarrow	=			54,
	CATExplicitLabelParameter_Check_G1Discontinuity					=			55,
	CATExplicitLabelParameter_Check_IfClosedBoundariesIsPartiallyNarrow	=			56,
	CATExplicitLabelParameter_NarrowTolerance							= 57,	
	//CATExplicitLabelParameter_CurveLimitsMode							= 58,
	//CATExplicitLabelParameter_Edge_ArcLenghtDegenerated_ComputationMethod	= 59,
	CATExplicitLabelParameter_CheckOnlyRefCurve							= 60,
	CATExplicitLabelParameter_MaxNumberOfCtrlPoints						= 61,
	CATExplicitLabelParameter_MaxNumberOfCtrlPointsInParamDir			= 62,
	CATExplicitLabelParameter_CheckOnlyPatchBoundaryLength				= 63,
	CATExplicitLabelParameter_CheckLengthRatioOfAdjacentPatches			= 64,
	CATExplicitLabelParameter_DenomLenghtRatioOfAdjacentPatches			= 65,
	CATExplicitLabelParameter_NbArcsPerGroup							= 66,
	CATExplicitLabelParameter_MaxNbInflectionPts						= 67,
	CATExplicitLabelParameter_InfiniteCurvatureRadius					= 68,
	CATExplicitLabelParameter_MinAngleCorner							= 69,
	CATExplicitLabelParameter_MaxAngleCorner							= 70,
	CATExplicitLabelParameter_MinAnglePseudoCorner						= 71,
	CATExplicitLabelParameter_MaxAnglePseudoCorner						= 72,
	CATExplicitLabelParameter_MinLengthPatchBoundary					= 73,
	CATExplicitLabelParameter_MinLengthOfNormal							= 74,
	CATExplicitLabelParameter_CheckOnArcOrIsoParamCrv					= 75,
	//CATExplicitLabelParameter_DoCheckInParameterDirection				= 62
	//CATExplicitLabelParameter_Min_Gap_Pts									=			5,		//	minimum gap between two points
	//CATExplicitLabelParameter_Max_Gap_Pts									=			6,		//	maximum gap between two points
	//CATExplicitLabelParameter_Max_Dev										=			7,		//	maximum deviation that a curve may have from its best fit straight line to be still considered a line.
	//CATExplicitLabelParameter_Max_Curv_Ratio								=			8,		//	maximum curvature ratio
	//CATExplicitLabelParameter_Min_Curv_Ratio								=			9,		//	minimum curvature ratio
	//CATExplicitLabelParameter_Infinit_Curv_Radius						=			10,	//	infinit curvature radius
	
	//CATExplicitLabelParameter_Min_Angle										=			12,	//	minimum angle
	//CATExplicitLabelParameter_Min_Curv_Radius								=			13,	//	minimun curvature radius
	
	
	//CATExplicitLabelParameter_Min_Length									=			16,	// minimal length
	//CATExplicitLabelParameter_Max_Length									=			17,	// maximal length
	//CATExplicitLabelParameter_Nb_Segments									=			18,	// Number of Segments per 
	//CATExplicitLabelParameter_Partial_Overlap								=			19,	// Partial Overlap
	//CATExplicitLabelParameter_Check_Minimal_Part							=			20,	// only a minimal part of the surface will be checked. This partial area is defined by the smallest possible rectangle that encloses all faces on the surface.
	//CATExplicitLabelParameter_Check_Undef_Surf_Norm						=			21,	// segments will only be regarded as faulty if the surface normal is not defined geometrically.
	//CATExplicitLabelParameter_Angle_Deviation								=			22,	// angle deviation between the tangent direction of the isoparametrical curves and the tangential plane
	//CATExplicitLabelParameter_Check_Segments_With_4_Bnd_Crv			=			23,	// 
	//CATExplicitLabelParameter_Check_Segments_With_3_Bnd_Crv			=			24,	// 
	//CATExplicitLabelParameter_Check_Neighbor_Segments					=			25,	//
	//CATExplicitLabelParameter_Check_Only_Bnd								=			26,	//
	//CATExplicitLabelParameter_Nb_Adj_Pts									=			27,	//	???	
	//CATExplicitLabelParameter_Max_Nb_Ctrl_Pts								=			30,	//	maximum allowed number of control points for the whole surface (i.e. the product of the number of control points in u and v directions)
	//CATExplicitLabelParameter_Max_Nb_Ctrl_Pts_Dir						=			31,	//	maximum allowed number of control points that may be situated in one of the u or v directions.
	//
	//CATExplicitLabelParameter_Check_Param_Deviation						=			33,	//	examine the parametrical deviation
	//CATExplicitLabelParameter_Min_Patch_Width								=			34,	//	minimum allowed value for the width of patches.
	//CATExplicitLabelParameter_Denom_Ratio_Patch							=			35,	//	denominator of the ratio  between adjacent patches . The ratio of the sizes of two adjacent surface patch boundaries (in one parameter direction within one surface) should not be less than 1:x.
	//CATExplicitLabelParameter_Tessellation_Sag							=			36,	//	maximum distance between curve section and the discretization line (i.e. the sag) for triangulation.
	//CATExplicitLabelParameter_Object_Computation							=			37,	//	on Tesselated Surface or Surface
	//CATExplicitLabelParameter_Computation_Mode							=			38,	//	Length of Bnd Curve or  Surface Area
	//CATExplicitLabelParameter_Min_Surface									=			39,	//	minimum length or area
	//CATExplicitLabelParameter_Max_Surface									=			40,	//	maximum length or area
	//CATExplicitLabelParameter_Check_UV_Direction							=			41,	//	
	//CATExplicitLabelParameter_Nb_IsoParamCrv								=			42,	// Number of the isoparametrical curves that are to be used for the examination	
	//CATExplicitLabelParameter_Nb_Pts_Segments								=			43,	// number of points per segment
	//CATExplicitLabelParameter_Check_Geo										=			44,	// allow topo or geo check will be executed.
	//CATExplicitLabelParameter_Max_Nb_Segments								=			45,	// Max number of segments
	//CATExplicitLabelParameter_Check_Outside_Range						=			46,	// if TRUE checked whether the boundary curve of the face lies outside of the parameter domain of the surface.
	//CATExplicitLabelParameter_Check_Planar_Surface						=			47,	// Ignore faces with planar support surface
	//CATExplicitLabelParameter_Check_Outside_ModelSize					=			48,	// faces that are located outside of the Catia surface area, but are situated in the continuation of the same surface, will not be rated to be an error.
	//CATExplicitLabelParameter_Algo_Kind										=			49,	// Select here which algorithm to use for the check
	//CATExplicitLabelParameter_Ratio_WidthHeigth							=			50,	// maximum allowed width-to-length ratio to be allowed for faces.
	//CATExplicitLabelParameter_Min_Area_Width								=			51,	// minimum value for width b that subareas of a face must have in order not to be rated narrow.
	//CATExplicitLabelParameter_Check_Small_Area							=			52,	// faces will be considered faulty that are partially small (in one ore several subareas).
	//CATExplicitLabelParameter_Check_TopoCreation_OverMultiSets		=			53,	// topologies can be generated over several sets
	//CATExplicitLabelParameter_Min_Gap_Transition							=			54,	// All transitions between faces with a distance greater than 1 and less than or equal to 3 additionally will be considered
	//CATExplicitLabelParameter_Max_Gap_Transition							=			55,	// All transitions between faces with a distance greater than 1 and less than or equal to 3 additionally will be considered
	
	//CATExplicitLabelParameter_Check_G1_Disc_Mode							=			57,	// Specify which definition of G1 discontinuity to apply: • If this check box is not selected, a transition is considered tangent-discontinuous if one of the detected angles between normals along the common edge is greater than 1 and less than 2.• If this check box is activated, a transition is considered tangent-discontinuous if the largest of the detected angles between normals along the common edge is greater than 1 and less than 2. 
	//CATExplicitLabelParameter_Min_Nb_Faces									=			58,	// minimum number of faces that a topology must have to be checked.
	//CATExplicitLabelParameter_Narrow_Tol									=			59,	// 
	//CATExplicitLabelParameter_Check_Open_Area								=			60,	// the topology will be searched for open areas.
	//CATExplicitLabelParameter_Check_Identical_Bnd_Loop					=			61,	// AcceptedNarrowBndLoop : if TRUE,  identical closed boundary loops will be not marked faulty if they are tangent continuous
	//CATExplicitLabelParameter_CheckOpen_Area_Partial_Narrow			=			62,	// CheckClosedBndForPartialNarrow : if TRUE, open areas inside of a topology that are only partially smaller than the tolerance will be rated faulty	
	//CATExplicitLabelParameter_Check_Inner_Pts_Face						=			65,	// inner points of faces
	//CATExplicitLabelParameter_Check_Volume									=			66,	//  
	//CATExplicitLabelParameter_Min_Volume									=			67,	// minimum volume 
	//CATExplicitLabelParameter_Max_Volume									=			68,	// maximum volume
	//CATExplicitLabelParameter_Check_Extension_Direction				=			69,	//
	//CATExplicitLabelParameter_Check_Single_Domain						=			70,	//  if TRUE, also solids will be considered faulty that have only one or a few domains (volumes) that are smaller than specified
	//CATExplicitLabelParameter_Check_Same_Type_Entity					=			71,	//  if TRUE  only elements of the same type are compared with each other, e.g. lines with lines and curves with curves.	
	//CATExplicitLabelParameter_Max_Nb_Domains								=			72,	
};


//enum CATExplicitValueParameter_Sampling_Pts_Mode
//{
//	CATExplicitValueParameter_Sampling_Pts_Mode_Unknown				=			0,
//	CATExplicitValueParameter_Sampling_Pts_Mode_Classic				=			1		//
//};
//
//enum CATExplicitValueParameter_Partial_Overlap
//{
//	CATExplicitValueParameter_Partial_Overlap_Off						=			0,		//
//	CATExplicitValueParameter_Partial_Overlap_On							=			1		//
//};
//
//enum CATExplicitValueParameter_Minimal_Part
//{
//	CATExplicitValueParameter_Minimal_Part_Off							=			0,		//
//	CATExplicitValueParameter_Minimal_Part_On								=			1		//
//};
//
//enum CATExplicitValueParameter_Undef_Surf_Norm
//{
//	CATExplicitValueParameter_Undef_Surf_Norm_Off						=			0,		//
//	CATExplicitValueParameter_Undef_Surf_Norm_On							=			1		//
//};
//
//enum CATExplicitValueParameter_Param_Deviation
//{
//	CATExplicitValueParameter_Param_Deviation_Off						=			0,		//
//	CATExplicitValueParameter_Param_Deviation_On							=			1		//
//};
//
//enum CATExplicitValueParameter_Check_Geo
//{
//	CATExplicitValueParameter_Check_Geo_Off								=			0,		//
//	CATExplicitValueParameter_Check_Geo_On									=			1		//
//};
//
//enum CATExplicitValueParameter_Outside_Range
//{
//	CATExplicitValueParameter_Outside_Range_Off							=			0,		//
//	CATExplicitValueParameter_Outside_Range_On							=			1		//
//};
//
//enum CATExplicitValueParameter_Outside_ModelSize
//{
//	CATExplicitValueParameter_Outside_ModelSize_Off						=			0,		//
//	CATExplicitValueParameter_Outside_ModelSize_On						=			1		//
//};
//
//
//
//enum CATExplicitValueParameter_Extension_Direction
//{
//	CATExplicitValueParameter_Extension_Direction_Unknown			=			0,
//	CATExplicitValueParameter_All_Directions							=			1,	
//	CATExplicitValueParameter_One_Direction							=			2,
//	CATExplicitValueParameter_Two_Directions							=			3,
//};
#endif
