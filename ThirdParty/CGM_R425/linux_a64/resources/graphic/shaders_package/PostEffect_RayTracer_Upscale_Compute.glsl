//layout(binding = 0, rgba8) uniform coherent image2D i_Source;
//layout(binding = 1, rgba8) uniform coherent image2D i_Dest;

layout (local_size_x = 16, local_size_y = 16) in;

void main() 
{
 ivec2 pos   = ivec2(gl_GlobalInvocationID.xy);
 
 vec4 A = imageLoad(i_Source, pos+ivec2(-1, 1)); 
 vec4 B = imageLoad(i_Source, pos+ivec2( 0, 1)); 
 vec4 C = imageLoad(i_Source, pos+ivec2( 1, 1)); 
 vec4 D = imageLoad(i_Source, pos+ivec2(-1, 0)); 
 vec4 E = imageLoad(i_Source, pos+ivec2( 0, 0)); 
 vec4 F = imageLoad(i_Source, pos+ivec2( 1, 0)); 
 vec4 G = imageLoad(i_Source, pos+ivec2(-1,-1)); 
 vec4 H = imageLoad(i_Source, pos+ivec2( 0,-1)); 
 vec4 I = imageLoad(i_Source, pos+ivec2( 1,-1)); 
    
 vec4 E0 = (D == B && B != H && D != F) ? D : E;
 vec4 E1 = (B == F && B != H && D != F) ? F : E;
 vec4 E2 = (D == H && B != H && D != F) ? D : E;
 vec4 E3 = (H == F && B != H && D != F) ? F : E;
 
 ivec2 storePos = pos*2;

 E0.w = 1.0;
 E1.w = 1.0;
 E2.w = 1.0;
 E3.w = 1.0;
 
 imageStore(i_Dest, storePos+ivec2(0,0), E0);
 imageStore(i_Dest, storePos+ivec2(0,1), E1);
 imageStore(i_Dest, storePos+ivec2(1,0), E2);
 imageStore(i_Dest, storePos+ivec2(1,1), E3);
}
