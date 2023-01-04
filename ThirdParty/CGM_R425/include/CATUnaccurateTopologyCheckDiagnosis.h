// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS-ICE-XDT  05/12/2000
//
// Gestion des diagnostics associes aux checks de validite topolgique
// 24/07/2015  G5S  Dump method changed because we have functionality for a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker, which uses diagnosis objects and we need
//                  Dump to take the same parameters.
//=============================================================================

#ifndef __CATUnaccurateTopologyCheckDiagnosis_h__
#define __CATUnaccurateTopologyCheckDiagnosis_h__

#include "CheckOperators.h"
#include "CATCheckDiagnosisImpl.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif


class ExportedByCheckOperators CATUnaccurateTopologyCheckDiagnosis: public CATCheckDiagnosisImpl
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATUnaccurateTopologyCheckDiagnosis(  
                                          CATGeometry   * iAssociatedObject = (CATGeometry*)0,
                                          double          iGap              = 0.0,
                                          CATBoolean      iMustThrow        = FALSE,
                                          CATBoolean      iMustDump         = FALSE,
                                          MessageId       iMessageId        = CATCheckDiagnosis::NoMessage,
                                          const char    * iSpecifiMesage    = (const char*)0);
                        
      virtual ~CATUnaccurateTopologyCheckDiagnosis();

      double  GetGap() { return _Gap; };
     
      //=================================
      // Methodes virtuelles
      //=================================

      virtual void         Dump(CATCGMOutput & iOutput) const;

      virtual const char * ClassName() const;
      
      virtual int          IsATypeOf(unsigned int iTypeReference) const;

      virtual unsigned int GetType() const;

   protected:

      double  _Gap ; // taille du trou
};

#endif
