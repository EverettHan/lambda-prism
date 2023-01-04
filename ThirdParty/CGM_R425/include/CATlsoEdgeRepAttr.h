// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2018
// ................................
//
// VB7
//
//Edge visu in NCGM
//-----------------------------
//A. Thickness
// 1 <= iThickness <= 8 otherwise throw
// 1=0.13f
// 2=0.35f;
// 3=0.70f;
// 4=1.00f;
// 5=1.40f;
// 6=2.00f;
// 7=2.30f;
// 8=2.60f;
//-----------------------------
//B. Type
// 1 :  solid</li>
// 2 :  dotted</li>
// 3 :  dashed</li>
// 4 :  dot-dashed</li>
// 5 :  phantom</li>
// ----------------------------------------------------------------------------//


#ifndef CATlsoEdgeRepAttr_H
#define CATlsoEdgeRepAttr_H

#include "CATCGMAttribute.h"
#include "CATBoolean.h"
#include "PersistentCell.h"

class CATEdge;


//@nocgmitf
class ExportedByPersistentCell CATlsoEdgeRepAttr : public CATCGMAttribute
{

public: 

  CATCGMDeclareAttribute(CATlsoEdgeRepAttr, CATCGMAttribute);

  CATlsoEdgeRepAttr(CATEdge & iEdge, unsigned int iThickness, unsigned int iLineType);

  unsigned int GetThickness() const;

  unsigned int GetLineType() const;

  virtual ~CATlsoEdgeRepAttr();

  void Dump( CATCGMOutput & os );

protected:
  //Default constructor
  CATlsoEdgeRepAttr(); 

private:
  
  unsigned int _Thickness;
  unsigned int _LineType;

};

#endif

