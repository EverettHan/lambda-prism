//===========================================================================
// Copyright Dassault Systemes Provence 2015, All Rights Reserved
//===========================================================================
//
// CATSobRawData.h
//
//===========================================================================
//
// Usage notes: Raw représentation of subdivision cells
//
//===========================================================================
// 27.07.2015 : RAQ : Creation
//===========================================================================
#ifndef CATSobRawData_H
#define CATSobRawData_H

//STL
#ifndef _AIX_SOURCE
#include <vector>
#endif  //!_AIX_SOURCE


namespace CATSobRawData
{
  class Vertex
  {
  public:

    //Constructeur
    Vertex() { m_Coords[0]=m_Coords[1]=m_Coords[2]=0.0; m_Tag=0; }

    //Destructeur
    ~Vertex() {}

    //----- Data :
    double m_Coords[3];
    int m_Tag;
  };


  class Face
  {
  public:

    //Constructeur
    Face() { m_Degree=0; m_Tag=0; }

    //Destructeur
    ~Face() {}


    //---- Data :
    int m_Tag, m_Degree;
#ifndef _AIX_SOURCE
    std::vector<int> m_VertexIndices; //vertex indices start at 1
#endif  //!_AIX_SOURCE
  };
};


#endif  //CATSobRawData_H


