#ifdef Lighting

#ifdef NumberOfLightsWithProfile

void ComputeProfileLighting(inout LightingResult res, inout LightingData iData, in BRDFParameters iParameters)
{
#ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
	iData.lightType = LIGHT_TYPE_PROFILE;
#endif
	for (int i = 0; i < vMin(NumberOfLightsWithProfile, _V_MAX_LIGHTS); ++i)
	{
#ifdef LightChannels
		if ((cb_cbVolMaterial.u_LightChannels & cb_LightChannels.ProfileChannels[i]) == 0)
			continue;
#endif
		iData.L = _sbCbLightsWithProfile.WorldMatrix[i][3].xyz - iData.P;
		const float lightDistSquare = vDot(iData.L, iData.L);
		iData.L *= 1. / vSqrt(lightDistSquare);
		const float lightAttenuation = 1.0 / lightDistSquare;
		iData.irradiance = lightAttenuation * _sbCbLightsWithProfile.PowerFactor[i] * _sbCbLightsWithProfile.Color[i];

		// Compute IES attenuation
		vec4 iesSampleDirection = - _sbCbLightsWithProfile.WorldMatrix[i] * vec4(iData.L, 0.0);
		float phiCoord = vAcos(iesSampleDirection.x) * INV_PI;
		float theta = vAtan(iesSampleDirection.y, iesSampleDirection.z);
		float thetaCoord = theta * INV_PI * 0.5;
#ifdef LightProfileMapAsArray
		vec3 texCoord = vec3(thetaCoord, phiCoord, float(_sbCbLightsWithProfile.MapIndex[i]));
#else
		vec2 texCoord = vec2(thetaCoord, phiCoord);
#endif
		float iesProfileScale = vTexture(lightProfileMap, texCoord).r;

		iData.irradiance *= iesProfileScale;
		iData.visibility = vMax(1.0, iData.minVisibility);
		iData.lightID = i;

		ComputeRenderingEquation(iData, iParameters, res);
	}
}

#endif // NumberOfLightsWithProfile

#ifdef NumberOfAreaLights

#define InvalidAreaType -1
#define SphereAreaType 0
#define TubeAreaType 1
#define DiskAreaType 2
#define RectangleAreaType 3

struct AreaLightData
{
	vec3 closestPoint;
	float lightDist;
	float lightRadius;
	float lightSpecAtt; // Manage some hacks
};

vec3 DiffuseLambertBRDF(vec3 diffuseColor) {
	return (diffuseColor * INV_PI);
}

#define LUT_SIZE 64.0
#define LUT_SCALE (LUT_SIZE - 1.0)/LUT_SIZE
#define LUT_BIAS 0.5/LUT_SIZE

#if defined(Coating) || defined(SO_EVISUPBR_CLEARCOAT)
#define COATINGF0 vec3(0.04)
#define COATINGF90 vec3(1.0)
#endif // Coating


float vMaxComp(const in vec2 v) {
	return vMax(v.x, v.y);
}

float vMaxComp(const in vec3 v) {
	return vMax(vMaxComp(v.xy), v.z);
}

float vMaxComp(const in vec4 v) {
	return vMax(vMaxComp(v.xy), vMaxComp(v.zw));
}

#ifdef XRiteCarPaint2

void XRiteCarPaint2AreaModel(out vec3 specular, out vec3 diffuse,
	in BRDFParameters materialData, in LightingData iData) {
	const vec3 N_ss  = iData.Nworld;
	const vec3 V_ss  = iData.Vworld;
	//const vec3 Nc_ss = vec3(vGetViewInvMatrix() * vec4(materialData.clearcoatNormal, 0.0));
	const vec3 Nc_ss = N_ss;
	const vec3 L_ss  = vec3(vGetViewInvMatrix() * vec4(iData.L, 0.0));
	const vec3 Rc_ss = vNormalize(-vReflect(V_ss, Nc_ss));
	const float solid_angle = 0.0;
	vec3 wo_trans;
	float f_trans_out;
	const float f_refl_out = CPA2_ProcessLight_clearcoat_layer(V_ss, Nc_ss, Rc_ss,
		materialData.clearcoat_no_refraction, materialData.clearcoat_ior, wo_trans, f_trans_out);
	const vec3 bsdf = CPA2_ProcessLightAxfCpa2(N_ss, V_ss, Nc_ss, L_ss, solid_angle,
		wo_trans, f_trans_out, materialData);
	specular += bsdf;
}

#endif // XRiteCarPaint2

#ifdef EVisuPBR

struct evisuBRDFData
{
	vec3 albedoEvisu;
	float F0;
	vec3 sr0Color;
	vec3 sr90Color;
	vec3 specularEnergyConservationConstant;
	float diffuseEnergyConservationConstant;
#if (defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x))
	float sheenEnergyConservationConstant;
#endif
};
evisuBRDFData evisuMaterialData;

#ifdef SO_EVISUPBR_FLAKES
struct evisuPBRFlakesData
{
	float smooth_weight;
	vec3 stochasticHemisphereFlakesOrientation;
	float stochastic_weight;
	float closeup_weight;
	vec3 voronoi_cell_orientation;
	float base_weight;
};
evisuPBRFlakesData evisuFlakesData;
#endif //SO_EVISUPBR_FLAKES

#ifdef SO_EVISUPBR_SHEEN
void setAreaSheenData(in float roughness, in float NoV, out mat3 Minv) {

	vec2 uvAr = vec2(roughness, 1.0 - vSqrt(1.0 - NoV)) * LUT_SCALE + LUT_BIAS;

#if ( defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x) )
	vec4 t1 = vTexture(AreaLightGGX, vec3(uvAr, 3));
#else
	vec4 t1 = vTexture(AreaLightGGX, vec3(uvAr, 2));
#endif //SO_EVISUPBR_ver21x || SO_EVISUPBR_ver22x

	Minv = mat3(
		vec3(t1.x, 0, t1.y),
		vec3(0, 1.0, 0),
		vec3(t1.z, 0, t1.w)
	);
}
#endif // SO_EVISUPBR_SHEEN

float vLerp(const in float a, const in float b, const in float w) {
	return a + w * (b - a);
}

float AverageDirectionalMultipleAlbedo(const in float roughness) {
	const float a2 = vPow4(roughness);
	return 1.0 + a2 * (-0.133 + a2 * (-1.8695 + a2 * (2.2268 - 0.83397*a2)));
}

vec3 AverageMultipleFresnel(const in vec3 sr0Color, const in vec3 sr90Color) {
	return vMix(sr90Color, sr0Color, 0.95238095238);
}

float DirectionalMultipleAlbedo(const in float cosTheta, const in float roughness) {
	const float a2 = vPow4(roughness);
	float res = 3.09507 + cosTheta * (-9.11369 + cosTheta * (15.8884 + cosTheta * (-13.70343 + 4.51786 * cosTheta)));
	res *= (-0.20277 + a2 * (2.772 + a2 * (-2.6175 + 0.73343*a2)));
	res *= 1.4594 * a2 * cosTheta;
	return 1.0 - res;
}

float DirectionalAlbedo(const in float F0, const in vec3 specularTint,
	const in float cosTheta, const in float roughness) {
	const float a2 = vPow4(roughness);
	const float E0 = F0 * vMaxComp(specularTint);
	return vLerp(E0 + (1.0 - E0) * vPow5(1.0 - cosTheta), 0.04762 + 0.95238*E0, 1.0 - vPow5(1.0 - a2));
}

float AverageDirectionalAlbedo(const in float F0, const in vec3 specularTint, const in float roughness) {
	const float a2 = vPow4(roughness);
	const float E0 = F0 * vMaxComp(specularTint);
	return E0 + (-0.33263 * a2 - 0.072359) * (1.0 - E0) * E0;
}

#if defined(SO_EVISUPBR_SHEEN) && ( defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x) )
float DirectionalSheenAlbedo(const in float cosTheta, const in float roughness) {
	return 0.04495972 + 0.47479907 * (sqrt(1.0 - cosTheta) + (1.0 - cosTheta) * sqrt(1.0 - sqrt(roughness)));
}
#endif

void computeBRDFParamforEvisu(in BRDFParameters materialData) {
	evisuMaterialData.albedoEvisu = materialData.albedo * (1.0 - materialData.metallic) * (1.0 - materialData.transparency);
	evisuMaterialData.F0 = vPow2((materialData.ior - 1.0) / (materialData.ior + 1.0));
	evisuMaterialData.sr0Color = (1.0 - materialData.metallic) * evisuMaterialData.F0 * materialData.specular * materialData.specularTint + materialData.metallic * materialData.albedo;
	evisuMaterialData.sr90Color = vec3(1.0) * ((1.0 - materialData.metallic) * materialData.specular + materialData.metallic);
}

void computeEvisuEnergyConservation(in vec3 N, in vec3 V, in BRDFParameters materialData) {
	float NoV = vSaturate(vDot(N, V));

	float averageDirectionalMultipleAlbedo = AverageDirectionalMultipleAlbedo(materialData.roughness);
	vec3 averageMultipleFresnel = AverageMultipleFresnel(evisuMaterialData.sr0Color, evisuMaterialData.sr90Color);

	evisuMaterialData.specularEnergyConservationConstant = vPow2(1.0 - DirectionalMultipleAlbedo(NoV, materialData.roughness)) / vMax(1.0 - averageDirectionalMultipleAlbedo, 1e-6)
		* (averageMultipleFresnel * averageMultipleFresnel * averageDirectionalMultipleAlbedo) / vMax(1.0 - averageMultipleFresnel
			* (1.0 - averageDirectionalMultipleAlbedo), vec3(1e-6));

	evisuMaterialData.diffuseEnergyConservationConstant = vMix(1.0, vPow2(1.0 - DirectionalAlbedo(evisuMaterialData.F0, materialData.specularTint, NoV, materialData.roughness))
		/ vMax(1.0 - AverageDirectionalAlbedo(evisuMaterialData.F0, materialData.specularTint, materialData.roughness), 1e-6), materialData.specular);

#if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver21x)
	evisuMaterialData.sheenEnergyConservationConstant = materialData.sheen * vMaxComp(materialData.sheenColor) * DirectionalSheenAlbedo(NoV, materialData.sheenRoughness);
#endif

#if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver22x)
	evisuMaterialData.sheenEnergyConservationConstant = vMaxComp(materialData.sheenColor) * DirectionalSheenAlbedo(NoV, materialData.sheenRoughness);
#endif
}

