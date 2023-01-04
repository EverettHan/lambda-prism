#ifndef CATechStreamer_h
#define CATechStreamer_h

/* 
* @COPYRIGHT DASSAULT SYSTEMES 2012
* -------------------------------------------------------------------------------------------------
* CATechModelData_Get : Usage notes:
* The class implements the CATechGet interface and is used for managing streaming/unstreaming
* of polyhedral data in a phoenix capture/redo scenario. Currently it supports streaming of:
* 1) CATRep to *.cgr or *.uvr files
* 2) CATPolyBody to *.poly files 
* 3) CATBVHTree to  *.bvh files
* 4) V4Models to *.model files
* -------------------------------------------------------------------------------------------------
*/

// CATMathStream
#include "CATechGetValues.h"

class CATRep;
class CATBVHTree;
class CATPolyBody;
class CATIDataStreamer;
class CATPolyPolygon2D;
class CATUnicodeString;
class CATIStreamManager;
class CATMathTransformation;


class ExportedByCATTechTools CATechModelData_Get : public CATechGetValues
{

  CATDeclareClass;

public:

  /*
  * Constructor : Creates a CATechModelData_Get from a CATIStreamManager. The actual component that implements
  *               CATIStreamManager is created by the CATech extension internally and is available in
  *               the _pStreamManager member
  * @param ipStreameMgr : Instance which implements the CATIStreameManager interface
  *
  */
  CATechModelData_Get(CATIStreamManager * ipStreamMgr);

  /*
  * Destructor
  */
  ~CATechModelData_Get();

  //-----------------------------------------------------------------------------------------------
  // STREAM METHODS
  //-----------------------------------------------------------------------------------------------
  /*
  * StreamRep : Streams the CATRep's into *.cgr/ *.uvr files based on their type
  * @param ipRep : CATRep to be streamed
  * @return
  *   Returns S_OK if the streaming is successful
  */
  HRESULT StreamRep(CATRep * ipRep);

  /*
  * StreamPolyBody : Streams the CATPolyBody's into *.poly files 
  * @param ipBody : CATPolyBody to be streamed
  * @param iOptionalPosition
  *   An optional position matrix associated to the CATPolyBody
  * @return
  *   Returns S_OK if the streaming is successful
  */
  HRESULT StreamPolyBody (const CATPolyBody* ipBody, const CATMathTransformation* iOptionalPosition = 0);

  /*
  * StreamBVHTree : Streams the CATBVHTree's into *.bvh files 
  * @param ipBVHTree : CATBVHTree to be streamed
  * @return
  *   Returns S_OK if the streaming is successful
  */
#ifdef CATIAR214
  HRESULT StreamBVHTree(CATBVHTree * ipBVHTree);
#endif

  /*
  * StreamV4Model : Streams the V4Model's into *.model files 
  * @param ipV4Model : V4Model to be streamed
  * @return
  *   Returns S_OK if the streaming is successful
  */
  HRESULT StreamV4Model(CATBaseUnknown * ipV4Model);

  /*  
  * StreamPolyPolygon2D : Streams the CATPolyPolygon2D's into *.txt files 
  * @param ipPolygon2D : CATPolyPolygon2D to be streamed
  * @return
  *   Returns S_OK if the streaming is successful
  */
  HRESULT StreamPolyPolygon2D(CATPolyPolygon2D * ipPolygon2D);

  /*
  * StreamVaultedData : In some case(like V4 entities), data is not streamed immediately as multiple entities
  *                     could be present in a file and we dont want them to be streamed separately. It is just 
  *                     stored temporarily. This method streams such data
  */
  HRESULT StreamVaultedData();

  /*
  * GetStreamedFileData : Get data associated with the streamed file
  * @param oFileName : Name of the streamed file (full name with extension)
  * @param oppFileData : Data associated with file
  */
  inline void GetStreamedFileData(CATUnicodeString & oFileName, void ** oppFileData);

  //-----------------------------------------------------------------------------------------------
  // UNSTREAM Methods
  //-----------------------------------------------------------------------------------------------
  // At the time of replay, the data is read automatically by the phoenix infrastructure after 
  // parsing through the phoenix.xml file. This can then be queried upon by the clients using
  // the appropriate get methods. 
  // IMPORTANT:  (D1A: July 2015)
  // The client should call below inline Get methods and further manage lifecycle of the obtained object.
  // These methods should be called only once.

  /*
  * GetRep : Returns the rep read in the Unstream operation
  */
  inline CATRep * GetRep();

  /*
  * GetPolyBody : Returns the polybody read in the Unstream operation.
  * The returned instance must be released.
  */
  inline CATPolyBody * GetPolyBody();

  /*
   * Returns the optional position matrix associated to a CATPolyBody instance.
   * The returned instance must be deleted.
   */
  inline CATMathTransformation* GetPositionMatrix () ;


