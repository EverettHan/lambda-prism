#ifndef CATDMUpToDateStatusDefine_H
#define CATDMUpToDateStatusDefine_H

typedef enum 
{
  NotUpToDateByCheckValidity = -3,
  NotUpToDateByClashAnalysis = -2,
  NotUpToDate                = -1,
  Unknown                    =  0,
  UpToDate                   =  1,
  UpToDateByCarrierAnalysis  =  2
}
CATDMUpToDateStatus;

#endif