#ifdef SO_EVISUPBR_FLAKES
void computeFlakesParam(in BRDFParameters iParameters, in LightingData iData)
{
	float total_flake_roughness = iParameters.flakeRoughness*iParameters.flakeRoughness;

	float flake_orientation_roughness;
	float flake_cos_cone_angle;

	float flake_coverage = iParameters.flakeCoverage;
	float flake_cone_roughness;

	distribute_flake_roughness(total_flake_roughness, flake_orientation_roughness, flake_cos_cone_angle, flake_cone_roughness);

	float a = 0.001 * (iParameters.flakeSize * 0.5);
	float avg_cell_area = 1.5 * sqrt(3.0) * a * a;
	float cells_per_area = 1.0 / avg_cell_area;

	mat3 mat = transpose(mat3(_vPrivGetWorldMatrix()));
	float scale = max(max(length(mat[0]), length(mat[1])), length(mat[2]));

	vec3 position_object = EVisuPBR_vLocalPosition;
	vec3 position_object_meters = 0.001 * scale * position_object;

	vec3 p_ddx = dFdxFine(position_object_meters);
	vec3 p_ddy = dFdyFine(position_object_meters);

	vec2 footprint_uv;
	vec2 footprint_uv_ddx;
	vec2 footprint_uv_ddy;
	triplanar_mapping(position_object_meters, p_ddx, p_ddy, EVisuPBR_vLocalNormal, footprint_uv, footprint_uv_ddx, footprint_uv_ddy);

	float footprint_det = footprint_uv_ddx.x * footprint_uv_ddy.y - footprint_uv_ddx.y * footprint_uv_ddy.x;
	float footprint_area = abs(footprint_det);

	float flakes_per_area = flake_coverage * cells_per_area;
	float expected_num_flakes_inside_footprint = footprint_area * flakes_per_area;

	float log_cells_in_footprint = log(footprint_area / avg_cell_area);

#ifdef SO_EVISUPBR_FLAKE_ACCURACY_GOAL
#if SO_EVISUPBR_FLAKE_ACCURACY_GOAL == 0
	//Quality
	float closeup_stochastic_transition = 1.0;
	float closeup_smooth_transition = 64.0;
	float stochastic_smooth_transition = 131072.0;
#elif SO_EVISUPBR_FLAKE_ACCURACY_GOAL == 1
	//Performance
	float closeup_stochastic_transition = 1.0;
	float closeup_smooth_transition = 4.0;
	float stochastic_smooth_transition = 1024.0;
#endif
#endif //SO_EVISUPBR_FLAKE_ACCURACY_GOAL

	model_weights(closeup_stochastic_transition, closeup_smooth_transition, stochastic_smooth_transition, flake_coverage, log_cells_in_footprint, evisuFlakesData.base_weight, evisuFlakesData.closeup_weight, evisuFlakesData.stochastic_weight, evisuFlakesData.smooth_weight, evisuFlakesData.voronoi_cell_orientation, flake_orientation_roughness, cells_per_area, footprint_uv, footprint_uv_ddx, footprint_uv_ddy);
	if (evisuFlakesData.stochastic_weight > 0.0)
	{
		evisuFlakesData.stochasticHemisphereFlakesOrientation = vec3(0.0);
		contributing_flakes_in_footprint_stochastic_hemisphere(flake_orientation_roughness, flake_cos_cone_angle, flake_coverage, cells_per_area, footprint_uv, footprint_uv_ddx, footprint_uv_ddy, -iData.V, iData.L, iData.N, evisuFlakesData.stochasticHemisphereFlakesOrientation);
	}
}
#endif //SO_EVISUPBR_FLAKES

#endif //EVisuPBR

#if (!(defined(EVisuPBR) || defined(XRiteCarPaint2)))
vec3 computeAreaSpecularBRDF(in LightingData iData, in AreaLightData iAreaData, in BRDFParameters iParameters)
{
	vec3 l = vNormalize(iAreaData.closestPoint);
	vec3 H = vHalfVector(iData.V, l);

	float dot_N_V = vMax(vDot(iData.N, iData.V), 0.0);
	float dot_N_L = vMax(vDot(iData.N, l), 0.0);
	float dot_N_H = vMin(vDot(iData.N, H), 1.0 - kEpsilon); // This clamp is required to avoid some distribution computation issues with low power lights.
#if defined(AnisotropicDistribution) && defined(Fabrics)
	float roughness = computeAnisotropicRoughness(iData.T, iData.B, iData.N, H, iParameters.roughness, iParameters.anisotropyAngle, iParameters.anisotropy);
#else
	float roughness = computeRoughness(iParameters.roughness);
#endif
	float alphaPrime = vClamp(iAreaData.lightRadius / (iAreaData.lightDist * 2.0) + vPow2(roughness), 0.0, 1.0);

	float D = 1.;
	{
#if defined(AnisotropicDistribution) && !defined(Fabrics)
		D = AnisotropicGGXNormalDistribution(iData.T, iData.B, iData.N, H, dot_N_H, roughness, iParameters.anisotropyAngle, iParameters.anisotropy);
#else
		D = NormalDistribution(dot_N_H, roughness);
#endif
		//D = vMax(D*alphaPrime, 0.0);
	}

	float LoH = max(vDot(l, H), kEpsilon);
	vec3 F = OptimizedSchlickFresnel(iParameters.f0, iParameters.f90, LoH);

	float Vis = UnrealVisibility(roughness, dot_N_L, dot_N_V);
	return dot_N_L * Vis * D * F; //* iAreaData.lightSpecAtt;
}

float SpecGlossEnergyConservationTerm(const in vec3 fresnel) {
	const vec3 luminanceVector = vec3(0.299, 0.587, 0.114);
	return 1.0 - vDot(fresnel, luminanceVector);
}

#endif // (!(defined(EVisuPBR) || defined(XRiteCarPaint2)))

