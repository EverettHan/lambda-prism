////////////////////////////////
// Client Code Basic Skeleton //
////////////////////////////////
//#define USE_TANGENT_SPACE

void pmComputeVaryingValues()
{        
  v_ObjectSpacePosition = vGetAttribPosition();
  v_ObjectSpaceNormal = vGetAttribNormal();
}

#ifndef PDSFX1_VS_Varyings_PhysicalMaterial
void ComputeVaryingValues()
{
  pmComputeVaryingValues();
}
#endif
