// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS  03/10/2000
// 24/07/2015  G5S  Dump method changed because we have functionality for a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker, which uses diagnosis objects and we need
//                  Dump to take the same parameters.
//
// Gestion des diagnostics associes aux checks d'intersection
//=============================================================================

#ifndef __CATVertexDecompositionCheckDiagnosis_h__
#define __CATVertexDecompositionCheckDiagnosis_h__

#include "CheckOperators.h"
#include "CATCheckDiagnosisImpl.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATWire;
class CATVertex;
class CATCXWire;

class ExportedByCheckOperators CATVertexDecompositionCheckDiagnosis: public CATCheckDiagnosisImpl
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

     CATVertexDecompositionCheckDiagnosis(CATVertex     * iInvalidVertex,
       CATWire       * iInvalidWire);
     CATVertexDecompositionCheckDiagnosis();

      virtual ~CATVertexDecompositionCheckDiagnosis();


      //==========================
      // Acces aux donnees membres
      //==========================

      CATWire * GetWire() const;


      //=================================
      // Methodes virtuelles
      //=================================

      virtual void         Dump(CATCGMOutput & iOutput) const;

      virtual const char * ClassName() const;
      
      virtual unsigned int GetType() const;

      virtual int          IsATypeOf(unsigned int iTypeReference) const;

   protected: // Methodes a usage interne

      
   protected: // Donnees membres

      CATCXWire  * _InvalidWire;  // Wire dont un des vertex extremite ne suit pas la
                                  // regle de decomposition (connection a un vertex
                                  // intermediaire d'un autre wire)
};

#endif
