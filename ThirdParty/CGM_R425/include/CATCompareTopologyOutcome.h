#ifndef CATCompareTopologyOutcome_h
#define CATCompareTopologyOutcome_h

#include "ExportedByCATTopologicalObjects.h"

typedef enum {Outcome_Unset,             //Comparison not done yet
              Outcome_Unknown,           //It's not possible to say if topologies are identical or not
              Outcome_Same,              //Topologies are identical
              Outcome_Different,         //Topologies are not identical
              Outcome_NotImplemented,    //Comparison not implemented for this kind of objects
              Outcome_Error              //Unexpected situation
              } CATCompareTopologyOutcome;

ExportedByCATTopologicalObjects CATCompareTopologyOutcome ReadCompareTopologyOutcome(const char *);

ExportedByCATTopologicalObjects const char * WriteCompareTopologyOutcome(CATCompareTopologyOutcome &);

#endif
