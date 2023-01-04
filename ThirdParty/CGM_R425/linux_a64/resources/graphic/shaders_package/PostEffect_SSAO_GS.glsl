layout(triangles) in;

#ifdef GL_NV_geometry_shader_passthrough
//--------------------------------------------------
// 1er pass
// Optim passthrough

layout(passthrough) in gl_PerVertex
{
  vec4 gl_Position;

};

void main()
{
  // on dessine deux triangles pour chaque quad -> /2
  gl_Layer = gl_PrimitiveIDIn / 2;
}

#else

layout(triangle_strip, max_vertices = 3) out;

//--------------------------------------------------
// Code standard

void main()
{
  for (int i = 0; i < 3; i++) 
  {
    // on dessine deux triangles pour chaque quad -> /2
    gl_Layer    = gl_PrimitiveIDIn / 2;
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }
  EndPrimitive();
}

#endif
