////////////////////////////////
// Client Code Basic Skeleton //
////////////////////////////////
//#define USE_TANGENT_SPACE

vec3 GetLocalPosition()
{
  return vGetPosition();
}

void TransformFinalPosition(inout vec4 position)
{    
}


void ComputeCommonValues()
{
  
}


// customize this function to handle additionnal vertex transformations
// 'Pos' in vOut will already have been written when this function is called, and can be modified is desired
void ProcessVertexCustom()
{        
}

// Customize this function to change the tangent space
// Tangent space coordinates are in world
void ProcessTangentSpaceCustom(inout TangentSpace worldTS)
{
}

// Specialize this to change the specular exponent. This function is called when performing per pvertex specular lighting.
// Coordinates are in world space
float ComputeSpecularPower()
{
  return 0.5;
}

