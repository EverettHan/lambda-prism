#ifndef CATCEF_OperatorDef_H
#define CATCEF_OperatorDef_H

#include "CATCGMOutput.h"
#include "CATUnicodeString.h"

enum CATCoincidenceType
{
  UNSET_COINCIDENCE,
  OVERLAPPED_COINCIDENCE,
  BUTT_COINCIDENCE,
  UNDEFINED_COINCIDENCE
};

static CATUnicodeString GetUCSfromCoincidenceType(CATCoincidenceType iType)
{
  CATUnicodeString oResult;

  switch ((iType))
  {
  case UNSET_COINCIDENCE:
    oResult.Append("UNSET");
    break;
  case OVERLAPPED_COINCIDENCE:
    oResult.Append("OVERLAPPED");
    break;
  case BUTT_COINCIDENCE:
    oResult.Append("BUTT");
    break;
  case UNDEFINED_COINCIDENCE:
    oResult.Append("UNDEFINED_COINCIDENCE");
    break;
  default:
    oResult.Append("UNDEFINED_COINCIDENCE");
    break;
  }
  return oResult;
}

static void DumpCoincidenceType(CATCoincidenceType iType, CATCGMOutput& os)
{
  CATUnicodeString dump = GetUCSfromCoincidenceType(iType);

  os << dump << " Coincidence";
}

#endif