void ComputeAreaLightEquation(out vec3 specular, out vec3 diffuse, in LightingData iData,
	in AreaLightData iAreaData, in BRDFParameters iParameters, inout LightingResult ioResult)
{
#ifdef XRiteCarPaint2
	XRiteCarPaint2AreaModel(specular, diffuse, iParameters, iData);
	return;
#endif // XRiteCarPaint2

#ifdef EVisuPBR

	vec3 n = iData.N;
	vec3 v = iData.V;
	vec3 l = vNormalize(iAreaData.closestPoint);
	vec3 h = normalize(l + v);
	vec3 t = normalize(iData.T);
	vec3 b = normalize(iData.B);

	const float NoL = max(vDot(n, l), 0.0);
	const float NoV = max(vDot(n, v), 0.0);
	const float NoH = max(vDot(n, h), 0.0);
	const float LoH = max(vDot(l, h), 0.0);
	const float VoH = max(vDot(v, h), 0.0);

	distribution_ggx_parameters ggxParams;
	distribution_ggx_initialize(ggxParams, iParameters.roughness, iParameters.anisotropy);

	specular = distribution_ggx(ggxParams, n, v, l, h, t, b, NoL, NoV, NoH, LoH) * fresnel_schlick(evisuMaterialData.sr0Color, evisuMaterialData.sr90Color, VoH);
	specular += DiffuseLambertBRDF(evisuMaterialData.specularEnergyConservationConstant);

#if !defined(LightMap) || (LightMap != LightMapIlluminanceMode)
	diffuse = DiffuseLambertBRDF(evisuMaterialData.albedoEvisu) * evisuMaterialData.diffuseEnergyConservationConstant;
#else
	diffuse = vec3(0.0);
#ifdef FragmentStage
	specular *= vSaturate(vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz);
#endif
#endif

#if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver19x)
	{
		distribution_inverted_ashikhmin_parameters sheenParams;
		distribution_inverted_ashikhmin_initialize(sheenParams, iParameters.sheen);

		float sheenBlending = 1.0 - vPow5(1.0 - iParameters.sheen);
		diffuse *= max(vec3(0.0), PI * (distribution_inverted_ashikhmin(sheenParams, NoH) / (4.0 * max(NoL + NoV - NoL*NoV, 1e-6))) * sheenBlending + (1 - sheenBlending));
	}
#endif

#if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver21x)
	{
		vec3 f_b = vec3(0.0);
		float b_weight = 1.0;

		// see dspbr_sheen.glsl
		ApplyDSPBR21xSheenLayer(f_b, b_weight, NoL, NoV, NoH,
			iParameters.sheen, iParameters.sheenColor, iParameters.sheenRoughness); // sheenDirectionalAlbedo_map

		specular *= b_weight;
		diffuse *= b_weight;
		specular += f_b;
	}
#endif // SO_EVISUPBR_SHEEN && SO_EVISUPBR_ver21x

#if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver22x)
	{
		vec3 f_b = vec3(0.0);
		float b_weight = 1.0;

		// see dspbr_sheen.glsl
		ApplyDSPBR22xSheenLayer(f_b, b_weight, NoL, NoV, NoH,
			iParameters.sheenColor, iParameters.sheenRoughness); // sheenDirectionalAlbedo_map

		specular *= b_weight;
		diffuse *= b_weight;
		specular += f_b;
	}
#endif // SO_EVISUPBR_SHEEN && SO_EVISUPBR_ver22x

#ifdef SO_EVISUPBR_FLAKES
	{
		float base_weight = 1.0;
		vec3 f_s = vec3(0.0);

		float total_flake_roughness = iParameters.flakeRoughness*iParameters.flakeRoughness;

		float flake_orientation_roughness;
		float flake_cos_cone_angle;

		float flake_coverage = iParameters.flakeCoverage;
		float flake_cone_roughness;

		distribute_flake_roughness(total_flake_roughness, flake_orientation_roughness, flake_cos_cone_angle, flake_cone_roughness);

		float a = 0.001 * (iParameters.flakeSize * 0.5);
		float avg_cell_area = 1.5 * sqrt(3.0) * a * a;
		float cells_per_area = 1.0 / avg_cell_area;

		mat3 mat = transpose(mat3(_vPrivGetWorldMatrix()));
		float scale = max(max(length(mat[0]), length(mat[1])), length(mat[2]));

		vec3 position_object = EVisuPBR_vLocalPosition;
		vec3 position_object_meters = 0.001 * scale * position_object;

		vec3 p_ddx = dFdxFine(position_object_meters);
		vec3 p_ddy = dFdyFine(position_object_meters);

		vec2 footprint_uv;
		vec2 footprint_uv_ddx;
		vec2 footprint_uv_ddy;
		triplanar_mapping(position_object_meters, p_ddx, p_ddy, EVisuPBR_vLocalNormal, footprint_uv, footprint_uv_ddx, footprint_uv_ddy);

		float footprint_det = footprint_uv_ddx.x * footprint_uv_ddy.y - footprint_uv_ddx.y * footprint_uv_ddy.x;
		float footprint_area = abs(footprint_det);

		float flakes_per_area = flake_coverage * cells_per_area;
		float expected_num_flakes_inside_footprint = footprint_area * flakes_per_area;

		float log_cells_in_footprint = log(footprint_area / avg_cell_area);

		float closeup_weight = 0.0;
		float stochastic_weight = 0.0;
		float smooth_weight = 0.0;
		vec3 voronoi_cell_orientation = vec3(0.0);

#ifdef SO_EVISUPBR_FLAKE_ACCURACY_GOAL
#if SO_EVISUPBR_FLAKE_ACCURACY_GOAL == 0
		//Quality
		float closeup_stochastic_transition = 1.0;
		float closeup_smooth_transition = 64.0;
		float stochastic_smooth_transition = 131072.0;
#elif SO_EVISUPBR_FLAKE_ACCURACY_GOAL == 1
		//Performance
		float closeup_stochastic_transition = 1.0;
		float closeup_smooth_transition = 4.0;
		float stochastic_smooth_transition = 1024.0;
#endif
#endif

		model_weights(closeup_stochastic_transition, closeup_smooth_transition, stochastic_smooth_transition, flake_coverage, log_cells_in_footprint, base_weight, closeup_weight, stochastic_weight, smooth_weight, voronoi_cell_orientation, flake_orientation_roughness, cells_per_area, footprint_uv, footprint_uv_ddx, footprint_uv_ddy);

		float cos_cone_angle = flake_cos_cone_angle;
		vec3 front_flake_orientation = voronoi_cell_orientation;
		float cone_solid_angle = 2.0 * PI * (1.0 - cos_cone_angle);
		vec3 front_flake_orientation_view = normalize(front_flake_orientation.x*t - front_flake_orientation.y*b + front_flake_orientation.z*n);
		vec3 r = normalize(reflect(-v, front_flake_orientation_view));
		bool inside_flake_cone = vDot(r, l) > cos_cone_angle;

		if (closeup_weight > 1e-6 && inside_flake_cone && front_flake_orientation.z > 0.0)
		{
			float single_flake_eval = 1.0 / (cone_solid_angle * abs(vDot(l, n)));
			f_s += iParameters.flakeColor * closeup_weight * single_flake_eval;
		}

		if (stochastic_weight > 1e-6)
		{
			float flakes_contributing = 0.0;
			float flakes_in_footprint = 0.0;
			stochastic_flakes(flake_orientation_roughness, cos_cone_angle, expected_num_flakes_inside_footprint, cells_per_area, footprint_uv, footprint_uv_ddx, footprint_uv_ddy, flake_coverage, -v, l, n, flakes_contributing, flakes_in_footprint);
			float dotVH = vDot(v, h);
			float flake_count_threshold = 10.0;
			float alpha = min(1.0, flakes_in_footprint / flake_count_threshold);
			float reference_flake_count = mix(expected_num_flakes_inside_footprint, flakes_in_footprint, alpha);
			reference_flake_count = max(0.01, reference_flake_count);

			float d = flakes_contributing / (cone_solid_angle * reference_flake_count);
			distribution_ggx_parameters params;
			distribution_ggx_initialize(params, flake_orientation_roughness, 0.0);
			float g = distribution_ggx_g(params, n, v, l, t, b, NoL, NoV);
			f_s += stochastic_weight * iParameters.flakeColor * dotVH * g * d / abs(vDot(v, n) * vDot(l, n));
		}

		if (smooth_weight > 1e-6)
		{
			distribution_ggx_parameters paramsSmooth;
			distribution_ggx_initialize(paramsSmooth, iParameters.flakeRoughness, 0.0);
			float smooth_flake = distribution_ggx(paramsSmooth, n, v, l, h, t, b, NoL, NoV, NoH, LoH);
			f_s += smooth_weight * iParameters.flakeColor * smooth_flake;
		}

		diffuse *= base_weight;
		specular *= base_weight;
		specular += f_s;
	}
#endif // SO_EVISUPBR_FLAKES

#ifdef SO_EVISUPBR_CLEARCOAT
	{
		distribution_ggx_parameters params;
		distribution_ggx_initialize(params, iParameters.clearcoatRoughness, 0.0);
		const float NcoV = vMax(vDot(iParameters.clearcoatNormal, v), 0.0);
		const float NcoL = vMax(vDot(iParameters.clearcoatNormal, l), 0.0);
		const float NcoH = vMax(vDot(iParameters.clearcoatNormal, h), 0.0);
		const float clearcoatF = 0.04 + 0.96 * vPow5(1.0 - LoH); // By definition LoH == VoH
		const float clearcoatF1 = 0.04 + 0.96 * vPow5(1.0 - NcoV);
		const float clearcoatF2 = 0.04 + 0.96 * vPow5(1.0 - NcoL);
		const float clearcoat_att_fac = (1.0 - iParameters.clearcoat * vMax(clearcoatF1, clearcoatF2));
		const float f_coat = distribution_ggx(params, iParameters.clearcoatNormal, v, l, h, t, b, NcoL, NcoV, NcoH, LoH) * iParameters.clearcoat * clearcoatF;

		diffuse *= clearcoat_att_fac;
		specular *= clearcoat_att_fac;
		specular += f_coat;
	}
#endif // SO_EVISUPBR_CLEARCOAT

#ifdef SO_EVISUPBR_SUBSURFACE
	diffuse *= getScattering(vDot(n, l), iParameters.curvature);
	ioResult.translucency += iData.irradiance * translucencyBRDF(iData.N, iData.L, iData.lightID, iData.V, iParameters.albedo, evisuMaterialData.sr0Color, evisuMaterialData.sr0Color);
#endif // SO_EVISUPBR_SUBSURFACE

#else // ----------------------------------------------------------------------

#ifndef XRiteCarPaint2

	// if not EVisuPBR and not XRiteCarPaint2

	vec3 H = vHalfVector(iData.V, iData.L);
	const float NoL = max(vDot(iData.N, iData.L), 0.0);

	specular = computeAreaSpecularBRDF(iData, iAreaData, iParameters);

#if !defined(LightMap) || (LightMap != LightMapIlluminanceMode)
	diffuse = computeDiffuseBRDF(iData, iParameters, H);
#else
	diffuse = vec3(0.0);
#ifdef FragmentStage
	specular *= vSaturate(vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz);
#endif
#endif

#ifdef Flakes
	specular += computeMetallicFlakesBRDF(iData, iParameters, H) + computePearlFlakesBRDF(iData, iParameters, H);
#endif

#ifdef Coating
	vec3 fresnelCore = fresnel_schlick(COATINGF0, COATINGF90, NoL);
	float fresnelEnergy = SpecGlossEnergyConservationTerm(fresnelCore);
	diffuse *= fresnelEnergy;
	specular *= fresnelEnergy;
	specular += computeCoatingBRDF(iData, iParameters, H);
#endif

#endif // !XRiteCarPaint2

#endif // EVisuPBR
}

struct areaLightingData
{
	mat3 Minv;
	vec2 fresnel;
#if defined(Coating) || defined(SO_EVISUPBR_CLEARCOAT)
	mat3 MinvCC;
	vec2 fresnelCC;
#endif

#ifdef SO_EVISUPBR_SHEEN
	mat3 MinvSheen;
#endif //SO_EVISUPBR_SHEEN

#ifdef Flakes
	mat3 MinvMetal;
	vec2 fresnelMetal;
	mat3 MinvMetalFlakes;
	vec2 fresnelMetalFlakes;
	// Pearl flakes
#if INTERNAL_FLAKES_PERFORMANCE_MODE < 1
	mat3 MinvPearlFlakes;
	vec2 fresnelPearlFlakes;
#endif
#endif //Flakes

#if SO_EVISUPBR_FLAKES
	mat3 MinvMetal;
	vec2 fresnelMetal;
	mat3 MinvMetalSto;
	vec2 fresnelMetalSto;
	mat3 MinvMetalClose;
	vec2 fresnelMetalClose;
#endif //SO_EVISUPBR_FLAKES
};

areaLightingData areaGGXData;

#ifndef XRiteCarPaint2

void setAreaGGXData(const in float roughness, const in float NoV, out vec2 fresnel, out mat3 Minv)
{
	const vec2 uvAr = vec2(roughness, 1.0 - vSqrt(1.0 - NoV)) * LUT_SCALE + LUT_BIAS;
	const vec4 t1 = vTexture(AreaLightGGX, vec3(uvAr, 0));
	const vec4 t2 = vTexture(AreaLightGGX, vec3(uvAr, 1));
	Minv = mat3(
		vec3(t1.x, 0, t1.y),
		vec3(0, 1.0, 0),
		vec3(t1.z, 0, t1.w)
	);
	fresnel = vec2(t2.z, t2.y);
}

