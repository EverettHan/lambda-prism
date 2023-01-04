// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathFractionXYDel:
// Class like CATMathFractionXY but which deletes the composite 
// functions in the destructor 
//
//===================================================================
// 06/06/19 NLD Renommage de _DelY en _DelQ
// 07/06/19 NLD Reception tardive de iTolObject dans le constructeur
//              (mise en conformité avec la classe mère CATMathFractionXY)
//              Reception de la configuration
//              Le constructeur par défaut devient privé
//===================================================================

#ifndef CATMathFractionXYDel_h
#define CATMathFractionXYDel_h

#include "CATMathFractionXY.h"
#include "YN000FUN.h"

#include "CATBoolean.h"
#include "CATTolerance.h"

class CATMathFunctionXY;
class CATSoftwareConfiguration;

//===================================================================
class ExportedByYN000FUN CATMathFractionXYDel : public CATMathFractionXY
{

 private:
   CATMathFractionXYDel();
 #ifdef CATMathFractionXY_NoCopyOperator
 // Attention c'est vicieux. En essayant de rendre privé l'operateur = de la classe mère CATMathFractionXY
 // je vois qu'il y a une utilisation implicite par cette classe fille, en fait sous l'implementation
 // par défaut de son propre operateur =
 // que je protège donc par la meme directive de compilation
 // Je constate alors qu'il n'y a PAS d'appel explicite, et plus d'implicite, à cet operateur de copie de la classe mère
 // NLD070619
   CATMathFractionXYDel& operator = (const CATMathFractionXYDel& iF);
 #endif

 public:
   CATMathFractionXYDel( const CATMathFunctionXY       * iP         ,
                         const CATMathFunctionXY       * iQ         ,
                         const CATTolerance            & iTolObject , //= CATGetDefaultTolerance(),
                               CATSoftwareConfiguration* iConfig    ,
                               CATBoolean                iDelQ      = TRUE);
  ~CATMathFractionXYDel();

   CATCGMNewClassArrayDeclare;

 protected:
   CATBoolean _DelQ;
};
#endif
