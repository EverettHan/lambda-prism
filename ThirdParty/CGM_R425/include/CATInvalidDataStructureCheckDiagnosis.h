// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation EDS-ICE-XDT  05/12/2000
// 24/07/2015  G5S  Dump method changed because we have functionality for a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker, which uses diagnosis objects and we need
//                  Dump to take the same parameters.
//
// Gestion des diagnostics associes aux checks de validite geometrique
//=============================================================================

#ifndef __CATInvalidDataStructureCheckDiagnosis_h__
#define __CATInvalidDataStructureCheckDiagnosis_h__

#include "CheckOperators.h"
#include "CATCheckDiagnosisImpl.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif


class ExportedByCheckOperators CATInvalidDataStructureCheckDiagnosis: public CATCheckDiagnosisImpl
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================
                        

      CATInvalidDataStructureCheckDiagnosis(CATGeometry   * iGeometry      = (CATGeometry*)0,
                                            CATBoolean      iMustThrow     = FALSE,
                                            CATBoolean      iMustDump      = FALSE,
                                            MessageId       iMessageId     = CATCheckDiagnosis::NoMessage,
                                            const char    * iSpecifiMesage = (const char*)0);
                        
      virtual ~CATInvalidDataStructureCheckDiagnosis();
    
      //=================================
      // Methodes virtuelles
      //=================================

      virtual void         Dump(CATCGMOutput & iOutput) const;

      virtual const char * ClassName() const;
      
      virtual unsigned int GetType() const;

      virtual int          IsATypeOf(unsigned int iTypeReference) const;

      virtual CATBoolean   IsInvalid() const; 

};

#endif
