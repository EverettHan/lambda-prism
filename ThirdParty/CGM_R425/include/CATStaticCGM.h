// COPYRIGHT DASSAULT SYSTEMES 2010
//==========================================================================
//
// CATStaticCGM: generic class for CGM static objects
//
//==========================================================================
//
// Usage notes:
//
// *** Dedicated to static data grouping and initialization ordering control ***
//==========================================================================
// 11/06/07 NLD Creation
//              Dans un premier temps permet de definir dans des classes filles
//              des regroupements de donnees statiques, avec adhesion,
//              et de reperer les ordres de chargement et initialisations,
//              avant eventuellement de fournir des mecanismes d'ordonnancement
//              des initialisations
// 30/05/12 NLD Ajout CATStaticCGMWrite() (breakpoint de modification)
//              et classe CATStaticCGMInt (entier avec controle de modification)
//==========================================================================
//
#ifndef CATStaticCGM_H
#define CATStaticCGM_H
//
#include <CATMathematics.h>
#include <CATMathInline.h>

//==========================================================================
class ExportedByCATMathematics CATStaticCGM
  {
   public :
   CATStaticCGM();
  ~CATStaticCGM();

   public :
   int _Number; // Occurence number between objects of this class
  };

//==========================================================================
// Static data modification breakpoint
//==========================================================================
extern "C" ExportedByCATMathematics void CATStaticCGMWrite(); // Write breakpoint

//==========================================================================
// Call containing an integer value with controlled access
// (modification only allowed
//==========================================================================
#define CATStaticCGMIntDefaultValue -654321
class ExportedByCATMathematics CATStaticCGMInt
  {
   private :
   int _Value;

   public :
   //---------------------------------------------------
   CATStaticCGMInt()
     {
      _Value = CATStaticCGMIntDefaultValue;
     }

   //---------------------------------------------------
   ~CATStaticCGMInt()
     {
     }
   //---------------------------------------------------
   INLINE int& GetAddress()
     {
      return _Value;
     }

   //--------------------------------------------------- Define initial value (to be called only once)
   void Init(int iValue)
     {
      // L'initialisation n'est pas controlée CATStaticCGMWrite();
      // N.B je controle que personne ne triche en initialisant deux fois
      if (_Value == CATStaticCGMIntDefaultValue)
         CATStaticCGMWrite();
      _Value = iValue;
     }

   //--------------------------------------------------- Set value
   void Set(int iValue)
     {
      CATStaticCGMWrite();
      _Value = iValue;
     }

   //--------------------------------------------------- Get value
   INLINE int Get()
     {
      return _Value;
     }

   //--------------------------------------------------- Increase value by 1
   void Incr()
     {
      CATStaticCGMWrite();
      _Value++;
     }
   //--------------------------------------------------- Decrease value by 1
   void Decr()
     {
      CATStaticCGMWrite();
      _Value--;
     }

  };

#endif

