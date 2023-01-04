#ifndef CATIPGMCornerChamferFace_h_
#define CATIPGMCornerChamferFace_h_

// COPYRIGHT DASSAULT SYSTEMES 2015

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDynChamferRibbon.h"

class CATLISTP_CATEdge_;
class CATLISTP_CATFace_;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCornerChamferFace;

/** 
 * Class representing the operator that creates a face on a body from a vertex
 * on a concavity of the shell boundary.
 * <br>To use the CATIPGMCornerChamferFace :
 * <ul><li>Create the <tt>CATPGMCreateCornerFace</tt> global function. 
 * <li> <tt>Run</tt> the operator
 * <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
 * <li>Delete with the usual C++ <tt>delete</tt> operator after use.</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMCornerChamferFace: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMCornerChamferFace();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCornerChamferFace(); // -> delete can't be called
};

/** 
 * Gives supplemental optional information <tt>this</tt> operator.
 * @param iFactory
 * The pointer to the list of bottom faces.
 * planned to solve potential ambiguity findig top faces 
 */
//virtual void SetTopFaces( CATLISTP(CATFace) * iListOfFaces )=0;
//// IZE wk. 01 2010 IR 021460 Some checks are too restrictive for SheetMetal configurations
//virtual void SetUnplugChecksForSheetMetal(CATBoolean iUnplugChecksForSheetMetal)=0;
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
 * @param iVertex
 * The pointer to vertex at which corner is to be created
 * @param iChamferType
 * The chamfer type - CATDynd1d2 or CATDynd1a1
 * @param iDistance1
 * The value of the first distance D1
 * @param iDistance2
 * The value of the second distance D2 or Angle A1
 * @param iListOfEdges
 * The edge sharing the vertex iVertex to create the Chamfer generating the corner face by its side.
  * @param iListOfFaces
 * The reference face used in determining the first and second lengths/angles of chamfer
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCornerChamferFace *CATPGMCreateCornerChamferFace(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iVolumeBody,
  CATBody *iShellBody,
  CATVertex *iVertex,
  CATDynTypeChamfer iChamferType,
  double iDistance1,
  double iDistance2,
  CATLISTP(CATEdge) *iListOfEdges,
  CATLISTP(CATFace) *iListOfFaces);

#endif /* CATIPGMCornerChamferFace_h_ */
