//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//==========================================================================
// class CATNurbsDiagnostic
//==========================================================================
// May 2001   Creation                                            CCK-PRG
//==========================================================================
// This object is used in the contect of geometry transfer.
// It relates about one geometrical pathology that has been detected
// during the transfer of a nurbs element.
// 
// It provides with some information about the pathology that has been detected :
//      1/ the severity of the pathology :
//             - In spite of this pathology, this element can be translated 
//            into a V5 element. It is just a warning.
//             - This pathology prevent us from translating the element into V5,
//             - the check detected a special behavious and could not conclude.
//             We have a doubt. A precise check has to be performed.
//      2/ geometrical elements other information like arc number, parameter, ...
//      that would be useful if we can not repair the element.
//
//-----------------------------------------------------------------------------
typedef enum {
              CATGeomNurbsCrvDiag_Std=0,
              CATGeomNurbsCrvDiag_ArcTooShort,
              CATGeomNurbsCrvDiag_ExtNullTangent,
              CATGeomNurbsCrvDiag_CuspInsideAnArc,
              CATGeomNurbsCrvDiag_CuspAtArcsJunction,
              CATGeomNurbsCrvDiag_BadParametrisation,
              CATGeomNurbsCrvDiag_ControlPointsOutOfSpace,
              CATGeomNurbsCrvDiag_ControlPointsTooClose,
              CATGeomNurbsCrvDiag_CurveTooShort,
              CATGeomNurbsCrvDiag_ArcWithAutoIntersection,
              CATGeomNurbsCrvDiag_CrvWithAutoIntersection,
              CATGeomNurbsCrvDiag_PCurveOutOfSupport
             } CATGeomNurbsDiagType;

#include "CATListOfCATGeometries.h"

#include "YP00IMPL.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"

class ExportedByYP00IMPL CATNurbsDiagnostic  : public CATCGMVirtual
{
  public :
    virtual ~CATNurbsDiagnostic(){};
    
    // returns :
    //  0 if it just a warning
    //  1 for a strong error, no transfer
    //  -1 if we do not know, precise check have to be called.
    virtual CATLONG32 GetSeverity()=0;
};


