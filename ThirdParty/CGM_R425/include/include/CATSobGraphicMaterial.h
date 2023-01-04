//=========================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//=========================================================================
//
// CATSobGraphicMaterial.h
//
//=========================================================================
//
// Usage notes: Graphic material for obj import.
//
//=========================================================================
// May,   2010 : RAQ : Création
//=========================================================================
#ifndef CATSobGraphicMaterial_H
#define CATSobGraphicMaterial_H

//Pour l'export
#include "CATSobObjects.h"

//Divers
#include "CATUnicodeString.h"


class ExportedByCATSobObjects CATSobGraphicMaterial
{
public:

  //Constructeurs
  CATSobGraphicMaterial();

  CATSobGraphicMaterial(const CATUnicodeString& iName, const float* iAmbientColorRGB, const float* iDiffuseColorRGB,
                        const float* iSpecularColorRGB, const float iSpecularExponent);

  CATSobGraphicMaterial(const CATUnicodeString& iName, const float* iAmbientColorRGB, const float* iDiffuseColorRGB,
                        const float* iSpecularColorRGB, const int iIlluminationMode, const float iDissolveCoef,
                        const float iSpecularExponent, const float iReflectionSharpness);

  //Destructeur
  ~CATSobGraphicMaterial();

  //Nom du matériau
  inline const CATUnicodeString& GetName() const { return _NameUStr; }

  //----------------------------- Récupération des infos graphiques -----------------------------//
  //Ambient reflectivity (Ka), 0 <= (R, G, B) <= 1
  void GetAmbientColor(float& oR, float& oG, float& oB) const;

  //Diffuse reflectivity (Kd), 0 <= (R, G, B) <= 1
  void GetDiffuseColor(float& oR, float& oG, float& oB) const;
  
  //Specular reflectivity (Ks), 0 <= (R, G, B) <= 1
  void GetSpecularColor(float& oR, float& oG, float& oB) const;

  //Transmission filter (Tf), 0 <= (R, G, B) <= 1
  void GetTransmissionFilter(float& oR, float& oG, float& oB) const;
  
  //Illumination mode (illum) : see mtl specs, not used, for compatibility only.
  int GetIlluminationMode() const;
  
  //Dissolve factor (d) : amount of material thah dissolves into the background, 0 <= d <= 1.
  float GetDissolveCoef() const;
  
  //Specular exponent (Ns) : focus of the specular highlight, 0 <= Ns <= 1000.
  float GetSpecularExponent() const;
  
  //Sharpness : sharpness of the reflections from the local reflection map, 0 <= sharpness <= 1000 (default = 60).
  float GetReflectionSharpness() const;

  //Refractive index (Ni)
  float GetRefractiveIndex() const;


  //--------------------------------- Comparaison ---------------------------------//
  inline CATBoolean operator==(const CATSobGraphicMaterial& iOtherGraphicMaterial) const
  {
    return _NameUStr==iOtherGraphicMaterial._NameUStr;
  }

  inline CATBoolean operator!=(const CATSobGraphicMaterial& iOtherGraphicMaterial) const
  {
    return _NameUStr!=iOtherGraphicMaterial._NameUStr;
  }

  //--------------------------------- Set des données ---------------------------------//
  void SetName(const CATUnicodeString& iName);

  void SetAmbientColor(const float iR, const float iG, const float iB);
  void SetDiffuseColor(const float iR, const float iG, const float iB);
  void SetSpecularColor(const float iR, const float iG, const float iB);
  void SetTransmissionFilter(const float iR, const float iG, const float iB);
  void SetIlluminationMode(const int iIlluminationMode);
  void SetDissolveCoef(const float iDissolveCoef);
  void SetSpecularExponent(const float iSpecularExponent);
  void SetReflectionSharpness(const float iReflectionSharpness);
  void SetRefractiveIndex(const float iRefractiveIndex);


protected:



private:

  //Initialisation
  void Initialize();


  //---------- Data:
  float _AmbientColor[3], _DiffuseColor[3], _SpecularColor[3], _TransmissionFilter[3];    //Ka, Kd, Ks, Tf
  float _SpecularExponent, _RefractiveIndex;  //Ns

  int _IlluminationMode;
  float _DissolveCoef, _ReflectionSharpness;
  
  CATUnicodeString _NameUStr;
};


//Déclaration de certains matériaux courants
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Amber;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Amber_trans;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Aqua;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Aqua_filter;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Archwhite;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Archwhite2;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Bflesh;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Black;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Blondhair;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Blue_pure;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Bluegrey;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Bluetint;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Blugrn;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Blutan;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Bluteal;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Bone;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Bone1;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Bone2;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Brass;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Brnhair;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Bronze;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Brown;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Brownlips;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Brownskn;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Brzskin;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Chappie;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Charcoal;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Deepgreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Default;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkblue;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkblue_pure;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkbrown;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkdkgrey;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkgreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkgrey;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkorange;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkpurple;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkred;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Dkteal;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Emerald;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fgreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flaqua;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flblack;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flblonde;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flblue_pure;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flbrown;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fldkblue_pure;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fldkdkgrey;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fldkgreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fldkgreen2;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fldkgrey;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fldkolivegreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fldkpurple;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fldkred;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flesh;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fleshtransparent;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flgrey;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fllime;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flltbrown;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flltgrey;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flltolivegreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flmintgreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flmustard;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Florange;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flpinegreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flpurple;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flred;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Fltan;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flwhite;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flwhite1;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Flyellow;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Glass;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Glassblutint;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Glasstransparent;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Gold;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Green;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Greenskn;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Grey;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Hair;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Iris;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Jetflame;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Lavendar;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Lcdgreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Lighttan;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Lighttan2;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Lighttan3;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Lighttannew;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Lightyellow;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Lime;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Lips;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Ltbrown;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Ltgrey;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Meh;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Metal;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Mintgrn;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Muscle;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Navy_blue;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Offwhite_cool;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Offwhite_warm;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Olivegreen;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Orange;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Pale_green;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Pale_pink;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Pale_yellow;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Peach;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Periwinkle;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Pink;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Pinktan;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Plasma;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Purple;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Red;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Redbrick;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Redbrown;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Redorange;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Redwood;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Rubber;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Ruby;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Sand_stone;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Sapphire;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Shadow;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Ship2;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Silver;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Skin;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Sky_blue;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Smoked_glass;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Tan;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Taupe;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Teeth;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Violet;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_White;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Yellow;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Yellow_green;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Yellowbrt;
extern ExportedByCATSobObjects const CATSobGraphicMaterial CATSobGraphicMaterial_Yelloworng;


#endif


