#ifndef CATMathVectorialFunctionXY_H  
#define CATMathVectorialFunctionXY_H  

//=============================================================================
//           Ajout de fonctions vectorielles
//   
//=============================================================================
// 2006, creation EZY
// 07/2008, kub : ajout de GetUnits pour connaitre des unités des valeurs de sortie
//=================================================================================


#include "YN000FUN.h"

#include "CATMathDef.h"

#include "CATCGMVirtual.h"


class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathVectorialFunctionXY  : public CATCGMVirtual
{ 
public:  
   //CATMathVectorialFunctionXY * _me;
   //----------------------------------------------------------  
   //  Constructor (iN is the number of functions of the system)
   //----------------------------------------------------------    
   CATMathVectorialFunctionXY (CATSoftwareConfiguration * iConfig,const CATLONG32  iN);   
   CATMathVectorialFunctionXY (const CATLONG32  iN);
   CATMathVectorialFunctionXY ();   
   //------------ 
   //  Destructor  
   //------------  
   virtual ~CATMathVectorialFunctionXY ();
   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------
   virtual CATBoolean IsOption(const CATMathOption iOption) const;

   //  Get the number of functions of the system (N) 
   CATLONG32 GetNumberOfFunctions () const; 

   // get the units of the evaluation
   virtual void GetUnits(int * oUnit) const = 0;

   // void SetDim (const CATLONG32 NbVariable);

   // Evaluators: iX is a point in R.
   //  . oFX = F(iX) is the image of iX by F. oFX is in RN and is already allocated. 
   //  . oDFX is the derivative of F at iX and is in RN and is already allocated. 
   //  . oD2FX is the second derivative of F at iX and is in RN and is already allocated. 
   //  . oTX is the normed tangent at iX and is in RN and is already allocated.
   virtual void Eval (const double  iX, const double iY, double *oFXY) const=0;


private:

   CATLONG32 _N;

   CATSoftwareConfiguration * _Config;

   //
   //
};  
#endif  
