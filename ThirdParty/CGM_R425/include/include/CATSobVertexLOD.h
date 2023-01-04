//====================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//====================================================================
//
// CATSobVertexLOD.h
//
//====================================================================
//
// Usage notes: Noeud de type 'Vertex' dans l'arbre de détail
//
//====================================================================
// Marsh,     2004 : RAQ : Création
//====================================================================
#ifndef CATSobVertexLOD_H
#define CATSobVertexLOD_H

#include "CATSobObjects.h"


class ExportedByCATSobObjects CATSobVertexLOD
{
public:

/**
 * @nodoc
 **/
  virtual ~CATSobVertexLOD() {};

/**
 * Gets the detail value for the vertex in this level of details
 *
 * @return
 * A pointer to an array of 3 double
 **/
  virtual double* GetDetail() = 0;

/**
 * Sets the detail value for the vertex in this level of details
 * If a detail already exists it is overwritten.
 *
 * @param iDetailValue
 * A pointer to an array of 3 double containing the detail vector coordinates
 *
 * @return
 * 1 if some problems occured, 0 else
 **/
  virtual int SetDetail(const double* iDetailValue) = 0;

/**
 * Sets the detail value for the vertex in this level of details
 * If a vector detail already exists they are summed.
 *
 * @param iDetailToAdd
 * A pointer to an array of 3 double containing the detail vector coordinates
 *
 * @return
 * 1 if some problems occured, 0 else
 **/
  virtual int AddDetail(const double* iDetailToAdd) = 0;

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
  virtual CATSobVertexLOD* GetNextLOD() = 0;
  
/**
 * Sets the next level of details after 'this'
 *
 * @param iNextVertexLOD
 * A pointer to the next level of details
 *
 * @return
 * 1 if some problems oocured, 0 else
 **/
  virtual int SetNextLOD(CATSobVertexLOD* iNextVertexLOD) = 0;

};


#endif


