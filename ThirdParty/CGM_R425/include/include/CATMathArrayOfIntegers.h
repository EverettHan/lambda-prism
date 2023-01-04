#ifndef CATMathArrayOfIntegers_h
#define CATMathArrayOfIntegers_h

#include "MathGeo.h"
#include "CATCGMNewArray.h"
#include "CATDataType.h"

// COPYRIGHT DASSAULT SYSTEMES  2001
/**
 * Class representing an array of integers
 *
 * Useful for AreaFill operation (Drafting) 07/02/2002
 */

class ExportedByMathGeo CATMathArrayOfIntegers 
{
  public:
//----------------------------------------------------------  
//- Constructors
//----------------------------------------------------------
/** 
 * Constructs an empty array
 */ 
    CATMathArrayOfIntegers ();
/** 
 * Constructs a single value array
 */ 
    CATMathArrayOfIntegers (CATLONG32 iVal);
 /**
 * Copy constructor.
 */
    CATMathArrayOfIntegers (const CATMathArrayOfIntegers & iArrayToCopy);

 	/** @nodoc */
  CATCGMNewClassArrayDeclare;

//----------------------------------------------------------  
//  Destructor  
//----------------------------------------------------------  
    ~CATMathArrayOfIntegers ();

//----------------------------------------------------------  
//- Get/Set
//----------------------------------------------------------
/**
 * Get back the number of integers of the array
 */ 
    CATLONG32 GetSize () const;
/**
 * Get back the value of the index iIndex of the array : 0<=iIndex<Size.
 */ 
    CATLONG32 GetValue (CATULONG32 iIndex) const;

//----------------------------------------------------------  
//- Utilities
//----------------------------------------------------------
/**
 * Add an integer at current position
 */ 
    void Add (CATLONG32 iValue);

//----------------------------------------------------------  
//- Dump the grid : for debug purposes
//----------------------------------------------------------
/**
 * Dump the values of the array
 */ 
    void Dump () const;


  private:
//----------------------------------------------------------  
//- Datas
//----------------------------------------------------------
    CATULONG32 _NbIntegers, _SizeAlloc;
    CATLONG32 *_Val;
};

#endif
