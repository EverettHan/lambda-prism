// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2018
// ................................
//
// VB7
//==========================================================
// !!!!!!!!!!!!!!!!!!!!!!DO NOT USE!!!!!!!!!!!!!!!!!!!!!!!!!
//==========================================================
// WORK IN PROGRESS VB7 W04 2018
// ----------------------------------------------------------------------------//

#ifndef CATDRepLabel_H
#define CATDRepLabel_H

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"
#include "ListPOfCATBody.h"
#include "CATErrorDef.h"

// class CATCGMStream;
class CATCGMOutput;
class CATDRepLabelCGM;
class CATMathStream;

class ExportedByCATGMModelInterfaces CATDRepLabel : public CATCGMVirtual
{
public: 

  virtual ~CATDRepLabel();

  virtual CATBoolean IsEqual(CATDRepLabel * iDRepLabel) const=0;

  virtual CATUnicodeString GetLabelStr() const=0;

  virtual void Dump(CATCGMOutput& os) const=0;

  virtual void Stream(CATMathStream & ioStream) const=0;  

  // protected -> Use CATLoadDRepLabel
  virtual void UnStream( CATMathStream& ioStr )=0;

protected:
  virtual CATDRepLabelCGM * GetDRepLabelCGM() const =0;

  /* Default constructor */
  CATDRepLabel();
  /**
	* Copy constructor. 
	**/
	CATDRepLabel(CATDRepLabel const& iOther);	
	/**
	* Assignment operator.
	**/
	CATDRepLabel& operator=(CATDRepLabel const& iOther); 

private:
  friend class CATDRepLabelCGM;
  friend class CATGMDRepLabelUtilities;
};

/*-------------------------------------------------------------
 * Official Unstream Method
 *-------------------------------------------------------------*/
ExportedByCATGMModelInterfaces HRESULT CATLoadDRepLabel(CATMathStream &ioStr, CATDRepLabel *& oDRepLabel);


#endif

