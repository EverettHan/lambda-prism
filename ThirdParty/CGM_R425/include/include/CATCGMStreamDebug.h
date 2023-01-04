/* -*-c++-*- */
#ifndef CATCGMStreamDebug_H_
#define CATCGMStreamDebug_H_
// COPYRIGHT DASSAULT SYSTEMES  2016


#include  "ExportedByGeometricObjects.h"

#include "CATMathODT.h"
#include "CATMathDebug.h"
#include "CATCGMStream.h"
#include "CATListOfCATCGMStream.h"
#include "CATGeoFactory.h"
#include "CATLib.h"
#include "CGMStreamMeasure.h"
#include "CATActivateCGMStreamTraces.h"
#include <iostream.h>
#include "CATCGMHashTableWithAssoc.h"

class ExportedByGeometricObjects CATCGMStreamDebug
{
public:
   CATCGMStreamDebug();
   ~CATCGMStreamDebug();

//======================
// static Methode
//======================
   static CATCGMStreamDebug* GetCGMStreamDebug();
	 static void CleanCGMStreamDebug();
   /*static void Init();
   static void Clean(short BufferNumber);*/

   // write
   //static void WriteIncrementalStreamBuffer(CATLONG64 BufferSize, char * Buffer);
   //static void CloseWriteIncrementalStreamBuffer(short BufferNumber);

   //// save standard
   //static void SaveFileInStandardMode(CATGeoFactory* iFactory, int IdxIncrement, CATUnicodeString iAdditionalInfo = "");

   // read
   //static void ReadIncrementalStreamBuffer(const char * FilePath);

	 // Incremental Save
   static int OpenINCSTRFile(const char * FilePath);
   // Save stream buffer in a file xxx.INCSTR
   // INCSTR = INCremental STReam
   static int SaveIncrementalStreamBufferAsINCSTR(char* iBuffer, CATLONG32 iBufferSize, int iCurIncrementIndex, int iNbIncrement);

	 int AppendIncrementalStreamBuffer(CATCGMStream * iCGMStream);
	 int ReadIncrementalStreamBuffer();
	 int WriteIncrementalStreamBuffer(const char * SavePath);

	 // Standard Save
   static int SaveStandardStreamBufferAsNCGM(char* iBuffer, size_t iBufferSize);


   static void WriteBuffer(void* ipId,size_t iBufferSize, unsigned char * iBuffer);
   static void ReadBuffer(void* ipId ,size_t & oBufferSize, unsigned char *& oBuffer);
   static void Clean(void* ipId);
   static void WriteMapping(void* ipId, CATCGMHashTableWithAssoc* pMapping);
   static void ReadMapping(void* ipId, CATCGMHashTableWithAssoc*& opMapping);

   // CATBack
   static void StartCATBackTrace();
   static void EndCATBackTrace();
   static void AddIncompatibleObject(CATICGMObject * & iIncompatibleObject, CATICGMObject * & iConvertedObject);
   static void GetIncompatibleObject(CATLISTP(CATICGMObject) & oIncompatibleObjects, int & oNbConvertedObjects);
   
   

//======================
// virtual Methode 
//======================
   virtual int  FeatureUpdateAndIncrementalSave(char * FilePath);
   virtual int  StandardSaveOpen(char * FilePath);

//======================
// Stauts file 
//======================
   // open : 1
   // close : 0
  void OpenCloseAdditionalStatusFile(int open_or_close);

  void OpenStatusFile(int WithAdditionalFile = 0);
  void CloseStatusFile(int WithAdditionalFile = 0);
  void FillStatusFile_IncrementalSave(char * StorageName, int IdxCase,  int UpdateReturnCode, int SaveReturnCode, CGMStreamMeasureData* GlobalMeasureData, int WithAdditionalFile = 0);
  void FillStatusFile_StandardSave(char * StorageName, int SaveReturnCode, int OpenReturnCode, CGMStreamMeasureData* GlobalMeasureData, int WithAdditionalFile = 0);

//======================
// membre data
//======================
   static CATUnicodeString          _FilePath;
   static CATCGMStream *            _Stream;
   static CATGeoFactory*            _Factory;
   static size_t                    _where1;
   static short                     _level1;
   static size_t                    _PosToInsertNbBuffer;

   static int                       _ReferenceFactors[100]; 
   static int                       _HasReference;
   
   static FILE*                     _IncrementalReadFile;

   static CATCGMHashTableWithAssoc* _pBufferTable;
   static CATCGMHashTableWithAssoc* _pSizeTable;
   static CATCGMHashTableWithAssoc* _pMappingTable;

   //CATBack test
   static CATCGMHashTableWithAssoc* _ObjectConvertMappingTag;
   static CATCGMHashTableWithAssoc* _ConvertedTagMappingType;

   static CATCGMStreamDebug*   _Debug;

	 // stream buffer
	 CATLISTP(CATCGMStream)  _IncrementCGMStream;
	 unsigned char **  _IncStrBufferList;
	 int               _NbIncStrBuffer;

   // status file
   ostream         *_OutputStatus;
   int              _NumberOfOKs;
   int              _NumberOfKOs;
};

#endif
