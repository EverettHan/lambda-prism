#ifdef USE_MUTEX

uniform coherent layout(r32ui) uimage2D semaphoreImg;

bool AcquireSemaphore(ivec2 iCoord)
{
  return imageAtomicExchange(semaphoreImg, iCoord, uint(1)) == uint(0);
}

void ReleaseSemaphore(ivec2 iCoord)
{
  imageAtomicExchange(semaphoreImg, iCoord, uint(0));
}


#ifdef OIT

uint AcquireSemaphoreOIT(ivec2 iCoord)
{
  return imageAtomicExchange(semaphoreImg, iCoord, uint(0));
}

void ReleaseSemaphoreOIT(ivec2 iCoord, uint iValue)
{
  imageAtomicExchange(semaphoreImg, iCoord, iValue);
}

#endif

#endif //USE_MUTEX
