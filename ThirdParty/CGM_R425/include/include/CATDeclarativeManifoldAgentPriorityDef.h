#ifndef CATDeclarativeManifoldAgentPriorityDef_H
#define CATDeclarativeManifoldAgentPriorityDef_H

// -----------------------------------------------------------------------------------------------
// Agent priority definition
// -----------------------------------------------------------------------------------------------
#define CATSharedManifoldAgentPriority                            0
#define CATCellManifoldCreatorPriority                            1
#define CATCellManifoldMergerPriority                             1
#define CATCellManifoldCreatorTransfoContextPriority              1
#define CATDeclarativeManifoldCarrierPriority                     2
#define CATAdvancedManifoldCarrierPriority                        2
#define CATDeclarativeManifoldCarrierTransfoContextPriority       2
#define CATDeclarativeManifoldDuplicationCarrierPriority          3
#define CATFilletManifoldCreatorInfraContextPriority              4
#define CATChamferManifoldCreatorInfraContextPriority             5
#define CATDraftManifoldCreatorInfraContextPriority               6
#define CATFilletManifoldCreatorPriority                          7
#define CATChamferManifoldCreatorPriority                         7
#define CATDraftManifoldCreatorPriority                           7

// AJT1: old DeclarativeManifold order
#define CATDraftRecognizerPriority_2018                           8
#define CATFilletRecognizerPriority_2018                          9
#define CATChamferRecognizerPriority_2018                         10

// AJT1: new DeclarativeManifold order (need RibbonSeedsSharedSorter)
#define CATFilletRecognizerPriority_2020                          8
#define CATChamferRecognizerPriority_2020                         9
#define CATDraftRecognizerPriority_2020                           10

#define CATCanonicRecognizerPriority                              11
#define CATExtrudeAndRevolRecognizerPriority                      12
#define CATSubdivisionRecognizerPriority                          13
#define CATDatumManifoldCarrierPriority                           14
#define CATDatumManifoldCreatorPriority                           15
#define CATManifoldGroupCarrierPriority                           20
#define CATCellManifoldGroupCarrierPriority                       22
#define CATCellManifoldPatternGroupCarrierPriority                21
#define CATCellManifoldGroupSplitterPriority                      22
#define CATCellManifoldGroupSplitterSCrtPriority                  22
#define CATCellManifoldPatternCreatorPriority                     24
#define CATCellManifoldOffsetCreatorPriority                      25
#define CATWallAndBendRecognizerPriority                          28
#define CATNotchManifoldCreatorPriority                           29
#define CATSlotManifoldCreatorPriority                            30
#define CATHoleManifoldCreatorPriority                            31
#define CATPadPocketManifoldCreatorPriority                       33
#define CATPatternAdvancedRecognizerPriority                      34
#define CATBRepCopyAdvancedRecognizerPriority                     35
#define CATCutoutAdvancedRecognizerPriority                       36
#define CATLogoRecognizerPriority                                 37
#define CATButtonManifoldRecognizerPriority                       38
#define CATButtonManifoldGlobalRecognizerPriority                 39
// IZE aims to replace Recognition/Creation Agents
#define CATDRepSeedAgentPriority                                  39
#define CATDRepAdvancedStampCreatorPriority                       40
#define CATDRepAdvancedStampLocalRecognitionPriority              41
#define CATDRepAdvancedStampGlobalRecognitionPriority             42
#define CATDRepNameCarrierAgentPriority                           43
// -----------------------------------------------------------------------------------------------

#endif
