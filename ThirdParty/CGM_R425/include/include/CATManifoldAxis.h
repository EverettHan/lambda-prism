#ifndef CATManifoldAxis_h
#define CATManifoldAxis_h 1

// CATManifoldParameter
#include "CATManifoldParameter.h"
#include "CATBody.h"
#include "CATMathAxis.h"
#include "CATGMModelInterfaces.h"

class CATMathAxis;

class ExportedByCATGMModelInterfaces CATManifoldAxis : public CATManifoldParameter
{

  public:
    //## Constructors (generated)
      CATManifoldAxis(const CATMathAxis& iAxis,
                      CATDeclarativeManifold* iDeclaration, 
                      CATLONG32 iKey, 
                      CATManifoldParamDescription iDescription,
                      CATBoolean iEditable=TRUE,
                      CATBoolean iActive=TRUE);

      CATManifoldAxis* GetAsAxis ();

      CATMathAxis& GetAxis();

      HRESULT SetAxis (const CATMathAxis& iAxis);

      virtual int operator == (/*const*/ CATManifoldParameter &iOther) const;

      virtual void Scale(const double iXScaleFactor);

  private:
    //## Destructor (generated)
    virtual ~CATManifoldAxis();

    CATManifoldAxis(CATManifoldAxis const& iOther); // forbidden

    //## Other Operations (specified)
    virtual HRESULT Check () const;

    //VB7 for CGMReplay
    //presume that this and ioParameter have same key
    virtual HRESULT UpdateSpecificParameter (CATManifoldParameter*& ioParameter);

    // Additional Private Declarations

  private: //## implementation
    // Data Members for Class Attributes

      CATMathAxis _Axis;

      CATMathAxis _FormerAxis;

    // Additional Implementation Declarations
};

// Class CATManifoldAxis 



#endif
