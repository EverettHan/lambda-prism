//====================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//====================================================================
//
// CATSobFaceLOD.h
//
//====================================================================
//
// Usage notes: Noeud de type 'Face' dans l'arbre de détail
//
//====================================================================
// April,     2008 : RAQ : Ajout AddDetailAtPoint
// Marsh,     2004 : RAQ : Création
//====================================================================
#ifndef CATSobFaceLOD_H
#define CATSobFaceLOD_H

//Pour l'export
#include "CATSobObjects.h"

//Divers
#include "CATBoolean.h"


class CATSobDetail;

class ExportedByCATSobObjects CATSobFaceLOD
{
public:

/**
 * @nodoc
 */
  virtual ~CATSobFaceLOD() {};

/**
 * Gets the detail value for a given index in this level of details
 *
 * @param u
 * The first index in this level
 * @param v
 * The second index in this level
 *
 * @return
 * A pointer to an array of 3 double
 **/
  virtual double* GetDetailAtPoint(const int u, const int v) = 0;

/**
 * @nodoc
 **/
  virtual double* GetDetailAtPoint(const int iLinearIndex) = 0;

/**
 * Sets the detail value for a given index in this level of details
 * If a detail already exists it is overwritten.
 *
 * @param u
 * The first index in this level
 * @param v
 * The second index in this level
 * @param iDetailValue
 * A pointer to an array of 3 double containing the detail vector coordinates
 *
 * @return
 * 1 if some problems occured, 0 else
 **/
  virtual int SetDetailAtPoint(const int u, const int v, const double* iDetailValue) = 0;

/**
 * @nodoc
 **/
  virtual int SetDetailAtPoint(const int iLinearIndex, const double* iDetailValue) = 0;

/**
 * Adds a detail value for a given index in 'this' level of details.
 * If a vector detail already exists they are summed.
 *
 * @param u
 * The first index in this level
 * @param v
 * The second index in this level
 * @param iDetailToAdd
 * A pointer to an array of 3 double containing the detail vector coordinates
 *
 * @return
 * 1 if some problems occured, 0 else
 **/
  virtual int AddDetailAtPoint(const int u, const int v, const double* iDetailToAdd) = 0;

/**
 * @nodoc
 **/
  virtual int AddDetailAtPoint(const int iLinearIndex, const double* iDetailToAdd) = 0;

/**
 * Removes a detail for a given index in this level of details
 *
 * @param u
 * The first index in this level
 * @param v
 * The second index in this level
 *
 * @return
 * 1 if some problems occured, 0 else
 **/
  virtual int RemoveDetailAtPoint(const int u, const int v) = 0;

/**
 * @nodoc
 **/
  virtual int RemoveDetailAtPoint(const int iLinearIndex) = 0;

/**
 * Gets the value of the subdivision level for which this level
 * of details is to be taken into account
 *
 * @return
 * The value of the subdivision level
 **/
  virtual int GetLODLevel() = 0;
  
/**
 * Gets the next level of details after 'this'
 *
 * @return
 * A pointer to the next level of details, 0 if none exists
 **/
  virtual CATSobFaceLOD* GetNextLOD() = 0;
  
/**
 * Sets the next level of details after 'this'
 *
 * @param iNextFaceLOD
 * A pointer to the next level of details
 *
 * @return
 * 1 if some problems oocured, 0 else
 **/
  virtual int SetNextLOD(CATSobFaceLOD* iNextFaceLOD) = 0;

/**
 * Gets the first detail object in this level of details
 *
 * @return
 * A pointer to the first detail object of this level, 0 if none exists
 **/
  virtual CATSobDetail* GetFirstDetailInLOD() = 0;

/**
 * Checks whether 'this' level is empty.
 *
 * @return
 * TRUE if 'this' level contains no details.
 **/
  virtual CATBoolean IsEmpty() const = 0;

};


#endif


