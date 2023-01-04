//====================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//====================================================================
//
// CATSobDetail.h
//
//====================================================================
//
// Usage notes: Classe représentant un unique détail qui est rattaché
//              à un vertex du maillage subdivisé
//
//====================================================================
// April,     2008 : RAQ : Ajout AddDetailValue
// October,   2004 : RAQ : Optimisation mémoire
// Marsh,     2004 : RAQ : Création
//====================================================================
#ifndef CATSobDetail_H
#define CATSobDetail_H

#include "CATSobObjects.h"


class ExportedByCATSobObjects CATSobDetail
{
public:

/**
 * Constructs a single detail from an index in the appropriate
 * level of details and a detail vector
 *
 * @param iIndex
 * The index of the detail in the level of details it belongs to
 * @param iDetailValue
 * An array of 3 double containing the detail vector coordinates
 **/
  CATSobDetail(const int iIndex, const double* iDetailValue);

/**
 * @nodoc
 **/
  ~CATSobDetail();

/**
 * Gets the index of this detail in the level of details it belongs to
 *
 * @return
 * The index
 **/
  int GetIndex();

/**
 * Sets the index of this detail in the level of details it belongs to
 **/
  void SetIndex(const int iIndex);

/**
 * Gets the detail value attached to 'this'
 *
 * @return
 * A pointer to an array of 3 double containing the detail vector coordinates
 **/
  double* GetDetailValue();

/**
 * Sets the detail value for 'this'
 * 
 * @param iDetailValue
 * A pointer to an array of 3 double containing the detail vector coordinates
 *
 * @return
 * 1 if some problems occured, 0 else
 **/
  int SetDetailValue(const double* iDetailValue);
  
/**
 * Adds a value to 'this' detail.
 * 
 * @param iDetailToAdd
 * A pointer to an array of 3 double containing the detail vector coordinates to add.
 *
 * @return
 * 1 if some problems occured, 0 else
 **/
  int AddDetailValue(const double* iDetailToAdd);

/**
 * Gets the next detail after 'this' in the cuurent level of details
 *
 * @return
 * A pointer to the next detail, 0 if none exists
 **/
  CATSobDetail* GetNextDetail();
  
/**
 * Sets the next detail after this in the current level of details
 *
 * @param iNextDetail
 * A pointer to a CATSobDetail object
 *
 * @return
 * 1 if some problems occured, 0 else
 **/
  int SetNextDetail(CATSobDetail* iNextDetail);


private:
  //Copy constructor and equal operator
  CATSobDetail(CATSobDetail&);
  CATSobDetail& operator=(CATSobDetail&);

  //Data
  double _DetailValue[3];
  int _Index;
  CATSobDetail* _NextDetail;
};


inline int CATSobDetail::GetIndex()
{
  return _Index;
}

inline void CATSobDetail::SetIndex(const int iIndex)
{
  _Index=iIndex;
}


inline CATSobDetail* CATSobDetail::GetNextDetail()
{
  return _NextDetail;
}


inline double* CATSobDetail::GetDetailValue()
{
  return &_DetailValue[0];
}


#endif

