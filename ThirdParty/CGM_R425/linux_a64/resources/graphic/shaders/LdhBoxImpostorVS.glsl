const int  BOX_TEXTURE_WIDTH = 16384;

uint modui( uint a, uint b ) { return a - b * (a / b); }

uint bitAtIndex( uint bits, uint index ) { return modui( bits / uint(exp2( index )), 2 ); }

uint getVisibility( int instanceID )
{
#ifdef PDSFXInstancing
  // CustomInstanceBuffer stores the visibility bits as RGBA (four 32-bit floats)
  // It amounts to 128 bits per texel

  int texelIndex = instanceID / 128;
  uint bitIndexInTexel = modui( instanceID, 128 );
  uint componentIndex = bitIndexInTexel / 32;
  uint bitIndexInComponent = modui( bitIndexInTexel, 32 );

  float visComponent = vGetInstanceData( texelIndex )[componentIndex];
  return bitAtIndex( floatBitsToUint( visComponent ), bitIndexInComponent );
#else
  return 0;
#endif
}

vec3 computePosition( vec3 pos, int instanceID )
{
    // The width of the texture MUST BE EVEN, so that the two pixels containing the box data are side by side (and not split on two different rows)
    int geomIndex = 2 * instanceID;
    int geomV = geomIndex / BOX_TEXTURE_WIDTH;
    int geomU = geomIndex - geomV * BOX_TEXTURE_WIDTH;

    vec3 trans = vTexelFetch( TextureGeometry, ivec2( geomU, geomV ), 0 ).rgb;
    vec3 scale = vTexelFetch( TextureGeometry, ivec2( geomU + 1, geomV ), 0 ).rgb;

    return trans + scale * pos;
}

vec3 ComputeObjectPosition()
{
    // Visibility
    uint visible = getVisibility( vGetInstanceID() );
    if( visible == 0 )
        return vec3( 0, 0, 0 );

    // Normal
    vNormal = vGetAttribNormal().xyz;

    // Position
    return computePosition( vGetPosition().xyz, vGetInstanceID() );
}
