#ifndef CATCpuQuery_h
#define CATCpuQuery_h

#include "CATIACGMLevel.h"
#include "CATMathematics.h"

class ExportedByCATMathematics CATCpuQuery
{
  enum Maker { Unknown = 0, Intel, AMD };
#if ! defined CATIACGMR421CAA || defined _AIX_SOURCE
	int maker;
	int packages;
  int coresPerPackage;
#endif
	int logicalCores;
	int physicalCores;
  int HttEnabled;
#if ! defined CATIACGMR421CAA || defined _AIX_SOURCE
	int logicalBits;
  int coreBits;
#endif

public:

	CATCpuQuery ();
  ~CATCpuQuery();
#if ! defined CATIACGMR421CAA || defined _AIX_SOURCE
	int GetClusters       ();
  int GetPhysiPacks     ();
#endif
	int GetCores          ();
	int GetLogiProcs      ();
  int GetHyperThreading();
#if ! defined CATIACGMR421CAA || defined _AIX_SOURCE
  int IsContiguous      ();
#endif
	void Edit              ( int Choice );
};

#endif // CATCpuQuery_h

