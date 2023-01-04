#ifdef Lighting

#define LightMapLuminosityMode  1
#define LightMapIlluminanceMode 2

#define _V_MAX_LIGHTS (8)

struct LightingResult
{
	vec3 radiance;
	vec3 fresnel;
#ifdef EVisuPBR
	float alpha;
#ifdef SO_EVISUPBR_SUBSURFACE
	//TODO EOO2 rename in order not to mix "SSS" translucency and "normal" translucency
	vec3 translucency; // EOO2 Is this variable unused?
#endif
#else
	float transparency;
#endif

// we need the diffuse contribution of area lights that produce shadows
#if defined(ImageBasedLighting) && defined(SO_HRTAO_ENABLE_AO_IBL) && defined(SO_HRTAO_SHADOWS_COUNT)
  vec3 diffuseContribForAreaLightShadows;
#endif
};

//Local Ligting Structure Definition
struct LightingData
{
	vec3 Vworld; // view direction in world space
	vec3 VworldTransformed;
	vec3 Nworld; // normal direction in world space
	vec3 P;
	vec3 L; // in view space
	vec3 N; // in view space
	vec3 V; // in view space

#ifdef PhysicalMaterial
#ifdef Flakes
	vec3 pearlFlakesN;
	vec3 pearlFlakesNWorld;
	vec3 metalFlakesN;
	vec3 metalFlakesNWorld;
#endif // Flakes
#ifdef Coating
	vec3 coatingN;
	vec3 coatingNWorld;
#endif // Coating
#endif // PhysicalMaterial

#if defined(AnisotropicDistribution) || defined(EVisuPBR) || defined(XRiteCarPaint2)
	vec3 T; // in view space
	vec3 B; // in view space
#endif // AnisotropicDistribution

	vec3 irradiance;
	float visibility;
	float minVisibility;

	int lightID;
	int lightType;
};

float computeRoughness(in float iRoughness)
{
	float roughness = iRoughness;
#ifdef Fabrics
	roughness = mix(MIN_Rough, MAX_Rough, roughness);
#endif // Fabrics
	return vClamp(roughness, 0.025, 0.999);
}

float computeAnisotropicRoughness(in vec3 T, in vec3 B, in vec3 N, in vec3 H, in float iRoughness, in float ansisotropyAngle, in float anisotropy) {
	//T = getGeomTApprox(N);
	//B = getGeomBApprox(N,T);
	vec3 rot_X = vCos(ansisotropyAngle *2. * PI) * T + vSin(ansisotropyAngle * 2.* PI) * B;
	vec3 rot_Y = vCross(N, rot_X);

	float dot_t_h = vDot(rot_X, H); // sin(theta) cos(phi)
	float dot_b_h = vDot(rot_Y, H); // sin(theta) sin(phi)
	float alpha_T = iRoughness;
	float alpha_B = vMix(0., alpha_T, 1. - anisotropy);

	alpha_T = vMax(vPow2(alpha_T), kEpsilon);
	alpha_B = vMax(vPow2(alpha_B), kEpsilon);

	float tmp = vSign(dot_b_h) * vSign(dot_t_h);

	dot_t_h = vMax(vAbs(dot_t_h), 0.05) * tmp;
	dot_b_h = vMax(vAbs(dot_b_h), 0.05);

	float phi = vAtan(dot_t_h, dot_b_h);
	float a = vPow2(vCos(phi) / alpha_T);
	float b = vPow2(vSin(phi) / alpha_B);
	float a2 = 1.0 / (a + b);
	///////
	float roughness = vSaturate(vSqrt(vSqrt(a2)));
	return computeRoughness(roughness);
}

