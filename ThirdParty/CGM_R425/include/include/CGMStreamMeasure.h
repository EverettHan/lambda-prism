#ifndef CGMStreamMeasure_H
#define CGMStreamMeasure_H

#include "CATCGATimer.h"
#include "ExportedByCATCGMFusion.h"

struct CGMStreamMeasureData
{
  double _StandardSaveCPUTime;
  double _StandardSaveElapsedTime;

  double _IncrementalSaveCPUTime;
  double _IncrementalSaveElapsedTime;

  double _StandardOpenCPUTime;
  double _StandardOpenElapsedTime;

  double _IncrementalOpenCPUTime;
  double _IncrementalOpenElapsedTime;

  size_t _StandardStreamSize;
  size_t _IncrementalStreamSize;
};

enum MeasureType {StandardSave, StandardOpen, IncrementalSave, IncrementalOpen};

class ExportedByCATCGMFusion CGMStreamMeasure
{
public :

  CGMStreamMeasure();
  ~CGMStreamMeasure();

  // Il faut appeler Inactive a la fin pour nettoyer les donnees.
  static void Activate();
  static void Inactive();
  static CATBoolean IsActivate();

  static void Reset();
  static void Start();
  static void End();

  // Il faut UpdateMeasureData pour recuperer le resultat de Timer
  static void UpdateMeasureData(MeasureType iMeasureType);
  static CGMStreamMeasureData* GetGlobalMeasure();

  static void SetStreamSize(size_t iStreamSize, MeasureType iMeasureType);

  static double _IncrementalSaveElapsedTime_Total;
  static double _StandardSaveElapsedTime_Total;

private:

  static CATCGATimer* _Timer;
  static CGMStreamMeasureData*  _MeasureData;
  

  static int          _IsInitialized;
  static CATBoolean   _IsActivated;
};


#endif
