/* -*-c++-*- */
#ifndef CATCGMEquation_H
#define CATCGMEquation_H

//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//-----------------------------------------------------------------------------
// Pour Activation d'une gestion equilibree des Equations sur Curve/Pcurve/Surface/Law
// Les Anomalies Severes qui ne sont acceptees dans le mode minimal sont :
//
//  1) Oubli d'ouverture de Lock/OpenEquation
//      Curve    :  GetEquation/GetGlobalEquation          sans Lock ou OpenEquation
//      PCurve   :  GetEquationUV/GetGlobalEquationUV      sans Lock ou OpenEquation
//      Law      :  GetGlobalEquation                      sans Lock ou OpenEquation
//      Surface  :  GetEquation/GetGlobalEquation          sans Lock ou OpenEquation
//
//  2) Oubli de fermeture par Unlock
//     ou non correlation Lock/Unlock --> (par exemple trop de Unlock...)
// 
// On acceptera toutefois les nettoyages d'equations si l'objet est en cours d'effacement
//
//-----------------------------------------------------------------------------

#define CATCGMEquationAddRefRelease 1

#endif
