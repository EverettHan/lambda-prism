#ifndef CATMathDefGraphic_H
#define CATMathDefGraphic_H


// COPYRIGHT DASSAULT SYSTEMES  1999


#ifndef CAT_NONE
#define CAT_NONE        1024   // no processing
#endif

#define CAT_POLYLINE       1   // open polyline
#define CAT_POLYMARKER     2   // single reticule
#define CAT_POLYVECTOR     4   // pairs of extremities
#define CAT_PIXEL_ARRAY    8   // non-isolated pixels
#define CAT_SYMMETRIC    128   // origin centered display
#define CAT_PROPORTIONAL   0   // vs CAT_SEMI_LOG
#define CAT_SEMI_LOG     256   // logarithmic ordinate
#define CAT_AUTO         512   // interactiveless
#define CAT_KEEP        2048   // curve file keeping
#define CAT_PAPER       4096   // for print

#define CAT_IS_NOT_LAST    0
#define CAT_IS_LAST        1

#endif
