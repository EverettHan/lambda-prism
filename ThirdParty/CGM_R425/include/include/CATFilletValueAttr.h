//* -*-c++-*- */
//===========================================================================
// Class CATFilletValueAttr
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
// Dec. 2010  Creation.                                                ANR
//
//===========================================================================
#ifndef CATFilletValueAttr_H
#define CATFilletValueAttr_H

//Pour l'export
#include "YP0LOGRP.h"

//Classe mère
#include "CATCGMStreamAttribute.h" 

class CATCGMOutput;
class CATVertex;

#define NO_VALUE_ADDED -99


class ExportedByYP0LOGRP  CATFilletValueAttr : public CATCGMStreamAttribute
{
  CATCGMDeclareAttribute( CATFilletValueAttr, CATCGMStreamAttribute );
  //CATCGMNewClassArrayDeclare; 

public:
  CATFilletValueAttr(); // Ne pas utiliser
  CATFilletValueAttr(double iValue, short iPrecisionValue=2);
  ~CATFilletValueAttr();

  void SetProfiledSurf(CATBoolean IsProfiledSurf = FALSE) ;

  void ModifyValue(double iValue, short iPrecisionValue=2);
  double GetValue(short &oPrecisionValue);

  // Associe une couleur d'affichage: Les parametres sont compris entre 0 et 255 inclus.
  void PutColor(short iR, short iG,short iB);

  void Dump(  CATCGMOutput  &  os  );

  //----------------------------------------------------------------
  // Stream / Unstream
  //----------------------------------------------------------------
  void Stream(CATCGMStream & ioStream) const;
  void UnStream(CATCGMStream& ioStr );

  // La couleur
  class Color
  {
  public:
    Color(short iR, short iG, short iB) { _R=iR; _G=iG; _B=iB; };
    ~Color() {};  
    int _R,_G,_B;
  };

  // Methode pour CAT3DNCGMDebug.cpp.
  inline Color * GetColor() const;

private: 

  double _Value;

  // iPrecisionValue : Nombre de chiffre derriere la virgule
  // Mettre 0 pour afficher les entiers.
  // Par default mis a -99 pas de valeur.
  short  _PrecisionValue;

  Color * _Color; 

};

//---------------------------------------------------------------------------
// GetColor 
//
//===========================================================================
inline CATFilletValueAttr::Color * CATFilletValueAttr::GetColor() const 
{ 
  return _Color; 
}

#endif
