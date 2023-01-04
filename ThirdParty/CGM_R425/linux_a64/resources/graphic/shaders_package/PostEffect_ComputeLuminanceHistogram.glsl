//layout(r32f)  uniform restrict coherent readonly  image2D  i_LuminanceMap;
//layout(r32ui) uniform restrict coherent           uimage1D i_HistogramMap;

layout (local_size_x = 16, local_size_y = 16) in;

void main() 
{
  int luminanceSize = vImageSize(i_LuminanceMap).x;

  if ( gl_GlobalInvocationID.x  >= luminanceSize 
      || gl_GlobalInvocationID.y  >= luminanceSize  
      || gl_GlobalInvocationID.z  >= luminanceSize)
    return;

  int histoSize = vImageSize(i_HistogramMap);

  float ev = vImageLoad (i_LuminanceMap, ivec2(gl_GlobalInvocationID.xy)).x;
  ev = (ev - cb_Luminance.u_HistoMin) / (cb_Luminance.u_HistoMax - cb_Luminance.u_HistoMin);
  
  int coord  = vClamp(int(ev * histoSize), 0, histoSize-1);
  int value = 1;
  vImageAtomicAdd(i_HistogramMap, coord, value);
}
