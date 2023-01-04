//========================================================================================
// Copyright Dassault Systemes Provence 2022, All Rights Reserved
//========================================================================================
//
// CATSmoBevelUserProfile.h
//
//========================================================================================
//
// Usage notes :  Bevel Classe permettant de definir un profil 
//
//========================================================================================
// 18.05.2022 : MPS : Création
//========================================================================================
#ifndef CATSmoBevelUserProfileParameters_H
#define CATSmoBevelUserProfileParameters_H

//Pour l'export
#include "CATSmoOperators.h"
#include "CATMathPoint.h"
#include <vector>

//Divers
#include "CATBoolean.h"
#include "CATSobDiag.h"




class ExportedByCATSmoOperators CATSmoBevelUserProfileParameters
{
public:

    //Constructeur
    CATSmoBevelUserProfileParameters();
    CATSmoBevelUserProfileParameters(const int iIndex, const short iSharpness, const CATBoolean iEnableSmoothing);
    void GetParameters(int& oIndex, short& oSharpness, CATBoolean& oEnableSmoothing);
  
    virtual ~CATSmoBevelUserProfileParameters();


protected:




private:
    int _Index;
    short _Sharpness;
    CATBoolean _EnableSmoothing;

};
#endif  

