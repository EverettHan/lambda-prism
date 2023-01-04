/* -*-C++-*-*/
// COPYRIGHT DASSAULT SYSTEMES  1999
//=============================================================================
//
// CATMathQuaternion:
/**
 * Class representing a quaternion  such that :
 *                 q= [s, (x, y, z)] according to the mathematical convention
 *           or   q= [(x, y, z), s] according to the game convention
 * WARNING : Be careful to the chosen convention
 * Element of the 4 dimensional space with the basis 1, i, j, k
 *    i*i = j*j = k*k = -1
 *    i*j = -j*i = k  ,  j*k = -k*j = i   ,   k*i = -i*k = j
 *    
 * Used for rotations in space
*/

#ifndef CATMathQuaternion_h
#define CATMathQuaternion_h

class CATMathVector;
class CATMath3x3Matrix;

#include "CATMathPoint.h"
#include "YN000MAT.h"
#include "CATMathInline.h"

enum QuaternionConvention {MathematicalConvention, GameConvention};

class ExportedByYN000MAT CATMathQuaternion
{
 public:
   
	
//--------------------------------------------------------------------------
// Constructors
//--------------------------------------------------------------------------
   
   /**
    * Default-Constructor
    * Initializes the quaternion to the 4D-Vector [1, 0, 0, 0] according to mathematical convention
    */
   CATMathQuaternion( );

   /**
    * Constructs from 4 coordinates 
    */
   CATMathQuaternion(const double               & iCoord1                              ,
                     const double               & iCoord2                              ,
                     const double               & iCoord3                              ,
                     const double               & iCoord4                              ,
                     const QuaternionConvention   Convention   = MathematicalConvention);

   /**
    * Constructs from an array of four coordinates.
    */
   CATMathQuaternion(const double                 iCoord     []                         ,
                     const QuaternionConvention   Convention   = MathematicalConvention);

   /**
    * Constructs from an axis and an angle
    */
   CATMathQuaternion(const CATMathVector        & iAxis                                ,
                     const double                 iAngle                               );

   /**
    * Constructs from a scalar and a vector
    */
   CATMathQuaternion(const double               & iCoord1                              ,
                     const CATMathVector        & iVector                              );


   /**
    * Copy constructor
    */
   CATMathQuaternion(const CATMathQuaternion    & iQuat                                );
   
   

   
   //--------------------------------------------------------------------------
   // Get interfaces
   //--------------------------------------------------------------------------
   
   /**
    * Retrieves the 4 coordinates
    */
   void GetCoord      (      double               & oCoord1                             ,
                             double               & oCoord2                             ,
                             double               & oCoord3                             ,
                             double               & oCoord4                             ,
                       const QuaternionConvention   Convention = MathematicalConvention ) const;
   
   /**
    * Retrieves 1 coordinate and a vector
    **/
   void GetCoord      (      double               & oCoord                              ,
                             CATMathVector        & oVector                             ) const;
   
   /**
    * Retrieves the coordinates in an array of four coordinates.
    **/
   void GetCoord      (      double                 oCoord    []                        ,
                       const QuaternionConvention   Convention  = MathematicalConvention) const;
   
   /*
    * Retrieves the first coordinates 
    */
   void GetScalar      (     double               & oScalar                             ) const;
   
   /**
    * Retrieves the last 3 coordinates by a vector.
    */
   void GetVector      (     CATMathVector        & oVector                             ) const;

   /**
    * Retrieves the last 3 coordinates by an array of 3 coordinates
    */
   void GetVector      (     double                 oCoord    []                        ) const;

   /**
    * Retrieves the data of the associated rotation : angle (radian) and axis.
    */
   void GetRotationData(     double               & oAngle                              ,
                             CATMathVector        & oAxis                               ) const;

   //--------------------------------------------------------------------------
   // Set interface
   //--------------------------------------------------------------------------
   
   /**
    * Sets 4 coordinates
    **/
   void SetCoord (const double               & iCoord1                               ,
                  const double               & iCoord2                               ,
                  const double               & iCoord3                               ,
                  const double               & iCoord4                               ,
                  const QuaternionConvention   Convention = MathematicalConvention   );
   
   /**
    * Sets 1 coordinate and a vector
    **/
   void SetCoord (const double               & iCoord                                ,
                  const CATMathVector        & iVector                               );
   
   /**
    * Modifies the coordinates from an array of four coordinates.
    **/
   void SetCoord (const double                 iCoord    [4]                         ,
                  const QuaternionConvention   Convention   = MathematicalConvention );
   
   /**
    * Modifies the first coordinates 
    **/
   void SetScalar(const double               & iScalar                               );
   
   /**
    * Modifies the last 3 coordinates by a vector.
    **/
   void SetVector(const CATMathVector        & iVector                               );
   
   /**
    * Modifies the last 3 coordinates by an array of 3 coordinates
    **/
   void SetVector(const double                 iCoord    [3]                         );


   //--------------------------------------------------------------------------
   // Overloaded Operators
   //--------------------------------------------------------------------------

   /**
    * Addition of two quaternions
    * q = [ s1+s2, x1+x2, y1+y2, z1+z2] 
    */
   CATMathQuaternion   operator+  (const CATMathQuaternion & quat2) const;
  
   CATMathQuaternion & operator+= (const CATMathQuaternion & iQuat);
   
   /**
    * Subtraction of two quaternions
    * q = [ s1-s2,  x1-x2, y1-y2, z1-z2 ] 
    */
   CATMathQuaternion   operator-  (const CATMathQuaternion & iQuat2) const;

   CATMathQuaternion & operator-= (const CATMathQuaternion & iQuat );
   
