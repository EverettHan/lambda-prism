// COPYRIGHT DASSAULT SYSTEMES 2003
#ifndef CATSubdIntersectingFunction_H
#define CATSubdIntersectingFunction_H
/** @CAA2Required */
class CATFace;

typedef enum
{
   CATSubdIntersectionDisjoint = -1 ,
   CATSubdIntersectionUnknown  =  0 ,
   CATSubdIntersectionOverlap      
} 
CATSubdIntersectionType;

typedef CATSubdIntersectionType (*IntersectingFunction)(CATFace*, CATFace*);

#endif