vec3 computeSpecularBRDF(in LightingData light, in BRDFParameters brdf, in vec3 H)
{
#if !defined(EVisuPBR) && !defined(XRiteCarPaint2)
	float dot_L_H = vMax(vDot(light.L, H), 0.0);
	float dot_N_V = vMax(vDot(light.N, light.V), 0.0);
	float dot_N_L = vMax(vDot(light.N, light.L), 0.0);
	float dot_N_H = vDot(light.N, H);

#if defined(AnisotropicDistribution) && defined(Fabrics)
	float roughness = computeAnisotropicRoughness(light.T, light.B, light.N, H, brdf.roughness, brdf.anisotropyAngle, brdf.anisotropy);
#else
	float roughness = computeRoughness(brdf.roughness);
#endif

	vec3 F = OptimizedSchlickFresnel(brdf.f0, brdf.f90, dot_L_H);
#if defined(AnisotropicDistribution) && !defined(Fabrics)
	// Keep the old method for GGX, fabrics' brdf does not have an explicit form for anisotropy
	float D = AnisotropicGGXNormalDistribution(light.T, light.B, light.N, H, dot_N_H, roughness, brdf.anisotropyAngle, brdf.anisotropy);
#else
	float D = NormalDistribution(dot_N_H, roughness);
#endif

	float Vis = UnrealVisibility(roughness, dot_N_L, dot_N_V);

	return dot_N_L * Vis * D * F;
#else
	return vec3(0.0);
#endif
}

vec3 computeDiffuseBRDF(in LightingData light, in BRDFParameters brdf, in vec3 H)
{
#if !defined(EVisuPBR) && !defined(XRiteCarPaint2)
	float dot_N_L = vDot(light.N, light.L);
	float dot_L_H = vMax(vDot(light.L, H), 0.0);

	dot_N_L = vMax(dot_N_L, 0.0);
	vec3 scattering = vec3(dot_N_L);
	vec3 F = OptimizedSchlickFresnel(brdf.f0, brdf.f90, dot_N_L);
	return scattering * INV_PI * brdf.albedo * (1.0 - vDot(F, vec3(0.299, 0.587, 0.114)));
#else
	return vec3(0.0);
#endif
}

#ifdef Flakes

vec3 computeMetallicFlakesBRDF(in LightingData light, in BRDFParameters brdf, in vec3 H)
{
	// TODO: implement for EVisuPBR !!!
	float dot_L_H = vMax(vDot(light.L, H), 0.0);
	//// metallic dye
#ifdef Coating
	vec3 metalN = light.coatingN;
#else
	vec3 metalN = light.N;
#endif // Coating
	float dot_N_V = vMax(vDot(metalN, light.V), 0.0);
	float dot_N_L = vMax(vDot(metalN, light.L), 0.0);
	float dot_N_H = vDot(metalN, H);
	float roughness = computeRoughness(brdf.metalRoughness);

	vec3 F = OptimizedSchlickFresnel(brdf.metalF0, vec3(0.0), dot_L_H);
	float D = NormalDistribution(dot_N_H, roughness);
	float Vis = UnrealVisibility(roughness, dot_N_L, dot_N_V);

	vec3 metalContrib = Vis * D * F;
	//// metallic micro flakes
	dot_N_V = vMax(vDot(light.metalFlakesN, light.V), 0.0);
	dot_N_L = vMax(vDot(light.metalFlakesN, light.L), 0.0);
	dot_N_H = (vDot(light.metalFlakesN, H));
	roughness = computeRoughness(brdf.metallicFlakesRoughness);

	F = OptimizedSchlickFresnel(brdf.metallicFlakesF0, vec3(0.0), dot_L_H);
	D = NormalDistribution(dot_N_H, roughness);
	Vis = UnrealVisibility(roughness, dot_N_L, dot_N_V);

	vec3 metallicFlakesContrib = Vis * D * F;

	return dot_N_L * (metalContrib + metallicFlakesContrib);
}

vec3 computePearlFlakesBRDF(in LightingData light, in BRDFParameters brdf, in vec3 H)
{
	// TODO: implement for EVisuPBR !!!
	float dot_L_H = vMax(vDot(light.L, H), 0.0);
	//// pearl dye
#ifdef Coating
	vec3 pearlN = light.coatingN;
#else
	vec3 pearlN = light.N;
#endif // Coating

	float dot_N_V = vMax(vDot(pearlN, light.V), 0.0);
	float dot_N_L = vMax(vDot(pearlN, light.L), 0.0);
	float dot_N_H = vDot(pearlN, H);
	float roughness = computeRoughness(brdf.pearlRoughness);

	vec3 F = OptimizedSchlickFresnel(brdf.pearlF0, vec3(0.0), dot_L_H);
	float D = NormalDistribution(dot_N_H, roughness);
	float Vis = UnrealVisibility(roughness, dot_N_L, dot_N_V);

	vec3 pearlContrib = Vis * D * F;
	//// pearl micro flakes
	vec3 pearlFlakesN = vNormalize(vMix(pearlN, light.pearlFlakesN, 0.65));
	dot_N_V = vMax(vDot(pearlFlakesN, light.V), 0.0);
	dot_N_L = vMax(vDot(pearlFlakesN, light.L), 0.0);
	dot_N_H = (vDot(pearlFlakesN, H));
	roughness = computeRoughness(brdf.pearlFlakesRoughness);

	F = OptimizedSchlickFresnel(brdf.pearlFlakesF0, vec3(0.0), dot_L_H);
	D = NormalDistribution(dot_N_H, roughness);
	Vis = UnrealVisibility(roughness, dot_N_L, dot_N_V);

	vec3 pearlFlakesContrib = Vis * D * F;

	return dot_N_L * (pearlContrib + pearlFlakesContrib);
}

