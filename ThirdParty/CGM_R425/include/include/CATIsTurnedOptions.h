#ifndef CATIsTurnedOptions_H
#define CATIsTurnedOptions_H

//===================================================================
// CATIsTurnedOptions: options for revolution detection
//===================================================================

#include "CATMathematics.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATIsTurnedOptions;
extern ExportedByCATMathematics const CATIsTurnedOptions CATIsTurnedOptionsDefault;

class ExportedByCATMathematics CATIsTurnedOptions : public CATCGMVirtual
{
public:
  //------------------------------------------------------------------------------
  CATIsTurnedOptions(); // Default options
  CATIsTurnedOptions(const CATBoolean iIncludeDisks, const short iRestrictToConvexity);
  virtual ~CATIsTurnedOptions();

  //------------------------------------------------------------------------------
  // Options
  //------------------------------------------------------------------------------
  void SetIncludeDisks(const CATBoolean iIncludeDisks = TRUE);
  CATBoolean GetIncludeDisks() const;
 
  //  1 --> Convex
  // -1 --> Concave
  //  0 --> Unknown (allow convex and concave)
  void SetRestrictToConvexity(const short iRestrictToConvexity = 0);
  short GetRestrictToConvexity() const;

  //------------------------------------------------------------------------------
  // Stream/Unstream/Dump
  //------------------------------------------------------------------------------
  void Dump(ostream* iStream) const;
  CATIsTurnedOptions(const unsigned char* iUCharArray, int& ioPosition);
  void Stream(unsigned char*& oUCharArray, int& oLength) const;

private:
  CATBoolean _IncludeDisks;
  short _RestrictToConvexity;
};
#endif
