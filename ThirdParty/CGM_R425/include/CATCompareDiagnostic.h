#ifndef CATCompareDiagnostic_h
#define CATCompareDiagnostic_h

//#define W94DBG //Decomment this line to activate debug code

#include "ExportedByCATTopologicalObjects.h"
#include "CATBaseUnknown.h"
#include "CATCGMOutput.h"
#include "CATGeometry.h"

class CATLISTP(CATGeometry);

typedef CATLISTP(CATGeometry) ListPOfCATGeometry;

typedef enum {
  Geometry_Difference,              //Geometric difference found
  Orientation_Difference,           //Orientation difference found
  Lower_Dim_Content_Difference,     //Quantity difference of element of LDC found
  Unexpected_Difference,            //Unexpected difference found
  No_Equivalent_Difference,         //Equivalent not found
  Type_Difference,                  //Types analyzed aren't the same
  Order_Difference,                 //Order of LDC topologies is different
  Not_Set_Difference                //Difference not set
} CATCompareDiagnosticOutcome;

class ExportedByCATTopologicalObjects CATCompareDiagnostic : public CATBaseUnknown
{
public:
  /**
   * @nodoc
   * Destructor.
  */
  CATCompareDiagnostic();

  /**
   * @nodoc
   * Destructor.
  */
  ~CATCompareDiagnostic();

  /**
   * @nodoc
  */
  CATCompareDiagnosticOutcome GetDifferenceType();

  /**
   * @nodoc
  */
  void Dump (CATCGMOutput & os);

  /**
   * @nodoc
  */
  void AddStack(CATGeometry *iGeometry1, CATGeometry *iGeometry2, CATCompareDiagnosticOutcome differenceType = Not_Set_Difference);

  /**
  * @nodoc
  */
  void SetDifferenceType(CATCompareDiagnosticOutcome outcome);

  /**
  * @nodoc
  */
  CATBoolean DoesThisGeometryBelongsToThisDiagnostic(CATGeometry *geometry1, CATGeometry *geometry2);

  /**
  * @nodoc
  */
  void SetWritingState(CATBoolean state);

protected:
  
private:
  ListPOfCATGeometry          _StackOfGeometries1;
  ListPOfCATGeometry          _StackOfGeometries2;
  CATCompareDiagnosticOutcome _DifferenceType;
  CATBoolean                  _WritingEnabled;     /* When it's false, prevents the writing in the
                                                      stack (for O(n2) loops in CATCompareTopoContext) */

};

#endif


