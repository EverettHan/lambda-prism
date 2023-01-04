#ifndef CATMathAttrDoubleArray_h
#define CATMathAttrDoubleArray_h

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "YN000FUN.h"

#include "CATMathAttribute.h"

class ExportedByYN000FUN CATMathAttrDoubleArray : public CATMathAttribute
   {
   private:
      char          * _id;
      const double  * _value;
      CATLONG32       _N;
      CATBoolean      _excl;

   public:
      CATMathAttrDoubleArray();
      CATMathAttrDoubleArray(CATMathAttrId id,
                             const CATLONG32 EltNb,
                             const double * value,
                             const CATLONG32 exclusive = 1);

      ~CATMathAttrDoubleArray();

      CATMathAttrId   GetType() const;
      const CATLONG32 GetSize() const;
      const double *  GetValue() const;
      CATBoolean   IsExclusive() const;
   };

#endif
