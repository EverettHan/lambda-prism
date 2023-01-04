#ifndef __CATPGMLayDownOperatorDef_h__
#define __CATPGMLayDownOperatorDef_h__

/** @CAA2Required */ 
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES 2006

/** @nodoc */
enum CATLayDownDiagnostic 
{
	NoLayDown            = +301,
		BodyIsLyingOn        = +302,
		BodyHasBeenLaidDown  = +303,
		BodyPartiallyLaid    = +304
};
/** @nodoc */

enum CATLayDownAnalysis 
{
	EmptyResult                       = +401,       // The Result Body is empty then Diagnosis is NoLayDown
		AlreadyLyingOn                    = +402,   // The Input Body is already LyingOn then Diagnosis is BodyIsLyingOn
		AfterComputationResultIsLayDown   = +403,   // After computation the Result Body is correctly LayDown then Diagnosis is BodyHasBeenLaidDown
		TooMuchResultDomain               = +404,   // The Result Body has more domains than Input Body then Diagnosis is BodyPartiallyLaid
		NotEnoughResultDomain             = +405,   // The Result Body has less domains than Input Body then Diagnosis is BodyPartiallyLaid
		DifferentExtremity                = +406,   // The Extremities of Result Body are different from Input Body then Diagnosis is BodyPartiallyLaid
		DifferentExtremityRelimitation    = +407    // idem DifferentExtremity and the reason is Relimitation
};

#endif // __CATPGMLayDownOperatorDef_h__
