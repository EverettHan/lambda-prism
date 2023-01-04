#ifndef CATWaveletCompression_h
#define CATWaveletCompression_h

#include "YN000WAV.h"
#include "CATWaveletCodecDef.h"
#include "CATBoolean.h"

class ExportedByYN000WAV CATWaveletCompression
{
public:
  //------------------------------------------------------------------------------------------
// GetBlock
//
// desc:  extract a tile from a bigger image (1 color channel)
// rval:  number of copied pixels
// param: idata: input data (size sx*sy)
//        odata: output tile (size w*h)
//
// notes: if the requested area exceeds the input borders,
//        then the exceeding space is filled with 0
//------------------------------------------------------------------------------------------

  static int GetBlock_8(   char* idata, int sx, int sy,  char* odata, int x, int y, int w, int h );
  static int GetBlock_16( short* idata, int sx, int sy, short* odata, int x, int y, int w, int h );
  static int GetBlock_32(   int* idata, int sx, int sy,   int* odata, int x, int y, int w, int h );
  static int GetBlock_32f(float* idata, int sx, int sy, float* odata, int x, int y, int w, int h );

//------------------------------------------------------------------------------------------
// Transform
//
// desc:  apply a wavelet transformation to a signal (1 color channel, 2 dimensions)
// rval:  true if succeeded
// param: transformID: see CATWaveletTransform
//        iodata: input AND output data (size sx*sy).
//                contains sx*sy wavelet coefficients after transformation
//        minLvl, maxLvl: used to limit the multi-resolution analysis
//                between 2 levels of frequencies
//
//
// notes: Transform_8 and Transform_16 are currently not implemented
//        Transform_32 only accept LG53 and Haar  :: performs lossless integer to integer transformations 
//        Transform_32f accept any transformation :: performs float to float transformations
//
//        if iodata is aligned on 16bits, if sx = sy = a power of two, and
//        if SSE2 instructions are supported, then the transformation will be
//        optimized with intrinsic instructions.
//------------------------------------------------------------------------------------------


//#define  CATWavelateNewArg

#ifdef CATWavelateNewArg
#define CATWaveletTransformARG  CATWaveletTransform
#define CATWaveletModeARG       CATWaveletMode
#define  CATWaveletSchemeARG    CATWaveletScheme
#else
#define CATWaveletTransformARG  int 
#define CATWaveletModeARG       int
#define CATWaveletSchemeARG     int

#endif

static CATBoolean Transform_8(   char* iodata, int sx, int sy, CATWaveletTransformARG transformID, int minLvl = 0, int maxLvl = -1);
static CATBoolean Transform_16( short* iodata, int sx, int sy, CATWaveletTransformARG transformID, int minLvl = 0, int maxLvl = -1);
static CATBoolean Transform_32(   int* iodata, int sx, int sy, CATWaveletTransformARG transformID, int minLvl = 0, int maxLvl = -1);
static CATBoolean Transform_32f(float* iodata, int sx, int sy, CATWaveletTransformARG transformID, int minLvl = 0, int maxLvl = -1);

//------------------------------------------------------------------------------------------
// ReverseTransform
//
// desc:  apply a reverse wavelet transformation to a signal (1 color channel, 2 dimensions)
// rval:  true if succeeded
// param: transformID: see CATWaveletTransform
//        iodata: input AND output data (size sx*sy).
//                contains sx*sy wavelet coefficients before reverse transformation
//        minLvl, maxLvl: used to limit the multi-resolution analysis
//                between 2 levels of frequencies
//
//
// notes: ReverseTransform_8 and ReverseTransform_16 are currently not implemented
//        ReverseTransform_32 only accept LG53 and Haar   :: performs lossless integer to integer reverse transformations
//        ReverseTransform_32f accept any transformation  :: performs float to float reverse transformations
//
//        if iodata is aligned on 16bits, if sx = sy = a power of two, and
//        if SSE2 instructions are supported, then the reverse transformation will be
//        optimized with intrinsic instructions.
//------------------------------------------------------------------------------------------

static CATBoolean ReverseTransform_8(   char* iodata, int sx, int sy, CATWaveletTransformARG transformID, int minLvl = 0, int maxLvl = -1);
static CATBoolean ReverseTransform_16( short* iodata, int sx, int sy, CATWaveletTransformARG transformID, int minLvl = 0, int maxLvl = -1);
static CATBoolean ReverseTransform_32(   int* iodata, int sx, int sy, CATWaveletTransformARG transformID, int minLvl = 0, int maxLvl = -1);
static CATBoolean ReverseTransform_32f(float* iodata, int sx, int sy, CATWaveletTransformARG transformID, int minLvl = 0, int maxLvl = -1);

// jsx temporaire pour debug odt appli (mais utilite douteuse )
//CATBoolean ReverseTransform_32fNONSTATIC(float* iodata, int sx, int sy, int transformID, int minLvl = 0, int maxLvl = -1);




//------------------------------------------------------------------------------------------
// Quantize
//
// desc:  quantize data (truncation from float to int)
// rval:  true if succeeded
// param: idata: input data (sx*sy)
//        odata: quantized data (MUST be already allocated)
//        modeID: see CATWaveletCompressionMode
//        info: parameters for quantization (use MACRO constructors) (see CATWavelet_QINFO)
//        error: rest of the quantization (ignored if left to NULL)
//------------------------------------------------------------------------------------------

static CATBoolean Quantize_32f(   float* idata, int sx, int sy, int* odata, CATWaveletModeARG modeID, CATWavelet_QINFO info, float** error = 0);


//------------------------------------------------------------------------------------------
// Restore
//
// desc:  used as a pendant to Quantize
// rval:  true if succeeded
// param: idata: input data (sx*sy)
//        odata: restored data (MUST be already allocated)
//        modeID: see CATWaveletCompressionMode
//        info: parameters for quantization (use MACRO constructors) (see CATWavelet_QINFO)
//------------------------------------------------------------------------------------------

static CATBoolean Restore_32f(int* idata, int sx, int sy, float* odata, CATWaveletModeARG modeID, CATWavelet_QINFO info);


//------------------------------------------------------------------------------------------
// Encode
//
// desc:  encode data
// rval:  length of compressed data (-1 = error)
// param: schemeID: combination of flags (see CATWaveletScheme)
//        idata: input data (size sx*sy)
//        odata: compressed data (MUST be already allocated)
//               (required size: sx*sy*8/16/32 at most)
//        minLvl, maxLvl: encode only a restricted area (see Transform)
//
// notes: Encode_16 currently not implemented
//        Encode_8 does not support SPIHT
//        schemeID may be a combination of any flags from CATWaveletScheme but:
//               - you cannot combine AC with Huffman
//               - combination with SPIHT is not supported by Encode_8
//------------------------------------------------------------------------------------------

static int Encode_8(   char* idata, int sx, int sy, char* odata, CATWaveletSchemeARG schemeID, int minLvl = 0, int maxLvl = -1);
static int Encode_16( short* idata, int sx, int sy, char* odata, CATWaveletSchemeARG schemeID, int minLvl = 0, int maxLvl = -1);
static int Encode_32(   int* idata, int sx, int sy, char* odata, CATWaveletSchemeARG schemeID, int minLvl = 0, int maxLvl = -1);

//------------------------------------------------------------------------------------------
// Decode
//
// desc:  decode data
// rval:  length of decompressed data (-1 = error)
// param: schemeID: combination of flags (see CATWaveletScheme)
//        idata: input data
//        length: length of iData
//        odata: decompressed data (MUST be already allocated)
//        minLvl, maxLvl: encode only a restricted area (see Transform)
//
// notes: Decode_16 currently not implemented
//        Decode_8 does not support SPIHT
//        schemeID may be a combination of any flags from CATWaveletScheme but:
//               - you cannot combine AC with Huffman
//               - combination with SPIHT is not supported by Decode_8
//------------------------------------------------------------------------------------------
static int Decode_8( char* idata, int length, int sx, int sy,  char* odata, CATWaveletSchemeARG schemeID, int minLvl = 0, int maxLvl = -1);
static int Decode_16(char* idata, int length, int sx, int sy, short* odata, CATWaveletSchemeARG schemeID, int minLvl = 0, int maxLvl = -1);
static int Decode_32(char* idata, int length, int sx, int sy,   int* odata, CATWaveletSchemeARG schemeID, int minLvl = 0, int maxLvl = -1);
static int Decode_32(char* idata,             int sx, int sy,   int* odata, CATWaveletSchemeARG schemeID, int minLvl = 0, int maxLvl = -1);


//private:
  CATWaveletCompression();
  ~CATWaveletCompression();
};
#endif
