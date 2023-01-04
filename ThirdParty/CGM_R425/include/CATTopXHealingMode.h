#ifndef CATTopXHealingMode_H
#define CATTopXHealingMode_H

//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012
//==========================================================================
//   /04/12 KTU Creation
// 25/10/18 NLD Correction typedef enum pour eviter warnings de compilation
// 14/10/20 RTE1 Adding the XHXSimplifTreatmentMode
//========================================================================== 

/**
* CATTopXHealingMode
* <br><b>Defines the behavior of the operator <\b>.
* <br>Each item is a bit-set and triggers a specific operation.
* So by using the c++ bit operator <b>"|"<\b> , they may be combined
* together to have the desired behavior. For all Shape Deformation items,
* call @SetMaxShapeDeformation to control the deformation.
*
* @param XHTopologicGapTreatmentMode
* No shape Deformation. Only the topological operations will be applied.
*
* @param XHGeometricGapTreatmentMode
* Shape Deformation. the geometric healing will be applied.

* @param SXHSimplificationTreatmentMode
* Can Deform the shape. Enable it simplification of cell. 
* Used @AddSetOfFaces for the sets of cells to simplify.
* if the Max deformation is less than  or equal to the resulolution
*  of the factory, then only the cells with the same supports will be simplified.
* So no shape deformation.

* @param XHSingularitiesTreatmentMode
* Shape Deformation. Enables the regularization of degenerated, 
* twisted and null curvature radius faces.

* @param XHOfsettabilityTreatmentMode
* Shape Deformation. Enables the regularization of all faces whose the curvature 
* radius value is less than or equal to a given value. See @SetMinOffSetValue
*
* @param XHTangencyTreatmentMode
* Shape Deformation. Enables geometric tangency defaults healing.
*
* @param XHXSimplifTreatmentMode
* Enable XSimplif Treatment.
*/
typedef enum  {
               XHTopologicGapTreatmentMode   = 0x01,
               XHGeometricGapTreatmentMode   = 0x02,
               XHSimplificationTreatmentMode = 0x04,
               XHSingularitiesTreatmentMode  = 0x08,
               XHOfsettabilityTreatmentMode  = 0x10,
               XHTangencyTreatmentMode       = 0x20,
			   XHXSimplifTreatmentMode       = 0x40,
               XHealingHistoricalMode        = 0x00 /*do not use internal */ 
              }CATTopXHealingMode;


///**
//* CATTopXHealingMode
//* <br><b>Defines the operator mode
//* <br><b> NoShapeDeformationMode, ShapeDeformationSimplifyOnlyMode, 
//* and ShapeDeformationFullMode can't be combined togetherneither 
//* with the rest of enumerators.
//* @param NoShapeDeformationMode
//* No deformation operators of geometric form will be applied
//* @param ShapeDeformationFullMode
//* The best of operator to improve the Geometries end the topology.
//* In this mode the shape may be deformed. 
//* Call SetMaxShapeDeformation to control the maximum shape deformation.
//* @param ShapeDeformationSimplifyOnlyMode
//* The same behaviour as ShapeDeformationFullMode in deformation term.
//* Except that here, only the simpifaction operation will be done.
//* In this mode the shape may be deformed. 
//* @See SetMaxShapeDeformation  and@ AddSetOfFaces
//* @param FreeShapeDeformationMode
//* Combine this value with one or several values of @{SingularityTreatment,
//* GeometricHealing, OffsetRegularization} to create the desired behaviour.
//* The simpifaction operator is managed by @AddSetOfFaces method.
//* @See SetMaxShapeDeformation  and@ AddSetOfFaces
//* @param SingularityTreatment
//* Combined with @FreeShapeDeformationMode, i.e FreeShapeDeformationMode|SingularityTreatment 
//* to actived the regularisation of sigulatries and twists.
//* @param GeometricHealing
//* Combined with @FreeShapeDeformationMode, i.e FreeShapeDeformationMode|GeometricHealing 
//* to actived Geometric healing.
//* @param OffsetRegularization
//* Combined with @FreeShapeDeformationMode, i.e FreeShapeDeformationMode|OffsetRegularization 
//* to actived the regularization of offset . See also @SetMinOffSetValue 
//* <br> See also  @SetMaxShapeDeformation , @SetMinOffSetValue, and@ AddSetOfFaces
//*/
//typedef enum  {
//               NoShapeDeformationMode           = 0x01,
//               ShapeDeformationSimplifyOnlyMode = 0x2,
//               InternalMode                     = 0x4, /*Do not used*/
//               /*For the future, be sure that full value = OR(all following optional values).*/
//               ShapeDeformationFullMode         = 0xF0,
//               FreeShapeDeformationMode         = 0x10,
//               SingularityTreatment             = 0x20,
//               GeometricHealing                 = 0x40,
//               OffsetRegularization             = 0x80
//              }CATTopXHealingMode;

#endif
