// CT = Cook-Torrance

#ifdef XRiteCarPaint2

// Forward declaration, actual implementation in iblHelpers.glsl
vec3 ComputeSpecularIBL(in vec3 iR, in float iMipMapLevel);

// ----------------------------------------------------------------------------

vec3 CPA2_MultMaterialLight(const in vec3 mat, const in vec3 light) {
	const mat3 mat_to_rspace = mat3(
	     0.76133, 0.23867, -2.98023E-08,
	-4.49363E-08,     1.0,  1.49012E-08,
	         0.0, 0.04288, 0.95712
	);
	const mat3 light_to_rspace = mat3(
	     0.76133, 0.23867, -2.98023E-08,
	-4.49363E-08,     1.0,  1.49012E-08,
	         0.0, 0.04288, 0.95712
	);

	return (mat * mat_to_rspace) * (light * light_to_rspace);
}

vec3 CPA2_MultMaterialLight(const in float achromaticMatValue, const in vec3 light) {
	const mat3 light_to_rspace = mat3(
	     0.76133, 0.23867, -2.98023E-08,
	-4.49363E-08,     1.0,  1.49012E-08,
	         0.0, 0.04288, 0.95712
	);
	return achromaticMatValue * (light * light_to_rspace);
}

// ----------------------------------------------------------------------------

float CPA2_fresnel_s(const in float fCosThetaI, const in float fCosThetaT,
	const in float n1, const in float n2) {
	const float n1ci = n1 * fCosThetaI;
	const float n2ct = n2 * fCosThetaT;
	const float nom = n1ci - n2ct;
	const float den = n1ci + n2ct;
	return (nom * nom) / (den * den);
}

float CPA2_fresnel_d(const in float fCosThetaI, const in float fCosThetaT,
	const in float n1, const in float n2) {
	const float n1ct = n1 * fCosThetaT;
	const float n2ci = n2 * fCosThetaI;
	const float nom = n1ct - n2ci;
	const float den = n1ct + n2ci;
	return (nom * nom) / (den * den);
}

float CPA2_fresnel(const in float fCosThetaI, const in float fCosThetaT,
	const in float n1, const in float n2) {
	return clamp(0.5 * (CPA2_fresnel_s(fCosThetaI, fCosThetaT, n1, n2) +
		CPA2_fresnel_d(fCosThetaI, fCosThetaT, n1, n2)), 0.0, 1.0);
}

// ----------------------------------------------------------------------------

float CPA2_CT_D(const in float N_H, const in float m) {
	const float cosb_sqr   = N_H * N_H;
	const float m_cosb_sqr = m * m * cosb_sqr;
	const float e          = (cosb_sqr - 1.0) / m_cosb_sqr;
	return exp(e) / (m_cosb_sqr * cosb_sqr);
}

float CPA2_CT_F(const in float V_H, const in float F0) {
	return F0 + (1.0 - F0) * vPow5(1.0 - V_H);
}

float CPA2_CT_G(const in float N_H, const in float N_V, const in float N_L, const in float V_H) {
	const float k = 2.0 * N_H / V_H;
	return min(1.0, min(N_V * k, N_L * k));
}

float CPA2_CT(const in float N_H, const in float N_V, const in float N_L, const in float V_H,
	const in float lightsize, const in BRDFParameters iParameters) {
	// Hack - CT lobes widening
	const float min_dist = (iParameters.clearcoat_no_refraction > 0) ? 0.8 : 0.6;
	const float Hz2 = vPow2(cos(clamp(0.5*lightsize, 0.0, 0.5*PI-0.001)));
	const float min_spread = sqrt((Hz2-1.0) / (Hz2*log(min_dist)));

	// everything for the sake of numerical stability :-(
	if (  (N_V < 0.00174532836589830883577820272085 //sin(0.1 degrees)
		|| N_L < 0.00174532836589830883577820272085))
		return 0.0;

	// diffuse term
	float result = iParameters.ct_diffuse * INV_PI * N_L; // multiply by N_L, we want to return brdf * cos
	// specular term
	const float scale = CPA2_CT_G(N_H, N_V, N_L, V_H) / (PI * N_V); // omit N_L in the denom., we want to return brdf * cos
	for (int i=0; i<iParameters.ct_n_lobes; i++) {
		const float spread = max(min_spread, iParameters.ct_spreads[i]);
		const float lobe = iParameters.ct_coeffs[i] *
			CPA2_CT_D(N_H, spread) * CPA2_CT_F(V_H, iParameters.ct_f0s[i]) * scale;
		result += lobe;
	}

	return result;
}

