float ComputePointSize()
{
  return cb_cbVolMaterial.u_PointSize;
}

// Customize this function to handle additionnal vertex transformations
void ComputeVaryingValues()
{
#ifdef VertexColor
  vColor = vGetColor();
#endif // VertexColor
}

void ProcessClipSpacePosition(inout vec4 ioPosition)
{ 
  AlignPoint(ioPosition);
}