void computeAreaGGXData(in BRDFParameters materialData, in LightingData iData)
{
	const float NoV = vSaturate(vDot(iData.N, iData.V));

	setAreaGGXData(materialData.roughness, NoV, areaGGXData.fresnel, areaGGXData.Minv);

#ifdef Coating
	setAreaGGXData(materialData.coatingRoughness, NoV, areaGGXData.fresnelCC, areaGGXData.MinvCC);
#endif //Coating

#ifdef SO_EVISUPBR_CLEARCOAT
	setAreaGGXData(materialData.clearcoatRoughness, vSaturate(vDot(materialData.clearcoatNormal, iData.V)), areaGGXData.fresnelCC, areaGGXData.MinvCC);
#endif //SO_EVISUPBR_CLEARCOAT

#ifdef SO_EVISUPBR_SHEEN
#if ( defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x) )
	setAreaSheenData(materialData.sheenRoughness, NoV, areaGGXData.MinvSheen);
#else
	setAreaSheenData(materialData.sheen, NoV, areaGGXData.MinvSheen);
#endif
#endif //SO_EVISUPBR_SHEEN

#ifdef Flakes
	setAreaGGXData(materialData.metalRoughness, vSaturate(vDot(iData.N, iData.V)), areaGGXData.fresnelMetal, areaGGXData.MinvMetal);
	setAreaGGXData(materialData.metallicFlakesRoughness, vSaturate(vDot(iData.metalFlakesN, iData.V)), areaGGXData.fresnelMetalFlakes, areaGGXData.MinvMetalFlakes);
	// Pearl flakes
#if INTERNAL_FLAKES_PERFORMANCE_MODE < 1
	setAreaGGXData(materialData.pearlFlakesRoughness, vSaturate(vDot(iData.pearlFlakesN, iData.V)), areaGGXData.fresnelPearlFlakes, areaGGXData.MinvPearlFlakes);
#endif
#endif //Flakes

#ifdef SO_EVISUPBR_FLAKES
	if (evisuFlakesData.smooth_weight > 0.0) {
		setAreaGGXData(materialData.flakeRoughness, NoV, areaGGXData.fresnelMetal, areaGGXData.MinvMetal);
	}
	if (evisuFlakesData.stochastic_weight > 0.0) {
		vec3 normalStoFlakes = vNormalize(iData.V + evisuFlakesData.stochasticHemisphereFlakesOrientation);
		const float NdotVSto = vSaturate(vDot(normalStoFlakes, iData.V));
		setAreaGGXData(materialData.flakeRoughness, NdotVSto, areaGGXData.fresnelMetalSto, areaGGXData.MinvMetalSto);
	}
	if (evisuFlakesData.closeup_weight > 0.0) {
		vec3 normalCloseUpFlakes = vNormalize(iData.V + evisuFlakesData.voronoi_cell_orientation);
		const float NdotVClose = vSaturate(vDot(normalCloseUpFlakes, iData.V));
		setAreaGGXData(materialData.flakeRoughness, NdotVClose, areaGGXData.fresnelMetalClose, areaGGXData.MinvMetalClose);
	}
#endif //SO_EVISUPBR_FLAKES
}

#endif // XRiteCarPaint2

vec3 getGeomT(const in vec3 N)
{
	const vec3 normN = vNormalize(N);
	const float x = normN.x;
	const float y = normN.y;
	const float z = normN.z;

	vec3 T = vec3(0.0);

	if (vAbs(z) > 0.0) {
		T.y += 0.0;
		T.x += 1.0;
		T.z += -x / z;
		return vNormalize(T);
	}
	if (vAbs(y) > 0.0) {
		T.x += 0.0;
		T.z += 1.0;
		T.y += -z / y;
		return vNormalize(T);
	}
	if (vAbs(x) > 0.0) {
		T.z += 0.0;
		T.y += 1.0;
		T.x += -y / x;
		return vNormalize(T);
	}

	return vec3(0.0);
}

void getSphereLightPoints(inout vec3 lP, in vec3 P, const in float radius, out vec3 p0, out vec3 p1, out vec3 p2)
{
	const vec3 toUse = vNormalize(P - lP);
	lP += radius * toUse;
	const vec3 right = getGeomT(toUse.xyz);
	const vec3 up = getGeomBApprox(toUse.xyz, right); //getGeomB replaced with in-built getGeomBApprox
	p0 = lP.xyz + right * radius - up * radius;
	p1 = lP.xyz - right * radius - up * radius;
	p2 = lP.xyz - right * radius + up * radius;
}

// An extended version of the implementation from
// "How to solve a cubic equation, revisited"
// http://momentsingraphics.de/?p=105
vec3 SolveCubic(vec4 Coefficient) {
	// Normalize the polynomial
	Coefficient.xyz /= Coefficient.w;
	// Divide middle coefficients by three
	Coefficient.yz /= 3.0;

	float A = Coefficient.w;
	float B = Coefficient.z;
	float C = Coefficient.y;
	float D = Coefficient.x;

	// Compute the Hessian and the discriminant
	vec3 Delta = vec3(
		-Coefficient.z*Coefficient.z + Coefficient.y,
		-Coefficient.y*Coefficient.z + Coefficient.x,
		vDot(vec2(Coefficient.z, -Coefficient.y), Coefficient.xy)
	);

	float Discriminant = vDot(vec2(4.0*Delta.x, -Delta.y), Delta.zy);

	vec3 RootsA, RootsD;

	vec2 xlc, xsc;

	// Algorithm A
	{
		float A_a = 1.0;
		float C_a = Delta.x;
		float D_a = -2.0*B*Delta.x + Delta.y;

		// Take the cubic root of a normalized complex number
		float Theta = vAtan(vSqrt(Discriminant), -D_a) / 3.0;

		float x_1a = 2.0*vSqrt(-C_a)*vCos(Theta);
		float x_3a = 2.0*vSqrt(-C_a)*vCos(Theta + (2.0 / 3.0)*3.14159265);

		float xl;
		if ((x_1a + x_3a) > 2.0*B)
			xl = x_1a;
		else
			xl = x_3a;

		xlc = vec2(xl - B, A);
	}

	// Algorithm D
	{
		float A_d = D;
		float C_d = Delta.z;
		float D_d = -D*Delta.y + 2.0*C*Delta.z;

		// Take the cubic root of a normalized complex number
		float Theta = vAtan(D*vSqrt(Discriminant), -D_d) / 3.0;

		float x_1d = 2.0*vSqrt(-C_d)*vCos(Theta);
		float x_3d = 2.0*vSqrt(-C_d)*vCos(Theta + (2.0 / 3.0)*3.14159265);

		float xs;
		if (x_1d + x_3d < 2.0*C)
			xs = x_1d;
		else
			xs = x_3d;

		xsc = vec2(-D, xs + C);
	}

	float E = xlc.y*xsc.y;
	float F = -xlc.x*xsc.y - xlc.y*xsc.x;
	float G = xlc.x*xsc.x;

	vec2 xmc = vec2(C*F - B*G, -B*F + C*E);

	vec3 Root = vec3(xsc.x / xsc.y, xmc.x / xmc.y, xlc.x / xlc.y);

	if (Root.x < Root.y && Root.x < Root.z)
		Root.xyz = Root.yxz;
	else if (Root.z < Root.x && Root.z < Root.y)
		Root.xyz = Root.xzy;

	return Root;
}

float areaDiskLight(vec3 N, vec3 V, vec3 P, mat3 Minv, vec3 p0, vec3 p1, vec3 p2) {
	// build TBN
	vec3 T = vNormalize(V - N*vDot(V, N));
	vec3 B = vCross(N, T);

	// rotate area light in (T1, T2, N) basis
	mat3 R = vTranspose(mat3(T, B, N));

	vec3 L[3];
	L[0] = R * (p0 - P);
	L[1] = R * (p1 - P);
	L[2] = R * (p2 - P);

	vec3 c = Minv *(0.5 * (L[0] + L[2]));
	vec3 v1 = Minv *(0.5 * (L[1] - L[2]));
	vec3 v2 = Minv *(0.5 * (L[1] - L[0]));

	if (vDot(vCross(v1, v2), c) < 0.0)
		return 0.0;

	float a, b;
	float d11 = vDot(v1, v1);
	float d22 = vDot(v2, v2);
	float d12 = vDot(v1, v2);
	if (vAbs(d12) / vSqrt(d11*d22) > 0.005) {
		float tr = d11 + d22;
		float det = -d12*d12 + d11*d22;

		det = vSqrt(det);
		float u = 0.5*vSqrt(tr - 2.0*det);
		float v = 0.5*vSqrt(tr + 2.0*det);
		float e_max = vPow((u + v), 2);
		float e_min = vPow((u - v), 2);

		vec3 v1_, v2_;

		if (d11 > d22) {
			v1_ = d12*v1 + (e_max - d11)*v2;
			v2_ = d12*v1 + (e_min - d11)*v2;
		}
		else {
			v1_ = d12*v2 + (e_max - d22)*v1;
			v2_ = d12*v2 + (e_min - d22)*v1;
		}

		a = 1.0 / e_max;
		b = 1.0 / e_min;
		v1 = vNormalize(v1_);
		v2 = vNormalize(v2_);
	}
	else {
		a = 1.0 / vDot(v1, v1);
		b = 1.0 / vDot(v2, v2);
		v1 *= vSqrt(a);
		v2 *= vSqrt(b);
	}

	vec3 v3 = vNormalize(vCross(v1, v2));
	if (vDot(c, v3) < 0.0)
		v3 *= -1.0;

	float L_ = vDot(v3, c);
	float x0 = vDot(v1, c) / L_;
	float y0 = vDot(v2, c) / L_;

	float E1 = vInversesqrt(a);
	float E2 = vInversesqrt(b);

	a *= L_*L_;
	b *= L_*L_;

	float c0 = a*b;
	float c1 = a*b*(1.0 + x0*x0 + y0*y0) - a - b;
	float c2 = 1.0 - a*(1.0 + x0*x0) - b*(1.0 + y0*y0);
	float c3 = 1.0;

	vec3 roots = SolveCubic(vec4(c0, c1, c2, c3));
	float e1 = roots.x;
	float e2 = roots.y;
	float e3 = roots.z;

	vec3 avgDir = vec3(a*x0 / (a - e2), b*y0 / (b - e2), 1.0);

	mat3 rotate = mat3(v1, v2, v3);

	avgDir = rotate*avgDir;
	avgDir = vNormalize(avgDir);

	float L1 = vSqrt(-e2 / e3);
	float L2 = vSqrt(-e2 / e1);

	float formFactor = L1*L2*vInversesqrt((1.0 + L1*L1)*(1.0 + L2*L2));

	// use tabulated horizon-clipped sphere
	vec2 uv = vec2(avgDir.z*0.5 + 0.5, 1.0 - formFactor);
	uv = uv*LUT_SCALE + LUT_BIAS;
	float scale = vTexture(AreaLightGGX, vec3(uv, 1)).w;

	float res = formFactor*scale;

	return vSaturate(res);
}

