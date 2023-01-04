#if (defined(Capping) || defined(CappingEnabled)) && !defined(GLES2Platform)

// Z value for a non initialiazed fragment
const uint kDefaultDepth = vFloatBitsToUint(1.0);

// Capping polygon offset due to Z fight with edges
const float kOffset = 0.000001;

// Infinite value for Z in view space
const float kInfiniteFloat = 1000000000.0;

#endif