#endif // Flakes

#ifdef Coating

vec3 computeCoatingBRDF(in LightingData light, in BRDFParameters brdf, in vec3 H)
{
	// TODO: implement for EVisuPBR !!!
	float dot_L_H = vMax(vDot(light.L, H), 0.0);

	float dot_N_V = vMax(vDot(light.coatingN, light.V), 0.0);
	float dot_N_L = vMax(vDot(light.coatingN, light.L), 0.0);
	float dot_N_H = vDot(light.coatingN, H);
	float roughness = computeRoughness(brdf.coatingRoughness);

	vec3 F = OptimizedSchlickFresnel(brdf.coatingF0, vec3(1.0), dot_L_H);
	float D = NormalDistribution(dot_N_H, roughness);
	float Vis = UnrealVisibility(roughness, dot_N_L, dot_N_V);

	return dot_N_L * Vis * D * F;
}

#endif // Coating

#ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
vec3 ComputeCustomBRDFLayer(in BRDFLayerParameters iParameters);
#endif // PDSFX_ENABLE_CUSTOM_BRDF_LAYER

#ifdef NumberOfLightsWithProfile
void ComputeProfileLighting(inout LightingResult res, inout LightingData iData, in BRDFParameters iParameters);
#endif // NumberOfLightsWithProfile

#ifdef NumberOfAreaLights
void ComputeAreaLighting(inout LightingResult res, inout LightingData iData, in BRDFParameters iParameters);
#endif // NumberOfAreaLights

void ComputeTransparency(in LightingData iData, in BRDFParameters iParameters, inout LightingResult ioResult)
{
	const vec3 n = iData.N;
	const vec3 v = iData.V;
	const float NoV = vMax(vDot(n, v), 0.0);

#ifdef EVisuPBR
	//const vec3 l = iData.L + 2.0 * n *(max(dot(-iData.L, n), 0.0));
	// Fresnel term at normal incidence
	const float F_0 = vPow2((1.0 - iParameters.ior) / (1.0 + iParameters.ior));
	// Fresnel term at grazing incidence F_90 = 1
	// Fresnel term at the current angle:
	const float F = F_0 + (1.0 - F_0) * vPow5(1.0 - NoV);
	const float rho_t = (1.0 - iParameters.metallic) * iParameters.transparency * (1.0 - F);
	//No colored blending yet...
	ioResult.alpha = 1.0 - vMin(rho_t, 1.0);

	#ifdef OIT_SORT_COLOR_AND_FRESNEL
		float trans_param = iParameters.transparency;
		#ifdef SO_EVISUPBR_TRANSLUCENCY
			trans_param = vClamp(iParameters.transparency + iParameters.translucency, 0.0, 1.0);
		#endif
		ioResult.fresnel = mix(vec3(1.0),
			iParameters.albedo * (1.0 - iParameters.metallic) * trans_param *
			(1.0 - iParameters.specular * SchlickFresnel(F_0 * iParameters.specularTint, vec3(1.0), NoV)),
			iParameters.opacity);
	#endif
#else

#ifdef XRiteCarPaint2

#else // all other

	vec3 Ft = OptimizedSchlickFresnel(iParameters.f0, iParameters.f90, NoV);
	ioResult.transparency = iParameters.transparency * (1.0 - 0.3333*(Ft.x + Ft.y + Ft.z));
	#ifdef OIT_SORT_COLOR_AND_FRESNEL
		ioResult.fresnel = vec3(ioResult.transparency);
	#endif

#endif // !XRiteCarPaint2

#endif // EVisuPBR
}

