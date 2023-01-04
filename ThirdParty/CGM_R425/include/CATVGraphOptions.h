#ifndef CATVGraphOptions_H
#define CATVGraphOptions_H

//===================================================================
// CATVGraphOptions: options for processes using VGraph
//===================================================================

#include "CATMathematics.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATVGraphOptions;
extern ExportedByCATMathematics const CATVGraphOptions CATVGraphOptionsDefault;

class ExportedByCATMathematics CATVGraphOptions : public CATCGMVirtual
{
public:
  //------------------------------------------------------------------------------
  CATVGraphOptions(); // Default options
  CATVGraphOptions(const CATBoolean iAllowOverConstrainedInstance);
  virtual ~CATVGraphOptions();

  //------------------------------------------------------------------------------
  // Options
  //------------------------------------------------------------------------------
  void SetAllowOverConstrainedInstance(const CATBoolean iAllowOverConstrainedInstance = TRUE);
  CATBoolean GetAllowOverConstrainedInstance() const;

  //------------------------------------------------------------------------------
  // Stream/Unstream/Dump
  //------------------------------------------------------------------------------
  void Dump(ostream* iStream) const;
  CATVGraphOptions(const unsigned char* iUCharArray, int& ioPosition);
  void Stream(unsigned char*& oUCharArray, int& oLength) const;

private:
  CATBoolean _AllowOverConstrainedInstance;
};
#endif
