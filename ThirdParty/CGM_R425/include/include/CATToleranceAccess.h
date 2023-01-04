#ifndef CATToleranceAccess_H
#define CATToleranceAccess_H
/**
 * @quickReview NLD 11:04:19
 */
//=============================================================================
// COPYRIGHT Dassault Systemes 2011
//=============================================================================
//
// Wrap geometric and mathematical tolerances.
// Special derives classes for direct and fast access
//=============================================================================
// 19/04/11 NLD Création pour accès optimisés après controle unitaire du bloc de tolérance
//              CATFullTolerance:     accès à toutes les tolérances (de nomenclature correcte)
//              CATRelativeTolerance: accès aux tolérances relatives
//              CATGetFullTolerance(),
//              CATGetRelativeTolerance()
//=============================================================================
#define EB_2013_06_10_CATTolerance_Friends_Not_Allowed
#ifdef EB_2013_06_10_CATTolerance_Friends_Not_Allowed
//-----------------------------------------------------------------------------------------------
#define CATFullTolerance CATTolerance
#define CATGetFullTolerance /**/
//-----------------------------------------------------------------------------------------------
#else

#include <CATIACGMLevel.h>
#include <YN000MAT.h>
#include <CATTolerance.h>

//-----------------------------------------------------------------------------------------------
// Test pour accès direct rapide sans controle
// (controle fait via CATGetFullTolerance())
// N.B je ne donne pas accès aux valeurs à la nomenclature douteuse

class ExportedByYN000MAT CATFullTolerance: public CATTolerance
  {
   private:
   CATFullTolerance();
   public:
   INLINE double GetScale() const;
   //
   INLINE double GetSquareScale() const;
   INLINE double GetSqrtScale() const;

   // Mathematic
   // Not-scaled values
   INLINE double Infinite() const;
   INLINE double EpsgForRelativeTest() const;
   INLINE double EpsilonForRelativeTest() const;
   INLINE double SquareEpsgForRelativeTest() const;

   INLINE double SquareEpsilonForRelativeTest() const;

   INLINE double SqrtEpsgForRelativeTest() const;
   INLINE double SqrtEpsilonForRelativeTest() const;

   public:
   // Radian
   INLINE CATAngle EpsgForAngleTest() const;
   // Radian
   INLINE CATAngle EpsilonForAngleTest() const;

   private: // nomenclature inadequate 
   INLINE double EpsgForSquareAngleTest() const;
   private: // nomenclature inadequate 

   INLINE double EpsilonForSquareAngleTest() const;
   private: // nomenclature inadequate 
   INLINE double EpsgForSqrtAngleTest() const;
   private: // nomenclature inadequate 
   INLINE double EpsilonForSqrtAngleTest() const;

   public:

   INLINE double EpsgForLengthTest() const;
   INLINE double EpsilonForLengthTest() const;

   private: // nomenclature inadequate 
   INLINE double EpsgForSquareLengthTest() const;
   INLINE double EpsilonForSquareLengthTest() const;

   private: // nomenclature inadequate 
   INLINE double EpsgForSqrtLengthTest() const;
   INLINE double EpsilonForSqrtLengthTest() const;

   public:
   // Geometric
   INLINE double ModelSize() const;
   INLINE double ModelInfinite() const;

   // Pow 1
   INLINE CATAngle  ResolutionForAngleTest() const;

   INLINE CATPositiveLength ResolutionForLengthTest() const;
   /**
     * @nodoc
     */
   INLINE double GetResolution(CATTolerance::ResolutionType iResolutionType) const;

   // Pow 2
   private: // nomenclature inadequate 
   INLINE double ResolutionForSquareLengthTest() const;

   // Pow 0.5
   private: // nomenclature inadequate 
   INLINE double ResolutionForSqrtLengthTest() const;

   public:
   /**
     * @nodoc
     */
   INLINE CATAngle LargeResolutionForAngleTest() const;
   /**
     * @nodoc
     */
   INLINE CATPositiveLength LargeResolutionForLengthTest() const;
   /**
     * @nodoc
     */
   private: // nomenclature inadequate  // nomenclature inadequate 
   INLINE double LargeResolutionForSquareLengthTest() const;
   /**
     * @nodoc
     */
   private: // nomenclature inadequate  // nomenclature inadequate 
   INLINE double LargeResolutionForSqrtLengthTest() const;
   public:
   /**
     * @nodoc
     */
   INLINE double LargeEpsgForLengthTest() const;
   /**
     * @nodoc
     */
   INLINE CATAngle LargeEpsgForAngleTest() const;
   /**
     * @nodoc
     */
   INLINE float EpsilonfForRelativeTest() const;

   /**
     * @nodoc
     */
   INLINE double LargeEpsgForRelativeTest() const;
  };

