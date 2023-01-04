//==========================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//==========================================================================
//
// CATSobHighResTimer.h
//
//==========================================================================
//
// Usage notes: High resolution timer.
//
//==========================================================================
// 30.01.2018 : RAQ : Ajout scoped timer
// February,   2009 : RAQ : Création
//==========================================================================
#ifndef CATSobHighResTimer_H
#define CATSobHighResTimer_H

//Pour l'export
#include "CATSobObjects.h"

//Divers
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATSobOStream.h"

//STL
#ifndef _AIX_SOURCE
  #include <string>
#endif  //!_AIX_SOURCE


class ExportedByCATSobObjects CATSobHighResTimer
{
public:

  //Constructeur et activation du compteur
  CATSobHighResTimer();

  //Destructeur
  ~CATSobHighResTimer();

  //Réinitialisation du compteur
  void Start();

  //Obtention du temps en millisecondes depuis la dernière initialisation
  double GetTime(const CATBoolean iReinitialize = FALSE);

private:

  CATSobHighResTimer(const CATSobHighResTimer&);
  CATSobHighResTimer& operator=(const CATSobHighResTimer);

  //-------- Data:
  double _HighResolutionFrequency;
  CATULONG64 _PerformanceCounterAtStart;
};


class CATSobScopedTimer
{
public:

  CATSobScopedTimer(const char* ipName = 0)
  {
#ifndef _AIX_SOURCE
    m_name=std::string(ipName ? ipName : "no_name");
#endif  //!_AIX_SOURCE
    m_timer.Start();
  }

  ~CATSobScopedTimer()
  {
#ifdef _AIX_SOURCE
    sobout << "[ SCOPED TIMER " << "No_name_under_AIX" << " ] elapsed time = " << m_timer.GetTime() << " ms\n";
#else
    sobout << "[ SCOPED TIMER " << m_name.c_str() << " ] elapsed time = " << m_timer.GetTime() << " ms\n";
#endif  //_AIX_SOURCE
  }

protected:

  //---- Data :
  CATSobHighResTimer m_timer;
#ifndef _AIX_SOURCE
  std::string m_name;
#endif  //_AIX_SOURCE
};


#endif

