#ifndef CATGMLiveExtrusionUtilities_H
#define CATGMLiveExtrusionUtilities_H

#include "CATCGMNewArray.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATGMLiveExtrusionPrimitive.h"
#include "CATMathVector.h"

#include "PersistentCell.h"

class CATSoftwareConfiguration;
class CATVertex;

class ExportedByPersistentCell CATGMLiveExtrusionUtilities
{
public:
    CATCGMNewClassArrayDeclare;      // Pool allocation

    CATGMLiveExtrusionUtilities(CATSoftwareConfiguration * iConfig);
    virtual ~CATGMLiveExtrusionUtilities();

    static CATBoolean GetSupportAndExitVertices(
            ListPOfCATFace const  & iExtrudeFaces,
            ListPOfCATFace const  & iSupportFaces,
            ListPOfCATFace const  & iSupportDecoFaces,
            ListPOfCATFace const  & iEndFaces,
            ListPOfCATFace const  & iEndDecoFaces,
            ListPOfCATFace const  & iExitFaces,
            ListPOfCATFace const  & iExitDecoFaces,
            CATVertex            *& oSupportVertex,
            CATVertex            *& oExitVertex);

    static CATMathVector GetExtrusionDirectionFromSupportToExit(
            CATMathVector const & iRoughDirection,
                                                                 ListPOfCATFace const & iExtrudeFaces,
                                                                 ListPOfCATFace const & iSupportFaces,
                                                                 ListPOfCATFace const & iSupportDecoFaces,
                                                                 ListPOfCATFace const & iEndFaces,
                                                                 ListPOfCATFace const & iEndDecoFaces,
                                                                 ListPOfCATFace const & iExitFaces,
                                                                 ListPOfCATFace const & iExitDecoFaces);

private:

    CATSoftwareConfiguration * _SoftwareConfiguration;
};

#endif 