//------------------------------------------------
INLINE double CATFullTolerance::GetScale() const
{
 return _Scale;
}
//
INLINE double CATFullTolerance::GetSquareScale() const
{
 return _SquareScale;
}

INLINE double CATFullTolerance::GetSqrtScale() const
{
 return _SqrtScale;
}

// Mathematic
// Not-scaled values
INLINE double CATFullTolerance::Infinite() const
{
 return _Infinite;
}

INLINE double CATFullTolerance::EpsgForRelativeTest() const
{
 return _EpsgForRelativeTest;
}

INLINE double CATFullTolerance::EpsilonForRelativeTest() const
{
 return _EpsilonForRelativeTest;
}

INLINE double CATFullTolerance::SquareEpsgForRelativeTest() const
{
 return _SquareEpsgForRelativeTest;
}

INLINE double CATFullTolerance::SquareEpsilonForRelativeTest() const
{
 return _SquareEpsilonForRelativeTest;
}

INLINE double CATFullTolerance::SqrtEpsgForRelativeTest() const
{
 return _SqrtEpsgForRelativeTest;
}

INLINE double CATFullTolerance::SqrtEpsilonForRelativeTest() const
{
 return _SqrtEpsilonForRelativeTest;
}


// Radian
INLINE CATAngle CATFullTolerance::EpsgForAngleTest() const
{
 return _EpsgForAngleTest;
}
// Radian
INLINE CATAngle CATFullTolerance::EpsilonForAngleTest() const
{
 return _EpsilonForAngleTest;
}

// nomenclature inadequate 
INLINE double CATFullTolerance::EpsgForSquareAngleTest() const
{
 return _EpsgForSquareAngleTest;
}
// nomenclature inadequate 

INLINE double CATFullTolerance::EpsilonForSquareAngleTest() const
{
 return _EpsilonForSquareAngleTest;
}

// nomenclature inadequate 
INLINE double CATFullTolerance::EpsgForSqrtAngleTest() const
{
return _EpsgForSqrtAngleTest;
}

// nomenclature inadequate 
INLINE double CATFullTolerance::EpsilonForSqrtAngleTest() const
{
return _EpsilonForSqrtAngleTest;
}

INLINE double CATFullTolerance::EpsgForLengthTest() const
{
 return _EpsgForLengthTest;
}
INLINE double CATFullTolerance::EpsilonForLengthTest() const
{
 return _EpsilonForLengthTest;
}

INLINE double CATFullTolerance::EpsgForSquareLengthTest() const
{
 return _EpsgForSquareLengthTest;
}
INLINE double CATFullTolerance::EpsilonForSquareLengthTest() const
{
 return _EpsilonForSquareLengthTest;
}

// nomenclature inadequate 
INLINE double CATFullTolerance::EpsgForSqrtLengthTest() const
{
 return _EpsgForSqrtLengthTest;
}
INLINE double CATFullTolerance::EpsilonForSqrtLengthTest() const
{
 return _EpsilonForSqrtLengthTest;
}


// Geometric
INLINE double CATFullTolerance::ModelSize() const
{
 return _ModelSize;
}
INLINE double CATFullTolerance::ModelInfinite() const
{
 return _ModelInfinite;
}

// Pow 1
INLINE CATAngle  CATFullTolerance::ResolutionForAngleTest() const
{
 return _ResolutionForAngleTest;
}

