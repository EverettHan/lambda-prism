//============================================================================================
// Copyright Dassault Systemes Provence 2018, All Rights Reserved
//============================================================================================
//
// CATSobOneRingUtilities.h
//
//============================================================================================
//
// Usage notes : Data structure to retreive ring of subdivision points from faces, edges and vertices
//
//============================================================================================
// 15.01.2018 : RAQ : Creation
//============================================================================================
#ifndef CATSobOneRingUtilities_H
#define CATSobOneRingUtilities_H


class CATSobOneRingData
{
public:

  //Constructeurs
  CATSobOneRingData(const bool iReleaseArraysAtDestructor = true) :
    m_pBetaCoords(0),
    m_pGammaCoords(0),
    m_nbBetaVertices(0),
    m_nbGammaVertices(0),
    m_arraysAllocatedByUser(false),
    m_mustReleaseArraysAtDestructor(iReleaseArraysAtDestructor)
  {
  }

  CATSobOneRingData(double* ipBetaCoords, double* ipGammaCoords) :
    m_pBetaCoords(ipBetaCoords),
    m_pGammaCoords(ipGammaCoords),
    m_nbBetaVertices(0),
    m_nbGammaVertices(0),
    m_arraysAllocatedByUser((ipBetaCoords || ipGammaCoords) ? true : false),
    m_mustReleaseArraysAtDestructor(false)
  {
  }

  //Destructeur
  ~CATSobOneRingData()
  {
    if(m_mustReleaseArraysAtDestructor)
    {
      if(m_pBetaCoords) delete[] m_pBetaCoords; m_pBetaCoords=0;
      if(m_pGammaCoords) delete[] m_pGammaCoords; m_pGammaCoords=0;
    }
    else
    {
      m_pBetaCoords=0;
      m_pGammaCoords=0;
    }
  }

  //---- Data :
  double *m_pBetaCoords, *m_pGammaCoords;
  int m_nbBetaVertices, m_nbGammaVertices;
  bool m_arraysAllocatedByUser, m_mustReleaseArraysAtDestructor;
};


#endif  //CATSobOneRingUtilities_H