vec3 CPA2_BRDF(const in float N_H, const in float N_V, const in float N_L, const in float V_H,
	const in float lightsize, const in BRDFParameters iParameters) {
	const float f_bright = CPA2_CT(N_H, N_V, N_L, V_H, lightsize, iParameters);
	const float f_thetaF = acos(clamp(N_H, -1.0, 1.0));
	const float f_thetaI = acos(clamp(V_H, -1.0, 1.0));
	const vec3 v3_color = texture(brdf_colors_map, 2.0*INV_PI*vec2(f_thetaF, f_thetaI)).xyz;
	return f_bright * v3_color;
}

// ----------------------------------------------------------------------------

const float CPA2_rnd_numbers[] = float[](
	0.2337269590, 0.8823386898, 0.4845325205, 0.0793774467,
	0.6743741046, 0.0815177151, 0.5103206574, 0.7493742577,
	0.6765019501, 0.5858515895, 0.0373273249, 0.4188504931,
	0.7854632330, 0.9488897296, 0.1448225946, 0.9828116549,
	0.0047927115, 0.0781099496, 0.5575552718, 0.7600885410,
	0.8365820088, 0.5743565992, 0.6763516161, 0.9535674100,
	0.7144283275, 0.7809197600, 0.3316376986, 0.2921663784,
	0.2858876519, 0.6901584751, 0.8054559712, 0.0602198739,
	0.0967901990, 0.5744455272, 0.7029143193, 0.3614076419,
	0.6103174857, 0.4013194986, 0.4869231275, 0.3439596611,
	0.0400759245, 0.7565069224, 0.2502401785, 0.0326807241,
	0.0697596838, 0.2420899525, 0.1016969505, 0.9291968916,
	0.7175966725, 0.1885724865, 0.2433946687, 0.7560654553,
	0.3379812734, 0.5997581410, 0.3887638151, 0.0653319398,
	0.8621750481, 0.6569763640, 0.6222405320, 0.0815121105,
	0.8334355493, 0.2661713284, 0.5374210835, 0.5589914055,
	0.2289622442, 0.0384152664, 0.9767260679, 0.3283991470,
	0.3867797853, 0.4430296545, 0.9824470867, 0.5148291621,
	0.3722282434, 0.1419718671, 0.7082816823, 0.0911295516,
	0.7703833607, 0.9127773987, 0.1744316441, 0.9608299486,
	0.3328830506, 0.9878704079, 0.7767569639, 0.5663943231,
	0.1387123362, 0.4696124549, 0.1906680432, 0.6614293796,
	0.7996986034, 0.9558977788);

