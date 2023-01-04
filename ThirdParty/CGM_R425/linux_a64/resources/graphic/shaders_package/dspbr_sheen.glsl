// sheen_alpha is the clamped sheen_roughness

struct DSPBR21xSheenLcurve {
  float a;
  float b;
  float c;
  float d;
  float e;
};

// vMix is an alias for GLSL
// mix(x,y,q) = x*(1-q) + y*q;
// q = (1-r_b)*(1-r_b)
// r_b=0; q=1; mix = y
// r_b=1; q=0; mix = x
void Init_DSPBR21xSheenLcurve(out DSPBR21xSheenLcurve oLCurve, in float sheen_alpha) {
  const float q = vPow2(1.0 - sheen_alpha);
  oLCurve.a = vMix( 21.5473,  25.3245, q);
  oLCurve.b = vMix( 3.82987,  3.32435, q);
  oLCurve.c = vMix( 0.19823,  0.16801, q);
  oLCurve.d = vMix(-1.97760, -1.27393, q);
  oLCurve.e = vMix(-4.32054, -4.85967, q);
}

float DSPBR21xSheenL(in float x, in DSPBR21xSheenLcurve Lcurve) {
  return Lcurve.a / (1.0 + Lcurve.b*vPow(x,Lcurve.c)) + Lcurve.d*x + Lcurve.e;
}

float DSPBR21xSheenLambda(in float costheta, in DSPBR21xSheenLcurve Lcurve) {
  const float costheta_abs = vAbs(costheta);
  return (costheta_abs < 0.5) ?
    vExp(DSPBR21xSheenL(costheta_abs, Lcurve)) :
    vExp(2.0*DSPBR21xSheenL(0.5, Lcurve) - DSPBR21xSheenL(1.0-costheta_abs, Lcurve));
}

float DSPBR21xSheenGb(in float v_dot_n, in float l_dot_n, in DSPBR21xSheenLcurve Lcurve) {
  return 1.0 / (1.0 + DSPBR21xSheenLambda(v_dot_n, Lcurve) + DSPBR21xSheenLambda(l_dot_n, Lcurve));
}

float DSPBR21xSheenDb(in float h_dot_n, in float sheen_alpha) {
  const float sin_theta_b_2 = 1.0 - vPow2(h_dot_n);
  const float rb_inv = 1.0 / vMax(1e-6, sheen_alpha);
  // Square root of sin_theta_b_2 is hidden here in the pow(..., 0.5*...) call
  return (2.0 + rb_inv) * vPow(sin_theta_b_2, 0.5*rb_inv) * 0.5 * INV_PI;
}

float DSPBR21xSheenMb(in float h_dot_n, in float v_dot_n, in float l_dot_n, in float sheen_alpha, in DSPBR21xSheenLcurve Lcurve) {
  return DSPBR21xSheenDb(h_dot_n, sheen_alpha) * DSPBR21xSheenGb(v_dot_n, l_dot_n, Lcurve) / (4.0 * v_dot_n * l_dot_n);
}

// Alternative sheen model
float DSPBR21xSheenMb_alt(in float h_dot_n, in float v_dot_n, in float l_dot_n, in float sheen_alpha) {
  return DSPBR21xSheenDb(h_dot_n, sheen_alpha) / (4.0 * max(l_dot_n + v_dot_n - l_dot_n*v_dot_n, 1e-6));
}

float DSPBR21xSheenEb(in sampler2D sheenDirAlbedoSampler, in float cos_theta, in float sheen_alpha) {
  //TODO remap cos_theta and sheen_alpha to texture coordinates
  return float(vTexture(sheenDirAlbedoSampler, vec2(cos_theta, sheen_alpha)));
}

// Fit of the directional albedo distribution from DSPBR 2021x
// Not described in the DSPBR spec.
// The fit for the 'full' (not alternative) sheen model
float DSPBR21xSheenEb_fit(in float cos_theta, in float sheen_alpha) {
  const float c = 1.0 - cos_theta;
  return 0.65584461 * c*c*c + 1.0 / (4.16526551 + exp(-7.97291361*sqrt(sheen_alpha) + 6.33516894));
}

