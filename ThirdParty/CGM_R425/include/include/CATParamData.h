/* -*-c++-*-*/
#ifndef CATParamData_H
#define CATParamData_H
/** @CAA2Required */
//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
// CATParamData 
//
/**
 * Class handling the local parameter on curves and surfaces.
 *<br>This object contains the number of the element <tt>n</tt>
 *(which might be the number of the arc on a curve or the patch on a surface) 
 * and the local position <tt>p</tt> on this arc.
 */
// 
//  Main method ;  operator < , <= , > , >=, == , !=
//  
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// INLINE Functions   : No
//=============================================================================
//
// History
//
// Jun. 97   Jose CHILLAN (jch)    Creation
// Dec. 97   C. Keribin            Documentation.             
//
//=============================================================================
#include "CATDataType.h"
#include "CATMathInline.h"

class CATParamData
{
 public:
  
//DG realignement
//  CATLONG32    PartNumber;
//  double  LocalParam;

  double  LocalParam;

  // One can access the data in its own signification
  // according to whether it relates to a curve or a surface.
  union
    {
      CATLONG32    PartNumber;
      CATLONG32    PatchNumber;
      CATLONG32    ArcNumber;
    };

  /*** @nodoc */
  INLINE CATParamData(CATLONG32 iPartNumber, double iLocalParam);

  /*** @nodoc */
  INLINE CATParamData();

  /*** @nodoc */
  INLINE CATParamData(const CATParamData& iRef); 

// Methods
   
/**
 * Defines the less than operator.
 *<br>Let <tt>Param1(n1,p1)</tt> and <tt>Param2(n2,p2)</tt> two CATParamDatas.
 *<br><tt> (Param1 < Param2) <=> ( (n1 < n2) or (n1==n2 and p1 < p2) )</tt>
 */
  INLINE CATLONG32 operator <  (const CATParamData &iComparedData) const;

/**
 * Defines the less than or equal to operator.
 *<br>Let <tt>Param1(n1,p1)</tt> and <tt>Param2(n2,p2)</tt> two CATParamDatas.
 *<br><tt> (Param1 <= Param2) <=> ( (n1 < n2) or (n1 == n2 and p1 <= p2) )</tt>
 */
  INLINE CATLONG32 operator <= (const CATParamData &iComparedData) const;

/**
 * Defines the greater than operator.
 *<br>Let <tt>Param1(n1,p1)</tt> and <tt>Param2(n2,p2)</tt> two CATParamDatas.
 *<br><tt> (Param1 > Param2) <=> ( (n1 > n2) or (n1 == n2 and p1 > p2) )</tt>
 */
  INLINE CATLONG32 operator >  (const CATParamData &iComparedData) const;

/**
 * Defines the greater than or equal to operator.
 *<br>Let <tt>Param1(n1,p1)</tt> and <tt>Param2(n2,p2)</tt> two CATParamDatas.
 *<br><tt> (Param1 >= Param2) <=> ( (n1 > n2) or (n1 == n2 and p1 >= p2) )</tt>
 */
  INLINE CATLONG32 operator >= (const CATParamData &iComparedData) const;

/**
 * Defines the logical equality.
 *<br>Let <tt>Param1(n1,p1)</tt> and <tt>Param2(n2,p2)</tt> two CATParamDatas.
 *<br><tt> (Param1 == Param2) <=> ( n1 == n2 and p1 == p2 )</tt>
 */
  INLINE CATLONG32 operator == (const CATParamData &iComparedData) const;

/**
 * Defines the logical non-equality.
 *<br>Let <tt>Param1(n1,p1)</tt> and <tt>Param2(n2,p2)</tt> two CATParamDatas.
 *<br><tt> (Param1 != Param2) <=> ( n1 != n2 or p1 != p2 )</tt>
 */
  INLINE CATLONG32 operator != (const CATParamData &iComparedData) const;
  
/**
 * Defines the operator equal
 */
  INLINE const CATParamData & operator = (const CATParamData & iCopiedParam);
  
};

// Converts a double and a local param into a CATParamData
#define CATConvertToParam(iPartNumber,iLocalParam) CATParamData(iPartNumber,iLocalParam)


//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE CATLONG32 CATParamData::operator < (const CATParamData &Compared) const
{
  CATLONG32 result = 0;
  if (PartNumber < Compared.PartNumber)
    {
      result = 1;
    }
  else 
    {
     if ((PartNumber == Compared.PartNumber) && ( LocalParam < Compared.LocalParam))
     {
      result = 1;
     }
    }
  return result;
}

INLINE CATLONG32 CATParamData::operator <= (const CATParamData &Compared) const
{
  CATLONG32 result = 0;
  if (PartNumber < Compared.PartNumber)
    {
      result = 1;
    }
  else { if ((PartNumber == Compared.PartNumber) && ( LocalParam <= Compared.LocalParam))
      {
        result = 1;
      }
    }
  return result;
}

INLINE CATLONG32 CATParamData::operator > (const CATParamData &Compared) const
{
  CATLONG32 result = 0;
  if (PartNumber > Compared.PartNumber)
    {
      result = 1;
    }
  else { if ((PartNumber == Compared.PartNumber) && ( LocalParam > Compared.LocalParam))
      {
        result = 1;
      }
     }
  return result;
}

INLINE CATLONG32 CATParamData::operator >= (const CATParamData &Compared) const
{
  CATLONG32 result = 0;
  if (PartNumber > Compared.PartNumber)
    {
      result = 1;
    }
  else { if ((PartNumber == Compared.PartNumber) && ( LocalParam >= Compared.LocalParam))
    {
      result = 1;
    }
    }
  return result;
}

INLINE CATLONG32 CATParamData::operator == (const CATParamData &Compared) const
{
  CATLONG32 result = 0;
  if ((PartNumber == Compared.PartNumber) && (LocalParam == Compared.LocalParam))
    {
      result = 1;
    }
  return result;
}

INLINE CATLONG32 CATParamData::operator != (const CATParamData &Compared) const
{
  CATLONG32 result = 0;
  if ((PartNumber != Compared.PartNumber) || (LocalParam != Compared.LocalParam))
    {
      result = 1;
    }
  return result;
}


INLINE const CATParamData & CATParamData::operator = (const CATParamData & Copied) 
{
  LocalParam = Copied.LocalParam;
  PartNumber = Copied.PartNumber;
  return * this;
}


INLINE CATParamData::CATParamData(CATLONG32 iPartNumber, double iLocalParam)  : PartNumber(iPartNumber), LocalParam(iLocalParam)
{
}

INLINE CATParamData::CATParamData()  : PartNumber(0), LocalParam(0.0)
{
}

INLINE CATParamData::CATParamData(const CATParamData& iRef)  : PartNumber(iRef.PartNumber), LocalParam(iRef.LocalParam)
{
}


#endif
