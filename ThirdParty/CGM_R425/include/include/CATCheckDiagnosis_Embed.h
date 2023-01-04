// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  03/10/2000
// 24/07/2015  G5S  Create read, write and validate functions so we can have a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker.
//
// Gestion des diagnostics associes aux checks
//=============================================================================

#ifndef __CATCheckDiagnosis_Embed_h__
#define __CATCheckDiagnosis_Embed_h__

#include "CheckOperators.h"
#include "CATGeometry.h"
#include "CATUnicodeString.h"
#include "CATTopology.h"
#include "CATCheckDiagnosis.h"

class CATCGMObject;
class CATCXTopology;

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/**
 * Class to be embedded in check diagnosis classes.
 */
class ExportedByCheckOperators CATCheckDiagnosis_Embed
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================
      CATCheckDiagnosis_Embed(CATGeometry   * iGeometry      = (CATGeometry*)0,
                        CATBoolean      iMustThrow     = FALSE,
                        CATBoolean      iMustDump      = FALSE,
                        CATCheckDiagnosis::MessageId       iMessageId     = CATCheckDiagnosis::NoMessage,
                        const char    * iSpecifiMesage = (const char*)0);

      virtual ~CATCheckDiagnosis_Embed();


      //==========================
      // Acces aux donnees membres
      //==========================
      CATTopology  * GetCheckedTopo() const ;
      void           SetCheckedTopo(CATTopology * iCheckedTopo) ;

      CATCheckDiagnosis::MessageId      GetMessageId() const;
      void SetMessageId(CATCheckDiagnosis::MessageId iMsgId);

      const char   * GetMessage() const;

      const char   * GetSpecificMessage() const;
      void           SetSpecificMessage(const char* iMessage);

      CATBoolean   MustDump()  const;
      void         SetMustDump(CATBoolean iMustDump); 
      
      CATBoolean   MustThrow() const;
      void         SetMustThrow(CATBoolean iMustThrow); 
      
      void *       GetAssociatedData() const;
      void         SetAssociatedData(void* ipAssociatedData);

      void         UpdateCheckDiagnosisType(CATCheckDiagnosis::CATCheckDiagnosisTypeId idiagTypeID);

      CATCGMObject      *GetAssociatedObjectPtr() const;

      //====================================================
      // Methods for CGMReplay recording.
      //====================================================
      virtual void        WriteOutput(CATCGMStream &ioStream);
      virtual void        WriteOutput(CATCGMStream &ioStream, CATBoolean iDefineAssociatedObject);

      // Set the member variables according to the stream.
      virtual CATBoolean  ReadReferenceOutput(CATCGMStream & Str, CATListOfInt & oVersionNumbers);
      virtual CATBoolean  ValidateOutput(CATCheckDiagnosis * iRefDiagnosis, CATSoftwareConfiguration * iConfig, 
         CATListOfInt & iVersionNumbers);
      virtual CATBoolean  ValidateOutput(CATCheckDiagnosis * iRefDiagnosis, CATSoftwareConfiguration * iConfig, 
        CATBoolean iDefineAssociatedObject, CATListOfInt & iVersionNumbers);

      //=================================
      // Methodes virtuelles
      //=================================

      virtual CATGeometry  * GetAssociatedObject() const ;

      virtual void           Dump(CATCGMOutput & iOutput) const;
      //virtual void           Dump(ostream& iOutput) const;

      virtual const char   * ClassName() const;

      virtual unsigned int   GetType() const;

      virtual int            IsATypeOf(unsigned int iTypeReference) const;
      
      virtual CATBoolean     IsInvalid() const;

      virtual int operator   == (const CATCheckDiagnosis& iDiagnosis) const;

      static CATGeometry * ScaleGeometry(CATGeometry * iGeometry);

   protected: // Methodes a usage interne

      void iCleanupAssociatedData();
      CATBoolean ValidateAssociatedGeometry (CATGeometry * iAssociatedGeometry, 
        CATGeometry * iRefAssociatedGeometry, CATSoftwareConfiguration * iConfig);

   protected: // Donnees membres
      CATCXTopology     * _CheckedTopo;           // Topologie checkee. face||wire 

      CATCGMObject      * _AssociatedObject;    // Topologie/Geometrie associee au diagnostic

      CATCheckDiagnosis::MessageId           _MessageId;           // Indice dans le tableau _ErrorMessages

      CATUnicodeString    _SpecificMessage;     // Au cas ou
  
      static const char * _ErrorMessages[];

      CATBoolean          _MustDump;

      CATBoolean          _MustThrow;

      void *              _pAssociatedData;

      CATCheckDiagnosis::CATCheckDiagnosisTypeId _diagTypeID;      // Explicit usage: for using _pAssociatedData 
};

#endif
