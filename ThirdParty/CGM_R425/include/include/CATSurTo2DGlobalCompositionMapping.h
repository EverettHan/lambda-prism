 /*
=============================================================================

 COPYRIGHT   : DASSAULT SYSTEMES 1999       
//==========================================================================
 DESCRIPTION 

// CATSurTo2DGlobalCompositionMapping:
// derives from CATSurTo2DGlobalMapping
//
//==========================================================================
//
// Usage notes:
//      This virtual Object describes the mapping between one set of CATSurface 
//   and a  virtual  2 dimension space defined by the composition of another mapping with
//        2 bivariable fonctions NewX(X,Y) and NewY(X,Y):
//          inverse functions must be provided as well if InvEval are necessary OldX,OldY
//             
//       
//	Methods : 
//             - CreateLocalMapping 
//
//==========================================================================
// August     99     Creation                                    OB                 
//========================================================================== 
//
*/  
#ifndef CATSurTo2DGlobalCompositionMapping_H
#define CATSurTo2DGlobalCompositionMapping_H 
 
#include "CATSurTo2DGlobalMapping.h"
class CATMathFunctionXY;  
 

class CATSurLimits;
class CATIPGMSurTo2DGlobalMapping;
 

//----------------------------------------------------------------------------
class CATSurTo2DGlobalCompositionMapping: public CATSurTo2DGlobalMapping
{ 
  CATCGMVirtualDeclareClass(CATSurTo2DGlobalCompositionMapping);
public :
	//-------------
	// Constructor
	//-------------
	CATSurTo2DGlobalCompositionMapping(CATGeoFactory *iFactory,		 
									const CATSurTo2DGlobalMapping * &iGlobalMapping,
									const CATMathFunctionXY * &iNewX,
									const CATMathFunctionXY * &iNewY,
									const CATMathFunctionXY * &iOldX,
									const CATMathFunctionXY * &iOldY	);

	CATSurTo2DGlobalCompositionMapping(CATGeoFactory *iFactory,		 
									CATIPGMSurTo2DGlobalMapping * &iGlobalMapping,
									const CATMathFunctionXY * &iNewX,
									const CATMathFunctionXY * &iNewY,
									const CATMathFunctionXY * &iOldX,
									const CATMathFunctionXY * &iOldY	);

	//-------------
	// Destructor
	//-------------
	~CATSurTo2DGlobalCompositionMapping();
	//-------------
	
	//-------------
	// Methods
	//-------------
	//  Create LocalMapping 
	
	CATSurTo2DMapping *  CreateLocalMapping(CATSurface * iLocalReference ,
		const double & iRefOrientation,
		const CATSurLimits &iRefLimits) const; 
 
	//----------------------
	// Set and Get Methods 
	//----------------------  
	
private :
	
	//----------------------
	// DATA 
	//----------------------  
	// global data
	const CATSurTo2DGlobalMapping * _GlobalMapping;
	CATIPGMSurTo2DGlobalMapping * _IGlobalMapping;
	const CATMathFunctionXY * _NewX,* _NewY,* _OldX,* _OldY;  
	
};
#endif
