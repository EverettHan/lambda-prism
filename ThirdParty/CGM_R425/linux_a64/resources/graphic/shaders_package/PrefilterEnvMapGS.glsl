layout(invocations = 6) in;
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec2 vTexCoord[3];

out vec2 gTexCoord;

void main()
{  
  for(int i = 0; i < gl_in.length(); i++)
  {
    gTexCoord = vTexCoord[i];
    gl_Position = gl_in[i].gl_Position;

    #ifdef SO_CUBE_MAP_LAYER
      gl_Layer = 6 * SO_CUBE_MAP_LAYER + gl_InvocationID;
    #else
      gl_Layer = gl_InvocationID;
    #endif

    EmitVertex();
  }

  EndPrimitive();
}
