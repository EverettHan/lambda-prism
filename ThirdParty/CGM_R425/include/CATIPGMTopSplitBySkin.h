#ifndef CATIPGMTopSplitBySkin_h_
#define CATIPGMTopSplitBySkin_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATTopSplitBySkinDef.h"

class CATExtTopOperator;
class CATLISTP(CATLump);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopSplitBySkin;

class ExportedByCATGMModelInterfaces CATIPGMTopSplitBySkin: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSplitBySkin();

  //===========================================
  // Methodes de parametrisation de l'operateur
  //===========================================
  virtual CATTopSplitBySkinSelectionSide GetSelectionSide() const = 0;

  virtual CATTopSplitBySkinSelectionMode GetSelectionMode() const = 0;

  virtual CATBoolean GetCheckJournal() const = 0;

  virtual CATBoolean GetSkinBodyIsInfinite() = 0;

  /**
			* Sets or unsets the ‘Keep elements in half space’ mode.
			*   @param iMode
			*      Mode on (TRUE) or off (FALSE)
			*/
  virtual void SetKeepHalfSpaceMode(CATBoolean iMode) = 0;

  /**
			* Queries whether ‘Keep elements in half space’ mode is activated or not.
			*   @param oMode
			*      Mode on (TRUE) or off (FALSE)
			*/
  virtual void GetKeepHalfSpaceMode(CATBoolean &oMode) = 0;

  virtual void SetCheckJournal(CATBoolean iCheckMode) = 0;

  virtual void SetSelectionSide(CATTopSplitBySkinSelectionSide iSelectionSide) = 0;

  virtual void SetSelectionMode(CATTopSplitBySkinSelectionMode iSelectionMode) = 0;

  virtual void SetSkinBodyIsInfinite(CATBoolean iIsInfinite) = 0;

  //======================================
  // Methodes specifiques a CATIPGMTopOperator
  //======================================
  // CATCGMReplay
  //virtual int Run() = 0;
  virtual CATBody *GetResult(CATCGMJournalList *ioJournal) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSplitBySkin(); // -> delete can't be called
};

#endif /* CATIPGMTopSplitBySkin_h_ */
