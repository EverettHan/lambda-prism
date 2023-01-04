#ifndef DSMMOCODECDEF_H
#define DSMMOCODECDEF_H

//==========================================================================================
// DSMMOCodecDef.h
// Author: qtu
// Version: 12/2012
// Desc: define several enums 
//==========================================================================================

//------------------------------------------------------------------------------------------
// wavelet transformations
//------------------------------------------------------------------------------------------

enum CATWaveletTransform {
  CATWaveletTransform_CDF97        = 0, // Cohen Daubechies Feauveau 9/7
  CATWaveletTransform_NormCDF97    = 1, // Normalized Cohen Daubechies Feauveau 9/7
  CATWaveletTransform_LG53         = 2, // Le Gall 5/3
  CATWaveletTransform_NormLG53     = 3, // Normalized Le Gall 5/3
  CATWaveletTransform_Haar         = 4, // Haar
  CATWaveletTransform_MinHaar      = 5, // Haar (min per level) variant
  CATWaveletTransform_MaxHaar      = 6, // Haar (max per level) variant
  CATWaveletTransform_None         = -1,
};


//------------------------------------------------------------------------------------------
// quantization mode
//------------------------------------------------------------------------------------------

enum CATWaveletMode {
  CATWaveletMode_Uniform           = 0, // Uniform scalar
  CATWaveletMode_Border            = 1, // Border preserving scalar
};

struct CATWavelet_QINFO 
{
  float stepJSX;
  CATWaveletTransform/*int*/ transformID;
  int bordersize;     // only used by CATWaveletMode_Border
  float borderstep;   // only used by CATWaveletMode_Border
  int minLvl;         // only used by CATWaveletMode_Border
  int maxLvl;         // only used by CATWaveletMode_Border

  // use this with uniform mode
  CATWavelet_QINFO(float istep, int itransform = CATWaveletTransform_None) :
  stepJSX(istep),/* transformID(itransform),*/ bordersize(0), borderstep(istep), minLvl(0), maxLvl(0) 
     {
     transformID = (CATWaveletTransform)itransform;
     };


  // use this with border mode
  CATWavelet_QINFO(float istep, int itransform, int ibordersize, float iborderstep, int minl=0, int maxl=-1) :
  stepJSX(istep), /*transformID(itransform),*/ bordersize(ibordersize), borderstep(iborderstep), minLvl(minl), maxLvl(maxl) 
     {
     transformID = (CATWaveletTransform)itransform;
     };
};

//------------------------------------------------------------------------------------------
// encoding schemes (flags: can be combined)
//------------------------------------------------------------------------------------------

enum CATWaveletScheme {
  CATWaveletScheme_SPIHT           = 1, // Set partitioning in hierarchical trees
  CATWaveletScheme_Huffman         = 2, // Huffman coding
  CATWaveletScheme_RLE             = 4, // Run Length Encoding
  CATWaveletScheme_Arithmetic      = 8, // Arithmetic coding
};

#endif