// Rect Light +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifdef AreaLight_ClipQuad

void ClipQuad(inout vec3 L[5], out int n)
{
	// detect clipping config
	int config = 0;
	if (L[0].z > 0.0) config += 1;
	if (L[1].z > 0.0) config += 2;
	if (L[2].z > 0.0) config += 4;
	if (L[3].z > 0.0) config += 8;

	// clip
	n = 0;

	if (config == 0)
	{
		// clip all
	}
	else if (config == 1)
	{
		n = 3;
		L[1] = -L[1].z * L[0] + L[0].z * L[1];
		L[2] = -L[3].z * L[0] + L[0].z * L[3];
	}
	else if (config == 2)
	{
		n = 3;
		L[0] = -L[0].z * L[1] + L[1].z * L[0];
		L[2] = -L[2].z * L[1] + L[1].z * L[2];
	}
	else if (config == 3)
	{
		n = 4;
		L[2] = -L[2].z * L[1] + L[1].z * L[2];
		L[3] = -L[3].z * L[0] + L[0].z * L[3];
	}
	else if (config == 4)
	{
		n = 3;
		L[0] = -L[3].z * L[2] + L[2].z * L[3];
		L[1] = -L[1].z * L[2] + L[2].z * L[1];
	}
	else if (config == 5)
	{
		n = 0;
	}
	else if (config == 6)
	{
		n = 4;
		L[0] = -L[0].z * L[1] + L[1].z * L[0];
		L[3] = -L[3].z * L[2] + L[2].z * L[3];
	}
	else if (config == 7)
	{
		n = 5;
		L[4] = -L[3].z * L[0] + L[0].z * L[3];
		L[3] = -L[3].z * L[2] + L[2].z * L[3];
	}
	else if (config == 8)
	{
		n = 3;
		L[0] = -L[0].z * L[3] + L[3].z * L[0];
		L[1] = -L[2].z * L[3] + L[3].z * L[2];
		L[2] = L[3];
	}
	else if (config == 9)
	{
		n = 4;
		L[1] = -L[1].z * L[0] + L[0].z * L[1];
		L[2] = -L[2].z * L[3] + L[3].z * L[2];
	}
	else if (config == 10)
	{
		n = 0;
	}
	else if (config == 11)
	{
		n = 5;
		L[4] = L[3];
		L[3] = -L[2].z * L[3] + L[3].z * L[2];
		L[2] = -L[2].z * L[1] + L[1].z * L[2];
	}
	else if (config == 12)
	{
		n = 4;
		L[1] = -L[1].z * L[2] + L[2].z * L[1];
		L[0] = -L[0].z * L[3] + L[3].z * L[0];
	}
	else if (config == 13)
	{
		n = 5;
		L[4] = L[3];
		L[3] = L[2];
		L[2] = -L[1].z * L[2] + L[2].z * L[1];
		L[1] = -L[1].z * L[0] + L[0].z * L[1];
	}
	else if (config == 14)
	{
		n = 5;
		L[4] = -L[0].z * L[3] + L[3].z * L[0];
		L[0] = -L[0].z * L[1] + L[1].z * L[0];
	}
	else if (config == 15)
	{
		n = 4;
	}

	if (n == 3)
		L[3] = L[0];
	if (n == 4)
		L[4] = L[0];
}

#endif // AreaLight_ClipQuad

vec3 IntegrateEdgeVec(const in vec3 v1, const in vec3 v2)
{
	const float x = vDot(v1, v2);
	const float y = abs(x);

	const float a = 0.8543985 + (0.4965155 + 0.0145206*y) * y;
	const float b = 3.4175940 + (4.1616724 + y) * y;
	const float v = a / b;

	const float theta_sintheta = (x > 0.0) ? v : 0.5*inversesqrt(1.0 - x*x) - v;
	return cross(v1, v2) * theta_sintheta;
}

float areaRectangleLight(in vec3 N, in vec3 V, in vec3 P, in mat3 Minv,
	in vec3 p0, in vec3 p1, in vec3 p2, in vec3 p3) {

	vec3 dir = p0 - P;
	vec3 lightNormal = cross(p1 - p0, p3 - p0);
	bool behind = (vDot(dir, lightNormal) < 0.0);
	if (behind) {
		return 0.0;
	}
	// build TBN
	vec3 T = normalize(V - N*vDot(V, N));
	vec3 B = cross(N, T);

	mat3 M = Minv*vTranspose(mat3(T, B, N));

#ifdef AreaLight_ClipQuad
	vec3 L[5];
#else
	vec3 L[4];
#endif

	L[0] = normalize(M * (p0 - P));
	L[1] = normalize(M * (p1 - P));
	L[2] = normalize(M * (p2 - P));
	L[3] = normalize(M * (p3 - P));

#ifdef AreaLight_ClipQuad
	int config = 0;
	ClipQuad(L, config);
	if (config == 0) {
		return 0.0;
	}
	L[0] = vNormalize(L[0]);
	L[1] = vNormalize(L[1]);
	L[2] = vNormalize(L[2]);
	L[3] = vNormalize(L[3]);
	L[4] = vNormalize(L[4]);

	float res = 0.0;
	res += (IntegrateEdgeVec(L[0], L[1])).z;
	res += (IntegrateEdgeVec(L[1], L[2])).z;
	res += (IntegrateEdgeVec(L[2], L[3])).z;
	if (config >= 4)
		res += (IntegrateEdgeVec(L[3], L[4])).z;
	if (config == 5)
		res += (IntegrateEdgeVec(L[4], L[0])).z;

	return vSaturate(res);
#else
	vec3 F = IntegrateEdgeVec(L[0], L[1]);
	F += IntegrateEdgeVec(L[1], L[2]);
	F += IntegrateEdgeVec(L[2], L[3]);
	F += IntegrateEdgeVec(L[3], L[0]);

	const float formFactor = vLength(F);
	const float z = F.z / formFactor;

	// use tabulated horizon-clipped sphere
	vec2 uv = vec2(z*0.5 + 0.5, 1.0 - formFactor);
	uv = uv*LUT_SCALE + LUT_BIAS;

	const float scale = vTexture(AreaLightGGX, vec3(uv, 1)).w;

	return vSaturate(scale * formFactor);
#endif // AreaLight_ClipQuad
}