#define SO_EVISUPBR_FLAKE_ACCURACY_GOAL 0

void ComputeRenderingEquation(in LightingData iData, in BRDFParameters iParameters, inout LightingResult ioResult)
{
#ifdef XRiteCarPaint2
	const vec3 N_ss  = iData.Nworld;
	const vec3 V_ss  = iData.Vworld;
	//const vec3 Nc_ss = vec3(vGetViewInvMatrix() * vec4(iParameters.clearcoatNormal, 0.0));
	const vec3 Nc_ss = N_ss;
	const vec3 L_ss  = vec3(vGetViewInvMatrix() * vec4(iData.L, 0.0));
	const vec3 Rc_ss = vNormalize(-vReflect(V_ss, Nc_ss));
	const float solid_angle = 0.0;
	vec3 wo_trans;
	float f_trans_out;
	const float f_refl_out = CPA2_ProcessLight_clearcoat_layer(V_ss, Nc_ss, Rc_ss,
		iParameters.clearcoat_no_refraction, iParameters.clearcoat_ior, wo_trans, f_trans_out);
	const vec3 bsdf = CPA2_ProcessLightAxfCpa2(N_ss, V_ss, Nc_ss, L_ss, solid_angle,
		wo_trans, f_trans_out, iParameters);
	ioResult.radiance += CPA2_MultMaterialLight(bsdf, iData.irradiance) * iData.visibility;
	return;
#endif // XRiteCarPaint2

// ----------------------------------------------------------------------------

#ifdef EVisuPBR

	vec3 n = iData.N;
	vec3 v = iData.V;
	vec3 l = iData.L;
	vec3 h = normalize(l + v);
	vec3 t = normalize(iData.T);
	vec3 b = normalize(iData.B);

	const float NoV = max(dot(n, v), 0.0);
	const float NoL = max(dot(n, l), 0.0);
	const float NoH = max(dot(n, h), 0.0);
	const float LoH = max(dot(l, h), 0.0); // VoH == LoH by definition

#ifdef SO_EVISUPBR_TRANSLUCENCY
	const float negNoL = max(dot(-n, l), 0.0);
	const float negNoV = max(dot(-n, v), 0.0);
#endif

	vec3 f_s = vec3(0.0);
	float base_weight = 1.0;

#ifdef SO_EVISUPBR_FLAKES
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
			const float closeup_stochastic_transition = 1.0;
			const float closeup_smooth_transition = 64.0;
			const float stochastic_smooth_transition = 131072.0;
		#elif SO_EVISUPBR_FLAKE_ACCURACY_GOAL == 1
			//Performance
			const float closeup_stochastic_transition = 1.0;
			const float closeup_smooth_transition = 4.0;
			const float stochastic_smooth_transition = 1024.0;
		#endif
		#endif

		// Filled inside the model_weights() below
		float closeup_weight = 0.0;
		float stochastic_weight = 0.0;
		float smooth_weight = 0.0;
		vec3 voronoi_cell_orientation = vec3(0.0);

		model_weights(closeup_stochastic_transition, closeup_smooth_transition, stochastic_smooth_transition,
			flake_coverage, log_cells_in_footprint,
			base_weight, closeup_weight, stochastic_weight, smooth_weight, voronoi_cell_orientation,
			flake_orientation_roughness, cells_per_area, footprint_uv, footprint_uv_ddx, footprint_uv_ddy);

		float cos_cone_angle = flake_cos_cone_angle;
		vec3 front_flake_orientation = voronoi_cell_orientation;
		float cone_solid_angle = 2.0 * PI * (1.0 - cos_cone_angle);
		vec3 front_flake_orientation_view = normalize(front_flake_orientation.x*t - front_flake_orientation.y*b + front_flake_orientation.z*n);
		vec3 r = normalize(reflect(-v, front_flake_orientation_view));
		bool inside_flake_cone = dot(r, l) > cos_cone_angle;

		#ifdef SO_EVISUPBR_ver22x
			// flake color accounting flip-flop effect, avaliable since DSPBR22x
			// If iParameters.flipFlop equals zero, flake_color should be iParameters.flakeColor
			// Blending parameter clamped to zero to avoid calculation problem when iParameters.flipFlop equals zero
			const vec3 flake_color = vMix(iParameters.flakeColor, iParameters.flipFlopColor, vMax(0.0, vPow(LoH, 1.0 / vPow2(iParameters.flipFlop))));
		#else
			const vec3 flake_color = iParameters.flakeColor;
		#endif // SO_EVISUPBR_ver22x

		if (closeup_weight > 1e-6 && inside_flake_cone && front_flake_orientation.z > 0.0)
		{
			const float single_flake_eval = 1.0 / (cone_solid_angle * abs(dot(l, n)));
			f_s += flake_color * closeup_weight * single_flake_eval;
		}

		if (stochastic_weight > 1e-6)
		{
			float flakes_contributing = 0.0;
			float flakes_in_footprint = 0.0;
			stochastic_flakes(flake_orientation_roughness, cos_cone_angle, expected_num_flakes_inside_footprint,
				cells_per_area, footprint_uv, footprint_uv_ddx, footprint_uv_ddy, flake_coverage,
				-v, l, n, flakes_contributing, flakes_in_footprint);
			float dotVH = dot(v, h);
			float flake_count_threshold = 10.0;
			float alpha = min(1.0, flakes_in_footprint / flake_count_threshold);
			float reference_flake_count = mix(expected_num_flakes_inside_footprint, flakes_in_footprint, alpha);
			reference_flake_count = max(0.01, reference_flake_count);

			float d = flakes_contributing / (cone_solid_angle * reference_flake_count);
			distribution_ggx_parameters params;
			distribution_ggx_initialize(params, flake_orientation_roughness, 0.0);
			float g = distribution_ggx_g(params, n, v, l, t, b, NoL, NoV);
			f_s += flake_color * stochastic_weight * dotVH * g * d / vMax(1e-6, abs(dot(v, n) * dot(l, n)));
		}

		if (smooth_weight > 1e-6)
		{
			distribution_ggx_parameters paramsSmooth;
			distribution_ggx_initialize(paramsSmooth, iParameters.flakeRoughness, 0.0);
			float smooth_flake = distribution_ggx(paramsSmooth, n, v, l, h, t, b, NoL, NoV, NoH, LoH);
			f_s += flake_color * smooth_weight * smooth_flake;
		}
	}