vec3 CPA2_flake_btf(const in float N_H, const in float N_V, const in float N_L, const in float V_H,
	const in vec2 texCoord, const in float lightsize, const in BRDFParameters iParameters)
{
	//const float su = iParameters.texture_transformation[0];
	//const float sv = iParameters.texture_transformation[1];
	const float su = iParameters.flakes_uv_trf_scale;
	const float sv = iParameters.flakes_uv_trf_scale;
	const mat3 uv_trf = mat3(su, 0.0, 0.0, 0.0, sv, 0.0, 0.0, 0.0, 1.0);

	//vec2 uv = (uv_trf * vec3(texCoord, 1.0)).xy; //TODO iParameters.flakes_tex_scale *
	vec2 uv = texCoord;

	// get gradients before shifting patches
	const vec2 uvDx = dFdx(uv);
	const vec2 uvDy = dFdy(uv);
	// hide simple tiling by shifting patches
	if (0 == (int(floor(uv[1]))%2)) {
		uv[0] += 0.5;
	} else if (0 == (int(abs(uv[0]))%3)) {
		uv[1] = 1.0 - uv[1];
	} else {
		uv[0] = 1.0 - uv[0];
	}

	//vec3 v3_half = normalize(wi_trans + wo_trans);
	const float f_thetaF = acos(clamp(N_H, -1.0, 1.0));
	const float f_thetaI = acos(clamp(V_H, -1.0, 1.0));
	// thetaF sampling defines the angular sampling, i.e. angular flake lifetime
	const int i_angular_sampling = iParameters.num_thetaF;

	const vec2 f_thetaFI = float(i_angular_sampling) * 2.0*INV_PI*vec2(f_thetaF, f_thetaI);
	//f_thetaF = float(i_angular_sampling) * (f_thetaF/M_PI_2);
	//f_thetaI = float(i_angular_sampling) * (f_thetaI/M_PI_2);

	// bilinear interp indices and weights
	int i_thetaF_low  = int(floor(f_thetaFI.x));
	int i_thetaF_high = i_thetaF_low + 1;
	int i_thetaI_low  = int(floor(f_thetaFI.y));
	int i_thetaI_high = i_thetaI_low + 1;

	const float f_thetaF_w = f_thetaFI.x - float(i_thetaF_low);
	const float f_thetaI_w = f_thetaFI.y - float(i_thetaI_low);

	// to allow lower thetaI samplings while preserving flake lifetime 
	// "virtual" thetaI patches are generated by shifting existing ones 
	vec2 v2_offset_l = vec2(0.0, 0.0);
	vec2 v2_offset_h = vec2(0.0, 0.0);
	if (iParameters.num_thetaI < i_angular_sampling)
	{
		v2_offset_l = vec2(CPA2_rnd_numbers[2*i_thetaI_low],  CPA2_rnd_numbers[2*i_thetaI_low+1]);
		v2_offset_h = vec2(CPA2_rnd_numbers[2*i_thetaI_high], CPA2_rnd_numbers[2*i_thetaI_high+1]);
		if (i_thetaI_low  % 2 == 1) uv.xy = uv.yx;
		if (i_thetaI_high % 2 == 1) uv.xy = uv.yx;
		// map to the original sampling
		i_thetaI_low  = int(floor(i_thetaI_low  * float(iParameters.num_thetaI) / float(iParameters.num_thetaF)));
		i_thetaI_high = int(floor(i_thetaI_high * float(iParameters.num_thetaI) / float(iParameters.num_thetaF)));
	}

	vec3 v3_ll = vec3(0.0, 0.0, 0.0);
	vec3 v3_lh = vec3(0.0, 0.0, 0.0);
	vec3 v3_hl = vec3(0.0, 0.0, 0.0);
	vec3 v3_hh = vec3(0.0, 0.0, 0.0);
	const float koef = 1.0f; // / 68.0f;
	// make sure to stay in the correct slices (no slip over)
	if (i_thetaI_low < iParameters.max_thetaI) {
		if (iParameters.thetaFI_sliceLUT[i_thetaI_low] + i_thetaF_low < iParameters.thetaFI_sliceLUT[i_thetaI_low + 1]) {
			v3_ll = textureGrad(btf_flakes_map, vec3(uv + v2_offset_l,
				koef * (iParameters.thetaFI_sliceLUT[i_thetaI_low] + i_thetaF_low)), uvDx, uvDy).xyz;
		}
		if (iParameters.thetaFI_sliceLUT[i_thetaI_low] + i_thetaF_high < iParameters.thetaFI_sliceLUT[i_thetaI_low + 1]) {
			v3_hl = textureGrad(btf_flakes_map, vec3(uv + v2_offset_l,
				koef * (iParameters.thetaFI_sliceLUT[i_thetaI_low] + i_thetaF_high)), uvDx, uvDy).xyz;
		}
	}
	if (i_thetaI_high < iParameters.max_thetaI) {
		if (iParameters.thetaFI_sliceLUT[i_thetaI_high] + i_thetaF_low < iParameters.thetaFI_sliceLUT[i_thetaI_high + 1]) {
			v3_lh = textureGrad(btf_flakes_map, vec3(uv + v2_offset_h,
				koef * (iParameters.thetaFI_sliceLUT[i_thetaI_high] + i_thetaF_low)), uvDx, uvDy).xyz;
		}
		if (iParameters.thetaFI_sliceLUT[i_thetaI_high] + i_thetaF_high < iParameters.thetaFI_sliceLUT[i_thetaI_high + 1]) {
			v3_hh = textureGrad(btf_flakes_map, vec3(uv + v2_offset_h,
				koef * (iParameters.thetaFI_sliceLUT[i_thetaI_high] + i_thetaF_high)), uvDx, uvDy).xyz;
		}
	}

	const vec3 v3_l = (1.0 - f_thetaF_w) * v3_ll + f_thetaF_w * v3_hl;
	const vec3 v3_h = (1.0 - f_thetaF_w) * v3_lh + f_thetaF_w * v3_hh;

	const float btf_lightsigma_sqr_inv = vPow2(2.0 * INV_PI * iParameters.num_thetaF);
	float scale = exp(-(0.64 * lightsize * lightsize) * (0.5 * btf_lightsigma_sqr_inv));

	return scale * mix(v3_l, v3_h, f_thetaI_w);
}

