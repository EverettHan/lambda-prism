// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyConcentricIterator.h
// Header definition of CATPolyConcentricIterator
//
//===================================================================
//
// Usage notes: iterator for points on a sphere, random or deterministic  
//
//===================================================================
//
// January 2017 Creation: ELN, JXO
//===================================================================
#ifndef CATPolyConcentricIterator_H
#define CATPolyConcentricIterator_H

#include "PolyMathUtils.h"
#include "CATMathTransformation.h"

class CATPolyUniformRandomGenerator;


/**
 class a splitté  en 
  3D/2D
  Random/Sequential

  ajouter un  contructeur par copie pour pouvoir se sauvgarder.
*/


/**
 * Iterator for points on a sphere, random or deterministic
 */
class ExportedByPolyMathUtils CATPolyConcentricIterator 
{
public:

  /** Type of iterator */
  enum Iteration {
    Random, Sequential
  };

  /**
   * Constructor
   * @param iDimension
   *        2 or 3
   * @param iDensity
   *        Density: Number of points in the first sphere
   */
  CATPolyConcentricIterator(int iDimension=3, int iDensity=8, Iteration iType=Sequential);
  /** Destructor */
  ~CATPolyConcentricIterator();
  /**
    @brief go to next circle dimenension 
    @param outside_mode true -> go outside , false go to the center
  */
  int NextConcentricityNumber(int outside_mode=1);
  Iteration Type();
  int NTrialsForThisConcentricity();
  int IncrementInCurrentConcentricity();

  double  alphaRot2D();//getter
  void SetAlphaOld();

  void  SetBackAndForth(int iFreq);
  void  SetVaEtVient(int iFreq);
  void  SetRestictedArea(double iDir_angle[4]);

  void  getcurrentdir(double oDir[4]);
  double getanglemax();
  void ComputeRandomRotationAndAdaptTranslation( CATPolyUniformRandomGenerator & Randomize, double iVTranslation[3], double m_jEquiX,double m_jEquiY,double m_jEquiZ,double oJequi, double oVRotation[4], double & oRadius);

 // Calls IAlphaAndJAlpha1, then compute translation, then calls PotentialRectification
  void GetRectifiedTranslation(double ot[3]);
  // Calls GetRectifiedTranslation then checks against restricted area, and returns TRUE if filtered out.
  CATBoolean ConeFiltered();
 
protected:
    int UnitaryIncrement();
  int UnitaryIncrementFromPole();
    void  change_circle();
    void  setcurrentdir(double dir[4]);
  int   HasRestictedArea(double oDir_angle[4]);
   
  
  void IAlphaAndJAlpha1(double &IA,double & JA1);
  void PotentialRectification(double v[3]);

protected:
  Iteration _Type = Sequential;
  int _Density = 8;
  int _Dimension = 3;
  int _CurrentConcentricNumber = 0;
  int _RangeMaxForRandom = 0;
  int _CurrentRangeForRandom = 0;
  int _ntrial = 0;
  int _i = 0; // indice selon _Alpha
  int _j = 0; // indice selon _Alpha1
  int _iRot = 0 ; // indice selon angle rotation en 2D 3doF
  int _iRotMax =0; // indice selon angle rotation en 2D 3doF
  double _Alpha = 0;
  double _Alpha1 = 0;
  int _Npoints___OnCircle_i=0; // nombre d epoints sur cercle i

  int _restricted_search_area=0;
  double  _direction_and_angle_area[4]={0,0,0,0};
  double  _current_direction_and_angle[4]={0,0,0,0};
  double  _angle_max_tested_in_current_concentricity=0;
  double  _current_translation[3]={0,0,0};

  int _outside_mode=1;	 
  int _VaEtVient_Mode=1;	 
  int _indice_pour_VaEtVient=0;	 

  CATMathVector _VectorAxisLastFound = CATMathVector(0,0,0);
  CATMathVector _orth1= CATMathVector(0,0,0);
  CATMathVector _orth2= CATMathVector(0,0,0);
  CATAngle _AngleLastFound =0.0;
  CATMathTransformation _NearOld=CATMathTransformation();
  int _NCircles=0; // nombre d epoints sur cercle i
  
};

#endif
