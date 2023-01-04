//=========================================================================================
// Copyright Dassault Systemes Provence 2018, All Rights Reserved
//=========================================================================================
//
// CATSmoEdgeData.h
//
//=========================================================================================
//
// Usage notes : Operator to retreive all subdivision points from an edge at a given level
//
//=========================================================================================
// 16.01.2018 : RAQ : Creation
//=========================================================================================
#ifndef CATSmoEdgeData_H
#define CATSmoEdgeData_H

//Pour l'export
#include "CATSmoOperators.h"

//Subdivision
#include "CATSobDiag.h"

//STL
#include <vector>

class CATSobFace;
class CATSobEdge;
class CATMathPoint;


class CATSmoEdgeData
{
public:

  //Constructor
  ExportedByCATSmoOperators
    CATSmoEdgeData(CATSobEdge& iSobEdge);

  //Destructor
  ExportedByCATSmoOperators
    ~CATSmoEdgeData();

  //Extract all subdivision points at a given level.
  //Points are ordered regarding the edge's orientation
  ExportedByCATSmoOperators
    CATSobDiag GetAllPoints(const unsigned int iLevel, std::vector<CATMathPoint>& oPoints);

  //Extract all neighbour points at a given level
  //Points are ordered regarding the edge's orientation
  ExportedByCATSmoOperators
    CATSobDiag GetAllNeighbourPoints(CATSobFace* ipFace, const unsigned int iLevel, std::vector<CATMathPoint>& oPoints);

private:
  
  //---- Data :
  CATSobEdge& m_sobEdge;
};

#endif  //CATSmoEdgeData_H


