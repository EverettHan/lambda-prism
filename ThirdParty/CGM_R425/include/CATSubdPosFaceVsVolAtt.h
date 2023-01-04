#ifndef CATSubdPosFaceVsVolAtt_H
#define CATSubdPosFaceVsVolAtt_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//============================================================================
// classe CATSubdPosFaceVsVolAtt
//
// C'est une classe d'attributs poses sur des faces qui servent a declarer
// logiquement un positionnement face/volume (interieur ou exterieur). Cette
// classe est utilisee dans le booleen, pour optimisation dans shell.
//
// This is an attribute class. These attributes are put on faces to declare
// their position (in or out) with respect a volume. This class is used in 
// the boolean code, to optimize the shelling algorithm.
// 
//============================================================================
// Fonctionnement
//
// Pendant l'algo de shell, on pose un attribut CATSubdPosFaceVsVolAtt sur l'offset
// d'une face d'origine, avec un flag 1 pour la peau interne, et 2 pour la peau
// externe.
// 
// Plus tard, dans le booleen, certains tests face/volume peuvent etre ainsi 
// resolus logiquement. 
// 
//
//============================================================================
// Sep. 98   Creation                                            L. Alt
//============================================================================
#include "CATSubdPosition.h"
#include "BOOLEAN.h"
#include "CATMathInline.h"

class CATFace;

class ExportedByBOOLEAN CATSubdPosFaceVsVolAtt 
{
  public :

      CATSubdPosFaceVsVolAtt( CATFace * iInitFace, short iInOrOut );
    ~CATSubdPosFaceVsVolAtt();

    // Returns 1 for inner shell and 2 for outer shell
    INLINE short     GetInOrOut(); 
    INLINE CATFace * GetInitFace();
    CATSubdPosition  GetPositionVs( CATSubdPosFaceVsVolAtt * iOtherAttribute );

  private : 

    CATFace * _InitFace;
    short     _InOrOut; // vaut 1 pour in et 2 pour out

};

INLINE short CATSubdPosFaceVsVolAtt::GetInOrOut() { return( _InOrOut ); }

INLINE CATFace * CATSubdPosFaceVsVolAtt::GetInitFace() { return( _InitFace ); }

#endif
