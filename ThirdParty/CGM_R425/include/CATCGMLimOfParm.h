#ifndef CATCGMLimOfParm_H
#define CATCGMLimOfParm_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
#include "ExportedByGeometricObjects.h"
#include "CATCGMNewArray.h"
#include "CATCrvLimits.h"
#include "CATSurLimits.h"
#include "CATCGMQueryManager.h"
#include "CATMathInline.h"
#include "CATDataType.h"
 
class CATICGMObject;
class CATCurve;
class CATSurface;
class CATCrvLimits;
class CATSurLimits;
class CATCGMOutput;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATUnicodeString;
class CATCXQueryManager;
class CATMapVoidToVoid;

//---------------------------------------------------
// Pour la geometrie cliente de Curve/Surface
//---------------------------------------------------
class  ExportedByGeometricObjects CATCGMLimOfParm
{
public:
  
  CATICGMObject*const _Obj;

  //------------------------------------------------------------------------
  // Classification pour eventuel Casting/Specialisation
  //     1:Curve/CrvLimits    (Casting possible en CATCGMLimOfParmCurve)
  //     2:Surface/SurLimits  (Casting possible en CATCGMLimOfParmSurface)
  //     0:Autre              (pas de Casting)
  //------------------------------------------------------------------------
  INLINE short GetType(); 
  
  //--------------------------------------------------------------------
  // Bilan de sante
  //--------------------------------------------------------------------
  enum Checkup { Okay, Fat, Unavailable };

  CATCGMLimOfParm::Checkup  Check(CATCGMQueryManager & QM);


  //--------------------------------------------------------------------
  // Test de validite de l'interpretation de OptimalLimits
  //--------------------------------------------------------------------
  virtual CATBoolean OptimalLimits_IsAvailable();

  //--------------------------------------------------------------------
  // Detection specifique
  //--------------------------------------------------------------------
  virtual CATBoolean IsKnot_NegativeOffset(CATBoolean OriginalTrue_OptimalFalse);


  //-----------------------------------------------------------------------------
  // HYPOTHESE : OptimalLimits est valide/accessible
  // Comparaison   OptimalLimits MaxLimits
  //     -1 : Invalide (OptimalLimits deborde des MaxLimits)
  //      0 : Okay
  //     +1 : Fat (MaxLimits contient des arcs/patchs inutiles
  //-----------------------------------------------------------------------------
  virtual short     OptimalLimits_ComparedWith_MaxLimits(CATCGMQueryManager & QM);


  //-----------------------------------------------------------------------------
  // HYPOTHESE : OptimalLimits est valide/accessible
  // Comparaison   OptimalLimits CurrentLimits (pour recadrage eventuel)
  //    TRUE  : Invalide (CurrentLimits deborde des OptimalLimits)
  //    FALSE : reajustement a effectuer sur les limites courantes 
  //-----------------------------------------------------------------------------
  virtual CATBoolean CurrentLimits_Inside_OptimalLimits();


  //-------------------------------------------------------------------
  // Analyse du nombre arcs/patchs  Optimal et Actuel (MaxLimits)
  // support que l'analyse a fourni des resultats interpretables
  //-------------------------------------------------------------------
  virtual void GetWeight(int &Useful, int &Actual);
  virtual int  GetMaxLimitsWeight();



  //-----------------------------------------------------------------------------
  // Marquage initial pour indiquer que OptimialLimits n'est pas significatif
  //-----------------------------------------------------------------------------
  INLINE short IsDummyLimits() const;
  INLINE void  SetDummyLimits(const short iDummyLimits);


  //-------------------------------------------------------------------
  // Marquage de la profondeur d'analyse de l'Objet
  //-------------------------------------------------------------------
  INLINE unsigned short GetLevel() const;
  INLINE void           SetLevel(const unsigned short iLevel);

  
  //-------------------------------------------------------------------
  // Detection d'un marquage MaxLimits
  // L'objet demeure valide, on veut eviter une desextrapolation locale
  //-------------------------------------------------------------------
  INLINE short IsMaxLimits();           
  void SetMaxLimits();