// ----------------------------------------------------------------------------

float CPA2_ProcessLight_clearcoat_layer(
	const in vec3 V, const in vec3 Nc, const in vec3 Rc,
	const in int clearcoat_no_refraction, const in float clearcoat_ior,
	out vec3 wo_trans, out float f_trans_out) {

	const vec3 Vt = -refract(-V, Nc, 1.0 / clearcoat_ior);

	const float V_dot_Nc  = dot(V,  Nc);
	const float Vt_dot_Nc = dot(Vt, Nc);

	const float f_refl_out = CPA2_fresnel(V_dot_Nc, Vt_dot_Nc, 1.0, clearcoat_ior);
	/*interm_data.*/f_trans_out = 1.0 - f_refl_out;
	/*interm_data.*/wo_trans = (clearcoat_no_refraction > 0) ? V : Vt;

	return f_refl_out;
	//const vec3 tex_sample = ComputeSpecularIBL(Rc, 0.0);
	//return CPA2_MultMaterialLight(f_refl_out, tex_sample.xyz);
}

// ----------------------------------------------------------------------------

vec3 CPA2_ProcessLightAxfCpa2(
	const in vec3 N_ss, const in vec3 V_ss, const in vec3 Nc_ss, const in vec3 L_ss,
	const in float solid_angle,
	const in vec3 wo_trans, const in float f_trans_out,
	const in BRDFParameters iParameters) {
	const float cc_ior_inv = 1.0 / iParameters.clearcoat_ior;

	///////////////////////////////////////////////////////////////////////////////////////////////
	// In view space - Original
	// V_ss // V
	// L_ss // L
	// In scene space - Reflect the view and light vectors around the (non-clearcoat) normal ------------- ?
	const vec3 Vr_ss  = reflect(-V_ss, N_ss); // Vr
	const vec3 Lr_ss  = reflect(-L_ss, N_ss); // Lr
	// In scene space - Refract the view and light vectors around the clearcoat normal
	const vec3 Vt_ss  = -refract(-V_ss, Nc_ss, cc_ior_inv); // Vt
	const vec3 Lt_ss  = -refract(-L_ss, Nc_ss, cc_ior_inv); // Lt
	// In scene space - Reflect the refracted view and lights vectors around the (non-clearcoat) normal ------------- ?
	const vec3 Vtr_ss = reflect(-Vt_ss, N_ss); // Vtr
	const vec3 Ltr_ss = reflect(-Lt_ss, N_ss); // Ltr
	///////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	const float V_dot_Nc  = dot(V_ss,  Nc_ss);
	const float Vt_dot_Nc = dot(Vt_ss, Nc_ss);
	const float L_dot_Nc  = dot(L_ss,  Nc_ss);
	const float Lt_dot_Nc = dot(Lt_ss, Nc_ss);
	///////////////////////////////////////////////////////////////////////////////////////////////

	const vec3 wi_trans_ss = (iParameters.clearcoat_no_refraction > 0) ? L_ss : Lt_ss;

	const vec3 wh_trans_ss = normalize(wi_trans_ss + /*g_XRiteCarPaint2_interm_data.*/wo_trans);

	const float wo_trans_dot_Nc = dot(/*g_XRiteCarPaint2_interm_data.*/wo_trans, Nc_ss); // NcoV
	const float wi_trans_dot_Nc = dot(wi_trans_ss, Nc_ss); // NcoL
	const float wh_trans_dot_Nc = dot(wh_trans_ss, Nc_ss); // NcoH
	const float wo_trans_dot_wh_trans = dot(/*g_XRiteCarPaint2_interm_data.*/wo_trans, wh_trans_ss); // VoH

	const float f_refl_in  = CPA2_fresnel(L_dot_Nc, Lt_dot_Nc, 1.0, iParameters.clearcoat_ior);
	// What is this?
	const float f_trans_in = (iParameters.clearcoat_no_refraction > 0) ?
		(1.0 - f_refl_in) :
		(1.0 - f_refl_in) * L_dot_Nc/wi_trans_dot_Nc;

	// lightsize calculation
	const float lightsize = 0.35 * sqrt(solid_angle);

	// At the moment the global (per-renderer, u_axf_cpa2_base_enabled and u_axf_cpa2_flakes_enabled) 'enabled' flags are used
	// instead of per-material (g_evald_mat._base_enabled and g_evald_mat._flakes_enabled)
	const vec3 base =
		CPA2_BRDF(wh_trans_dot_Nc, wo_trans_dot_Nc, wi_trans_dot_Nc, wo_trans_dot_wh_trans, lightsize, iParameters);
	const vec3 flakes = // vec3(0.0);
		CPA2_flake_btf(wh_trans_dot_Nc, wo_trans_dot_Nc, wi_trans_dot_Nc, wo_trans_dot_wh_trans,
			iParameters.tc_gpu_mapping.xy, lightsize, iParameters);

	return /*g_XRiteCarPaint2_interm_data.*/f_trans_out * f_trans_in * (base + flakes);

	//return CPA2_MultMaterialLight(
	//	g_XRiteCarPaint2_interm_data.f_trans_out * f_trans_in * (base + flakes),
	//	frag_light_data.inRad);
}

