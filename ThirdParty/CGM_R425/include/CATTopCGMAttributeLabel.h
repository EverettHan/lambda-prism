#ifndef CATTopCGMAttributeLabel_H
#define CATTopCGMAttributeLabel_H


// COPYRIGHT DASSAULT SYSTEMES  2009
//===========================================================================  
//  Class  CATTopCellWithCGMAttribute  
//---------------------------------------------------------------------------  
//
//  
//
//
//
//
//===========================================================================   

/** @nodoc @nocgmitf */
enum CATTopCGMAttributeLabel
{	
	CATTopCGMAttributeLabel_NoneAttribute			= 0x00000000,
   CATTopCGMAttributeLabel_HiddenSeam				= 0x00000001,
   CATTopCGMAttributeLabel_ImprintCell				= 0x00000010,
   CATTopCGMAttributeLabel_NewImprintCell			= 0x00000100,
	CATTopCGMAttributeLabel_AllFlags					= 0x00000111,
	CATTopCGMAttributeLabel_MaxFlag					= 0xFFFFFFFF
};

#endif
