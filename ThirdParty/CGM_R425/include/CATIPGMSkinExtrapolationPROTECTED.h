#ifndef CATIPGMSkinExtrapolationPROTECTED_h_
#define CATIPGMSkinExtrapolationPROTECTED_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMSkinExtrapolation.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSkinExtrapolationPROTECTED;

class ExportedByCATGMOperatorsInterfaces CATIPGMSkinExtrapolationPROTECTED: public CATIPGMSkinExtrapolation
{
public:
  /**
   * Constructor
   */
  CATIPGMSkinExtrapolationPROTECTED();

  //////////////////////////////////////////////////////////////////
  // for reduce radius fillet (DS-Provence)
    virtual void      SetUnExtrapolMode              ()                                              = 0;

  // For FSS Extrapolation 
  // 1)Force the Use of FSS geometric operator (sweep is not used in this case )
  // 2) Precise the construction mode
  // 0 GEOmetrique / 1 ANAlytique / 2 AUTO
  // default mode is GEO ( GSD mode)
  // Throw on Error is wire is multi cells
    virtual void      SetFSSGeoAnaMode               (CATLONG32               iGeoAnaMode       = 0) = 0;

  //
  //  Usefull when Wire's Edges have gaps between their 3d and 2d representations
  //
  // ! Do not use this option with SetJournalMode(1) or SetJournalMode(2)
  // ! Can remove some vertex of the wire (less output faces than input edges) 
  // defaut is 0 ( no laydown , GSD behavior)
    virtual void      SetInternalLayDown             (CATLONG32               iLayDownMode      = 0) = 0;

  //
    virtual void      SetPlanesDetection             (CATBoolean              iPlanesDetection  = CATBoolean(1)) = 0;

    // 0 (default behavior), 1: active
    virtual void      SetC0UntwistMode               (CATLONG32               iC0UntwistMode    ) = 0;


protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSkinExtrapolationPROTECTED(); // -> delete can't be called
};

#endif /* CATIPGMSkinExtrapolationPROTECTED_h_ */