  //-------------------------------------------------------------------
  // Les limites optimales ont ete obtenues 
  // avec une extension aux frontieres d'arcs
  //-------------------------------------------------------------------
 INLINE short IsExtendedToArcLimits(); // Extension aux frontieres d'Arcs ?

  //-------------------------------------------------------------------
  // Marquage d'invalidite suite a une detection d'incoherence interne
 //-------------------------------------------------------------------
 INLINE short IsDisabledAnalysis();    // Non valide pour l'analyse
 void         SetDisabledForAnalysis();  // Non valide pour l'analyse
 
 //--------------------------------------------------------------------------------
 // Detection d'un usage degenere de l'element
 // Peut-etre une action plus radicale que le desextrapolator serait le bienvenu
 //--------------------------------------------------------------------------------
 INLINE short IsUsefulDegenerated();           
 void SetUsefulDegenerated();
 
  //-------------------------------------------------------------------
  // Cycle de Vie
  //-------------------------------------------------------------------
  CATCGMLimOfParm(CATICGMObject *Obj);
  virtual ~CATCGMLimOfParm();
  CATCGMNewClassArrayDeclare;  
  virtual void  Dump( CATCGMOutput& os );
  
  //---------------------------------------------------
  // Internal
  //---------------------------------------------------
  CATCGMLimOfParm(CATICGMObject *Obj, CATCXQueryManager *iCtrl);

  static void       CleanSessionAtExit();
  static CATULONG32 catcgmlimtag(CATULONG32  tag) ;
  static CATBoolean CATCGMLimTag(CATICGMObject *iObj);

protected :

  CATCGMLimOfParm(const CATCrvLimits &iLimits, CATCurve *iCurve );
  CATCGMLimOfParm(const CATSurLimits &iLimits, CATSurface *iSurface );

  struct CATCGMLimOfParmBits
  {
    unsigned int	Level                 : 16;
    unsigned int	ForceMaxLimits        :  1;
    unsigned int	ExtendedToArcLimits   :  1;
    unsigned int	DisabledAnalysis      :  1;
    unsigned int	DummyLimits           :  1;
    unsigned int	UsefulDegenerated     :  1;
    unsigned int	Type                  :  2;
    unsigned int	RFU                   :  9;
  } _Bits;

  static CATBoolean  _Initialised;
  static CATMapVoidToVoid * _CATCGMLimTag;

  static void         Initialise(); 

  void CATCGMLimTag_ChangeLimits(CATICGMUnknown *iFrom, const CATCrvLimits & iNewLimits, const CATCrvLimits & iExtendLimits);
  void CATCGMLimTag_ChangeLimits(CATICGMUnknown *iFrom, const CATSurLimits & iNewLimits, const CATSurLimits & iExtendLimits);

};


//---------------------------------------------------
// definition des methodes inlines
//---------------------------------------------------
INLINE short CATCGMLimOfParm::GetType()
{
  return  (short)_Bits.Type;
}

INLINE short CATCGMLimOfParm::IsExtendedToArcLimits()
{
  return  _Bits.ExtendedToArcLimits  ? 1 : 0;
}

INLINE short CATCGMLimOfParm::IsMaxLimits()
{
  return  _Bits.ForceMaxLimits ? 1 : 0;
}


INLINE short CATCGMLimOfParm::IsDisabledAnalysis()
{
  return  _Bits.DisabledAnalysis ? 1 : 0;
}

INLINE unsigned short CATCGMLimOfParm::GetLevel() const
{
  return (unsigned short)_Bits.Level;
}

INLINE void  CATCGMLimOfParm::SetLevel(const unsigned short iLevel)
{
  _Bits.Level = iLevel;
}

INLINE  short CATCGMLimOfParm::IsDummyLimits() const
{
  return _Bits.DummyLimits ? 1 : 0;
}

INLINE void  CATCGMLimOfParm::SetDummyLimits(const short iDummyLimits)
{
  _Bits.DummyLimits = iDummyLimits ? 1 : 0;
}


INLINE short CATCGMLimOfParm::IsUsefulDegenerated()
{
  return _Bits.UsefulDegenerated ? 1 : 0;
}


