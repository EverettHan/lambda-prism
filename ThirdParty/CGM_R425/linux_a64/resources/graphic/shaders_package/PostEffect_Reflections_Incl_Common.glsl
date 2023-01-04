//Same as in vRasterizerStructs.h
#define kMaxElementCount (16u)

//enum EAttribIndices
//{
#define EAttribIndicesPosition 0
#define EAttribIndicesNormal 1
#define EAttribIndicesTangent 2
#define EAttribIndicesBinormal 3
#define EAttribIndicesTexCoord0 4
#define EAttribIndicesLegacyUV 5
#define EAttribIndicesLightMapCoord 6
#define EAttribIndicesSlot7 7
#define EAttribIndicesCount 8
//};

struct Vertex_t
{
  vec3 attrib[EAttribIndicesCount];
};

struct ObjectDesc_t
{
  uint64_t indexAddr;
  uint64_t bufferAddr[kMaxElementCount];
};

struct ObjectFormat_t
{
  uint16_t attribMapping[EAttribIndicesCount];
  uint16_t vertexStride[kMaxElementCount];
  uint16_t indexSize;
  uint16_t compressedNormal;
  uint material;
};

struct PerMatrixCbOffsets_t
{
  uint perMatrixConstantBufferOffsets[16];
};

struct MaterialBuffer_t
{
  uint perMaterialConstantBufferOffsets[16];
  uint textures[64];
};
