// COPYRIGHT DASSAULT SYSTEMES 2004
//================================================================================
// Creation ICE  28/02/2006
//
// Operateur de split d'un wire helice
// cf CATCreateSplitHelixWire.
//================================================================================

#ifndef __CATTopSplitHelixWire_h__
#define __CATTopSplitHelixWire_h__

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

class CATGeoFactory;
class CATTopData;

class CATBody;

class CATMathConstant;

class CATTopSplitHelixWire: public CATTopOperator
{
   protected:
      
      //============================
      // Constucteur et destructeurs
      //============================

      CATTopSplitHelixWire(CATGeoFactory * iFactory, CATTopData * iTopData);
       
     public:

      virtual ~CATTopSplitHelixWire();

      //========================================================
      // Methodes de parametrisation de l'operateur (INTERFACES)
      //========================================================
      virtual void SetEndAngle(CATAngle iEndAngle) = 0;
      virtual void SetHelixLaw(CATBoolean iLawMode) = 0;
  
      //========================================================
      // Methodes d'execution et de resultats (INTERFACES)
      //========================================================
 
      virtual int         Run() = 0;
      virtual int         RunOperator() = 0;

      virtual CATBody *   GetResult() = 0;
};


#endif

