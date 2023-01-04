
//layout(std430) buffer hashMapBuffer
//{
//  HashRecordContrib hashMap[];
//};

void main(void)
{
  // Maximum weight allowed to add new contributions. This limit is due to many threads potentially
  // adding to the same hash cell, and the weight being encoded on 16bit only. Half the range seems 
  // to avoid any overflow, while 32K samples is usually enough to obtain a converged result in any case.
  const int maxWeight = 32768;

  ivec2 pixel = ivec2(gl_FragCoord.xy);

  #ifdef IS_MSAA
    uvec4 cellIds = texelFetch(cellIndices, pixel, gl_SampleID);
    uint contribution = texelFetch(changeList, pixel, gl_SampleID).x;
  #else
    uvec4 cellIds = texelFetch(cellIndices, pixel, 0);
    uint contribution = texelFetch(changeList, pixel, 0).x;
  #endif

  if (cellIds.x == HASH_CELL_NOT_FOUND)
    return;

  if (contribution != 0)
  {
    if (cellIds.y != HASH_CELL_NOT_FOUND && getWeight(hashMap[cellIds.y].contribWeight) < maxWeight)
      atomicAdd(hashMap[cellIds.y].contribWeight, contribution);

    if (cellIds.z != HASH_CELL_NOT_FOUND && getWeight(hashMap[cellIds.z].contribWeight) < maxWeight)
      atomicAdd(hashMap[cellIds.z].contribWeight, contribution);

    if (cellIds.w != HASH_CELL_NOT_FOUND && getWeight(hashMap[cellIds.w].contribWeight) < maxWeight)
      atomicAdd(hashMap[cellIds.w].contribWeight, contribution);
  }


}
