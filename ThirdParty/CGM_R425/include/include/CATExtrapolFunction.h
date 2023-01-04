#ifndef CATExtrapolFunction_H
#define CATExtrapolFunction_H

// COPYRIGHT DASSAULT SYSTEMES 2007

//===================================================================
//
class CATGeoFactory;
class CATTopData;

class CATBody;

//===================================================================
typedef void (*CATExtrapolFunction)(CATGeoFactory * iFactory,
                                    CATTopData    * iTopData,
                                    CATBody       * iBodyToExtrapol,
                                    CATBody       * iSupportBody,
                                    CATBody      ** oExtrapolatedBody);     
//===================================================================
#endif
