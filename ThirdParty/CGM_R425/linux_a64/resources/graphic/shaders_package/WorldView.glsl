//layout(binding = 0, rgba8) uniform coherent image2D textureDesaturate;



layout (local_size_x = V_LOCAL_SIZE_X, local_size_y = 1) in;


bool IsValid(int iPos)
{
	return (g_worldVisibility[iPos >> 5] & (1 << (iPos & 31))) != 0;
}


void main() 
{
  int position = int(gl_GlobalInvocationID.x) * cb_worldView.batchSize;

  #ifdef V_WEIRD_BUG
  for(int i = 0 ; i < cb_worldView.batchSize ; ++i)
  #else
  for(int i = 0 ; i < 16 ; ++i)
  #endif
  {
	int fetch = position + i;
	  
	if(fetch < cb_worldView.nbMatrices && IsValid(fetch) )
	  g_worldViewMatrix[fetch] = mat4(cb_worldView.ViewMatrix * g_worldMatrix[fetch]);
  }

  
}