//---------------------------------------------------
// Pour le parametrage curviligne
//---------------------------------------------------
class  ExportedByGeometricObjects CATCGMLimOfParmCurve : public CATCGMLimOfParm
{
public:

  //--------------------------------------------------------------------
  // Test de validite de l'interpretation de OptimalLimits
  //--------------------------------------------------------------------
  virtual CATBoolean OptimalLimits_IsAvailable();

  //--------------------------------------------------------------------
  // Detection specifique
  //--------------------------------------------------------------------
  virtual CATBoolean IsKnot_NegativeOffset(CATBoolean OriginalTrue_OptimalFalse);

  //-----------------------------------------------------------------------------
  // HYPOTHESE : OptimalLimits est valide/accessible
  // Comparaison   OptimalLimits MaxLimits
  //     -1 : Invalide (OptimalLimits deborde des MaxLimits)
  //      0 : Okay
  //     +1 : Fat (MaxLimits contient des arcs/patchs inutiles
  //-----------------------------------------------------------------------------
  virtual short     OptimalLimits_ComparedWith_MaxLimits(CATCGMQueryManager & QM);
  

  //-----------------------------------------------------------------------------
  // HYPOTHESE : OptimalLimits est valide/accessible
  // Comparaison   OptimalLimits CurrentLimits (pour recadrage eventuel)
  //    TRUE  : Invalide (CurrentLimits deborde des OptimalLimits)
  //    FALSE : reajustement a effectuer sur les limites courantes 
  //-----------------------------------------------------------------------------
  virtual CATBoolean CurrentLimits_Inside_OptimalLimits();


  //-------------------------------------------------------------------
  // Analyse du nombre arcs/patchs  Optimal et Actuel (MaxLimits)
  // support que l'analyse a fourni des resultats interpretables
  //-------------------------------------------------------------------
  virtual void GetWeight(int &Useful, int &Actual);
  virtual int  GetMaxLimitsWeight();

  //--------------------------------------------------------------------
  // Analyse ..
  //--------------------------------------------------------------------
  INLINE CATCurve           * GetCurve()  const;
  
  INLINE const CATCrvLimits & GetLimits() const;
  INLINE void                 GetLimits(CATCrvLimits &ioLimits) const;
  
  
  //--------------------------------------------------------------------
  // Pour recadrage sur les arcs
  //--------------------------------------------------------------------
  static short ExtendToArcLimits(CATCurve *iCurve, CATCrvLimits &ioLimits);
  
  //--------------------------------------------------------------------
  // Interne pour enrichissement au propagate
  //--------------------------------------------------------------------
  void ChangeLimits(CATICGMUnknown *iFrom, const CATCrvLimits & iNewLimits, const short iExtendedToArcLimits);
  
  //--------------------------------------------------------------------
  // Dumps
  //--------------------------------------------------------------------
  virtual void Dump( CATCGMOutput& os );
  
  static void Dump( const CATCrvLimits &iLimits, CATCGMOutput& os , const short iShowLowHigh=3);
  static void Dump( const CATCrvLimits &iLimits, ostream &os , const short iShowLowHigh=3);
  static void Dump( const CATCrvLimits &iLimits, CATUnicodeString &os, const short iShowLowHigh=3 );

  //-------------------------------------------------------------------
  // Cycle de Vie
  //-------------------------------------------------------------------
  CATCGMLimOfParmCurve(CATCurve *iCurve, const CATCrvLimits &iLimits, const short iExtendedToArcLimits=0);
  virtual ~CATCGMLimOfParmCurve();
  CATCGMNewClassArrayDeclare;  



protected :
  CATCrvLimits   _Limits;

};

INLINE CATCurve *CATCGMLimOfParmCurve::GetCurve() const
{
  return (CATCurve *)((void *)_Obj);
}

INLINE const CATCrvLimits & CATCGMLimOfParmCurve::GetLimits() const
{
  return _Limits;
}

INLINE void CATCGMLimOfParmCurve::GetLimits(CATCrvLimits &ioLimits) const
{
  ioLimits = _Limits;
}




