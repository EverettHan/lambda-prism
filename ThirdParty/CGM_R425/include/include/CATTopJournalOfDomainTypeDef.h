#ifndef CATTopJournalOfDomainTypeDef_H
#define CATTopJournalOfDomainTypeDef_H 


#define __CATTopDomainGraphDebug__
//#undef  __CATTopDomainGraphDebug__

/** @nodoc @nocgmitf */
enum CATTopDomainNodeOriginKind
{
	CATTopDomainNodeOriginKind_Unknown,
	CATTopDomainNodeOriginKind_FromInput,
	CATTopDomainNodeOriginKind_FromOutput,
	CATTopDomainNodeOriginKind_FromBoth
};

/** @nodoc @nocgmitf */
enum CATTopDomainPolarityStatus
{
	CATTopDomainPolarityStatus_Unknown,
	CATTopDomainPolarityStatus_Stable,
	CATTopDomainPolarityStatus_Inverted
};

/** @nodoc @nocgmitf */
enum CATTopDomainTypeOfConstruction
{
	CATTopDomainTypeOfConstruction_Unknown		= 0x00000000,
	CATTopDomainTypeOfConstruction_Creation		= 0x00000001,
	CATTopDomainTypeOfConstruction_Modification	= 0x00000010,
	CATTopDomainTypeOfConstruction_Deletion		= 0x00000100
};

/** @nodoc @nocgmitf */
enum CATTopDomainProperties
{	
	CATTopDomainProperties_Unknown				= 0x00000000,
   CATTopDomainProperties_Created				= 0x00000001,
   CATTopDomainProperties_Modified				= 0x00000010,
	CATTopDomainProperties_Deleted				= 0x00000100,
	CATTopDomainProperties_EquiPolarity			= 0x00001000,
	CATTopDomainProperties_InvertPolarity		= 0x00010000
};


#endif