void areaRectangleLightModel(out vec3 specular, out vec3 diffuse, out vec3 translucency,
	in vec3 N, in vec3 V, in vec3 P, in vec3 p0, in vec3 p1, in vec3 p2, in vec3 p3,
	in BRDFParameters materialData, in LightingData iData) {

#ifdef AnisotropicDistribution
	const vec3 bitangent = vNormalize(
		vSin(2.0 * PI * materialData.anisotropyAngle) * iData.T +
		vCos(2.0 * PI * materialData.anisotropyAngle) * iData.B);
	const vec3 anisotropicTangent = vCross(bitangent, -V);
	const vec3 anisotropicNormal = vCross(anisotropicTangent, bitangent);
	const vec3 bentNormal = vNormalize(vMix(N, anisotropicNormal, 0.22*materialData.anisotropy));
	const vec3 coreView = vReflect(vReflect(V, bentNormal), N);
#else
	const vec3 coreView = V;
#endif

#ifdef EVisuPBR
	specular = evisuMaterialData.sr0Color * areaGGXData.fresnel.x + evisuMaterialData.sr90Color * areaGGXData.fresnel.y;
#else // ------
	#ifdef XRiteCarPaint2
		XRiteCarPaint2AreaModel(specular, diffuse, materialData, iData);
	#else
		specular = materialData.f0 * areaGGXData.fresnel.x + materialData.f90 * areaGGXData.fresnel.y;
		vec3 fresnelCore = specular;
	#endif
#endif // EVisuPBR

#ifndef XRiteCarPaint2
	specular *= areaRectangleLight(N, coreView, P, areaGGXData.Minv, p0, p1, p2, p3);
	float diffusevalue = areaRectangleLight(N, V, P, mat3(1.0), p0, p1, p2, p3);
#endif // !XRiteCarPaint2

#ifdef EVisuPBR

	specular += diffusevalue * evisuMaterialData.specularEnergyConservationConstant;
	#if !defined(LightMap) || (LightMap != LightMapIlluminanceMode)
		diffusevalue *= evisuMaterialData.diffuseEnergyConservationConstant;
		diffuse = evisuMaterialData.albedoEvisu * diffusevalue;
	#else
		diffuse = vec3(0.0);
		#ifdef FragmentStage
			specular *= vSaturate(vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz);
		#endif
	#endif

#else // ------

	#ifdef XRiteCarPaint2
		// do nothing
	#else
		#if !defined(LightMap) || (LightMap != LightMapIlluminanceMode)
			diffusevalue *= SpecGlossEnergyConservationTerm(fresnelCore);
			diffuse = materialData.albedo * diffusevalue;
		#else
			#ifdef FragmentStage
				specular *= vSaturate(vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz);
			#endif
			diffuse = vec3(0.0);
		#endif
	#endif // XRiteCarPaint2

#endif // EVisuPBR

#ifdef SO_EVISUPBR_SHEEN
	vec3 sheen = vec3(areaRectangleLight(N, V, P, areaGGXData.MinvSheen, p0, p1, p2, p3));
#if (defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x))
	const float sheenBlending = 1.0 - evisuMaterialData.sheenEnergyConservationConstant;
	diffuse *= sheenBlending;
	specular *= sheenBlending;
	#if defined(SO_EVISUPBR_ver21x) // 21x
		specular += materialData.sheen * sheen * materialData.sheenColor;
	#else // 22x (and up)
		specular += sheen * materialData.sheenColor; // don't need materialData.sheen
	#endif
#else // 19x (deprecated)
	const float sheenBlending = 1.0 - vPow5(1.0 - materialData.sheen);
	diffuse *= PI * sheen * sheenBlending + (1.0 - sheenBlending);
#endif
#endif // SO_EVISUPBR_SHEEN

#ifdef SO_EVISUPBR_SUBSURFACE
	vec3 transColor = vec3(0.0);
	transColor = materialData.albedo * (1.0 - materialData.metallic) * materialData.transparency;
	#ifdef SO_EVISUPBR_TRANSLUCENCY
		const vec3 scatteringColor = SssLUTSampling(materialData.curvature);
		diffuse = vMix(diffuse, scatteringColor * diffuse, materialData.translucency);
	#endif
	diffuse += transColor * diffusevalue;
#elif defined(SO_EVISUPBR_TRANSLUCENCY)
	diffuse *= (1.0 - materialData.translucency);
	translucency = materialData.translucency * evisuMaterialData.albedoEvisu *
		areaRectangleLight(-N, V, P, mat3(1.0), p0, p1, p2, p3) *
		evisuMaterialData.diffuseEnergyConservationConstant;
#endif // SO_EVISUPBR_SUBSURFACE / SO_EVISUPBR_TRANSLUCENCY

#ifdef Flakes
	vec3 fresnelMetal = materialData.metallicFlakesF0 * areaGGXData.fresnelMetalFlakes.x;
	vec3 flakesVal = fresnelMetal;
	flakesVal *= areaRectangleLight(N, V, P, areaGGXData.MinvMetalFlakes, p0, p1, p2, p3);
	float energyFlakes = SpecGlossEnergyConservationTerm(fresnelMetal);
	specular *= energyFlakes;
	diffuse *= energyFlakes;
	specular += flakesVal;

	fresnelMetal = materialData.metalF0 * areaGGXData.fresnelMetal.x;
	flakesVal = fresnelMetal;
	flakesVal *= areaRectangleLight(N, V, P, areaGGXData.MinvMetal, p0, p1, p2, p3);
	energyFlakes = SpecGlossEnergyConservationTerm(fresnelMetal);
	specular *= energyFlakes;
	diffuse *= energyFlakes;
	specular += flakesVal;

	// Pearl flakes
	#if INTERNAL_FLAKES_PERFORMANCE_MODE < 1
		fresnelMetal = materialData.pearlFlakesF0 * areaGGXData.fresnelPearlFlakes.x;
		flakesVal = fresnelMetal;
		flakesVal *= areaRectangleLight(N, V, P, areaGGXData.MinvPearlFlakes, p0, p1, p2, p3);
		energyFlakes = SpecGlossEnergyConservationTerm(fresnelMetal);
		specular *= energyFlakes;
		diffuse *= energyFlakes;
		specular += flakesVal;
	#endif
#endif // Flakes

#ifdef SO_EVISUPBR_FLAKES
	vec3 flakesVal = vec3(0.0);
	if (evisuFlakesData.smooth_weight > 0.0) {
		flakesVal += evisuFlakesData.smooth_weight * areaRectangleLight(N, V, P, areaGGXData.MinvMetal, p0, p1, p2, p3);
	}
	if (evisuFlakesData.stochastic_weight > 0.0) {
		const vec3 normalStoFlakes = vNormalize(V + evisuFlakesData.stochasticHemisphereFlakesOrientation);
		flakesVal += evisuFlakesData.stochastic_weight * areaRectangleLight(normalStoFlakes, V, P, areaGGXData.MinvMetalSto, p0, p1, p2, p3);
	}
	if (evisuFlakesData.closeup_weight > 0.0) {
		const vec3 normalCloseUpFlakes = vNormalize(V + evisuFlakesData.voronoi_cell_orientation);
		flakesVal += evisuFlakesData.closeup_weight * areaRectangleLight(normalCloseUpFlakes, V, P, areaGGXData.MinvMetalClose, p0, p1, p2, p3);
	}
	diffuse *= evisuFlakesData.base_weight;
	specular *= evisuFlakesData.base_weight;
	specular += flakesVal * materialData.flakeColor;
#endif // SO_EVISUPBR_FLAKES

#if defined(Coating) || defined(SO_EVISUPBR_CLEARCOAT)
#ifdef SO_EVISUPBR_CLEARCOAT
	const float clearCoat = materialData.clearcoat;
	const vec3 fresnelCoat = COATINGF0 * areaGGXData.fresnelCC.x + COATINGF90 * areaGGXData.fresnelCC.y;
	const float fresnelEnergy = 1.0 - materialData.clearcoat * vMaxComp(SchlickFresnel(COATINGF0, COATINGF90, vSaturate(vDot(materialData.clearcoatNormal, V))));
#else
	const float clearCoat = 1.0;
	const vec3 fresnelCoat = materialData.coatingF0 * areaGGXData.fresnelCC.x + COATINGF90 * areaGGXData.fresnelCC.y;
	const float fresnelEnergy = SpecGlossEnergyConservationTerm(fresnelCoat);
#endif // SO_EVISUPBR_CLEARCOAT
	vec3 coat = fresnelCoat;
	coat *= areaRectangleLight(N, V, P, areaGGXData.MinvCC, p0, p1, p2, p3);
	diffuse *= fresnelEnergy;
	specular *= fresnelEnergy;
	specular += clearCoat * coat;
#endif // Coating || SO_EVISUPBR_CLEARCOAT

} // areaRectangleLightModel

// Rect Light -----------------------------------------------------------------

void areaDiskLightModel(out vec3 specular, out vec3 diffuse, out vec3 translucency,
	in vec3 N, in vec3 V, in vec3 P, in vec3 p0, in vec3 p1, in vec3 p2,
	in BRDFParameters materialData, in LightingData iData) {

#ifdef AnisotropicDistribution
	const vec3 bitangent = vNormalize(
		vSin(2.0 * PI * materialData.anisotropyAngle) * iData.T +
		vCos(2.0 * PI * materialData.anisotropyAngle) * iData.B);
	const vec3 anisotropicTangent = vCross(bitangent, -V);
	const vec3 anisotropicNormal = vCross(anisotropicTangent, bitangent);
	const vec3 bentNormal = vNormalize(vMix(N, anisotropicNormal, 0.22*materialData.anisotropy));
	const vec3 coreView = vReflect(vReflect(V, bentNormal), N);
#else
	const vec3 coreView = V;
#endif

#ifdef EVisuPBR
	specular = evisuMaterialData.sr0Color * areaGGXData.fresnel.x + evisuMaterialData.sr90Color * areaGGXData.fresnel.y;
#else // ------
	#ifdef XRiteCarPaint2
		XRiteCarPaint2AreaModel(specular, diffuse, materialData, iData);
	#else
		specular = materialData.f0 * areaGGXData.fresnel.x + materialData.f90 * areaGGXData.fresnel.y;
		vec3 fresnelCore = specular;
	#endif
#endif // EVisuPBR

#ifndef XRiteCarPaint2
	specular *= areaDiskLight(N, coreView, P, areaGGXData.Minv, p0, p1, p2);
	float diffusevalue = areaDiskLight(N, V, P, mat3(1.0), p0, p1, p2);
#endif // !XRiteCarPaint2

#ifdef EVisuPBR

	diffuse += diffusevalue * evisuMaterialData.specularEnergyConservationConstant;
	#if !defined(LightMap) || (LightMap != LightMapIlluminanceMode)
		diffusevalue *= evisuMaterialData.diffuseEnergyConservationConstant;
		diffuse = evisuMaterialData.albedoEvisu * diffusevalue;
	#else
		diffuse = vec3(0.0);
	#endif

#else // ------

	#ifdef XRiteCarPaint2
		// do nothing
	#else
		#if !defined(LightMap) || (LightMap != LightMapIlluminanceMode)
			diffusevalue *= SpecGlossEnergyConservationTerm(fresnelCore);
			diffuse = materialData.albedo * diffusevalue;
		#else
			diffuse = vec3(0.0);
		#endif
	#endif // XRiteCarPaint2

#endif // EVisuPBR

#ifdef SO_EVISUPBR_SHEEN
	vec3 sheen = vec3(areaDiskLight(N, V, P, areaGGXData.MinvSheen, p0, p1, p2));
#if (defined(SO_EVISUPBR_ver21x) || defined(SO_EVISUPBR_ver22x))
	const float sheenBlending = 1.0 - evisuMaterialData.sheenEnergyConservationConstant;
	diffuse *= sheenBlending;
	specular *= sheenBlending;
	#if defined(SO_EVISUPBR_ver21x) // 21x
		specular += materialData.sheen * sheen * materialData.sheenColor;
	#else // 22x (and up)
		specular += sheen * materialData.sheenColor; // don't need materialData.sheen
	#endif
#else // 19x (deprecated)
	const float sheenBlending = 1.0 - vPow5(1.0 - materialData.sheen);
	diffuse *= PI * sheen * sheenBlending + (1.0 - sheenBlending);
#endif
#endif // SO_EVISUPBR_SHEEN

#ifdef SO_EVISUPBR_SUBSURFACE
	vec3 transColor = vec3(0.0);
	transColor = materialData.albedo * (1.0 - materialData.metallic) * materialData.transparency;
	#ifdef SO_EVISUPBR_TRANSLUCENCY
		const vec3 scatteringColor = SssLUTSampling(materialData.curvature);
		diffuse = vMix(diffuse, scatteringColor * diffuse, materialData.translucency);
	#endif
	diffuse += transColor * diffusevalue;
#elif defined(SO_EVISUPBR_TRANSLUCENCY)
	diffuse *= (1.0 - materialData.translucency);
	translucency = materialData.translucency * evisuMaterialData.albedoEvisu *
		areaDiskLight(-N, V, P, mat3(1.0), p0, p1, p2) *
		evisuMaterialData.diffuseEnergyConservationConstant;
#endif // SO_EVISUPBR_SUBSURFACE / SO_EVISUPBR_TRANSLUCENCY

#ifdef Flakes
	vec3 fresnelMetal = materialData.metallicFlakesF0 * areaGGXData.fresnelMetalFlakes.x;
	vec3 flakesVal = fresnelMetal;
	flakesVal *= areaDiskLight(N, V, P, areaGGXData.MinvMetalFlakes, p0, p1, p2);
	float energyFlakes = SpecGlossEnergyConservationTerm(fresnelMetal);
	specular *= energyFlakes;
	diffuse *= energyFlakes;
	specular += flakesVal;

	fresnelMetal = materialData.metalF0 * areaGGXData.fresnelMetal.x;
	flakesVal = fresnelMetal;
	flakesVal *= areaDiskLight(N, V, P, areaGGXData.MinvMetal, p0, p1, p2);
	energyFlakes = SpecGlossEnergyConservationTerm(fresnelMetal);
	specular *= energyFlakes;
	diffuse *= energyFlakes;
	specular += flakesVal;

	// Pearl flakes
	#if INTERNAL_FLAKES_PERFORMANCE_MODE < 1
		fresnelMetal = materialData.pearlFlakesF0 * areaGGXData.fresnelPearlFlakes.x;
		flakesVal = fresnelMetal;
		flakesVal *= areaDiskLight(N, V, P, areaGGXData.MinvPearlFlakes, p0, p1, p2);
		energyFlakes = SpecGlossEnergyConservationTerm(fresnelMetal);
		specular *= energyFlakes;
		diffuse *= energyFlakes;
		specular += flakesVal;
	#endif
#endif // Flakes

#ifdef SO_EVISUPBR_FLAKES
	vec3 flakesVal = vec3(0.0);
	if (evisuFlakesData.smooth_weight > 0.0) {
		flakesVal += evisuFlakesData.smooth_weight * areaDiskLight(N, V, P, areaGGXData.MinvMetal, p0, p1, p2);
	}
	if (evisuFlakesData.stochastic_weight > 0.0) {
		const vec3 normalStoFlakes = vNormalize(V + evisuFlakesData.stochasticHemisphereFlakesOrientation);
		flakesVal += evisuFlakesData.stochastic_weight * areaDiskLight(normalStoFlakes, V, P, areaGGXData.MinvMetalSto, p0, p1, p2);
	}
	if (evisuFlakesData.closeup_weight > 0.0) {
		const vec3 normalCloseUpFlakes = vNormalize(V + evisuFlakesData.voronoi_cell_orientation);
		flakesVal += evisuFlakesData.closeup_weight * areaDiskLight(normalCloseUpFlakes, V, P, areaGGXData.MinvMetalClose, p0, p1, p2);
	}
	diffuse *= evisuFlakesData.base_weight;
	specular *= evisuFlakesData.base_weight;
	specular += flakesVal * materialData.flakeColor;
#endif // SO_EVISUPBR_FLAKES

#if defined(Coating) || defined(SO_EVISUPBR_CLEARCOAT)
#ifdef SO_EVISUPBR_CLEARCOAT
	const float clearCoat = materialData.clearcoat;
	const vec3 fresnelCoat = COATINGF0 * areaGGXData.fresnelCC.x + COATINGF90 * areaGGXData.fresnelCC.y;
	const float fresnelEnergy = 1.0 - materialData.clearcoat * vMaxComp(SchlickFresnel(COATINGF0, COATINGF90, vSaturate(vDot(materialData.clearcoatNormal, V))));
#else
	const float clearCoat = 1.0;
	const vec3 fresnelCoat = materialData.coatingF0 * areaGGXData.fresnelCC.x + COATINGF90 * areaGGXData.fresnelCC.y;
	const float fresnelEnergy = SpecGlossEnergyConservationTerm(fresnelCoat);
#endif // SO_EVISUPBR_CLEARCOAT
	vec3 coat = fresnelCoat;
	coat *= areaDiskLight(N, V, P, areaGGXData.MinvCC, p0, p1, p2);
	diffuse *= fresnelEnergy;
	specular *= fresnelEnergy;
	specular += clearCoat * coat;
#endif // Coating || SO_EVISUPBR_CLEARCOAT

} // areaDiskLightModel

