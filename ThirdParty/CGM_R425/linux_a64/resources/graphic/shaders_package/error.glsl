float hash(in vec2 uv) 
{
  return fract(sin(dot(uv.xy ,vec2(12.9898,78.233))) * 43758.5453);
}
#ifdef VertexStage
void main()
{
  gl_Position = vec4(0.0,0.0,0.0,1.0);
}
#endif


#ifdef TessControlStage

layout (vertices = 1) out;

void main()
{
}

#endif //TessControlStage

#ifdef TessEvaluationStage

layout(triangles, equal_spacing, ccw) in;

void main()
{
  gl_Position = vec4(0.0,0.0,0.0,1.0);
}

#endif //TessEvaluationStage


#ifdef GeometryStage


layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

void main()
{  

}

#endif //GeometryStage


#ifdef ComputeStage

layout(local_size_x = 1, local_size_y = 1) in;

void main()
{ }


#endif //ComputeStage

#ifdef FragmentStage

const vec4 green   = vec4(0.0,1.0,0.0,1.);
const vec4 red = vec4(1.0,0.0,0.0,1.);

#ifndef GLES2Platform
layout(location = 0) out vec4 fragColor;
#endif

void main(void)
{
  vec4 noise;
  vec2 uv = normalize(gl_FragCoord.xy);
  float tt = hash(uv);
  noise = mix(red, green, tt);  
#ifndef GLES2Platform
  fragColor  = noise;
#else
  gl_FragColor = noise;
#endif
}


#endif


#ifdef RaygenStage

void main()
{ }


#endif //RayGenStage

#ifdef MissStage

void main()
{ }


#endif //RayGenStage
