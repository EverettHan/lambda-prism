#ifndef MIPMAP_MODE
#define MIPMAP_MODE 0
#endif

//#if MIPMAP_MODE==3
//#define IMAGE_LAYOUT rgba8
//#else
//#define IMAGE_LAYOUT r8
//#endif

//layout(IMAGE_LAYOUT) uniform coherent image3D i_SrcImage;
//layout(IMAGE_LAYOUT) uniform coherent image3D i_DstImage;

layout (local_size_x = 16, local_size_y = 16) in;

void main() 
{
  if ( gl_GlobalInvocationID.x  >= MIPMAP_DEPTH 
    || gl_GlobalInvocationID.y  >= MIPMAP_DEPTH  
    || gl_GlobalInvocationID.z  >= MIPMAP_DEPTH)
    return;

  for (int depth = 0; depth < MIPMAP_DEPTH; depth++)
  {
    ivec3 coord = ivec3(gl_GlobalInvocationID.xy, depth);

#if MIPMAP_MODE==2
    // occ factor is computed using a mix between linear filtering and occ factor for each main direction

    float value = 0;
    float voxel_cube_2x2x2[2][2][2];

    for (int x = 0; x < 2; x++)
    {
      for (int y = 0; y < 2; y++)
      {
        for (int z = 0; z < 2; z++)
        {
          voxel_cube_2x2x2[x][y][z] = vImageLoad(i_SrcImage, 2 * coord + ivec3(x, y, z)).x;
        }
      }
    }
    
    for (int y = 0; y < 2; y++)
    {
      for (int z = 0; z < 2; ++z)
      {
        value += vMax(voxel_cube_2x2x2[0][y][z], voxel_cube_2x2x2[1][y][z]);
      }
    }

    for (int x = 0; x < 2; x++)
    {
      for (int z = 0; z < 2; z++)
      {
        value += vMax(voxel_cube_2x2x2[x][0][z], voxel_cube_2x2x2[x][1][z]);
      }
    }

    for (int x = 0; x < 2; x++)
    {
      for (int y = 0; y < 2; y++)
      {
        value += vMax(voxel_cube_2x2x2[x][y][0], voxel_cube_2x2x2[x][y][1]);
      }
    }

    value += vMax( voxel_cube_2x2x2[1][0][0], voxel_cube_2x2x2[0][1][1]);
    value += vMax( voxel_cube_2x2x2[0][1][0], voxel_cube_2x2x2[1][0][1]);
    value += vMax( voxel_cube_2x2x2[0][0][1], voxel_cube_2x2x2[1][1][0]);
    value += vMax( voxel_cube_2x2x2[0][0][0], voxel_cube_2x2x2[1][1][1]);
    
    vImageStore(i_DstImage, coord, vec4(value/16.0));

#elif MIPMAP_MODE==3
    // Tri Occ: one occlusion factor is computed for each main directrion

    vec3 value = vec3(0);
    vec3 voxel_cube_2x2x2[2][2][2];

    int i,j,k;

    for (i = 0; i < 2; i++)
    {
      for (j = 0; j < 2; j++)
      {
        for (k = 0; k < 2; k++)
        {
          voxel_cube_2x2x2[i][j][k] = vImageLoad(i_SrcImage, 2 * coord + ivec3(i, j, k)).xyz;
        }
      }
    }

    for (i= 0; i < 2; i++)
    {
      for (int j = 0; j < 2; j++)
      {
        value.x += vMax(voxel_cube_2x2x2[0][i][j].x, voxel_cube_2x2x2[1][i][j].x);
        value.y += vMax(voxel_cube_2x2x2[i][0][j].y, voxel_cube_2x2x2[i][1][j].y);
        value.z += vMax(voxel_cube_2x2x2[i][j][0].z, voxel_cube_2x2x2[i][j][1].z);

        /*value.x += voxel_cube_2x2x2[0][i][j].x + (1.0 - voxel_cube_2x2x2[0][i][j].x) * voxel_cube_2x2x2[1][i][j].x;
        value.y += voxel_cube_2x2x2[i][0][j].y + (1.0 - voxel_cube_2x2x2[i][0][j].y) * voxel_cube_2x2x2[i][1][j].y;
        value.z += voxel_cube_2x2x2[i][j][0].z + (1.0 - voxel_cube_2x2x2[i][j][0].z) * voxel_cube_2x2x2[i][j][1].z;*/
      }
    }

    vImageStore(i_DstImage, coord, vec4(value.xyz/4.0, 0.0));
    //vImageStore(i_DstImage, coord, vec4(1.0));
#else
    // Tri Linear Filtering

    float value = 0;
    for (int i = 0; i < 2; i++)
    {
      for (int j = 0; j < 2; j++)
      {
        for (int k = 0; k < 2; k++)
        {
          ivec3 tmpCoord = coord*2 + ivec3(i,j,k);
          value += vImageLoad(i_SrcImage, tmpCoord).x;
        }
      }
    }

    vImageStore(i_DstImage, coord, vec4(value/8.0));

#endif
  }
}

