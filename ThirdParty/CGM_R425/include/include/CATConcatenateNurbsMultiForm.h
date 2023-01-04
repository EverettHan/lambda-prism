// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATConcatenateNurbsMultiForm  
//
//=============================================================================
// Jan. 99  Creation                          DHN
//=============================================================================
#ifndef CATConcatenateNurbsMultiForm_H 
#define CATConcatenateNurbsMultiForm_H 
//
#include "YP00IMPL.h"
#include "CATDataType.h"
//
#include "CATTolerance.h"
class CATFrFNurbsMultiForm;
//
ExportedByYP00IMPL
void CATConcatenateNurbsMultiForm(const double &iMaxDeviation,
				  CATFrFNurbsMultiForm **Tab_in, 
				  const CATLONG32 &Nb_in,
				  CATFrFNurbsMultiForm **&Tab_out, 
				  CATLONG32 *&oNb_Concatenated, CATLONG32 &Nb_out
                  ,const CATTolerance & iTolObject =CATGetDefaultTolerance()
                  
                  );

#endif


