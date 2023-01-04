// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  03/10/2000
// 24/07/2015  G5S  Create read, write and validate functions so we can have a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker, which uses diagnosis objects.
//
// Gestion des diagnostics associes aux checks d'intersection face/face
//=============================================================================

#ifndef __CATFaceFaceIntersectionCheckDiagnosis_Embed_h__
#define __CATFaceFaceIntersectionCheckDiagnosis_Embed_h__

#include "CheckOperators.h"
#include "CATIntersectionCheckDiagnosis_Embed.h"
#include "CATFaceFaceIntersectionCheckDiagnosis.h"

#include "CATListOfCATGeometries.h"
#include "CATCollec.h"

class CATTopology;
class CATCell;
class CATFace;
class CATShell;

class CATCXFace;
class CATFaceFaceIntersectionCheckDiagnosis;
class CATLISTP(CATCGMObject);

class ExportedByCheckOperators CATFaceFaceIntersectionCheckDiagnosis_Embed: public CATIntersectionCheckDiagnosis_Embed
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATFaceFaceIntersectionCheckDiagnosis_Embed(CATCheckDiagnosisLocation   iCheckDiagnosisLocation,
                                            CATFace                   * iFirstIntersectedFace,
                                            CATFace                   * iSecondIntersectedFace,
                                            CATShell                  * iFirstIntersectedDomain,
                                            CATShell                  * iSecondIntersectedDomain,
                                            CATTopology               * iTopologicalIntersection  = (CATTopology*)0,
                                            CATLISTP(CATGeometry)     * iTopologicalIntersections = (CATLISTP(CATGeometry)*)0);

      CATFaceFaceIntersectionCheckDiagnosis_Embed();

      virtual ~CATFaceFaceIntersectionCheckDiagnosis_Embed();


      //==========================
      // Acces aux donnees membres
      //==========================

      // Retourne les deux faces dont la confrontation a donné naissance au diagnostic
      void GetIntersectedFaces(CATFace*& oFirstFace, CATFace*& oSecondFace) const;

      int  GetAssociatedObjects(CATLISTP(CATGeometry)& ioAssociatedObjects) const;

      CATFaceFaceIntersectionCheckDiagnosis* Clone() const;

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
      virtual void           GetIntersectedCells(CATCell*& oFirstCell, CATCell*& oSecondCell) const;

      virtual CATGeometry  * GetAssociatedObject() const ;

      virtual void           Dump(CATCGMOutput& iOutput) const;

      virtual const char *   ClassName() const;
      
      virtual unsigned int   GetType() const;

      virtual int            IsATypeOf(unsigned int iTypeReference) const;

   protected: // Methodes a usage interne
      // virtual void       WriteOutput(        CATCGMStream &ioStream);
      // virtual CATBoolean ReadReferenceOutput(CATCGMStream & Str    );
      
   protected: // Donnees membres

      CATLISTP(CATCGMObject) * _AssociatedObjects;
      CATCXFace              * _FirstIntersectedFace;
      CATCXFace              * _SecondIntersectedFace;
};

#endif
