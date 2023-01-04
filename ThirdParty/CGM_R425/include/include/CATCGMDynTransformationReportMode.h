#ifndef CATCGMDynTransformationReportMode_h_
#define CATCGMDynTransformationReportMode_h_

// COPYRIGHT DASSAULT SYSTEMES 2006 

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
* Type of follow-up to be written in the journal.<br>
* This information is used by applications, depending on the type of operations they want to 
* perform after calling the transformation. This information has no impact on the objects of the
* geometrical modeler itself.
* @param CATCGMDynTransformationModification
* The transformation is seen as a modification: the body is always duplicated, but the application
* wants to mask the input body for showing only the resulting body (case of an applicative
* transformation). This is the default of a CATCGMDynTransformation.
* @param CATCGMDynTransformationCreation
* The transformation is seen as a creation: The application keeps the input body and
* the duplicated body, and wants to union them for example:
* this is a typical case of an applicative operation of mirror.
*/
enum CATCGMDynTransformationReportMode { CATCGMDynTransformationModification=0,CATCGMDynTransformationCreation=1 }; 

#endif /* CATCGMDynTransformationReportMode_h_ */
