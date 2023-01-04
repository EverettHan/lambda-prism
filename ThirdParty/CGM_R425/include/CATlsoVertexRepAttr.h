// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2018
// ................................
//
// LAP
//
//Vertex visu in NCGM
//-----------------------------

// ----------------------------------------------------------------------------//


#ifndef CATlsoVertexRepAttr_H
#define CATlsoVertexRepAttr_H

#include "CATCGMAttribute.h"
#include "CATBoolean.h"
#include "PersistentCell.h"

class CATVertex;


//@nocgmitf
class ExportedByPersistentCell CATlsoVertexRepAttr : public CATCGMAttribute
{

public: 

  CATCGMDeclareAttribute(CATlsoVertexRepAttr, CATCGMAttribute);

  CATlsoVertexRepAttr(CATVertex & iVertex, unsigned int iVisible, unsigned int iSymbol = 5/*FULLCIRCLE*/);

  void SetVisible(const unsigned int iVisible);
  void SetSymbol(const unsigned int iSymbol);

  unsigned int GetVisible() const;
  unsigned int GetSymbol() const;

  virtual ~CATlsoVertexRepAttr();

  void Dump( CATCGMOutput & os );

protected:
  //Default constructor
  CATlsoVertexRepAttr(); 

private:
  
  unsigned int _Visible;

  unsigned int _Symbol;

};

#endif

