#ifndef LimitCompactInfoForIncStr_H
#define LimitCompactInfoForIncStr_H

// Only used in Incremental Stream
// For specific unstream of support object in order to get the good limit for LimitCompact object
struct LimitCompactInfo
	{
		double     LowLimit;
		double     HighLimit;
		CATLONG32  LowPartNumber;
		CATLONG32  HighPartNumber;
		double     StartU;
		double     StartV;
		double     EndU;
		double     EndV;
	};

#endif