INLINE CATPositiveLength CATFullTolerance::ResolutionForLengthTest() const
{
 return _ResolutionForLengthTest;
}
/**
* @nodoc
*/
INLINE double CATFullTolerance::GetResolution(CATTolerance::ResolutionType iResolutionType) const
{
 if (iResolutionType == CATTolerance::CatC0)
    return ResolutionForLengthTest();
  else if (iResolutionType == CATTolerance::CatC1)
    return ResolutionForAngleTest();
  return _Curvature;
}

// Pow 2
// nomenclature inadequate 
INLINE double CATFullTolerance::ResolutionForSquareLengthTest() const
{
 return _ResolutionForSquareLengthTest;
}

// Pow 0.5
// nomenclature inadequate 
INLINE double CATFullTolerance::ResolutionForSqrtLengthTest() const
{
 return _ResolutionForSqrtLengthTest;
}


/**
* @nodoc
*/
INLINE CATAngle CATFullTolerance::LargeResolutionForAngleTest() const
{
 return _LargeResolutionForAngleTest;
}
/**
* @nodoc
*/
INLINE CATPositiveLength CATFullTolerance::LargeResolutionForLengthTest() const
{
 return _LargeResolutionForLengthTest;
}
/**
* @nodoc
*/
// nomenclature inadequate 
INLINE double CATFullTolerance::LargeResolutionForSquareLengthTest() const
{
 return _LargeResolutionForSquareLengthTest;
}
/**
* @nodoc
*/
// nomenclature inadequate 
INLINE double CATFullTolerance::LargeResolutionForSqrtLengthTest() const
{
 return _LargeResolutionForSqrtLengthTest;
}

/**
* @nodoc
*/
INLINE double CATFullTolerance::LargeEpsgForLengthTest() const
{
 return _LargeEpsgForLengthTest;
}
/**
* @nodoc
*/
INLINE CATAngle CATFullTolerance::LargeEpsgForAngleTest() const
{
 return _LargeEpsgForAngleTest;
}
/**
* @nodoc
*/
INLINE float CATFullTolerance::EpsilonfForRelativeTest() const
{
 return _EpsilonfForRelativeTest;
}

/**
* @nodoc
*/
INLINE double CATFullTolerance::LargeEpsgForRelativeTest() const
{
 return _LargeEpsgForRelativeTest;
}

