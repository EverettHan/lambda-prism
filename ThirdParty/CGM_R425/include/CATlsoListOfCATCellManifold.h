#ifndef CATlsoListOfCATCellManifold_H
#define CATlsoListOfCATCellManifold_H

#include "PersistentCell.h"
#include "CATGMList.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATFace.h"

class CATCellManifold;
class CATCellHashTable;

class ExportedByPersistentCell CATlsoListOfCATCellManifold : public CATGMList<CATCellManifold>
{

public : 

   CATlsoListOfCATCellManifold(int iSize = 0);
   CATlsoListOfCATCellManifold(const ListPOfCATCellManifold & iCMList);
   virtual ~CATlsoListOfCATCellManifold();

 
  // virtual void DeleteElem(void * iElem); 
  // virtual void * CreateElement(void * iElem) const;
  // virtual void AppendInObjectList ( void *iAdd ); // Par default Append dans la list PV de CATlsoList.
  // virtual void * GetFromObjectList(int iPos) const; 


   CATCellManifold * Get(int iPos) const;
   CATCellManifold * operator[](int iPos) const;
   void Append ( CATCellManifold *iAdd );
   void Append ( const CATlsoListOfCATCellManifold & iConcat );
   void RemoveAll();

   CATCellHashTable * GetAllCell(int idim = -1);

   void GetFaces(ListPOfCATFace & oResultList);
};

#endif
