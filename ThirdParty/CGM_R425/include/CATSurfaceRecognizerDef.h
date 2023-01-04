#ifndef CATSurfaceRecognizerDef_h_
#define CATSurfaceRecognizerDef_h_
//==============================================================================================
//
//  Values to use with CATIPGMSurfaceRecognizer
//  these values can be stored by the application => do not change them
//
//==============================================================================================
// Creation ? KJD
// Mise en page 07/10/19 JSX 

enum CATSurfReco_DetectionMode{CATSurfReco_CanonicDetection = 0,
                               CATSurfReco_FilletDetection  = 1,
                               CATSurfReco_ChamferDetection = 2,
                               CATSurfReco_AdvServices      = 3,
                               CATSurfReco_DraftDetection   = 4,
                               CATSurfReco_CircularSweepDetection = 5 };


enum CATSurfReco_SurfaceType{CATSurfReco_Undefined = 0, 
                             CATSurfReco_Plane     = 1,
                             CATSurfReco_Sphere    = 2,
                             CATSurfReco_Cylinder  = 3,
                             CATSurfReco_Cone      = 4,
                             CATSurfReco_Torus     = 5, 
                             CATSurfReco_Fillet    = 6, 
                             CATSurfReco_CircleFillet = 7,
                             CATSurfReco_DirtyFillet  = 8, 
                             CATSurfReco_Chamfer      = 9, 
                             CATSurfReco_DirtyChamfer = 10, 
                             CATSurfReco_G2Fillet     = 11, 
                             CATSurfReco_Draft        = 12, 
                             CATSurfReco_CircularSweep = 13 };

enum CATSurfReco_FilletType{CATSurfReco_None     = 0, 
                            CATSurfReco_Constant = 1, 
                            CATSurfReco_Variable = 2, 
                            CATSurfReco_ConstantChordal = 3,
                            CATSurfReco_G2         = 4, 
                            CATSurfReco_VariableG1 = 5}; 

enum CATSurfReco_FilletBorderType{CATSurfReco_Unknown     = 0,
                                  CATSurfReco_StartCircle = 1, 
                                  CATSurfReco_EndCircle   = 2,
                                  CATSurfReco_LowContactBorder  = 3,
                                  CATSurfReco_HighContactBorder = 4};
 
enum CATSurfReco_PointedDeformation{CATSurfReco_Any       = 0,
                                    CATSurfReco_UMinPoint = 1, 
                                    CATSurfReco_UMaxPoint = 2,
                                    CATSurfReco_VMinPoint = 3,
                                    CATSurfReco_VMaxPoint = 4};

enum CATSurfReco_BorderType{CATSurfReco_Ambiguous = 0, 
                            CATSurfReco_UMin      = 1,
                            CATSurfReco_UMax      = 2,
                            CATSurfReco_VMin      = 3, 
                            CATSurfReco_VMax      = 4};

enum CATSurfReco_ChamferType{CATSurfReco_NotDefined  = 0, 
                             CATSurfReco_D1D2Chamfer = 1, 
                             CATSurfReco_D1A1Chamfer = 2, 
                             CATSurfReco_DA1Chamfer  = 3, 
                             CATSurfReco_ApproxD1D2Chamfer = 4}; 

enum CATSurfReco_AdvToolId{CATSurfReco_Recognition  = 0,
                           CATSurfReco_ExtractFromRadiusAndPCurve = 1,
                           CATSurfReco_ExtractForOffset = 2,
                           CATSurfReco_PredictAnOffsetPoint = 3,
                           CATSurfReco_PredictOffsetPoints = 4,
                           CATSurfReco_ExtractFromRadius = 5,
                           CATSurfReco_RadiusLawAnchors = 6}; 

enum CATSurfReco_LawCanonicity{CATSurfReco_NotCanonical = 0, 
                               CATSurfReco_ConstantLaw = 1, 
                               CATSurfReco_LinearLaw = 2, 
                               CATSurfReco_SLaw = 3,
                               CATSurfReco_CubicLaw = 4};
#endif
