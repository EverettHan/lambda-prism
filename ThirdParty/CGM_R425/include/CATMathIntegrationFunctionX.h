//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// Historic:
// 30/10/15 F1Z : Clean + Add the possibility to have more than one function.
// DD/MM/YY
//=============================================================================

#ifndef CATMathIntegrationFunctionX_H
#define CATMathIntegrationFunctionX_H

//=============================================================================
// Advanced Mathematics
#include "YN000FUN.h"
#include "CATMathIntegration.h"

class CATMathFunctionX;

//=============================================================================
class ExportedByYN000FUN CATMathIntegrationFunctionX : public CATMathIntegration
{

public:
   //-----------------------------------------------------------------------------
   // Class Management
   //-----------------------------------------------------------------------------
   CATMathIntegrationFunctionX(      CATSoftwareConfiguration *   iSoftwareConfiguration      ,
                               const CATMathFunctionX         *   iFunctionX                  );

   CATMathIntegrationFunctionX(      CATSoftwareConfiguration *   iSoftwareConfiguration      ,
                                     CATLONG32                    iDimension                  ,
                               const CATMathFunctionX         * * iFunctionsX                 ,
                                     CATBoolean                   iNewAllocate          = TRUE);
   virtual ~CATMathIntegrationFunctionX();

   //-----------------------------------------------------------------------------
   // Heritance of CATMathIntegration
   //-----------------------------------------------------------------------------
   void Eval(const double t, double * oFX);

protected:
   //-----------------------------------------------------------------------------
   // Protected methods
   //-----------------------------------------------------------------------------
   void SetFunctionsX(      CATLONG32            iDimension         ,
                      const CATMathFunctionX * * iFunctionsX        ,
                            CATBoolean           iNewAllocate = TRUE);

   void CleanFunctionsX();


private:
   //-----------------------------------------------------------------------------
   // Private constructor
   //-----------------------------------------------------------------------------
   CATMathIntegrationFunctionX();
   CATMathIntegrationFunctionX(const CATMathIntegrationFunctionX &);
   void operator = (const CATMathIntegrationFunctionX &);

   //-----------------------------------------------------------------------------
   // Private attributs
   //-----------------------------------------------------------------------------
   const CATMathFunctionX *   _F ;
   const CATMathFunctionX * * _Fs;
         CATBoolean           _FsAllocated;
};

#endif