#endif // SO_EVISUPBR_FLAKES

	fresnel_dielectric_parameters fresnelParams;
	fresnel_dielectric_init(fresnelParams, iParameters.albedo, iParameters.ior,
		iParameters.specularTint, iParameters.specular, iParameters.metallic);

	const vec3 F1 = fresnel_dielectric(fresnelParams, NoV);
	const vec3 F2 = fresnel_dielectric(fresnelParams, NoL);
#ifdef SO_EVISUPBR_TRANSLUCENCY
	const vec3 F1n = fresnel_dielectric(fresnelParams, negNoV);
	const vec3 F2n = fresnel_dielectric(fresnelParams, negNoL);
#endif // SO_EVISUPBR_TRANSLUCENCY

	distribution_ggx_parameters ggxParams;
	distribution_ggx_initialize(ggxParams, iParameters.roughness, iParameters.anisotropy);

	vec3 f_r = distribution_ggx(ggxParams, fresnelParams, n, v, l, h, t, b, NoL, NoV, NoH, LoH);

	vec3 f_b = vec3(0.0);
	float b_weight = 1.0;

#if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver19x)
	{
		distribution_inverted_ashikhmin_parameters sheenParams;
		distribution_inverted_ashikhmin_initialize(sheenParams, iParameters.sheen);
		b_weight = vPow5(1.0 - iParameters.sheen);
		const vec3 rho_b = iParameters.albedo * (1.0 - iParameters.metallic)*(1.0 - iParameters.transparency) * (1.0 - b_weight);
		f_b = max(vec3(0.0), rho_b * distribution_inverted_ashikhmin(sheenParams, NoH) / (4.0 * (NoL + NoV - NoL*NoV)) * (vec3(1.0) - vMax(F1, F2)));
	}
