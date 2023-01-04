#ifndef ListOfListOfIntegers_h
#define ListOfListOfIntegers_h

#include "ExportedByCATTopologicalObjects.h"

class CATCGMStream;

class ExportedByCATTopologicalObjects ListOfListOfIntegers
{
public:

  static ListOfListOfIntegers * Create();

  //The Nth list will contain all values from 1 to N
  static ListOfListOfIntegers * CreateTriangular(int iNbLists);

  virtual void NewList() = 0;

  virtual void AppendToLastList(int iInteger) = 0;

  virtual int GetNbElementsInList(int iListIndex) = 0;

  virtual int GetElement(int iListIndex, int iElementIndex) = 0;

  virtual int GetNbLists() = 0;

  virtual void AddRef() = 0;

  virtual void Release() = 0;

  static void Stream(ListOfListOfIntegers * iTable, CATCGMStream & oStr);

  static ListOfListOfIntegers * Unstream(CATCGMStream & iStr);

protected:

  ListOfListOfIntegers();

  //call Release!
  virtual ~ListOfListOfIntegers();

private:

  //not implemented yet
  ListOfListOfIntegers(const ListOfListOfIntegers &);

};

#define ListOfListOfIntegers_ListBegin(Table, ListIndex, VALUE) \
{ \
  int VALUE##ElementIndex; \
  int VALUE##NbElementsInList = (Table).GetNbElementsInList(ListIndex); \
  for (VALUE##ElementIndex = 1; VALUE##ElementIndex <= VALUE##NbElementsInList; VALUE##ElementIndex++) \
  { \
    int VALUE = (Table).GetElement(ListIndex, VALUE##ElementIndex);

#define ListOfListOfIntegers_ListEnd \
  } \
}



#endif
