#ifndef CATechFormat_h
#define CATechFormat_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/** @CAA2Required */
/**
* @level Private
* @usage U1
*    GMTk journaling idea is to collect an history of operations
*        in one zip auto-described file with data meaningfull for a GM support.
*    It enables some preliminary analysis of a scenario focusing on GM domain.
*     (forcasting availability inside CGMOFF/CGMPRJ workspace is about collect of end week 42 of year 2010)
* 
*    Objective is to ease some debug/support with application based upon GMTk.
*        by mean of an auto-described zip files containing a all-in-one list of GM operations or data.
*     Remarks 1) not all GM operations may have implemented GMTkJournaling mecanisms (with underlining CGMReplay file).
*     Remarks 2) GMTkJournaling is also gathering information about scenarios
*                   (some statistics on I/O operations, or intermediate operation data (CATCX_NCGM))
* 
*   About some known limitations : structure of zip may changed at any software iteration.
*       -each type of file has its own data compatibility management (NCGM,CGMReplay)
*       -CSV file has no defined compatibility management 
*/
//------------------------------------------------------------ 
// Small metadata for genuine Extract/Redo infrastructure
// DO NOT CHANGE VALUE (PERSISTENCY MANDATORY)
//------------------------------------------------------------ 

#include "CATDataType.h"
#include "CATUnicodeString.h"

struct CATechFormatDataLink
{
    //Default consturctor
    CATechFormatDataLink() : _IdSession(0) {};

    /**
    * Parametrized constructor
    * @param iIdSession : Session id which can be used to identify the file
    * @param iDataType : Type of the file that is streamed
    * @param iBaseName : Filename for the file
    */
    CATechFormatDataLink(CATULONG32 iIdSession, 
                         const CATUnicodeString & iDataType, 
                         const CATUnicodeString & iBaseName)
                        : _DataType(iDataType), 
                        _BaseName(iBaseName), 
                        _IdSession(iIdSession) 
    {};

    /*
    * Gets the complete filename along with its extension for
    * streaming the same into the Phoenix.xml file
    * @param oDataLink : Filename with extension
    */
    void GetDataLink(CATUnicodeString & oDataLink)
    {
        oDataLink = _BaseName;
        oDataLink.Append(".");
        oDataLink.Append(_DataType);
    }

    CATUnicodeString _DataType;
    CATUnicodeString _BaseName;
    CATULONG32       _IdSession;
};

/**
* CATechFormat : enumeration of atomic format .
*/
enum CATechFormat                           //Associated Types
{
    CATechFormat_NoValue       =   0,
    CATechFormat_Int32         =   1,       //int, CATLONG32
    CATechFormat_Int64         =   2,       //CATINTPTR64(64 bits)
    CATechFormat_Real64        =   3,       //double
    CATechFormat_Real32        =   4,       //float
    CATechFormat_CATUnicode    =   5,       //CATUnicodeString
    CATechFormat_Int16         =   6,       //short
    CATechFormat_byte8         =   7,       //unsigned char, CATBoolean

    CATechFormat_Pt3D          =  8,        //CATMathPoint
    CATechFormat_Tranfo3D      =  9,        //CATMathTransformation
    CATechFormat_Box2D         =  10,       //CATMathBox2D
    CATechFormat_Vector3D      =  11,       //CATMathVector

    CATechFormat_Instance3D    =  12,       //For CATICGMObject + CATMathTransformation

    CATechFormat_Phoenix       = 13,        //Phoenix internal type used for indicating
                                            //the beginning of a phoenix transaction in phoenix.xml

    CATechFormat_Variant       = 14,        //Phoenix internal type defined for indicating a stored attribute
                                            //(composed of other CATechFormats and their associated values) 
                                            //in the phoenix.xml

    CATechFormat_CATechGet     = 15,
    CATechFormat_CATICGMObject = 16,        //Type for capturing information relevant to CATICGMObjects usually
                                            //associated with a CATechFormat_Instance3D in the phoenix.xml

    CATechFormat_CATGMAdapter  = 17,

    CATechFormat_Attribute      = 18,
    CATechFormat_CATechDataLink = 19,       //Type for dumping information related to a file which is dumped
                                            //in same directory as Phoenix.xml.

    CATechFormat_CATCGMRefCounted = 21,

    CATechFormat_CATREP        = 22,        //Type defined for managing CATRep's
    CATechFormat_CATPOLYBODY   = 23,        //Type defined for managing CATPolyBody's
    CATechFormat_MODELV4       = 24,        //Type defined for managing V4 model's
    CATechFormat_CATBVHTREE    = 25,        //Type defined for managing CATBVHTree's
    CATechFormat_POLYGON2D     = 26,        //Type defined for managing CATPolyPolygon2D's

    CATechFormat_Unset         = 66  

};


#endif
