#ifdef PDSFX1_VS_Varyings_GASLook0
void gasComputeVaryingValues()
#else
void ComputeVaryingValues()
#endif
{  
  noiseCoords = vGetAttribPosition();

#ifdef VertexColor
  vColor = vGetColor();
#endif // VertexColor
}