// Contribution of sheen into the final radiance, which should added to the attenuated core BSDF
vec3 DSPBR21xSheen_contribution(in float v_dot_n, in float l_dot_n, in float h_dot_n,
  in float sheen_intensity, in vec3 sheen_color, in float sheen_alpha) {
  DSPBR21xSheenLcurve sheenLcurve;
  Init_DSPBR21xSheenLcurve(sheenLcurve, sheen_alpha);
  const float Mb = DSPBR21xSheenMb(h_dot_n, v_dot_n, l_dot_n, sheen_alpha, sheenLcurve);
  const float Mb_alt = DSPBR21xSheenMb_alt(h_dot_n, v_dot_n, l_dot_n, sheen_alpha);
  return Mb_alt * sheen_intensity * sheen_color;
}

// Core BSDF attenuation due to sheen
float DSPBR21xSheen_core_att(in float v_dot_n, in float l_dot_n,
  in float sheen_intensity, in vec3 sheen_color, in float sheen_alpha/*, in sampler2D sheen_dir_albedo_texture*/) {
  // max_sheen_color = pho_b^ = max(rho_b)
  const float max_sheen_color = max(max(sheen_color.r, sheen_color.g), sheen_color.b);
  // Don't mix up these two:
  // b_rho_b = iParameters.sheen * iParameters.sheenColor, used to scale the microfacet distribution
  // b_rho_b_hat = iParameters.sheen * max_sheen_color, used to scale the Core BSDF
  const float b_rho_b_hat = sheen_intensity * max_sheen_color;
  // DSPBR21xSheenEb_fit(v_dot_n, sheen_alpha)
  return vMin(
    1.0 - b_rho_b_hat * DSPBR21xSheenEb_fit(/*sheen_dir_albedo_texture,*/ v_dot_n, sheen_alpha),
    1.0 - b_rho_b_hat * DSPBR21xSheenEb_fit(/*sheen_dir_albedo_texture,*/ l_dot_n, sheen_alpha));
}

// Core BSDF attenuation due to sheen
// Version for IBL which differs in that only v_dot_n is used, as there is no light vector available
float DSPBR21xSheen_core_att_2(in float v_dot_n,
  in float sheen_intensity, in vec3 sheen_color, in float sheen_alpha/*, in sampler2D sheen_dir_albedo_texture*/) {
  // max_sheen_color = pho_b^ = max(rho_b)
  const float max_sheen_color = max(max(sheen_color.r, sheen_color.g), sheen_color.b);
  // Don't mix up these two:
  // b_rho_b = iParameters.sheen * iParameters.sheenColor, used to scale the microfacet distribution
  // b_rho_b_hat = iParameters.sheen * max_sheen_color, used to scale the Core BSDF
  const float b_rho_b_hat = sheen_intensity * max_sheen_color;
  // DSPBR21xSheenEb_fit(v_dot_n, sheen_alpha)
  return 1.0 - b_rho_b_hat * DSPBR21xSheenEb_fit(/*sheen_dir_albedo_texture,*/ v_dot_n, sheen_alpha);
}

void ApplyDSPBR21xSheenLayer(out vec3 sheen_contribution, out float core_att_from_sheen,
  in float v_dot_n, in float l_dot_n, in float h_dot_n,
  in float sheen_intensity, in vec3 sheen_color, in float sheen_roughness) {
  // Sheen roughness is clamped to range [0.07; 1] to avoid numerical issues, see DSPBR 2021x spec, section about Sheen
  const float sheen_alpha = max(sheen_roughness, 0.07);
  sheen_contribution = DSPBR21xSheen_contribution(v_dot_n, l_dot_n, h_dot_n, sheen_intensity, sheen_color, sheen_alpha);
  core_att_from_sheen = DSPBR21xSheen_core_att(v_dot_n, l_dot_n, sheen_intensity, sheen_color, sheen_alpha);
}

void ApplyDSPBR22xSheenLayer(out vec3 sheen_contribution, out float core_att_from_sheen,
  in float v_dot_n, in float l_dot_n, in float h_dot_n, in vec3 sheen_color, in float sheen_roughness) {
  // For DSPBR22x sheen roughness is not clamped
  // sheen_intensity fixed to one according to DSPBR22x specification
  sheen_contribution = DSPBR21xSheen_contribution(v_dot_n, l_dot_n, h_dot_n, 1.0, sheen_color, vPow2(sheen_roughness));
  core_att_from_sheen = DSPBR21xSheen_core_att(v_dot_n, l_dot_n, 1.0, sheen_color, vPow2(sheen_roughness));
}
