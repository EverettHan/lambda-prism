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
#ifndef CATSmoBevelUserProfile_H
#define CATSmoBevelUserProfile_H

//Pour l'export
#include "CATSmoOperators.h"
#include "CATMathPoint.h"
#include <vector>

//Divers
#include "CATBoolean.h"
#include "CATSobDiag.h"


class CATSobMesh;


class ExportedByCATSmoOperators CATSmoBevelUserProfile
{
public:

  //Constructeur
    CATSmoBevelUserProfile();
    CATSmoBevelUserProfile(const std::vector <CATMathPoint>& iProfilePoints);
    const std::vector <CATMathPoint>& GetProfilePoints() const;
    virtual ~CATSmoBevelUserProfile();
   

protected:

  //Destructeur
  

  

private:
    std::vector <CATMathPoint> _ProfilePoints; 
 
};
#endif