vec3 vOrthoProjectionOnLine(const in vec3 P, const in vec3 A, const in vec3 B) {
	const vec3 v = vNormalize(B - A);
	const vec3 AP = P - A;
	return A + vDot(AP, v) * v;
}

float cropRectangleLight(const in vec3 lP,
	const in vec3 p0, const in vec3 p1, const in vec3 p2, const in vec3 p3,
	const in vec3 P, const in vec3 N) {
	const float A = vDot(vNormalize(lP - P), N);
	const float B = vDot(vNormalize(p0 - P), N);
	const float C = vDot(vNormalize(p1 - P), N);
	const float D = vDot(vNormalize(p2 - P), N);
	const float E = vDot(vNormalize(p3 - P), N);
	return max(A, max(B, max(C, max(D, E)))) <= 1e-6 ? 0.0 : 1.0;
}

float cropDiskLight(const in vec3 lP,
	const in vec3 p0, const in vec3 p1, const in float radius,
	const in vec3 P, const in vec3 N) {
	const vec3 p2 = lP - (p0 - lP);
	const vec3 p3 = lP - (p1 - lP);
	return cropRectangleLight(lP, p0, p1, p2, p3, P, N);
}

// Tube Light +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

float rectangleSolidAngle(const in vec3 worldPos,
	const in vec3 p0, const in vec3 p1, const in vec3 p2, const in vec3 p3)
{
	const vec3 v0 = p0 - worldPos;
	const vec3 v1 = p1 - worldPos;
	const vec3 v2 = p2 - worldPos;
	const vec3 v3 = p3 - worldPos;

	const vec3 n0 = vNormalize(vCross(v0, v1));
	const vec3 n1 = vNormalize(vCross(v1, v2));
	const vec3 n2 = vNormalize(vCross(v2, v3));
	const vec3 n3 = vNormalize(vCross(v3, v0));

	const float g0 = vAcos(vDot(-n0, n1));
	const float g1 = vAcos(vDot(-n1, n2));
	const float g2 = vAcos(vDot(-n2, n3));
	const float g3 = vAcos(vDot(-n3, n0));

	return g0 + g1 + g2 + g3 - 2.0 * PI;
}

vec3 closestPointOnLine(const in vec3 a, const in vec3 b, const in vec3 c)
{
	const vec3 ab = b - a;
	const float t = vDot(c - a, ab) / vDot(ab, ab);
	return a + t * ab;
}

vec3 closestPointOnSegment(const in vec3 a, const in vec3 b, const in vec3 c)
{
	const vec3 ab = b - a;
	const float t = vDot(c - a, ab) / vDot(ab, ab);
	return a + vClamp(t, 0.0, 1.0) * ab;
}

vec3 closestPointTube(const in vec3 P0, const in vec3 P1, const in vec3 r, const in vec3 vPos)
{
	const vec3 L0 = P0 - vPos;
	const vec3 L1 = P1 - vPos;
	const vec3 Ld = L1 - L0;
	const float RoL0 = vDot(r, L0);
	const float RoLd = vDot(r, Ld);
	const float L0oLd = vDot(L0, Ld);
	const float distLd = vLength(Ld);
	const float t = (RoL0 * RoLd - L0oLd) / (distLd * distLd - RoLd * RoLd);
	return (L0 + Ld * vClamp(t, 0.0, 1.0)); // Specular reference point on tube neutral axis
}

float illuminanceTube(const in vec3 P0, const in vec3 P1, const in vec3 lightPos, const in vec3 vPos,
	const in vec3 N, const in vec3 tubeDir, const in float halfLength, const in float radius)
{
	const vec3 forward = vNormalize(closestPointOnLine(P0, P1, vPos) - vPos);
	const vec3 up = vCross(tubeDir, forward);

	const vec3 p0 = lightPos - tubeDir * halfLength + radius * up;
	const vec3 p1 = lightPos - tubeDir * halfLength - radius * up;
	const vec3 p2 = lightPos + tubeDir * halfLength - radius * up;
	const vec3 p3 = lightPos + tubeDir * halfLength + radius * up;

	const float solidAngle = rectangleSolidAngle(vPos, p0, p1, p2, p3);

#ifdef EVisuPBR
	// In case of EvisuPBR below code is giving better results
	// With this code disabled, it seems that we have better results
	// (no higher diffuse in the tube middle and extremities)
	const float illu = (vClamp(vDot(vNormalize(p0 - vPos), N), 0.0, 1.0)
		+ vClamp(vDot(vNormalize(p1 - vPos), N), 0.0, 1.0)
		+ vClamp(vDot(vNormalize(p2 - vPos), N), 0.0, 1.0)
		+ vClamp(vDot(vNormalize(p3 - vPos), N), 0.0, 1.0)
		+ vClamp(vDot(vNormalize(lightPos - vPos), N), 0.0, 1.0))
		* solidAngle * 0.2;
#else
	// Replace the disabled code effect for energy consistency
	const float illu = solidAngle;
#endif

	const vec3 spherePosition = closestPointOnSegment(P0, P1, vPos);
	const vec3 sphereUnormL = spherePosition - vPos;
	const vec3 sphereL = vNormalize(sphereUnormL);
	const float sqrSphereDistance = vDot(sphereUnormL, sphereUnormL);
	const float sqrLightRadius = radius * radius;
	const float illu2 = vClamp(vDot(sphereL, N), 0.0, 1.0) * (sqrLightRadius / sqrSphereDistance) * PI;
	return illu + illu2;
}

// TubeLight ------------------------------------------------------------------

vec4 GetValueFromHashMap(const in int i, const in int idAreaShadowOffset,
	const in int areaShadowMask, const in int idAreaShadow)
{
	#ifdef SO_HRTAO_SHADOWS_COUNT
		if (idAreaShadow < SO_HRTAO_SHADOWS_COUNT) {
			if ((areaShadowMask & (1<<i)) != 0) {
				#ifdef SO_HRTAO_AS_ARRAY
					const ivec3 coords = ivec3(gl_FragCoord.xy, idAreaShadow+idAreaShadowOffset); // because 0 is always AO
				#else
					const ivec2 coords = ivec2(gl_FragCoord.xy);
				#endif

				#ifdef IS_MSAA
					const vec4 value = texelFetch(RTAOOutput, coords, gl_SampleID);
				#else
					const vec4 value = texelFetch(RTAOOutput, coords, 0);
				#endif

				return value;
			}
		}
	#endif

	return vec4(1.0);
}

float GetLuminance(const in vec3 color)
{
	return dot(color, vec3(0.2126, 0.7152, 0.0722));
}

