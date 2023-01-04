// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.

#ifndef CATCGMTessellateParam_H
#define CATCGMTessellateParam_H

/**
 * @CAA2Level L1 
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"

/**
* Class for the new tessellation parameters.  
*/

class ExportedByCATGMModelInterfaces CATCGMTessellateParam
{
public:
  /**
   * Constructs an instance of CATCGMTessellateParam given the maximum chord deviation.
   * @param iMaxDeviation
   *   The maximum chord deviation (sag) to be met by the tessellated body.
   */
  CATCGMTessellateParam(double iMaxDeviation);
  
  virtual ~CATCGMTessellateParam();

  /**
   * Constructs an instance of CATCGMTessellateParam given an other instance of CATCGMTessellateParam.
   * @param iTessParamToCopy
   *   The other instance of CATCGMTessellateParam.
   */
  CATCGMTessellateParam(const CATCGMTessellateParam &iTessParamToCopy);
	
public:
  /**
   * Sets the maximum chord deviation.
   * @param iMaxDeviation
   *   The maximum chord deviation (sag) to be met by the tessellated body.
   */
  void SetMaxDeviation(double iMaxDeviation){_MaxDeviation = iMaxDeviation;}
  /**
   * Gets the maximum chord deviation.
   * @return 
   *  The maximum chord deviation.
   */
  double GetMaxDeviation()const{return _MaxDeviation;}

  /**
   * Sets the maximum step (default MaxStep = CATMathInfinite).
   * @param iMaxStep
   *   The maximum step to be met by the tessellated body.
   */
  void SetMaxStep(double iMaxStep){_MaxStep = iMaxStep;}
  /**
   * Gets the maximum step.
   * @return 
   *  The maximum step.
   */
  double GetMaxStep()const{return _MaxStep;}

  /**
   * Sets the maximum angle (default MaxAngle = CATPI * 0.25).
   * @param iMaxAngle
   *   The maximum angle to be met by the tessellated body.
   */
  void SetMaxAngle(double iMaxAngle){_MaxAngle = iMaxAngle;}
  /**
   * Gets the maximum angle.
   * @return 
   *  The maximum angle.
   */
  double GetMaxAngle()const{return _MaxAngle;}

public:
  /**
   * Asks for normal vector (on surface) at vertice.
   * @param iActivate
   *   default is FALSE.
   */
  void DoGenerateVertexNormals(CATBoolean iActivate){_GenerateVertexNormals=iActivate;}
  /**
   * Asks for normal vector at vertice.
   * @return 
   *  is normal vector at vertice asked.
   */
  CATBoolean GenerateVertexNormals()const{return _GenerateVertexNormals;}
 
  /**
   * Asks for UV (2D parameter on surface) at vertice.
   * @param iActivate
   *   default is FALSE.
   */
  void DoGenerateVertexUVs(CATBoolean iActivate){_GenerateVertexUVs=iActivate;}
  /**
   * Asks for UV at vertice.
   * @return 
   *  is UV at vertice asked.
   */
  CATBoolean GenerateVertexUVs()const{return _GenerateVertexUVs;}

  /**
   * Asks for W (1D parameter on curve) at vertice.
   * @param iActivate
   *   default is FALSE.
   */
  void DoGenerateVertexWs(CATBoolean iActivate){_GenerateVertexWs=iActivate;}
  /**
   * Asks for W at vertice.
   * @return 
   *  is W at vertice asked.
   */
  CATBoolean GenerateVertexWs()const{return _GenerateVertexWs;}
 
  /**
   * Asks for tangent vector (on curve) at vertice.
   * @param iActivate
   *   default is FALSE.
   */
  void DoGenerateVertexTangents(CATBoolean iActivate){_GenerateVertexTangents=iActivate;}
  /**
   * Asks for tangent vector at vertice.
   * @return 
   *  is tangent vector at vertice asked.
   */
  CATBoolean GenerateVertexTangents()const{return _GenerateVertexTangents;}

private:
  double _MaxDeviation;
  double _MaxStep;
  double _MaxAngle;
  CATBoolean _GenerateVertexNormals, _GenerateVertexUVs,_GenerateVertexWs,_GenerateVertexTangents;
};

#endif