   /**
    * Multiplication of two quaternions
    * s = s1*s2 - x1*x2 - y1*y2 - z1*z2;
    * x = s1*x2 + x1*s2 + y1*z2 - z1*y2;
    * y = s1*y2 - x1*z2 + y1*s2 + z1*x2;
    * z = s1*z2 + x1*y2 - y1*x2 + z1*s2;
    * So the multiplication isn't commutative.
    */   
   CATMathQuaternion   operator*  (const CATMathQuaternion & iQuat2) const;
  
   CATMathQuaternion & operator*= (const CATMathQuaternion & iQuat );
   
   /**
    * Division of two quaternions
    * q = q1 * q2(-1)
    */
   CATMathQuaternion   operator/  (const CATMathQuaternion & iQuat2) const;
   
   CATMathQuaternion & operator/= (const CATMathQuaternion & iQuat );
   
   /**
    * Multiplication of a quaternion with a scalar
    * q = [ Scalar * ( s, x, y, z)]
    */
   friend ExportedByYN000MAT CATMathQuaternion operator*(const double iScalar, const CATMathQuaternion &iQuat);
   
   CATMathQuaternion & operator*= (const double            & iScalar);
   CATMathQuaternion   operator/  (const double            & iScalar) const;
   CATMathQuaternion & operator/= (const double            & iScalar);

   //--------------------------------------------------------------------------
   // Methods
   //--------------------------------------------------------------------------
   /**
    * The conjugate of a quaternion
    * q_conj = [ s, -x, -y, -z ]
    * Modifies the quaternion
    */
   CATMathQuaternion & Conjugate ();
   
   /**
    * The inverse of a quaternion
    * q(-1) = [ s, -x, -y, -z ] / squarenorm(q)
    * Modifies the quaternion
    */
   void Inverse();

   /**
    * This quaternion becomes the spherical interpolation between this quaternion and the given one at a given ratio.
    * <br>
    * If the quaternion are not a unit quaternion, the computation will use their normalized form.
    * @param iQ       The unit quaternion to be used with this in the slerp computation.
    * @param iT       The ratio in [0,1]. If equals to 0 this stays inchanged, if equals to 1 this becomes a copy of iQ.
    * @param iShorter If set to TRUE (default), will use -iQ instead of iQ if -iQ is closest to this. Note iQ and -iQ represents the same rotation.
    *                 This allows to perform the shorter interpolation between the two quaternions.
    */
   void Slerp   (const CATMathQuaternion & iQ             ,
                 const double              iT             ,
                 const CATBoolean          iShorter = TRUE);

   void GetSlerp(const CATMathQuaternion & iQ             ,
                       CATMathQuaternion & oQ             ,
                 const double              iT             ,
                 const CATBoolean          iShorter = TRUE) const;

   /**
    * This quaternion becomes the linear interpolation between this quaternion and the given one at a given ratio, then normalize it.
    * <br>
    * If the quaternion are not a unit quaternion, the computation will use their normalized form.
    * @param iQ       The unit quaternion to be used with this in the lerp computation.
    * @param iT       The ratio in [0,1]. If equals to 0 this stays inchanged, if equals to 1 this becomes a copy of iQ.
    * @param iShorter If set to TRUE (default), will use -iQ instead of iQ if -iQ is closest to this. Note iQ and -iQ represents the same rotation.
    *                 This allows to perform the shorter interpolation between the two quaternions.
    */
   void Lerp    (const CATMathQuaternion & iQ             ,
                 const double              iT             ,
                 const CATBoolean          iShorter = TRUE);

   void GetLerp (const CATMathQuaternion & iQ             ,
                       CATMathQuaternion & oQ             ,
                 const double              iT             ,
                 const CATBoolean          iShorter = TRUE) const;


   /**
    * Dot product between two quaternions
    */
   double Dot(const CATMathQuaternion & iQ) const;

   /**
    * Returns the square norm :  s^2 + x^2 + y^2 + z^2 
    */
   double SquareNorm() const;

   /**
    * Returns the euclidean norm :  sqrt(s^2 + x^2 + y^2 + z^2) 
    */
   double Norm() const;

   /**
    * Normalize a quaternion, so 
    * q_norm = 1/norm(q)*[ s, x, y, z ]
    * Modifies the quaternion
    */
   void Normalize();
   
   /** 
    * Computes the rotation matrix from a quaternion q = [ s, x, y, z ]
    * Rotation of axis  (x, y, z )
    *        with an angle w, such as cos(w) = (s*s - x*x - y*y - z*z) / norm(q) 
    *                                 sin(w) = 2*s*sqrt(x*x + y*y + z*z) / norm(q)
    */
   void QuaternionToRotMatrix (      CATMath3x3Matrix & oMatrix   ) const;

   /** 
    * Computes an unit quaternion q = [ s, x, y, z ] associated with the rotation matrix 
    * WARNING : No test is done to check that  the matrix is a rotation
    */
   void RotMatrixToQuaternion (const CATMath3x3Matrix & iMatrix   );

   /** 
    * Rotation of a point p = (p1, p2, p3)  by a quaternion q = [ s, x, y, z ]
    * The result p' = (p'1, p'2, p'3) is calculated with the multiplication of quaternions
    * [ 0, p'1, p'2, p'3] = q * [ 0, p1, p2, p3] * q(-1)
    */
   void Rotate                (const CATMathPoint     & ipoint    ,
                                     CATMathPoint     & oPoint    ) const;

   void Dump   (                     ostream          * iStream=0L) const;
   
 private:
   
   double _scal, _x, _y, _z;
};

//======================================================================
// INLINE IMPLEMENTATIONS
//======================================================================

#endif
