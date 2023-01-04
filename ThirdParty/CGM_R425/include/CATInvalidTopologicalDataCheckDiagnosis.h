// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS-ICE-XDT  05/12/2000
//
// Gestion des diagnostics associes aux checks de validite topolgique
//=============================================================================

#ifndef __CATInvalidTopologicalDataCheckDiagnosis_h__
#define __CATInvalidTopologicalDataCheckDiagnosis_h__

#include "CheckOperators.h"
#include "CATCheckDiagnosisImpl.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif


class ExportedByCheckOperators CATInvalidTopologicalDataCheckDiagnosis: public CATCheckDiagnosisImpl
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATInvalidTopologicalDataCheckDiagnosis(CATGeometry   * iGeometry      = (CATGeometry*)0,
                                              CATBoolean      iMustThrow     = FALSE,
                                              CATBoolean      iMustDump      = FALSE,
                                              MessageId       iMessageId     = CATCheckDiagnosis::NoMessage,
                                              const char    * iSpecifiMesage = (const char*)0);
                        
      virtual ~CATInvalidTopologicalDataCheckDiagnosis();


      //=================================
      // Methodes virtuelles
      //=================================

      virtual const char * ClassName() const;

      virtual unsigned int GetType() const;

      virtual int          IsATypeOf(unsigned int iTypeReference) const;

      virtual CATBoolean   IsInvalid() const; 

};

#endif
