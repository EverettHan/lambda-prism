// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  03/10/2000
// 24/07/2015  G5S  Create read, write and validate functions so we can have a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker, which uses diagnosis objects.
//
// Gestion des diagnostics associes aux checks d'intersection
//=============================================================================

#ifndef __CATIntersectionCheckDiagnosis_Embed_h__
#define __CATIntersectionCheckDiagnosis_Embed_h__

#include "CheckOperators.h"
#include "CATCheckDiagnosis_Embed.h"
#include "CATIntersectionCheckDiagnosis.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATTopology;
class CATDomain;
class CATCell;

class CATCXTopology;
class CATCXDomain;

class ExportedByCheckOperators CATIntersectionCheckDiagnosis_Embed: public CATCheckDiagnosis_Embed
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATIntersectionCheckDiagnosis_Embed(CATCheckDiagnosisLocation   iIntersectionLocation,
                                    CATDomain                 * iFirstIntersectedDomain,
                                    CATDomain                 * iSecondIntersectedDomain,
                                    CATTopology               * iAssociatedTopology = (CATTopology*)0);
      CATIntersectionCheckDiagnosis_Embed();
                        
      virtual ~CATIntersectionCheckDiagnosis_Embed();


      //==========================
      // Acces aux donnees membres
      //==========================

      CATCheckDiagnosisLocation   GetCheckDiagnosisLocation() const;
      const char                * GetCheckDiagnosisLocationAsString() const;
 

      //	Retourne les deux domains (shell/wire) auquels appartiennent les deux topologies confrontées.
      void GetIntersectedDomains(CATDomain*& oFirstDomain, CATDomain*& oSecondDomain) const;

      //====================================================
      // Methods for CGMReplay recording.
      //====================================================
      virtual void        WriteOutput(CATCGMStream &ioStream);
      virtual void        WriteOutput(CATCGMStream &ioStream, CATBoolean iDefineAssociatedObject);

      // Set the member variables according to the stream.
      virtual CATBoolean  ReadReferenceOutput(CATCGMStream & Str, CATListOfInt & oVersionNumbers);
      virtual CATBoolean  ValidateOutput(CATCheckDiagnosis * iRefDiagnosis, CATSoftwareConfiguration * iConfig, 
        CATListOfInt &iVersionNumbers);
      virtual CATBoolean  ValidateOutput(CATCheckDiagnosis * iRefDiagnosis, CATSoftwareConfiguration * iConfig, 
        CATBoolean iDefineAssociatedObject, CATListOfInt & iVersionNumbers);

      //=================================
      // Methodes virtuelles
      //=================================

      // Retourne les deux topologies dont la confrontation a donné naissance au diagnostic
      virtual void         GetIntersectedCells(CATCell*& oFirstCell, CATCell*& oSecondCell) const;

      virtual void         Dump(CATCGMOutput & iOutput) const;

      virtual const char * ClassName() const;
      
      virtual int          IsATypeOf(unsigned int iTypeReference) const;

      virtual unsigned int GetType() const;

      virtual int          operator == (const CATCheckDiagnosis& iDiagnosis) const;
      
   protected: // Donnees membres

      CATCheckDiagnosisLocation   _CheckDiagnosisLocation; // Location/localisation de l'intersection invalide
      CATCXDomain               * _FirstDomain;            // Domaines confrontes sources de l'invalidite
      CATCXDomain               * _SecondDomain;
};

#endif
