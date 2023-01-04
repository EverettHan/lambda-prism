// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// Creation AJM 12.Dec.2003
//
// For diagnostics associated with CGM checks
//=============================================================================

#ifndef __CATCheckDiagnosis_EmbedClasses_h__
#define __CATCheckDiagnosis_EmbedClasses_h__

#include "CheckOperators.h"
#include "CATCheckDiagnosis_Embed.h"
#include "CATBoolean.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATGeometry;

//====================================================================================================

#define DECLARE_BEGIN_CATCheckDiagnosisEmbedClass(CATCheckDiagnosisClassName)                           \
class CATCheckDiagnosisClassName##_Embed: public CATCheckDiagnosis_Embed                           \
{                                                                                                  \
   public:                                                                                         \
      CATCheckDiagnosisClassName##_Embed( CATGeometry   * iGeometry      = (CATGeometry*)0,        \
                                  CATBoolean      iMustThrow     = FALSE,                          \
                                  CATBoolean      iMustDump      = FALSE,                          \
                                  CATCheckDiagnosis::MessageId       iMessageId     = CATCheckDiagnosis::NoMessage,   \
                                  const char    * iSpecifiMesage = (const char*)0);                \
      virtual ~CATCheckDiagnosisClassName##_Embed();                                               \
      virtual const char * ClassName() const;                                                      \
      virtual unsigned int GetType() const;                                                        \
      virtual int          IsATypeOf(unsigned int iTypeReference) const;                           \
      virtual CATBoolean   IsInvalid() const;                                                      \


#define DECLARE_END_CATCheckDiagnosisEmbedClass()                                                       \
};                                                                                                 \


#define DECLARE_CATCheckDiagnosisEmbedClass(CATCheckDiagnosis_EmbedClassName)                                 \
        DECLARE_BEGIN_CATCheckDiagnosisEmbedClass(CATCheckDiagnosis_EmbedClassName)                           \
        DECLARE_END_CATCheckDiagnosisEmbedClass()                                                       \

//====================================================================================================

#define DECLARE_BEGIN_CATCheckDiagnosisClass(CATCheckDiagnosisClassName)                           \
class CATCheckDiagnosisClassName: public CATCheckDiagnosis                                         \
{                                                                                                  \
   public:                                                                                         \
      CATCheckDiagnosisClassName( CATGeometry   * iGeometry      = (CATGeometry*)0,                \
                                  CATBoolean      iMustThrow     = FALSE,                          \
                                  CATBoolean      iMustDump      = FALSE,                          \
                                  MessageId       iMessageId     = NoMessage,                      \
                                  const char    * iSpecifiMesage = (const char*)0);                \
      virtual ~CATCheckDiagnosisClassName();                                                       \

#define DECLARE_END_CATCheckDiagnosisClass(CATCheckDiagnosisClassName)                             \
private:                                                                                           \
  CATCheckDiagnosisClassName##_Embed _EmbeddedObject;                                              \
};                                                                                                 \

//====================================================================================================
// Pay attention: it's not possible to pass a macro as another macro's argument.
// You have to repeat the name of the class as often as needed.

DECLARE_CATCheckDiagnosisEmbedClass(CATCheckDiagnosisInvalidCurvatureCurve)
DECLARE_BEGIN_CATCheckDiagnosisClass(CATCheckDiagnosisInvalidCurvatureCurve)
#undef  CATCGM_DIAG_IMPL_CLASS
#define CATCGM_DIAG_IMPL_CLASS CATCheckDiagnosisInvalidCurvatureCurve
#include "CATCheckDiagnosisImplDeclare.h"
DECLARE_END_CATCheckDiagnosisClass(CATCheckDiagnosisInvalidCurvatureCurve)

DECLARE_CATCheckDiagnosisEmbedClass(CATCheckDiagnosisInvalidCurvatureSurface)
DECLARE_BEGIN_CATCheckDiagnosisClass(CATCheckDiagnosisInvalidCurvatureSurface)
#undef  CATCGM_DIAG_IMPL_CLASS
#define CATCGM_DIAG_IMPL_CLASS CATCheckDiagnosisInvalidCurvatureSurface
#include "CATCheckDiagnosisImplDeclare.h"
DECLARE_END_CATCheckDiagnosisClass(CATCheckDiagnosisInvalidCurvatureSurface)

DECLARE_CATCheckDiagnosisEmbedClass(CATCheckDiagnosisInvalidTopologicalEdgeLength)
DECLARE_BEGIN_CATCheckDiagnosisClass(CATCheckDiagnosisInvalidTopologicalEdgeLength)
#undef  CATCGM_DIAG_IMPL_CLASS
#define CATCGM_DIAG_IMPL_CLASS CATCheckDiagnosisInvalidTopologicalEdgeLength
#include "CATCheckDiagnosisImplDeclare.h"
DECLARE_END_CATCheckDiagnosisClass(CATCheckDiagnosisInvalidTopologicalEdgeLength)

//====================================================================================================

#endif // __CATCheckDiagnosis_EmbedClasses_h__

