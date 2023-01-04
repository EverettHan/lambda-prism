#ifndef CATBissectorInterpol_h
#define CATBissectorInterpol_h

// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Class CATBissectorInterpol
//
//=============================================================================
//   /04/08 PKC Versionning Classe Mere
// 10/07/18 NLD Suppression ancien constructeur sans configuration
//              XScale: L'argument iTolObject du constructeur n'admet plus de valeur par defaut
//              et passe en position 2
//=============================================================================

#include "CATMathExplicitInterpol.h"
#include "YP00IMPL.h"

class CATSoftwareConfiguration;

class ExportedByYP00IMPL CATBissectorInterpol : public CATMathExplicitInterpol
{
public:

  /* NLD100718
  CATBissectorInterpol(const CATLONG32 iN,
                       CATMathVectorialFunctionX * iSampler,
                       const double iTolerance, 
                       const CATTolerance & iTolObject = CATGetDefaultTolerance());
  */
         CATBissectorInterpol(      CATSoftwareConfiguration  *  iConfig    ,
                              const CATTolerance               & iTolObject , // NLD100718 passe de derniere en deuxieme position = CATGetDefaultTolerance()
                              const CATLONG32                    iN         ,
                                    CATMathVectorialFunctionX *  iSampler   ,
                              const double                       iTolerance );

  virtual ~CATBissectorInterpol();

  double GetSquare3DDistance (const double                    *  iP0          ,
                              const double                    *  iP1          ,
                                    double                    *& ioPosition0  ,
                                    double                    *& ioPosition1  ,
                                    CATBoolean                   iRequestData0,
                                    CATBoolean                   iRequestData1);

private:

  CATBissectorInterpol();
  CATBissectorInterpol(const CATBissectorInterpol & iToCopy);
  void operator     = (const CATBissectorInterpol & iToCopy);

};


#endif

