//======================================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//======================================================================================
//
// CATSobVertexOnEdge.h
//
//======================================================================================
//
// Usage notes: Class representing a Vertex on Edge object.
//              A CATSobVertexOnEdge object is not a real vertex in a sense that
//              it doesn't modifiy the topology of the mesh. It just adds informations
//              for the subdivision.
//
//======================================================================================
// November,  2004 : RAQ : Création
//======================================================================================
#ifndef CATSobVertexOnEdge_H
#define CATSobVertexOnEdge_H

#include "CATSobObjects.h"

#include "CATSobDiag.h"

#include "CATBoolean.h"

class CATSobVertex;
class CATSobEdge;
class CATSobFace;

//--------------------------------------------------------
// Some enums used to identify on which side of the edge
// a CATSobVertexOnEdge is located:
//
enum ExportedByCATSobObjects CATSobVertexOnEdgeLocation
{
  // The vertex is located on the direct face of the edge
  VERTEX_ON_DIRECT_FACE,

  // The vertex is located on the invert face of the edge
  VERTEX_ON_INVERT_FACE,

  // The vertex is located on both the direct and the invert face of the edge
  VERTEX_ON_BOTH_FACES
};
//--------------------------------------------------------


class ExportedByCATSobObjects CATSobVertexOnEdge
{
public:

/**
 * Constructs a CATSobVertexOnEdge object
 *
 * @param iEdge
 * The edge on which 'this' is lying on
 * @param iRatioOnEdge
 * A ratio used to locate the point on the edge. The ratio is such that:
 * 0 < iRatioOnEdge < 1
 * The smaller iRatioOnEdge is, the more it is close to the edge's StartVertex
 * @param iVertexLocation
 * Indicates on which side of the edge 'this' is located
 **/
  CATSobVertexOnEdge(CATSobEdge* iEdge, const double iRatioOnEdge, CATSobVertexOnEdgeLocation iVertexLocation);

/**
 * @nodoc
 **/
  virtual ~CATSobVertexOnEdge();

/**
 * Attach a CATSobVertex on 'this' respect to a face
 *
 * @param iVertex
 * The CATSobVertex to attach to 'this'
 * @param iFace
 * The face on which the vertex is to be attached
 *
 * @return
 * CATSobDiag_OK if no errors, else see CATSobDiag.h
 **/
  CATSobDiag Add(CATSobVertex* iVertex, CATSobFace* iFace);

/**
 * Gets the ratio of 'this' on the edge containing 'this'
 *
 * @return
 * The ratio, 0 < Ratio < 1
 **/
inline  double GetRatio() const { return _Ratio; }

/**
 * Indicates on which side of the edge 'this' is located
 *
 * @param iVertexLocation
 * The location of the vertex, ie:
 * - on the direct face
 * - on the invert face
 * - on both the direct and the invert face
 **/
  void AddLocation(CATSobVertexOnEdgeLocation iVertexLocation);

/**
 * Gets the location of 'this', ie on which side of the edge
 * 'this' is located
 *
 * @return
 * The location of 'this'
 **/
  CATSobVertexOnEdgeLocation GetLocation();

/**
 * Gets the CATSobVertex contained in 'this' respect to a face
 *
 * @param iFace
 * An adjacent face of the edge on which 'this' is located
 *
 * @return
 * A pointer to the CATSobVertex
 **/
  CATSobVertex* GetVertexOnFace(CATSobFace* iFace);
  
/**
 * Gets the CATSobVertex contained in 'this' respect to a CATSobVertexOnEdgeLocation
 *
 * @param iVertexLocation
 * A location, iVertexLocation can not be VERTEX_ON_BOTH_FACES
 *
 * @return
 * A pointer to the CATSobVertex
 **/
  CATSobVertex* GetVertexOnFace(CATSobVertexOnEdgeLocation iVertexLocation);

/**
 * Remove a CATSobVertex from 'this' respect to a face
 *
 * @param iFace
 * An adjacent face of the edge on which 'this' is located
 *
 * @return
 * CATSobDiag_OK if no errors, else see CATSobDiagh
 **/
  CATSobDiag RemoveVertexOnFace(CATSobFace* iFace);

/**
 * Remove a CATSobVertex from 'this' respect to a CATSobVertexOnEdgeLocation
 *
 * @param iVertexLocation
 * A location
 *
 * @return
 * CATSobDiag_OK if no errors, else see CATSobDiagh
 **/
  CATSobDiag RemoveVertexOnFace(CATSobVertexOnEdgeLocation iVertexLocation);

/**
 * Check if 'this' contains some CATSobVertex
 *
 * @return
 * TRUE if 'this' doesn't contain any CATSobVertex, else FALSE
 **/
  CATBoolean IsEmpty();

  void SwapLocation();


private:

  // Copy constructor and equal operator
  CATSobVertexOnEdge (CATSobVertexOnEdge &);
  CATSobVertexOnEdge& operator=(CATSobVertexOnEdge&);

  //Data
  CATSobEdge* _MotherEdge;
  CATSobVertex* _VertexOnDirectFace;
  CATSobVertex* _VertexOnInvertFace;
  double _Ratio;

  //Codage de données binaires:
  // Bit 0x01: Point sur edge relativement à direct face de l'edge
  // Bit 0x02: Point sur edge relativement à invert face de l'edge
  // Bit 0x04: Not used
  // Bit 0x08: Not used
  // Bit 0x10: Not used
  // Bit 0x20: Not used
  // Bit 0x40: Not used
  // Bit 0x80: Not used
  //
  // Les bits 0x01 et 0x02 peuvent être à 1 simultanément
  //si le point existe sur les deux faces
  unsigned char _Infos;

};


#endif

