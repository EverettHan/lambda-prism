///////////////////////////////////////
// Shader Builder Vertex Shader Code //
///////////////////////////////////////


void main()
{
  //If we have a Tessellation stage, we must output in the vertex shader the object space.
#ifdef UseTessellationStage
  _ProcessVertexOperation(true);
#else
  _ProcessVertexOperation(false);
#endif
}
