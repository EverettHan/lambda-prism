//===========================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//===========================================================================
//
// CATSobOBJParser.h
//
//===========================================================================
//
// Usage notes: OBJ file parser.
//
//===========================================================================
// November,  2009 : RAQ : Creation
//===========================================================================
#ifndef CATSobOBJParser_H
#define CATSobOBJParser_H

//Pour l'export
#include "CATSobObjects.h"

//Structure subdivision
#include "CATSobRawData.h"
#include "CATSobDiag.h"
#include "CATSobListOfMesh.h"

//STL
#ifndef _AIX_SOURCE
#include <vector>
#endif  //!_AIX_SOURCE

//Divers
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"

class CATSobMesh;


class ExportedByCATSobObjects CATSobOBJParser
{
public:

  //************************ Data Source Type ************************//
  class FileData;
  class RawData;
  class DataSource
  {
  public:
    //Gestion AddRef/Release
    unsigned int AddRef()
    {
      return ++m_RefCounter;
    }

    unsigned int Release()
    {
      if(--m_RefCounter==0)
      {
        delete this;
        return 0;
      }
      else
        return m_RefCounter;
    }

    //Cast
    virtual const FileData* GetAsFileData() const { return 0; }
    virtual const RawData* GetAsRawData() const { return 0; }

  protected:

    DataSource(): m_RefCounter(1) {}
    virtual ~DataSource() {}

    //------ Data :
    unsigned int m_RefCounter;

  };

  class FileData : public DataSource
  {
  public:
    FileData(const CATUnicodeString& iFileName) { m_FileName=iFileName; }

    //Cast
    virtual const FileData* GetAsFileData() const { return this; }

    //------ Data :
    CATUnicodeString m_FileName;

  protected:

    ~FileData() {}
  };

  class RawData : public DataSource
  {
  public:
#ifndef _AIX_SOURCE
    RawData(std::vector<CATSobRawData::Vertex*>& ioVertices,
            std::vector<CATSobRawData::Face*>& ioFaces)
    {
      m_RawVertices.swap(ioVertices);
      m_RawFaces.swap(ioFaces);
    }

#endif  //!_AIX_SOURCE
    //Cast
    virtual const RawData* GetAsRawData() const { return this; }

    //------ Data :
#ifndef _AIX_SOURCE
    std::vector<CATSobRawData::Vertex*> m_RawVertices;
    std::vector<CATSobRawData::Face*> m_RawFaces;
#endif  //!_AIX_SOURCE
  protected:

    ~RawData()
    {
#ifndef _AIX_SOURCE
      for(auto& pRawVertex : m_RawVertices)
      {
        if(pRawVertex) delete pRawVertex; pRawVertex=0;
      }
      for(auto& pRawFace : m_RawFaces)
      {
        if(pRawFace) delete pRawFace; pRawFace=0;
      }
#endif  //!_AIX_SOURCE
    }
  };


  //Destructeur
  virtual ~CATSobOBJParser() {}

  //************************ LECTURE ************************//
  //Pour passer les mesh qui ont des erreurs topologiques
  virtual void SetIgnoreMeshesInTopologicalErrors() = 0;

  //Lecture du fichier
  virtual CATSobDiag Read(const CATSobOBJParser::DataSource* ipDataSource, CATSobListOfMesh& ioBaseMeshes,
                          CATListOfCATUnicodeString* ioBaseMeshesNames, const CATBoolean iImportColors = FALSE) = 0;

  //Récupération des mesh en erreur sous réserve de l'appel à 'SetIgnoreMeshesInTopologicalErrors'
  virtual int GetNbIgnoredMeshes() const = 0;
  virtual const CATListOfCATUnicodeString& GetIgnoredMeshesNames() const = 0;

  //Récupération du nombre de matériaux lus
  virtual int GetNbImportedMaterials() const = 0;


  //************************ ECRITURE ************************//
  //Ecriture du fichier
  virtual CATSobDiag Write(const CATUnicodeString& iFileName, const CATSobListOfMesh& iBaseMeshes, const CATListOfCATUnicodeString* iBaseMeshesNames) = 0;

};


//Création du parseur
ExportedByCATSobObjects
CATSobOBJParser* CATSobCreateOBJParser();


#endif