// ----------------------------------------------------------------------------

/*
vec3 CPA2_ProcessLight(//const in FragLightingData frag_light_data,
	const in BRDFParameters iParameters) {
	const float solid_angle = 0.0;
	return CPA2_ProcessLightAxfCpa2(//frag_light_data,
		solid_angle, iParameters);
}

#ifdef ImageBasedLighting

vec3 CPA2_ProcessIBL(//const in FragLightingData frag_light_data,
	const in BRDFParameters iParameters) {
	// We need to make a copy in order to be able to modify some fields.
	FragLightingData frag_light_data2 = frag_light_data;

	vec3 outRad_sum = vec3(0.0, 0.0, 0.0);

	for (int iDirLight = 0; iDirLight < 16; iDirLight++) {
		const vec3 L_ss = cb_IBLDirLightsApprox.u_IBLDirLightsApprox[iDirLight]._direction;
		const float solid_angle = cb_IBLDirLightsApprox.u_IBLDirLightsApprox[iDirLight].solid_angle;
		const vec3 inRad = cb_IBLDirLightsApprox.u_IBLDirLightsApprox[iDirLight]._color;

		// Prepare the fragment lighting data which contains different vectors in view space - part2
		const vec3 L_vs = mat3(u_sce2vie) * L_ss;
		BuildFragLightingData2(frag_light_data2, L_vs, inRad);

		outRad_sum += //u_ibl_dir_lights_approx[iDirLight]._enabled ?
			CPA2_ProcessLightAxfCpa2(//frag_light_data2,
				solid_angle, iParameters);
			//vec3(0.0, 0.0, 0.0);
	}

	return outRad_sum;
}

#endif // ImageBasedLighting
*/

// ----------------------------------------------------------------------------

#endif // XRiteCarPaint2
