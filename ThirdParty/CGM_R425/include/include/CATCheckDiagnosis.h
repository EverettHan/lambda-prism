#ifndef CATCheckDiagnosis_h_
#define CATCheckDiagnosis_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
//===========================================================================================
// 24/07/2015  G5S  Create read, write and validate functions so we can have a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker.
//===========================================================================================

#include "CATGMModelInterfaces.h"
#include "CATGeometry.h"
#include "CATUnicodeString.h"
#include "CATTopology.h"
#include "CATSoftwareConfiguration.h"

class CATCGMObject;
class CATCXTopology;

class CATCGMStream;

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/////////////////////////////////////////////////////////////////////////
// Following #defines are kept for backward compatibility only.
// Do not add/remove/modify these.
// Please use enum "CATCheckDiagnosisTypeId" instead.
#define CATCheckDiagnosisType ((unsigned int)0x01)
#define CATEdgeEdgeIntersectionCheckDiagnosisType ((unsigned int)0x03)
#define CATFaceFaceIntersectionCheckDiagnosisType ((unsigned int)0x04)
#define CATIntersectionCheckDiagnosisType ((unsigned int)0x02)
#define CATInvalidDataStructureCheckDiagnosisType ((unsigned int)0x10)
#define CATInvalidGeometricalDataCheckDiagnosisType ((unsigned int)0x07)
#define CATInvalidTopologicalDataCheckDiagnosisType ((unsigned int)0x06)
#define CATUnaccurateGeometryCheckDiagnosisType ((unsigned int)0x09)
#define CATUnaccurateTopologyCheckDiagnosisType ((unsigned int)0x08)
#define CATVertexDecompositionCheckDiagnosisType ((unsigned int)0x05)
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
// Following #defines are kept for backward compatibility only.
// Do not add/remove/modify these.
// Please use enum "CATCheckDiagnosisTypeId" instead.
/////////////////////////////////////////////////////////////////////////

class ExportedByCATGMModelInterfaces CATCheckDiagnosis
{
public:
      enum CATCheckDiagnosisTypeId
      {
        CATCheckDiagnosisNoneType                         = 0,
        CATCheckDiagnosisBaseType                         = 1,
        CATCheckDiagnosisIntersectionType                 = 2,
        CATCheckDiagnosisEdgeEdgeIntersectionType         = 3,
        CATCheckDiagnosisFaceFaceIntersectionType         = 4,
        CATCheckDiagnosisVertexDecompositionType          = 5,
        CATCheckDiagnosisInvalidTopologicalDataType       = 6,
        CATCheckDiagnosisInvalidGeometricalDataType       = 7,
        CATCheckDiagnosisUnaccurateTopologyType           = 8,
        CATCheckDiagnosisUnaccurateGeometryType           = 9,
        CATCheckDiagnosisInvalidDataStructureType         = 10,
        CATCheckDiagnosisInvalidCurvatureCurveType        = 11,
        CATCheckDiagnosisInvalidCurvatureSurfaceType      = 12,
        CATCheckDiagnosisInvalidTopologicalEdgeLengthType = 13
      };

      enum MessageId
      {
         NoMessage                         = -1,
         UndefinedLocation                 =  0,  
         UndefinedOrientation              =  1,
         InvalidLoopPosition               =  2,
         InvalidLoopOrientation            =  3,
         IncoherentEdgeOrientationInShell  =  4,
         IncoherentEdgeOrientationInFace   =  5,
         FaceWithoutExternalLoop           =  6,
         TopologyWithNoGeometryAssociated  =  7,
         InvalidSurface                    =  8,
         CuttingElementRemaining           =  9,
         CorruptedElement                  = 10,
         IntermediateModelisationRemaining = 11,
         EmptyClass                        = 12,
         IncompleteGeometricalDefinition   = 13,
         LoopNotClosed                     = 14,
         BigGap                            = 15,
         EdgeInsideVertex                  = 16,
         FlattenedTopology                 = 17,
         InvalidFace                       = 18,
         TooSmallElement                   = 19,
         InvalidDecomposition              = 20,
         InvalidEdgeOrientation            = 21,
         WireNotDone                       = 22,
         HermetisedEdgeDomain              = 23,
         InvalidCurve                      = 24,
         VolumeWithoutExternalShell        = 25,
         InvalidShellPosition              = 26,
         InvalidShellOrientation           = 27,
         ShellWithComposite                = 28,
         InvalidCurvatureCurve             = 29,
         InvalidCurvatureSurface           = 30,
         SelfIntersectionShell             = 31,
         TopologicalEdgeLength             = 32,
         SelfIntersectionWire              = 33
      };

  /**
   * Constructor
   */
  CATCheckDiagnosis();

  /**
   * Destructor
   */
  virtual ~CATCheckDiagnosis();

  //==========================
  // Acces aux donnees membres
  //==========================
  virtual CATTopology *GetCheckedTopo() const = 0;

  virtual void SetCheckedTopo(CATTopology *iCheckedTopo) = 0;

  virtual MessageId GetMessageId() const = 0;

  virtual void SetMessageId(CATCheckDiagnosis::MessageId iMsgId) = 0;

  virtual const char *GetMessage() const = 0;

  virtual const char *GetSpecificMessage() const = 0;

  virtual void SetSpecificMessage(const char *iMessage) = 0;

  virtual CATBoolean MustDump() const = 0;

  virtual void SetMustDump(CATBoolean iMustDump) = 0;

  virtual CATBoolean MustThrow() const = 0;

  virtual void SetMustThrow(CATBoolean iMustThrow) = 0;

  virtual void *GetAssociatedData() const = 0;

  virtual void SetAssociatedData(void *ipAssociatedData) = 0;

  virtual void UpdateCheckDiagnosisType(
    CATCheckDiagnosis::CATCheckDiagnosisTypeId idiagTypeID) = 0;

  //===================================================================================
  // Methods for CGMReplay of operators using CATCheckDiagnosis, including CATChecker.
  //===================================================================================
  virtual void        WriteOutput(CATCGMStream &ioStream) = 0;
  virtual CATBoolean  ReadReferenceOutput(CATCGMStream & Str, CATListOfInt & oVersionNumbers) = 0;
  virtual CATBoolean  ValidateOutput(CATCheckDiagnosis * iRefDiagnosis, CATSoftwareConfiguration * iConfig, 
                                     CATListOfInt & iVersionNumbers) = 0;

  //=================================
  // Methodes virtuelles
  //=================================
  virtual CATGeometry *GetAssociatedObject() const = 0;

  virtual void Dump(CATCGMOutput &iOutput) const = 0;
  //virtual void Dump(ostream &iOutput) const = 0;

  virtual const char *ClassName() const = 0;

  virtual unsigned int GetType() const = 0;

  virtual int IsATypeOf(unsigned int iTypeReference) const = 0;

  virtual CATBoolean IsInvalid() const = 0;

  virtual int operator == (const CATCheckDiagnosis& iDiagnosis) const = 0;
};

#endif /* CATCheckDiagnosis_h_ */
