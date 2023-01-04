/* -*-c++-*- */
#ifndef ListVOfCATCellManifoldGroupInLiveBodies_h
#define ListVOfCATCellManifoldGroupInLiveBodies_h

#include "CATCellManifoldGroupInLiveBody.h"
#include "PersistentCell.h"

#include "CATLISTV_Clean.h"
#define CATLISTV_Append
#define CATLISTV_AppendList
#define CATLISTV_RemovePosition
#include "CATLISTV_Declare.h"

CATLISTV_DECLARE (CATCellManifoldGroupInLiveBody)
typedef CATLISTV(CATCellManifoldGroupInLiveBody) ListVOfCATCellManifoldGroupInLiveBodies;

#endif
