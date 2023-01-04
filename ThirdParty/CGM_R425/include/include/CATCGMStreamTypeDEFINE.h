#ifndef CATCGMStreamTypeDEFINE_h
#define CATCGMStreamTypeDEFINE_h
// COPYRIGHT DASSAULT SYSTEMES  2009
//-------------------------------------------------------- 
//  V E R Y     I M P O R T A N T  !!!!!!!
//
//    F O R     E A C H    C H A N G E   
//
//    N E C E S S A R Y    T O     U P D A T E 
//
//  CATMathStream\ProtectedInterfaces\CATCGMStreamTypeDEFINE_MAX.h
//----------------------------------------------------------------------------
// Persistency.Engineering.Change  "DataBase" 
//
//        CGM Object Types
//
//  CATCGMStreamTypeDECLARE(CGMTypeName,CGMTypeValue,CGMTypeIndex,CGMStreamBinder)  
//
//----------------------------------------------------------------------------
//  DO NOT INCLUDE THIS HEADER DIRECTLY
//
//  YOU MAY RATHER USE FOLLOWING HEADER FOR ACCESS TO  ACTIVE PERSISTENCY CHANGE
//      GeometricObjectsCGM\ProtectedInterfaces\ObjectTypesCGM.h
//
//    ROOT INTERNAL DEFINITION IS HOLDED BY
//        CATMathStream\ProtectedInterfaces\CATCGMStreamTypeDEFINE.h
//----------------------------------------------------------------------------
//  Storage : Persistency Change Management   
//
 

 
CATCGMStreamTypeDECLARE( UserAttrRefTableCGM,               9,    1, CATGeometricObjects,               0,   2010Spring,   NeverActivated,  -1 )
 
 
  // Geometry 0D
