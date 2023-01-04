// Creation: November 2021 - TCT5

#ifndef _AIX_SOURCE

#ifndef CATPolyEdgeBreakerStreamable_h
#define CATPolyEdgeBreakerStreamable_h

#include "PolyEdgeBreaker.h"

#include "CATDataType.h"
#include "CATSysErrorDef.h"

#include <vector>

#define EDGEBREAKER_PERSIST_INDICES 0x1
#define EDGEBREAKER_QUANTIZE_POSITIONS 0x2
#define EDGEBREAKER_QUANTIZE_NORMALS 0x4
#define EDGEBREAKER_QUANTIZE_NORMALS_24_BIT 0x8
#define EDGEBREAKER_QUANTIZE_NORMALS_PREDICTOR_AVERAGE 0x10
#define EDGEBREAKER_QUANTIZE_NORMALS_PREDICTOR_AVERAGE_WITH_ANGLES 0x20

class CATPolyEdgeBreakerCompressedLayer;

enum CATPolyEdgeBreakerOPCode
{
  C = 0,
  L,
  E,
  R,
  S
};

class CATIPolyEdgeBreakerStreamer
{
public:
  CATIPolyEdgeBreakerStreamer() {}
  virtual ~CATIPolyEdgeBreakerStreamer() {}

public:
  virtual void WriteULong(CATULONG32 iVal) = 0;
  virtual void WriteLong(CATLONG32 iVal) = 0;
  virtual void WriteULong64(CATULONG64 iVal) = 0;
  virtual void WriteUChar(unsigned char iVal) = 0;
  virtual void WriteBit(unsigned char iBit) = 0;
  virtual void WriteFloat(float iVal) = 0;
  virtual void WriteDouble(double iVal) = 0;

  virtual void FlushBits() = 0;
};

class CATIPolyEdgeBreakerUnstreamer
{
public:
  CATIPolyEdgeBreakerUnstreamer() {}
  virtual ~CATIPolyEdgeBreakerUnstreamer() {}

public:
  virtual void ReadULong(CATULONG32 &oVal) = 0;
  virtual void ReadLong(CATLONG32 &oVal) = 0;
  virtual void ReadULong64(CATULONG64 &oVal) = 0;
  virtual void ReadUChar(unsigned char &oVal) = 0;
  virtual void ReadBit(unsigned char &oBit) = 0;
  virtual void ReadFloat(float &oVal) = 0;
  virtual void ReadDouble(double &oVal) = 0;

  virtual void FlushBits() = 0;
};

class ExportedByPolyEdgeBreaker CATPolyEdgeBreakerStreamable
{
public:
  CATPolyEdgeBreakerStreamable();
  virtual ~CATPolyEdgeBreakerStreamable();

public:
  HRESULT Stream(CATIPolyEdgeBreakerStreamer &ioStream) const;
  HRESULT Unstream(CATIPolyEdgeBreakerUnstreamer& ioStream);

public:
  CATULONG64 m_Options;
  CATULONG32 m_Version;

  std::vector<CATPolyEdgeBreakerOPCode> m_Codes;
  std::vector<int> m_Topology;

  std::vector<int> m_MapOfStreamedVertexIndicesToInputIndices;
  std::vector<int> m_MapOfStreamedTriangleIndicesToInputIndices;
  std::vector<unsigned char> m_MapOfTriangleRotations;
  
  CATULONG32 m_NbOfBoundaryVertices;
  std::vector<bool> m_StartOnBoundary;

  CATPolyEdgeBreakerCompressedLayer *m_pCompressedPositions;
  CATPolyEdgeBreakerCompressedLayer *m_pCompressedNormals;
};

#endif // !CATPolyEdgeBreakerStreamable_h

#endif // AIX
