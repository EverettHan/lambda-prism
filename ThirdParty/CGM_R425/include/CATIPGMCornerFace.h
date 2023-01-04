#ifndef CATIPGMCornerFace_h_
#define CATIPGMCornerFace_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATLISTP_CATEdge_;
class CATLISTP_CATFace_;
class CATVertex;
class CATLISTP(CATEdge);
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCornerFace;

/** 
 * Class representing the operator that creates a face on a body from a vertex
 * on a concavity of the shell boundary.
 * <br>To use the CATIPGMCornerFace :
 * <ul><li>Create the <tt>CATPGMCreateCornerFace</tt> global function. 
 * <li> <tt>Run</tt> the operator
 * <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
 * <li>Release the operator with the <tt>Release</tt> method after use.</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMCornerFace: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCornerFace();

  /** 
 * Gives supplemental optional information <tt>this</tt> operator.
 * @param iFactory
 * The pointer to the list of bottom faces.
 * planned to solve potential ambiguity findig top faces 
 */
  virtual void SetTopFaces(CATLISTP(CATFace) *iListOfFaces) = 0;

  // IZE wk. 01 2010 IR 021460 Some checks are too restrictive for SheetMetal configurations
  virtual void SetUnplugChecksForSheetMetal(
    CATBoolean iUnplugChecksForSheetMetal) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCornerFace(); // -> delete can't be called
};

/**
 * @ deprecated
 * Creates an operator to build a new shell from an initial body and a vertex where to create faces to make a 2D corner.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside the
 * configuration is <tt>NULL</tt>, it is not filled. 
 * @param iBody
 * The pointer to the 3D body containing the shell with the vertex
 * @param iRadius
 * The value of the corner face to create
 * @param iEdge
 * The edge sharing the vertex iVertex to create the fillet generating the corner face by its side.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCornerFace *CATPGMCreateCornerFace(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATVertex *iVertex,
  double iRadius,
  CATLISTP(CATEdge) *iListOfEdges);

/**
 * Creates an operator to build a new shell from an initial body and a vertex where to create faces to make a 2D corner.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside the
 * configuration is <tt>NULL</tt>, it is not filled. 
 * @param iVolumeBody
 * The pointer to the 3D body containing the shell with the vertex
 * @param iShellBody
 * The pointer to the Shell containing the vertex and contained in 3D body
 * @ param 
 * @param iRadius
 * The value of the corner face to create
 * @param iEdge
 * The edge sharing the vertex iVertex to create the fillet generating the corner face by its side.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCornerFace *CATPGMCreateCornerFace(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iVolumeBody,
  CATBody *iShellBody,
  CATVertex *iVertex,
  double iRadius,
  CATLISTP(CATEdge) *iListOfEdges);

/**
 * Creates an operator to build a new shell from an initial body and a vertex where to create faces to make a 2D corner.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside the
 * configuration is <tt>NULL</tt>, it is not filled. 
 * @param iVolumeBody
 * The pointer to the 3D body containing the shell with the vertex
 * @param iShellBody
 * The pointer to the Shell containing the vertex and contained in 3D body
 * @ param 
 * @param iRadius
 * The value of the corner face to create
 * @param iListofLeftFaces
 * The list of faces from left side of the edge to fillet
 * @param iListofRightFaces
 * The list of faces from rightt side of the edge to fillet
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCornerFace *CATPGMCreateCornerFace(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iVolumeBody,
  CATBody *iShellBody,
  CATLISTP(CATFace) *iListOfLeftFaces,
  CATLISTP(CATFace) *iListOfRightFaces,
  double iRadius,
  CATVertex *iVertex);

/**
 * Creates an operator to build a new shell from an initial body to create faces to make a 2D corner.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside the
 * configuration is <tt>NULL</tt>, it is not filled. 
 * @param iVolumeBody
 * The pointer to the 3D body containing the shell with the vertex
 * @param iShellBody
 * The pointer to the Shell containing the vertex and contained in 3D body
 * @ param  
 * @param iListofLeftFaces
 * The list of faces from left side of the Tritangent fillet
 * @param iListofRightFaces
 * The list of faces from right side of the Tritangent fillet
 * @param iListofFacesToRemove
 * The list of faces to be removed by the Tritangent fillet
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCornerFace *CATPGMCreateCornerFace(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iVolumeBody,
  CATBody *iShellBody,
  CATLISTP(CATFace) *iListOfLeftFaces,
  CATLISTP(CATFace) *iListOfRightFaces,
  CATLISTP(CATFace) *iListOfFacesToRemove);

#endif /* CATIPGMCornerFace_h_ */