  /*
  * GetBVHTree : Returns the CATBVHTree read in the Unstream operation
  */
#ifdef CATIAR214
  inline CATBVHTree * GetBVHTree();
#endif

  /*
  * GetV4Model : Returns the V4Model read in the Unstream operation
  */
  inline CATBaseUnknown * GetV4Model();

  /*
  * GetPolyPolygon2D : Returns the CATPolyPolygon2D read in the Unstream operation
  */
  inline CATPolyPolygon2D * GetPolyPolygon2D();


  //-----------------------------------------------------------------------------------------------
  //  CATechGet  adhesion  
  //-----------------------------------------------------------------------------------------------
  virtual HRESULT GetSchema(CATechSchema  & oSchema) const;

  virtual HRESULT GetTechValue(const CATechMeta & iRole, 
                               void             * ioValue) const  ;

  virtual HRESULT GetTech3DValue(const CATechMeta      &  iRole, 
                                 CATMathTransformation *  oXMath, 
                                 CATechGet             ** oReferenceToRelease) const;

  virtual HRESULT CopyTechValue(const CATechGet * iAttribute, 
                                const CATBoolean iEmptyBefore);
 
  virtual HRESULT IsCopyTechValueImplemented() const;

  virtual CATechSet * IsASet() const  ; 

  virtual CATechAttribute * IsAttribute() const ; 

public:

  // An instance of a CATPolyBody with its position matrix for 
  // streaming and unstreaming purposes.
  // (For CATechPolyBodyStreamer usage.)
  struct PolyBodyAndPosition
  {
    CATPolyBody* _PolyBody;
    CATMathTransformation* _PositionMatrix;
  };

private:

  //Initializes all the pointer data memebers to NULL
  void Initialize();

  /*
  * Unstream : Unstreams the passed file. Used by SAXHandler for reading the streamed data.
  *            The unstreamed data can be read by using GetRep, GetPolyBody...methods
  * @param iFileName : File name(with extension) for the file to be read
  * @param ippData : Additional data needed for unstreaming the file
  * @return
  *   Returns S_OK if the unstreaming succeeds without any issues
  */
  HRESULT Unstream(const CATUnicodeString & iFileName, void ** ippData);

  CATIStreamManager   * _pStreamMgr;        //Pointer to the stream manager
  CATIDataStreamer    * _pCurrentStreamer;  //Pointer to current streamer used

  CATRep              * _pReadRep;          //Pointer to the CATRep read from the streamer
  CATPolyBody         * _pReadPolyBody;     //Pointer to CATPolyBody read from the streamer
  CATMathTransformation* _pReadPosMatrix;   // Pointer to the position matrix read from the streamer.
  CATBVHTree          * _pReadBVHTree;      //Pointer to CATBVHTree read from the streamer
  CATBaseUnknown      * _pReadV4Model;      //Pointer to CATBVHTree read from the streamer
  CATPolyPolygon2D    * _pReadPolyPolygon2D;//Pointer to CATPolyPolygon2D read from the streamer

  CATUnicodeString      _fileName;          //Filename for the data streamed using this class
  void                * _pFileData;         //Data associated with the file

  friend class CATechSAXHandler;

};

inline void CATechModelData_Get::GetStreamedFileData(CATUnicodeString & oFileName, void ** oppFileData)
{
  oFileName     = _fileName;
  *oppFileData  = _pFileData;
}

inline CATRep * CATechModelData_Get::GetRep() 
{
  CATRep * rep = _pReadRep;
  _pReadRep = NULL;
  return rep;
}

inline CATPolyBody * CATechModelData_Get::GetPolyBody() 
{
  CATPolyBody * polybody = _pReadPolyBody;
  _pReadPolyBody = NULL;
  return polybody;
}

inline CATMathTransformation* CATechModelData_Get::GetPositionMatrix () 
{
  CATMathTransformation* posMatrix = _pReadPosMatrix;
  _pReadPosMatrix = 0;
  return posMatrix;
}

#ifdef CATIAR214
inline CATBVHTree * CATechModelData_Get::GetBVHTree() 
{
  CATBVHTree * bvhTree = _pReadBVHTree;
  _pReadBVHTree = NULL;
  return bvhTree;
}
#endif

inline CATBaseUnknown * CATechModelData_Get::GetV4Model() 
{
  CATBaseUnknown * v4Model = _pReadV4Model;
  _pReadV4Model = NULL;
  return v4Model;
}

inline CATPolyPolygon2D * CATechModelData_Get::GetPolyPolygon2D() 
{
  CATPolyPolygon2D * polygon2D = _pReadPolyPolygon2D;
  _pReadPolyPolygon2D = NULL;
  return polygon2D;
}

#endif