CATCGMStreamTypeDECLARE( CartesianPointCGM,               10,     2 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( PointOnCurveCGM,                 11,     3 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( PointOnSurfaceCGM,               12,     4 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( MacroPointCGM,                   13,     5 , CATGeometricObjectsCGM,     -1,   2010Spring,   NeverActivated,  0 )
CATCGMStreamTypeDECLARE( PointOnEdgeCurveCGM,             14,     6 , CATGeometricObjectsCGM,     -1,   2010Spring,   NeverActivated,  0 )

CATCGMStreamTypeDECLARE( CloudOfPointsCGM,                20,     7 , CATMeshObjectsCGM,           0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SetOfPointsCGM,                  21,     8 , CATMeshObjectsCGM,           0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SetOfSetOfPointsCGM,             30,     9 , CATMeshObjectsCGM,           0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CloudCGM,                        35,    10 , CATMeshObjectsCGM,           0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( ScanCGM,                         36,    11 , CATMeshObjectsCGM,           0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( TessCloudCGM,                    40,    12 , CATMeshObjectsCGM,           1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( TessScanCGM,                     41,    13 , CATMeshObjectsCGM,           1,   2010Spring,   NeverActivated,  -1 )
 

  // Geometry 1D
CATCGMStreamTypeDECLARE( LineCGM,                       100,    14 , CATGeometricObjectsCGM,       0,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( CircleCGM,                     101,    15 , CATGeometricObjectsCGM,       0,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( EllipseCGM,                    102,    16 , CATGeometricObjectsCGM,       0,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( ParabolaCGM,                   103,    17 , CATGeometricObjectsCGM,       0,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( HyperbolaCGM,                  104,    18 , CATGeometricObjectsCGM,       0,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( HelixCGM,                      105,    19 , CATGeometricObjectsCGM,      -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( ProcCurveCGM,                  110,    20 , CATGeometricObjectsCGM,       1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SplineCurveCGM,                120,    21 , CATGeometricObjectsCGM,       0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( NurbsCurveCGM,                 130,    22 , CATGeometricObjectsCGM,       0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( ForeignCurveCGM,               140,    23 , CATGeometricObjectsCGM,       0,   2010Spring,   NeverActivated,  -1 )
 

CATCGMStreamTypeDECLARE( PLineCGM,                      150,    24 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( PCircleCGM,                    151,    25 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( PEllipseCGM,                   152,    26 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( PParabolaCGM,                  153,    27 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( PHyperbolaCGM,                 154,    28 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( PCurveEquationCGM,             155,    29 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( NonLinearTransfoPCurveCGM,     156,    30 , CATGeometricObjectsCGM,      2,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( TrimmedPCurveCGM,              157,    31 , CATGeometricObjectsCGM,      2,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( PSplineCGM,                    160,    32 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( PNurbsCGM,                     170,    33 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  -1 )
 
CATCGMStreamTypeDECLARE( ForeignPCurveCGM,              180,    34 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( IntCurveCGM,                   191,    35 , CATGeometricObjectsCGM,     -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SimCurveCGM,                   192,    36 , CATGeometricObjectsCGM,     -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( MergedCurveCGM,                193,    37 , CATGeometricObjectsCGM,     -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( ContactCurveCGM,               194,    38 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  -1 )

  // Geometry 2D
CATCGMStreamTypeDECLARE( PlaneCGM,                      200,    39 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( CylinderCGM,                   201,    40 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( ConeCGM,                       202,    41 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SphereCGM,                     203,    42 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( TorusCGM,                      204,    43 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( TabulatedCylinderCGM,          210,    44 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( RevolutionSurfaceCGM,          211,    45 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SweepSurfaceCGM,               212,    46 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CircularSweepCGM,              213,    47 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( OffsetSurfaceCGM,              214,    48 , CATGeometricObjectsCGM,      2,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( ProcOffsetSurfaceCGM,          215,    49 , CATGeometricObjectsCGM,      1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GenericFilletCGM,              216,    50 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SplineSurfaceCGM,              220,    51 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( NurbsSurfaceCGM,               231,    52 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( DirectionalSurfaceCGM,         239,    53 , CATGeometricObjectsCGM,      2,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( RuledSurfaceCGM,               240,    54 , CATGeometricObjectsCGM,      0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( FilletSurfaceCGM,              241,    55 , CATGeometricObjectsCGM,     -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( DraftSurfaceCGM,               242,    56 , CATGeometricObjectsCGM,     -1,   2010Spring,   NeverActivated,  -1 )
  
  
CATCGMStreamTypeDECLARE( GenericRuledSurfaceCGM,        243,   57 , CATGeometricObjectsCGM,        0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( ChamferSurfaceCGM,             244,   59 , CATGeometricObjectsCGM,       -1,   2010Spring,   NeverActivated,  -1 )
 
CATCGMStreamTypeDECLARE( NonLinearTransfoSurfaceCGM,    245,   60 , CATGeometricObjectsCGM,       -1,   2010Spring,   NeverActivated,  -1 )
 

CATCGMStreamTypeDECLARE( LinearTransfoSurfaceCGM,       246,   61 , CATGeometricObjectsCGM,        1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SweepSegmentSurfaceCGM,        247,   62 , CATGeometricObjectsCGM,       -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( ForeignSurfaceCGM,             250,   63 , CATGeometricObjectsCGM,        0,   2010Spring,   NeverActivated,  -1 )


CATCGMStreamTypeDECLARE( SpecSurfaceCGM,                251,   64 , CATGeometricObjectsCGM,       -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( ProcSurfaceCGM,                252,   65 , CATGeometricObjectsCGM,        1,   2010Spring,   NeverActivated,  -1 )

CATCGMStreamTypeDECLARE( SubdivCellSurfaceCGM,          253,   66 , CATMeshObjectsCGM,            1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SubdivGridSurfaceCGM,          254,   67 , CATMeshObjectsCGM,            1,   2010Spring,   NeverActivated,  -1 )


  // Law
CATCGMStreamTypeDECLARE( ConstantLawCGM,                300,   68 , CATGeometricObjectsCGM,        0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( LinearLawCGM,                  301,   69 , CATGeometricObjectsCGM,        0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( STypeLawCGM,                   302,   70 , CATGeometricObjectsCGM,        0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SplineLawCGM,                  303,   71 , CATGeometricObjectsCGM,        0,   2010Spring,   NeverActivated,  -1 ) 
CATCGMStreamTypeDECLARE( CompositeLawCGM,               304,   72 , CATGeometricObjectsCGM,        0,   2010Spring,   NeverActivated,  -1 )
 

  // Cloud
CATCGMStreamTypeDECLARE( CldBodyCGM,                     400,   73 , CATMeshObjectsCGM,          -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CldCloudCGM,                    401,   74 , CATMeshObjectsCGM,            1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CldScanCGM,                     402,   75 , CATMeshObjectsCGM,            1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CldGridCGM,                     403,   76 , CATMeshObjectsCGM,            1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CldPolygonCGM,                  404,   77 , CATMeshObjectsCGM,            1,   2010Spring,   NeverActivated,  -1 )
 
CATCGMStreamTypeDECLARE( CldSetOfScansCGM,               405,   78 , CATMeshObjectsCGM,           -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CldSetOfGridsCGM,               406,   79 , CATMeshObjectsCGM,           -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CldScanOnPolygonCGM,            407,   80 , CATMeshObjectsCGM,            2,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CldVectorsCGM,                  408,   81 , CATMeshObjectsCGM,            2,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CldSubPolygonCGM,               409,   82 , CATMeshObjectsCGM,            2,   2010Spring,   NeverActivated,  -1 )
 
CATCGMStreamTypeDECLARE( CldSetOfPointsFCGM,             420,   83 , CATMeshObjectsCGM,            0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CldSetOfPointsDCGM,             421,   84 , CATMeshObjectsCGM,            0,   2010Spring,   NeverActivated,  -1 )
 

//Subdivision Mesh
CATCGMStreamTypeDECLARE( SubdivMeshCGM,                  450,   85 , CATMeshObjectsCGM,           -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SubdivMeshGeoCGM,               451,   86 , CATMeshObjectsCGM,            0,   2010Spring,   NeverActivated,  -1 )
 

// Polyhedral objects
CATCGMStreamTypeDECLARE( GeoPolyPointImpl,               460,   87 , CATMeshObjectsCGM,            0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GeoPolyCurveImpl,               470,   88 , CATMeshObjectsCGM,            0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GeoPolySurfaceImpl,             480,   89 , CATMeshObjectsCGM,            0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GeoPolyBodyImpl,                490,   90 , CATMeshObjectsCGM,            0,   2010Spring,   NeverActivated,  -1 )
 
 
// Topology
CATCGMStreamTypeDECLARE( BodyCGM,                      500,   91 , CATTopologicalObjects,         -1,   2010Spring,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( WireCGM,                      502,   92 , CATTopologicalObjects,         -1,   2010Spring,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( VertexCGM,                    510,   93 , CATTopologicalObjects,          1,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( EdgeCGM,                      511,   94 , CATTopologicalObjects,          5,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( FaceCGM,                      512,   95 , CATTopologicalObjects,         -1,   2010Spring,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( VolumeCGM,                    513,   96 , CATTopologicalObjects,         -1,   2010Spring,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( ShellCGM,                     520,   97 , CATTopologicalObjects,         -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( LoopCGM,                      521,   98 , CATTopologicalObjects,         -1,   2010Spring,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( VertexInFaceCGM,              523,   99 , CATTopologicalObjects,          2,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( VertexInVolumeCGM,            524,  100 , CATTopologicalObjects,          1,   2010Spring,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( LumpCGM,                      525,  101 , CATTopologicalObjects,         -1,   2010Spring,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( ConfusedLoopCGM,              526,  102 , CATTopologicalObjects,          0,   2010Spring,   NeverActivated,  -1 )
 

// Live Shape  
//    ???  CATManifoldCGMType     = 530 
CATCGMStreamTypeDECLARE( CellManifoldCGM,                    531,  103 , CATTopologicalObjects,  -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( DatumManifoldCGM,                   540,  104 , CATTopologicalObjects,  -1,   2010Spring,   NeverActivated,  -1 )

 //    ???  CATContextualManifoldCGMType = 550,
CATCGMStreamTypeDECLARE( BoneFilletCGM,                      550,  105 , CATTopologicalObjects,  -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( JointFilletCGM,                     551,  106 , CATTopologicalObjects,  -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( BoneChamferCGM,                     552,  123 , CATTopologicalObjects,  -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( DraftManifoldCGM,                   557,  150 , CATTopologicalObjects,  -1,   2016Fall,   NeverActivated,  -1 ) //SOU
CATCGMStreamTypeDECLARE( ButtonManifoldCGM,                  558,  151 , CATTopologicalObjects,  -1,   2017Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( JointChamferCGM,                    559,  153 , CATTopologicalObjects,  -1,   2020Fall,   NeverActivated,  -1 )//REN

 //    ???  CATEvaluableManifoldCGMType = 570,
CATCGMStreamTypeDECLARE( SubdivisionManifoldCGM,            571,  107 , CATTopologicalObjects,   -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( PlaneManifoldCGM,                  572,  108 , CATTopologicalObjects,   -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CylinderManifoldCGM,               573,  109 , CATTopologicalObjects,   -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SphereManifoldCGM,                 574,  110 , CATTopologicalObjects,   -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( ConeManifoldCGM,                   575,  111 , CATTopologicalObjects,   -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( TorusManifoldCGM,                  576,  112 , CATTopologicalObjects,   -1,   2010Spring,   NeverActivated,  -1 )


 //    ??? CATManifoldGroupCGMType = 580,
 //    ??? CATForeignManifoldGroupCGMType = 582,   
CATCGMStreamTypeDECLARE( ContextualManifoldGroupCGM,      581,  113 , CATTopologicalObjects,     -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( HierarchicalManifoldGroupCGM,    585,  114 , CATTopologicalObjects,     -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( CellManifoldGroupCGM,            586,  124 , CATTopologicalObjects,     -1,   2010Spring,   NeverActivated,  -1 )

  // User Geometry
CATCGMStreamTypeDECLARE( UserGeometryCGM,                 600,  115 , CATGeometricObjectsCGM,     0,   2010Spring,   NeverActivated,  -1 )

  // Attributes
CATCGMStreamTypeDECLARE( HeadAttributeDefCGM,             700,  116 , CATGeometricObjects,        0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( AttributeDefCGM,                 701,  117 , CATGeometricObjects,        0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( HeadAttributeCGM,                702,  118 , CATGeometricObjects,        0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( AttributeCGM,                    703,  119 , CATGeometricObjects,        0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( SharpnessDefCGM,                 800,  120 , CATGeometricObjects,        0,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( LyingOnDefCGM,                   900,  121 , CATTopologicalObjects,      0,   2010Spring,   NeverActivated,  -1 )
 
CATCGMStreamTypeDECLARE( RootContainerCGM,                  1,  122 , CATGeometricObjectsCGM,    -1,   2010Spring,   NeverActivated,  -1 )

// HGeometry
CATCGMStreamTypeDECLARE( IntersectionHVertexCGM,          554,  125 , CATTopologicalObjects,     -1,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( RatioHVertexCGM,                 555,  126 , CATTopologicalObjects,      2,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( DistanceHVertexCGM,              556,  127 , CATTopologicalObjects,      2,   2010Spring,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( HEdgeCGM,                        553,  128 , CATTopologicalObjects,     -1,   2010Spring,   NeverActivated,  -1 )


// polyhedral Topology
CATCGMStreamTypeDECLARE( GMPolyBody,                      430,  129 , CATGMPolyObjects,         -1,   2016Fall,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( GMPolyVertex,                    431,  130 , CATGMPolyObjects,         -1,   2016Fall,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( GMPolyEdge,                      432,  131 , CATGMPolyObjects,         -1,   2016Fall,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( GMPolyFace,                      433,  132 , CATGMPolyObjects,         -1,   2016Fall,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( GMPolyVolume,                    434,  133 , CATGMPolyObjects,         -1,   2016Fall,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( GMPolyVertexInFace,              435,  134 , CATGMPolyObjects,          2,   2016Fall,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( GMPolyVertexInVolume,            436,  135 , CATGMPolyObjects,          1,   2016Fall,   NeverActivated,  +1 )
CATCGMStreamTypeDECLARE( GMPolyWire,                      437,  136 , CATGMPolyObjects,         -1,   2016Fall,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( GMPolyLoop,                      438,  137 , CATGMPolyObjects,         -1,   2016Fall,   NeverActivated,   0 )
CATCGMStreamTypeDECLARE( GMPolyShell,                     439,  138 , CATGMPolyObjects,         -1,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyLump,                      440,  139 , CATGMPolyObjects,         -1,   2016Fall,   NeverActivated,   0 )


// polyhedral Geometry
CATCGMStreamTypeDECLARE( GMPolyPoint,                     441,  140 , CATGMPolyObjects,          0,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyPointOnCurve,              442,  141 , CATGMPolyObjects,          1,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyPointOnSurface,            443,  142 , CATGMPolyObjects,          1,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolySingleCurve,               444,  143 , CATGMPolyObjects,          0,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyCurveOnCurve,              445,  144 , CATGMPolyObjects,          1,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyCurveOnSurface,            446,  145 , CATGMPolyObjects,          1,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyCouplingCurve,             447,  146 , CATGMPolyObjects,          2,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolySurface,                   448,  147 , CATGMPolyObjects,          0,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolySurfOnExactSurf,           449,  148 , CATGMPolyObjects,          1,   2016Fall,   NeverActivated,  -1 )

// additional polyhedral Geometry
CATCGMStreamTypeDECLARE( GMPolyCurve3D,                   410,  149 , CATGMPolyObjects,          0,   2016Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyCurveOnPlane,              411,  152 , CATGMPolyObjects,          2,   2019Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyCurveOnExactCurve,         412,  154 , CATGMPolyObjects,          1,   2021Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyCurve3DOnExactCurve,       413,  155 , CATGMPolyObjects,          1,   2021Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyCurveOnDirSurf,            414,  156 , CATGMPolyObjects,          1,   2021Fall,   NeverActivated,  -1 )
CATCGMStreamTypeDECLARE( GMPolyGeoPolyBody,               415,  157 , CATGMPolyObjects,          0,   2021Fall,   NeverActivated,  -1 )

// implicit Geometry
CATCGMStreamTypeDECLARE( GMImplicitSurface,               452,  158 , GMScalarFieldsObjects,       -1,   2022Fall,   NeverActivated,  -1 )
#endif
