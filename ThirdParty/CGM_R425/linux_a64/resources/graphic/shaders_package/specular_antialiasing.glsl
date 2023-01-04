// [EOO2]
// See paper "Stable Geometric Specular Antialiasing with Projected-Space NDF Filtering"
// and related publications by Anton S. Kaplanyan

#ifdef FragmentStage

// Listing 1. Our projected-space non-axis-aligned filtering (HLSL). -> GLSL
// This version is not used, but still valid, could be experimented with if the approximate
// version (listing 2) is not good enough.
//mat2 NonAxisAlignedNDFFiltering(const in vec3 H_ts, const in vec2 roughness2) {
//	const vec2 deltaU = vDFdx(H_ts.xy);
//	const vec2 deltaV = vDFdy(H_ts.xy);
//	const float SIGMA2 = 0.15915494f; // 0.5/pi
//	const mat2 delta = mat2(deltaU, deltaV);
//	// 2 * covariance matrix for the filter kernel
//	const mat2 kernelRoughnessMat = 2.0f * SIGMA2 * transpose(delta) * delta;
//	const vec2 projRoughness2 = roughness2 / (1.0f - roughness2);
//	const mat2 projRoughnessMat = mat2(projRoughness2.x, 0.0f, 0.0f, projRoughness2.y);
//	const mat2 filteredProjRoughnessMat = projRoughnessMat + kernelRoughnessMat;
//	const float detMin = projRoughness2.x * projRoughness2.y;
//	const float det = max(determinant(filteredProjRoughnessMat), detMin);
//	const mat2 m = filteredProjRoughnessMat / det + mat2(1.0f, 0.0f, 0.0f, 1.0f);
//	const mat2 filteredRoughnessMat = m / max(determinant(m), 1.0);
//	return filteredRoughnessMat;
//}

// Listing 2. Practical approximation of our projected-space non-axis-aligned filtering (HLSL). -> GLSL
// This implementation is the same as Kaplanyan et al.’s slope-space filtering, except the red
// code is removed.
mat2 NonAxisAlignedNDFFiltering2(const in vec3 H_ts, const in vec2 roughness2) {
	const vec2 deltaU = vDFdx(H_ts.xy);
	const vec2 deltaV = vDFdy(H_ts.xy);
	const float SIGMA2 = 0.15915494f; // 0.5/pi
	const mat2 delta = mat2(deltaU, deltaV);
	// 2 * covariance matrix for the filter kernel
	const mat2 kernelRoughnessMat = 2.0f * SIGMA2 * transpose(delta) * delta;
	const mat2 roughnessMat = mat2(roughness2.x, 0.0f, 0.0f, roughness2.y);
	const mat2 filteredRoughnessMat = roughnessMat + kernelRoughnessMat;
	return filteredRoughnessMat;
}

#endif // FragmentStage
