
void basicProcessBRDFParameters(inout BRDFParameters oParameters)
{
  oParameters.roughness = 1.0 - cb_cbVolMaterial.u_Shininess;
}

#ifndef PDSFX1_FS_AdvancedBRDFUser_BaseShaded
void ProcessBRDFParameters(inout BRDFParameters oParameters)
{
  basicProcessBRDFParameters(oParameters);
}
#endif
