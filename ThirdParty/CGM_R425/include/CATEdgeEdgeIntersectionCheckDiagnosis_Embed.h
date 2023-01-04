// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  06/10/2000
// 24/07/2015  G5S  Create read, write and validate functions so we can have a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker, which uses diagnosis objects.
//
// Gestion des diagnostics associes aux checks d'intersection edge/edge
//=============================================================================

#ifndef __CATEdgeEdgeIntersectionCheckDiagnosis_Embed_h__
#define __CATEdgeEdgeIntersectionCheckDiagnosis_Embed_h__

#include "CheckOperators.h"
#include "CATIntersectionCheckDiagnosis_Embed.h"
#include "CATEdgeEdgeIntersectionCheckDiagnosis.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATCell;
class CATDomain;
class CATEdge;
class CATWire;

class CATCXEdge;


class ExportedByCheckOperators CATEdgeEdgeIntersectionCheckDiagnosis_Embed: public CATIntersectionCheckDiagnosis_Embed
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATEdgeEdgeIntersectionCheckDiagnosis_Embed(
                                            CATCheckDiagnosisLocation   iCheckDiagnosisLocation,
                                            CATEdge                   * iFirstIntersectedEdge,
                                            CATEdge                   * iSecondIntersectedEdge,
                                            CATDomain                 * iFirstIntersectedDomain,
                                            CATDomain                 * iSecondIntersectedDomain,
                                            CATTopology               * iTopologicalIntersection = (CATTopology*)0);
      CATEdgeEdgeIntersectionCheckDiagnosis_Embed();
  
      virtual ~CATEdgeEdgeIntersectionCheckDiagnosis_Embed();


      //==========================
      // Acces aux donnees membres
      //==========================

      // Retourne les deux edges dont la confrontation a donné naissance au diagnostic
       void GetIntersectedEdges(CATEdge*& oFirstEdge, CATEdge*& oSecondEdge) const;

       //====================================================
       // Methods for CGMReplay recording.
       //====================================================
       virtual void        WriteOutput(CATCGMStream &ioStream);

       // Set the member variables according to the stream.
       virtual CATBoolean  ReadReferenceOutput(CATCGMStream & Str, CATListOfInt & oVersionNumbers);
       virtual CATBoolean  ValidateOutput(CATCheckDiagnosis * iRefDiagnosis, CATSoftwareConfiguration * iConfig, 
        CATListOfInt & iVersionNumbers);

      //=================================
      // Methodes virtuelles
      //=================================

      // Retourne les deux topologies dont la confrontation a donné naissance au diagnostic
      virtual void         GetIntersectedCells(CATCell*& oFirstCell, CATCell*& oSecondCell) const;
      
      virtual void         Dump(CATCGMOutput& iOutput) const;

      virtual const char * ClassName() const;
      
      virtual unsigned int GetType() const;

      virtual int          IsATypeOf(unsigned int iTypeReference) const;
 
   protected: // Methodes a usage interne
      // virtual void       WriteOutput(        CATCGMStream &ioStream);
      // virtual CATBoolean ReadReferenceOutput(CATCGMStream & Str    );

      
   protected: // Donnees membres

      CATCXEdge   * _FirstIntersectedEdge;
      CATCXEdge   * _SecondIntersectedEdge;
};

#endif