#endif // SO_EVISUPBR_SHEEN && SO_EVISUPBR_ver19x

	distribution_modified_lambert_parameters diffParam;
	distribution_modified_lambert_init(diffParam, iParameters.albedo, iParameters.metallic, iParameters.transparency);

	vec3 f_d = vec3(0.0);
#if defined(LightMap) && (LightMap == LightMapIlluminanceMode)
#ifdef FragmentStage
	vec3 lightMapAtt = vSaturate(vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz);
	f_r *= lightMapAtt;
	f_b *= lightMapAtt;
#endif
#else
	f_d = distribution_modified_lambert(diffParam, NoV, NoL, F1, F2) * b_weight;
#endif

#ifdef SO_EVISUPBR_SUBSURFACE
	f_d *= getScattering(dot(n, l), iParameters.curvature);
#else
	f_d *= NoL;
#endif

#ifdef SO_EVISUPBR_TRANSLUCENCY
	vec3 f_nd = distribution_modified_lambert(diffParam, negNoV, negNoL, F1n, F2n) * b_weight;
	f_d *= (1.0 - iParameters.translucency);
	f_d += iParameters.translucency * f_nd * negNoL;
#endif

	f_r *= NoL;
	f_b *= NoL;
	f_s *= NoL;

	base_weight = clamp(base_weight, 0.0, 1.0);

	vec3 sum = mix(f_s, f_r + f_d + f_b, base_weight);

#if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver21x)
	{
		// see dspbr_sheen.glsl
		ApplyDSPBR21xSheenLayer(f_b, b_weight, NoL, NoV, NoH,
			iParameters.sheen, iParameters.sheenColor, iParameters.sheenRoughness);
		sum = sum * b_weight + f_b * NoL;
	}
#endif // SO_EVISUPBR_SHEEN && SO_EVISUPBR_ver21x

#if defined(SO_EVISUPBR_SHEEN) && defined(SO_EVISUPBR_ver22x)
	{
		// see dspbr_sheen.glsl
		ApplyDSPBR22xSheenLayer(f_b, b_weight, NoL, NoV, NoH,
			iParameters.sheenColor, iParameters.sheenRoughness);
		sum = sum * b_weight + f_b * NoL;
	}
#endif // SO_EVISUPBR_SHEEN && SO_EVISUPBR_ver22x

#ifdef SO_EVISUPBR_CLEARCOAT
	{
		distribution_ggx_parameters params;
		distribution_ggx_initialize(params, iParameters.clearcoatRoughness, 0.0);
		const float NcoV = vMax(vDot(iParameters.clearcoatNormal, v), 0.0);
		const float NcoL = vMax(vDot(iParameters.clearcoatNormal, l), 0.0);
		const float NcoH = vMax(vDot(iParameters.clearcoatNormal, h), 0.0);
		//// clearcoatF0 = 0.04;
		//// clearcoatF90 = 1.0;
		//// F(cosTheta) = clearcoatF0 + (clearcoatF90 - clearcoatF0) * (1.0-cosTheta)^5
		//// F(cosTheta) = 0.04 + 0.96 * (1.0-cosTheta)^5
		const float clearcoatF = 0.04 + 0.96 * vPow5(1.0 - LoH); // By definition LoH == VoH
		const float clearcoatF1 = 0.04 + 0.96 * vPow5(1.0 - NcoV);
		const float clearcoatF2 = 0.04 + 0.96 * vPow5(1.0 - NcoL);
		const float clearcoat_att_fac = (1.0 - iParameters.clearcoat * vMax(clearcoatF1, clearcoatF2));
		const float f_coat = distribution_ggx(params, iParameters.clearcoatNormal, v, l, h, t, b, NcoL, NcoV, NcoH, LoH) * iParameters.clearcoat * clearcoatF;

		sum *= clearcoat_att_fac;
		sum += f_coat;
	}
#endif // SO_EVISUPBR_CLEARCOAT

#ifdef SO_EVISUPBR_SUBSURFACE
	{
		float F_0 = pow((1.0 - iParameters.ior) / (1.0 + iParameters.ior), 2.0);
		vec3 rho_sr0 = (1.0 - iParameters.metallic) * F_0 * iParameters.specular * iParameters.specularTint + iParameters.metallic * iParameters.albedo;
		float rho_sr90 = (1.0 - iParameters.metallic) * iParameters.specular + iParameters.metallic;
		ioResult.translucency += iData.irradiance * translucencyBRDF(iData.N, iData.L, iData.lightID, iData.V, iParameters.albedo, rho_sr0, vec3(rho_sr90));
	}