void ComputeAreaLighting(inout LightingResult res, inout LightingData iData, in BRDFParameters iParameters)
{
#ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
	iData.lightType = LIGHT_TYPE_AREA;
#endif

#ifdef EVisuPBR
	computeBRDFParamforEvisu(iParameters);
	computeEvisuEnergyConservation(iData.N, iData.V, iParameters);
#ifdef SO_EVISUPBR_FLAKES
	computeFlakesParam(iParameters, iData);
#endif
#endif // EVisuPBR

#ifndef XRiteCarPaint2
	computeAreaGGXData(iParameters, iData);
#endif

	#ifdef SO_HRTAO_SHADOWS_COUNT
		int areaShadowMask = _sbCbAreaLights.Type[0] >> 8;
		int idAreaShadow = 0;
		int idAreaShadowOffset = 0;

		#ifdef SO_HRTAO_ENABLE_AO
			idAreaShadowOffset = 1; // if AO is enabled, it will be in the first slot, so we skip it
		#endif
	#endif

	for (int i = 0; i < vMin(NumberOfAreaLights, _V_MAX_LIGHTS); ++i)
	{
		const int lightType = _sbCbAreaLights.Type[i] & 0xFF;

#ifdef LightChannels
		if ((cb_cbVolMaterial.u_LightChannels & cb_LightChannels.AreaChannels[i]) == 0)
			continue;
#endif
		AreaLightData areaData;
		areaData.lightSpecAtt = 1.0;
		const vec3 lightPoweredColor = _sbCbAreaLights.Color[i] * _sbCbAreaLights.PowerPerAreaUnit[i];
		vec3 lightPos = _sbCbAreaLights.Position[i];
		const vec3 L = lightPos - iData.P;
		const float lightDistSquare = vDot(L, L);
		areaData.lightDist = vSqrt(lightDistSquare);
		iData.L = L / areaData.lightDist;

		vec3 r = vReflect(iData.V, iData.N);

		vec3 FinalDiffuse = vec3(0.0);
		vec3 FinalSpecular = vec3(0.0);
		vec3 FinalTranslucency = vec3(0.0);

		// Sphere light
		if (lightType == SphereAreaType)
		{
			const float radius = _sbCbAreaLights.Size[i].x;
			vec3 p0, p1, p2;
			getSphereLightPoints(lightPos, iData.P, radius, p0, p1, p2);

			vec3 diffuse = vec3(0.0);
			vec3 specular = vec3(0.0);
			vec3 translucency = vec3(0.0);

			areaDiskLightModel(specular, diffuse, translucency, iData.N, iData.V, iData.P, p0, p1, p2, iParameters, iData);

			const float attenuation = cropDiskLight(lightPos, p0, p1, radius, iData.P, iData.N);

			FinalDiffuse = attenuation * lightPoweredColor * diffuse;
			FinalSpecular = attenuation * lightPoweredColor * specular;

		  //#if defined(SO_HRTAO_SHADOWS_COUNT) && defined(SO_HRTAO_ENABLE_AO_IBL)
			//	if((areaShadowMask & (1<<i)) != 0) // irradiance from HRTAO is enabled for this light
      //  {
      //    FinalDiffuse = evisuMaterialData.albedoEvisu * GetValueFromHashMap(i, idAreaShadowOffset, areaShadowMask, idAreaShadow).xyz;
      //
      //    //attenuate specular by isolating the shadowing term
      //    float diffuseFromHashMapLuminance = GetLuminance(FinalDiffuse);
      //    float diffuseLuminance = GetLuminance(diff);
      //    float visibilityRatio = diffuseFromHashMapLuminance / diffuseLuminance;
      //
      //    if(isnan(visibilityRatio) || isinf(visibilityRatio))
      //      visibilityRatio = 0.0;
      //
      //    FinalSpecular *= visibilityRatio;
      //  }
      //  else
      //#endif

			FinalTranslucency = translucency * lightPoweredColor * cropDiskLight(lightPos, p0, p1, radius, iData.P, -iData.N);
		}

		// Tube light
		if (lightType == TubeAreaType)
		{
			const float radius = _sbCbAreaLights.Size[i].x;
			const float halfLength = _sbCbAreaLights.Size[i].y * 0.5;
			const vec3 tubeDir = _sbCbAreaLights.OtherDirection[i];
			const vec3 P0 = lightPos - halfLength * tubeDir;
			const vec3 P1 = lightPos + halfLength * tubeDir;

			const vec3 E = lightPoweredColor * illuminanceTube(P0, P1, lightPos, iData.P, iData.N, tubeDir, halfLength, radius);
			areaData.closestPoint = closestPointTube(P0, P1, r, iData.P);

			const vec3 centerToRay = vDot(areaData.closestPoint, r) * r - areaData.closestPoint;
			areaData.closestPoint = areaData.closestPoint + centerToRay * vClamp(radius / vLength(centerToRay), 0.0, 1.0);

			vec3 diffuse = vec3(0.0);
			vec3 specular = vec3(0.0);

			ComputeAreaLightEquation(specular, diffuse, iData, areaData, iParameters, res);

			FinalSpecular = E * specular;
			FinalDiffuse = E * diffuse;

#if !defined(SO_EVISUPBR_SUBSURFACE) && defined(SO_EVISUPBR_TRANSLUCENCY)
			FinalTranslucency = iParameters.translucency * lightPoweredColor
				* illuminanceTube(P0, P1, lightPos, iData.P, -iData.N, tubeDir, halfLength, radius)
				* DiffuseLambertBRDF(evisuMaterialData.albedoEvisu) * evisuMaterialData.diffuseEnergyConservationConstant;
#endif
			//iData.L = sphereL;
			//areaData.lightRadius = radius;
			//vec3 posToLight = areaData.closestPoint - iData.P;
			//areaData.lightDist = vSqrt(vDot(posToLight, posToLight)); // Distance from position to point on tube neutral axis
		}

		// Planar light direction check
		vec3 lightNormal = _sbCbAreaLights.MainDirection[i];
		if (lightType > TubeAreaType && vDot(-iData.L, lightNormal) < 0.0)
			continue;

		// Disk light
		if (lightType == DiskAreaType)
		{
			const float radius = _sbCbAreaLights.Size[i].x;
			const vec3 right = getGeomT(lightNormal);
			const vec3 up = getGeomBApprox(lightNormal, right);
			const vec3 p0 = lightPos + right * radius - up * radius;
			const vec3 p1 = lightPos - right * radius - up * radius;
			const vec3 p2 = lightPos - right * radius + up * radius;

			vec3 diffuse = vec3(0.0);
			vec3 specular = vec3(0.0);
			vec3 translucency = vec3(0.0);

			areaDiskLightModel(specular, diffuse, translucency, iData.N, iData.V, iData.P, p0, p1, p2, iParameters, iData);

			const float attenuation = cropDiskLight(lightPos, p0, p1, radius, iData.P, iData.N);
			FinalDiffuse = attenuation * lightPoweredColor * diffuse;
			FinalSpecular = attenuation * lightPoweredColor * specular;
			FinalTranslucency = translucency * lightPoweredColor * cropDiskLight(lightPos, p0, p1, radius, iData.P, -iData.N);
		}

		// Rectangle light
		if (lightType == RectangleAreaType)
		{
			const float halfWidth = _sbCbAreaLights.Size[i].x * 0.5;
			const float halfHeight = _sbCbAreaLights.Size[i].y * 0.5;
			const vec3 rectangleUp = _sbCbAreaLights.OtherDirection[i];
			const vec3 rectangleLeft = vCross(lightNormal, rectangleUp);
			const vec3 p0 = lightPos + rectangleLeft * -halfWidth + rectangleUp *  halfHeight;
			const vec3 p1 = lightPos + rectangleLeft * -halfWidth + rectangleUp * -halfHeight;
			const vec3 p2 = lightPos + rectangleLeft *  halfWidth + rectangleUp * -halfHeight;
			const vec3 p3 = lightPos + rectangleLeft *  halfWidth + rectangleUp *  halfHeight;

			vec3 diffuse = vec3(0.0);
			vec3 specular = vec3(0.0);
			vec3 translucency = vec3(0.0);

			areaRectangleLightModel(specular, diffuse, translucency, iData.N, iData.V, iData.P, p0, p1, p2, p3, iParameters, iData);

			const float attenuation = cropRectangleLight(lightPos, p0, p1, p2, p3, iData.P, iData.N);
			FinalDiffuse = attenuation * lightPoweredColor * diffuse;
			FinalSpecular = attenuation * lightPoweredColor * specular;
			FinalTranslucency = translucency * lightPoweredColor * cropRectangleLight(lightPos, p0, p1, p2, p3, iData.P, -iData.N);
		}

		iData.visibility = vMax(1.0, iData.minVisibility);

		#ifdef SO_HRTAO_SHADOWS_COUNT
			#ifdef SO_HRTAO_ENABLE_AO_IBL
				const float v = GetLuminance(GetValueFromHashMap(i, idAreaShadowOffset, areaShadowMask, idAreaShadow).xyz);
			#else
				const float v = GetValueFromHashMap(i, idAreaShadowOffset, areaShadowMask, idAreaShadow).x;
			#endif //#ifndef SO_HRTAO_ENABLE_AO_IBL
			iData.visibility *= v;
			idAreaShadow++;
		#else
			iData.visibility = vMax(1.0, iData.minVisibility);
		#endif //#ifdef SO_HRTAO_SHADOWS_COUNT

		iData.lightID = i;

#ifndef EVisuPBR

#ifdef PDSFX_ENABLE_BRDF_CONTROL
		// TODO: implement for EVisuPBR !!!
		diffuse *= iParameters.diffuseBRDFFactor;
		specular *= iParameters.specularBRDFFactor;
#endif

#ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
		BRDFLayerParameters params;
		// TODO: implement for EVisuPBR !!!
		params.fresnel = OptimizedSchlickFresnel(iParameters.f0, iParameters.f90, vDot(iData.L, vHalfVector(iData.V, iData.L)));
		params.irradiance = iData.irradiance;
		params.lightType = iData.lightType;
		params.lightID = iData.lightID;
		res.radiance += ComputeCustomBRDFLayer(params);
#endif

#endif // !EVisuPBR

		res.radiance += (FinalDiffuse + FinalSpecular + FinalTranslucency) * iData.visibility;
	}
}

#endif // NumberOfAreaLights

#endif // Lighting
