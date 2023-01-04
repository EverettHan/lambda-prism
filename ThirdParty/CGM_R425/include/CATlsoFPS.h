/* -*-C++-*- */

#ifndef CATlsoFPS_H
#define CATlsoFPS_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier

DESCRIPTION  : 

=============================================================================
                The options
                -----------



=============================================================================
                PPT documentation
                -----------------


=============================================================================
*/
#include "PersistentCell.h"
#include "IUnknown.h"
#include "CATBoolean.h"

class CATCGMOutput;

//-----------------------------------------------------------------------------
// Methods for cpp file 
//-----------------------------------------------------------------------------
// @nocgmitf
ExportedByPersistentCell void LSOFPSIncr(CATBoolean iOneFPS=FALSE);
ExportedByPersistentCell void LSOFPSClose(CATBoolean iOneFPS=FALSE);

class CATlsoFPS
{
public:
    CATlsoFPS(CATBoolean iOneFPS=FALSE);
    virtual ~CATlsoFPS();

    void Incr();

private:
  void CreateFile();
  void CreateFileForOneFPS();
  void CloseFile();
  CATCGMOutput * GetOutput();

private:
#ifdef WIN32
  double      _Frequency;
#else
  double      _Frequency;
#endif
  int         _RunCounter;
  CATULONG32  _CurrentTime;

  CATCGMOutput * _OneFPSCGMOutput;
  CATBoolean     _OneFPS;
};

#endif