#endif // SO_EVISUPBR_SUBSURFACE

	ioResult.radiance += iData.irradiance * sum * iData.visibility;

#else // ----------------------------------------------------------------------

	// if not EVisuPBR

	vec3 H = vHalfVector(iData.V, iData.L);

	vec3 baseSpec = computeSpecularBRDF(iData, iParameters, H);
	vec3 baseDiff = vec3(0.0);

#if defined(LightMap) && (LightMap == LightMapIlluminanceMode)
#ifdef FragmentStage
	baseSpec *= vSaturate(vTexture(lightMapTexture, _vPrivGetLightMapUVs()).xyz);
#endif
#else
	baseDiff = computeDiffuseBRDF(iData, iParameters, H);
#endif

#ifdef PDSFX_ENABLE_BRDF_CONTROL
	// TODO: implement for EVisuPBR !!!
	baseDiff *= iParameters.diffuseBRDFFactor;
	baseSpec *= iParameters.specularBRDFFactor;
#endif

#ifdef Flakes
	vec3 flakes = computeMetallicFlakesBRDF(iData, iParameters, H) + computePearlFlakesBRDF(iData, iParameters, H);
#else
	vec3 flakes = vec3(0.0);
#endif

#ifdef Coating
	vec3 coating = computeCoatingBRDF(iData, iParameters, H);
#else
	vec3 coating = vec3(0.0);
#endif

#ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
	BRDFLayerParameters params;
	// TODO: implement for EVisuPBR !!!
	params.fresnel = OptimizedSchlickFresnel(iParameters.f0, iParameters.f90, vDot(iData.L, H));
	params.irradiance = iData.irradiance;
	params.lightType = iData.lightType;
	params.lightID = iData.lightID;
	params.shadowTerm = iData.visibility;
	ioResult.radiance += ComputeCustomBRDFLayer(params);
#endif // PDSFX_ENABLE_CUSTOM_BRDF_LAYER

	// base contribution
	ioResult.radiance += iData.irradiance * ((baseSpec + baseDiff + flakes + coating) * iData.visibility);

#endif // EVisuPBR
}

//------------------------------------
// Shadows

float ComputeVisibility(int iShadowLayer)
{
	float visibility = 1.0;

#if defined(ShadowMap) && !defined(VertexStage) && !defined(DecalLighting) 
	if (iShadowLayer >= 0)
	{
    visibility = ComputeShadows(iShadowLayer);
	}
#endif

	return visibility;
}

float ComputeVisibilityPointLights(int iShadowLayer, int iLightLayer, vec3 iLightPos)
{
	float visibility = 1.0;

#if defined(ShadowMap) && !defined(VertexStage) && !defined(DecalLighting)
	if (iShadowLayer >= 0)
	{
    visibility = ComputePointLightShadows(iShadowLayer, iLightLayer, iLightPos);
	}
#endif

	return visibility;
}

//------------------------------------
//  Transparent Shadows map

void ComputeTransparentShadow(inout LightingResult ioRes, int iShadowLayer)
{
#if defined(TransparentShadow) && defined(ShadowMap) && !defined(VertexStage) && !defined(DecalLighting)
  vec4 transShadowFrag = vec4(1.0);
  if (iShadowLayer >= 0)
  {
    transShadowFrag = GetTransparentShadowMap(iShadowLayer);
  }
  ioRes.radiance *= transShadowFrag.rgb;
#endif //TransparentShadow 
}

void ComputeTransparentShadowPointLights(inout LightingResult ioRes, int iShadowLayer, vec3 iLightPos, int iLightLayer)
{
#if defined(TransparentShadow) && (defined(PointLightShadows) || defined(MultiPointLightShadows))
  vec4 transShadowFrag = vec4(1.0);
  if (iShadowLayer >= 0)
  {
    transShadowFrag = GetTransparentShadowMapPointLight(iLightPos, iShadowLayer, iLightLayer);
  }
  ioRes.radiance *= transShadowFrag.rgb;
#endif //TransparentShadow 
}

#endif // Lighting