//---------------------------------------------------
// Pour le parametrage surfacique
//---------------------------------------------------
class  ExportedByGeometricObjects CATCGMLimOfParmSurface : public CATCGMLimOfParm
{
public:

  //--------------------------------------------------------------------
  // Test de validite de l'interpretation de OptimalLimits
  //--------------------------------------------------------------------
  virtual CATBoolean OptimalLimits_IsAvailable();

  //--------------------------------------------------------------------
  // Detection specifique
  //--------------------------------------------------------------------
  virtual CATBoolean IsKnot_NegativeOffset(CATBoolean OriginalTrue_OptimalFalse);

  //-----------------------------------------------------------------------------
  // HYPOTHESE : OptimalLimits est valide/accessible
  // Comparaison   OptimalLimits MaxLimits
  //     -1 : Invalide (OptimalLimits deborde des MaxLimits)
  //      0 : Okay
  //     +1 : Fat (MaxLimits contient des arcs/patchs inutiles
  //-----------------------------------------------------------------------------
  virtual short     OptimalLimits_ComparedWith_MaxLimits(CATCGMQueryManager & QM);

  //-----------------------------------------------------------------------------
  // 
  //-----------------------------------------------------------------------------
  virtual CATBoolean UselessPatches_ComparedWith_MaxLimitsPatches(CATListOfInt& ioListOfUIdx, CATListOfInt& ioListOfVIdx);

  //-----------------------------------------------------------------------------
  // HYPOTHESE : OptimalLimits est valide/accessible
  // Comparaison   OptimalLimits CurrentLimits (pour recadrage eventuel)
  //    TRUE  : Invalide (CurrentLimits deborde des OptimalLimits)
  //    FALSE : reajustement a effectuer sur les limites courantes 
  //-----------------------------------------------------------------------------
  virtual CATBoolean CurrentLimits_Inside_OptimalLimits();


  //-------------------------------------------------------------------
  // Analyse du nombre arcs/patchs  Optimal et Actuel (MaxLimits)
  // support que l'analyse a fourni des resultats interpretables
  //-------------------------------------------------------------------
  virtual void GetWeight(int &Useful, int &Actual);
  virtual int  GetMaxLimitsWeight();

  //--------------------------------------------------------------------
  // Analyse ..
  //--------------------------------------------------------------------
  INLINE CATSurface         * GetSurface()  const;
  INLINE const CATSurLimits & GetLimits() const;
  INLINE void                 GetLimits(CATSurLimits &ioLimits) const;


  void ChangeLimits(CATICGMUnknown *iFrom, const CATSurLimits & iNewLimits, const short iExtendedToArcLimits);

  // Pour recadrage sur les arcs
  static short ExtendToArcLimits(CATSurface *iSurface, CATSurLimits &ioLimits);


  //--------------------------------------------------------------------
  // Dumps
  //--------------------------------------------------------------------
  virtual void Dump( CATCGMOutput& os );

  static void Dump( const CATSurLimits &iLimits, CATCGMOutput& os, const short iShowLowHigh=3 );
  static void Dump( const CATSurLimits &iLimits, ostream& os, const short iShowLowHigh=3 );
  static void Dump( const CATSurLimits &iLimits, CATUnicodeString& os, const short iShowLowHigh=3 );

  //-------------------------------------------------------------------
  // Cycle de Vie
  //-------------------------------------------------------------------
  CATCGMLimOfParmSurface(CATSurface *iSurface, const CATSurLimits &iLimits, const short iExtendedToArcLimits=0);
  virtual ~CATCGMLimOfParmSurface();
  CATCGMNewClassArrayDeclare;  


protected :
  CATSurLimits   _Limits;
  
};

INLINE CATSurface *CATCGMLimOfParmSurface::GetSurface() const
{
  return (CATSurface *)((void *)_Obj);
}

INLINE const CATSurLimits & CATCGMLimOfParmSurface::GetLimits() const
{
  return _Limits;
}

INLINE void CATCGMLimOfParmSurface::GetLimits(CATSurLimits &ioLimits) const
{
  ioLimits = _Limits;
}




#endif
