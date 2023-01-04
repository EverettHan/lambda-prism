/* -*-c++-*- */
#ifndef ListVOfCATGMLiveContextualFeatureFollowers_h
#define ListVOfCATGMLiveContextualFeatureFollowers_h

#include "CATGMLiveContextualFeatureFollower.h"
#include "PersistentCell.h"

#include "CATLISTV_Clean.h"
#define CATLISTV_Append
#define CATLISTV_AppendList

#include "CATLISTV_Declare.h"

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPersistentCell

CATLISTV_DECLARE (CATGMLiveContextualFeatureFollower)
typedef CATLISTV(CATGMLiveContextualFeatureFollower) ListVOfCATGMLiveContextualFeatureFollowers;

#endif


