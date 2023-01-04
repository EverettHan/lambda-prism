//====================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//====================================================================
//
// CATSobMeshCompressor.h
//
//====================================================================
//
// Usage notes: Operateur de compression d'un base mesh polygonal.
//
//====================================================================
// June,     2004 : RAQ : Création
//====================================================================
#ifndef CATSobMeshCompressor_H
#define CATSobMeshCompressor_H

#include "CATSobObjects.h"

#include "CATDataType.h"
#include "CATSobDiag.h"
class CATSobMesh;
class CATSobStream;


//--------------------------------------------------------------------------
// Construction de l'opérateur de compression avec sortie sur un Stream
//--------------------------------------------------------------------------
/**
 * Stream of a polygonal mesh via a given Stream.
 *
 * @param iMeshToCompress
 * The Base Mesh to stream
 *
 * @param iStreamOut
 * The stream to use to save the mesh, the stream must be open
 * in binary writing mode (See CATSobStream.h).
 *
 * @param iStreamInfos
 * A pointer to an array of 7 CATLONG32, where some informations about how
 * many bytes have been written are saved. If no pointer is given, informations
 * are not saved.
 * .1 st element: Number of bytes used for Huffman header
 * .2 nd element: Number of bytes used for connectivity
 * .3 rd element: Number of bytes used for vertices coordinates
 * .4 th element: Number of bytes used for faces orientation
 * .5 th element: Number of bytes used for faces tags
 * .6 th element: Number of bytes used for vertices weight
 * .7 th element: Number of bytes used for edges weight
 * .8 th element: Number of bytes used for details
 * .9 th element: Number of details written
 *
 * @return
 * CATSobDiag_OK if no error, else see CATSobDiag.h
 **/
ExportedByCATSobObjects
CATSobDiag CATSobCreateMeshCompressor(CATSobMesh*   iMeshToCompress,
                                      CATSobStream* iStreamOut,
                                      CATLONG32*    iStreamInfos=0);


//----------------------------------------------------------------------
// Construction de l'opérateur de décompression à partir d'un Stream
//----------------------------------------------------------------------
/**
 * Unstream of a polygonal mesh from a given Stream.
 *
 * @param iMeshToUncompress
 * This pointer will contain the adress of the unstreamed mesh if the
 * operator succeedes.
 *
 * @param iStreamIn
 * The stream to use to read the mesh, the stream must be open
 * in binary reading mode (See CATSobStream.h).
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
ExportedByCATSobObjects
CATSobDiag CATSobCreateMeshUncompressor(CATSobMesh*&  oMeshToUncompress,
                                        CATSobStream* iStreamIn);


//--------------------------------------------------------------------------
// Construction de l'opérateur de compression pour sortie dans un fichier
//--------------------------------------------------------------------------
/**
 * Stream of a polygonal mesh to a given file.
 *
 * @param iMeshToCompress
 * The Base Mesh to stream
 *
 * @param iFileName
 * The file where the mesh is to be stream
 *
 * @param iStreamInfos
 * A pointer to an array of 7 CATLONG32, where some informations about how
 * many bytes have been written are saved. If no pointer is given, informations
 * are not saved.
 * .1 st element: Number of bytes used for Huffman header
 * .2 nd element: Number of bytes used for connectivity
 * .3 rd element: Number of bytes used for vertices coordinates
 * .4 th element: Number of bytes used for faces orientation
 * .5 th element: Number of bytes used for faces tags
 * .6 th element: Number of bytes used for vertices weight
 * .7 th element: Number of bytes used for edges weight
 * .8 th element: Number of bytes used for details
 * .9 th element: Number of details written
 *
 * @return
 * CATSobDiag_OK if no error, else see CATSobDiag.h
 **/
ExportedByCATSobObjects
CATSobDiag CATSobCreateMeshCompressor(CATSobMesh* iMeshToCompress,
                                      const char* iFileName,
                                      CATLONG32*  iStreamInfos=0);


//----------------------------------------------------------------------
// Construction de l'opérateur de décompression à partir d'un fichier
//----------------------------------------------------------------------
/**
 * Unstream of a polygonal mesh from a given file.
 *
 * @param iMeshToUncompress
 * This pointer will contain the adress of the unstreamed mesh if the
 * operator succeedes.
 *
 * @param iFileName
 * The name of the file containing the streamed mesh.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
ExportedByCATSobObjects
CATSobDiag CATSobCreateMeshUncompressor(CATSobMesh*& oMeshToUncompress,
                                        const char*  iFileName);

#endif