//-----------------------------------------------------------------------------------------------
// Déclaration (et controle) d'accès aux tolérances complètes
//-----------------------------------------------------------------------------------------------
ExportedByYN000MAT const CATFullTolerance& CATGetFullTolerance(const CATTolerance& iTolerance);
#endif
/*  EB--  Recentrage CATTolerance et limitation des Friend class. CATRelativeTolerance inutile car inutilisée
//-----------------------------------------------------------------------------------------------
// Classe ne donnant accès qu'aux tolérances relatives
//-----------------------------------------------------------------------------------------------
class ExportedByYN000MAT CATRelativeTolerance: public CATTolerance
  {
   private:
   CATRelativeTolerance();
   // sont mises en privé les méthodes que l'on veut rendre inaccessibles

   private: // depend du scale 
   INLINE double GetScale() const;
   //
   INLINE double GetSquareScale() const;
   INLINE double GetSqrtScale() const;

   // Mathematic
   // Not-scaled values
   public:
   INLINE double Infinite() const;

   INLINE double EpsgForRelativeTest() const;

   INLINE double EpsilonForRelativeTest() const;

   INLINE double SquareEpsgForRelativeTest() const;

   INLINE double SquareEpsilonForRelativeTest() const;

   INLINE double SqrtEpsgForRelativeTest() const;
   INLINE double SqrtEpsilonForRelativeTest() const;

   public:
   // Radian
   INLINE CATAngle EpsgForAngleTest() const;
   // Radian
   INLINE CATAngle EpsilonForAngleTest() const;

   private: // nomenclature inadequate 
   INLINE double EpsgForSquareAngleTest() const;
   private: /* nomenclature inadequate 

   INLINE double EpsilonForSquareAngleTest() const;
   private: /* nomenclature inadequate 
   INLINE double EpsgForSqrtAngleTest() const;
   private: /* nomenclature inadequate 
   INLINE double EpsilonForSqrtAngleTest() const;
   private: /* depend du scale 
   INLINE double EpsgForLengthTest() const;
   INLINE double EpsilonForLengthTest() const;
   INLINE double EpsgForSquareLengthTest() const;
   INLINE double EpsilonForSquareLengthTest() const;

   private: /* nomenclature inadequate 
   INLINE double EpsgForSqrtLengthTest() const;
   INLINE double EpsilonForSqrtLengthTest() const;


   // Geometric
   private: /* depend du scale 
   INLINE double ModelSize() const;
   private: /* depend du scale 
   INLINE double ModelInfinite() const;

   public:
   // Pow 1
   INLINE CATAngle  ResolutionForAngleTest() const;

   private: // depend du scale  
   INLINE CATPositiveLength ResolutionForLengthTest() const;
   private: // depend du scale  
   
   INLINE double GetResolution(CATTolerance::ResolutionType iResolutionType) const;

   // Pow 2
   private: // nomenclature inadequate 
   INLINE double ResolutionForSquareLengthTest() const;

   // Pow 0.5
   private: // nomenclature inadequate 
   INLINE double ResolutionForSqrtLengthTest() const;

   public:
   INLINE CATAngle LargeResolutionForAngleTest() const;
   
   private: // depend du scale 
   INLINE CATPositiveLength LargeResolutionForLengthTest() const;
   
   private: // nomenclature inadequate  
   INLINE double LargeResolutionForSquareLengthTest() const;
   
   private: // nomenclature inadequate 
   INLINE double LargeResolutionForSqrtLengthTest() const;
   private: // depend du scale 
   
   INLINE double LargeEpsgForLengthTest() const;
   
   public:
   INLINE CATAngle LargeEpsgForAngleTest() const;
   
   INLINE float EpsilonfForRelativeTest() const;

   INLINE double LargeEpsgForRelativeTest() const;
  };

//-----------------------------------------------------------------------------------------------
// depend du scale 
INLINE double CATRelativeTolerance::GetScale() const
{
 return _Scale;
}
//
INLINE double CATRelativeTolerance::GetSquareScale() const
{
 return _SquareScale;
}

INLINE double CATRelativeTolerance::GetSqrtScale() const
{
 return _SqrtScale;
}

// Mathematic
// Not-scaled values
INLINE double CATRelativeTolerance::Infinite() const
{
 return _Infinite;
}

INLINE double CATRelativeTolerance::EpsgForRelativeTest() const
{
 return _EpsgForRelativeTest;
}

INLINE double CATRelativeTolerance::EpsilonForRelativeTest() const
{
 return _EpsilonForRelativeTest;
}

INLINE double CATRelativeTolerance::SquareEpsgForRelativeTest() const
{
 return _SquareEpsgForRelativeTest;
}

INLINE double CATRelativeTolerance::SquareEpsilonForRelativeTest() const
{
 return _SquareEpsilonForRelativeTest;
}

INLINE double CATRelativeTolerance::SqrtEpsgForRelativeTest() const
{
 return _SqrtEpsgForRelativeTest;
}
INLINE double CATRelativeTolerance::SqrtEpsilonForRelativeTest() const
{
 return _SqrtEpsilonForRelativeTest;
}

// Radian
INLINE CATAngle CATRelativeTolerance::EpsgForAngleTest() const
{
 return _EpsgForAngleTest;
}
// Radian
INLINE CATAngle CATRelativeTolerance::EpsilonForAngleTest() const
{
 return _EpsilonForAngleTest;
}

// nomenclature inadequate 
INLINE double CATRelativeTolerance::EpsgForSquareAngleTest() const
{
 return _EpsgForSquareAngleTest;
}
// nomenclature inadequate 

INLINE double CATRelativeTolerance::EpsilonForSquareAngleTest() const
{
 return _EpsilonForSquareAngleTest;
}
// nomenclature inadequate 
INLINE double CATRelativeTolerance::EpsgForSqrtAngleTest() const
{
return _EpsgForSqrtAngleTest;
}
// nomenclature inadequate 
INLINE double CATRelativeTolerance::EpsilonForSqrtAngleTest() const
{
return _EpsilonForSqrtAngleTest;
}
// depend du scale 
INLINE double CATRelativeTolerance::EpsgForLengthTest() const
{
 return _EpsgForLengthTest;
}
INLINE double CATRelativeTolerance::EpsilonForLengthTest() const
{
 return _EpsilonForLengthTest;
}
INLINE double CATRelativeTolerance::EpsgForSquareLengthTest() const
{
 return _EpsgForSquareLengthTest;
}
INLINE double CATRelativeTolerance::EpsilonForSquareLengthTest() const
{
 return _EpsilonForSquareLengthTest;
}

// nomenclature inadequate 
INLINE double CATRelativeTolerance::EpsgForSqrtLengthTest() const
{
 return _EpsgForSqrtLengthTest;
}
INLINE double CATRelativeTolerance::EpsilonForSqrtLengthTest() const
{
 return _EpsilonForSqrtLengthTest;
}


// Geometric
// depend du scale 
INLINE double CATRelativeTolerance::ModelSize() const
{
 return _ModelSize;
}
// depend du scale 
INLINE double CATRelativeTolerance::ModelInfinite() const
{
 return _ModelInfinite;
}

// Pow 1
INLINE CATAngle  CATRelativeTolerance::ResolutionForAngleTest() const
{
 return _ResolutionForAngleTest;
}

// depend du scale 
INLINE CATPositiveLength CATRelativeTolerance::ResolutionForLengthTest() const
{
 return _ResolutionForLengthTest;
}
// depend du scale 
INLINE double CATRelativeTolerance::GetResolution(CATTolerance::ResolutionType iResolutionType) const
{
 if (iResolutionType == CATTolerance::CatC0)
    return ResolutionForLengthTest();
  else if (iResolutionType == CATTolerance::CatC1)
    return ResolutionForAngleTest();
  return _Curvature;
}

// Pow 2
// nomenclature inadequate 
INLINE double CATRelativeTolerance::ResolutionForSquareLengthTest() const
{
 return _ResolutionForSquareLengthTest;
}

// Pow 0.5
// nomenclature inadequate 
INLINE double CATRelativeTolerance::ResolutionForSqrtLengthTest() const
{
 return _ResolutionForSqrtLengthTest;
}

INLINE CATAngle CATRelativeTolerance::LargeResolutionForAngleTest() const
{
 return _LargeResolutionForAngleTest;
}
// depend du scale 
INLINE CATPositiveLength CATRelativeTolerance::LargeResolutionForLengthTest() const
{
 return _LargeResolutionForLengthTest;
}
// nomenclature inadequate  // nomenclature inadequate 
INLINE double CATRelativeTolerance::LargeResolutionForSquareLengthTest() const
{
 return _LargeResolutionForSquareLengthTest;
}
// nomenclature inadequate  // nomenclature inadequate 
INLINE double CATRelativeTolerance::LargeResolutionForSqrtLengthTest() const
{
 return _LargeResolutionForSqrtLengthTest;
}
// depend du scale 
INLINE double CATRelativeTolerance::LargeEpsgForLengthTest() const
{
 return _LargeEpsgForLengthTest;
}
INLINE CATAngle CATRelativeTolerance::LargeEpsgForAngleTest() const
{
 return _LargeEpsgForAngleTest;
}
INLINE float CATRelativeTolerance::EpsilonfForRelativeTest() const
{
 return _EpsilonfForRelativeTest;
}

INLINE double CATRelativeTolerance::LargeEpsgForRelativeTest() const
{
 return _LargeEpsgForRelativeTest;
}

//-----------------------------------------------------------------------------------------------
// Déclaration d'accès aux tolérances relatives
//-----------------------------------------------------------------------------------------------
ExportedByYN000MAT const CATRelativeTolerance& CATGetRelativeTolerance(const CATTolerance& iTolerance);
*/
 
#endif
