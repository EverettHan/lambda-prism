#ifdef SO_EVISUPBR_FLAKES

void triplanar_mapping(in vec3 pp, in vec3 pp_ddx, in vec3 pp_ddy, in vec3 nn, out vec2 uv, out vec2 uv_ddx, out vec2 uv_ddy)
{
	vec3 p = vec3(pp.x, pp.y, pp.z);
	vec3 n = vec3(nn.x, nn.y, nn.z);

	vec3 p_ddx = vec3(pp_ddx.x, pp_ddx.y, pp_ddx.z);
	vec3 p_ddy = vec3(pp_ddy.x, pp_ddy.y, pp_ddy.z);

	vec3 s = sign(n);

	if (abs(n.x) >= abs(n.y) && abs(n.x) >= abs(n.z))
	{
		uv = vec2(s.x * p.y, p.z);
		uv_ddx = vec2(s.x * p_ddx.y, p_ddx.z);
		uv_ddy = vec2(s.x * p_ddy.y, p_ddy.z);
	}
	else if (abs(n.y) >= abs(n.z))
	{
		uv = vec2(-s.y * p.x, p.z);
		uv_ddx = vec2(-s.y * p_ddx.x, p_ddx.z);
		uv_ddy = vec2(-s.y * p_ddy.x, p_ddy.z);
	}
	else
	{
		uv = vec2(s.z * p.x, p.y);
		uv_ddx = vec2(s.z * p_ddx.x, p_ddx.y);
		uv_ddy = vec2(s.z * p_ddy.x, p_ddy.y);
	}

	uv = fract(uv + vec2(0.5));
}

void parallelogram_bounding_box(in vec2 pos, in vec2 ddx, in vec2 ddy, out vec2 par_bb_min, out vec2 par_bb_max)
{
	vec2 par_corner_1 = pos;
	vec2 par_corner_2 = pos + ddx;
	vec2 par_corner_3 = pos + ddy;
	vec2 par_corner_4 = pos + ddx + ddy;

	par_bb_min = vec2(min(min(par_corner_1.x, par_corner_2.x), min(par_corner_3.x, par_corner_4.x)),
		min(min(par_corner_1.y, par_corner_2.y), min(par_corner_3.y, par_corner_4.y)));

	par_bb_max = vec2(max(max(par_corner_1.x, par_corner_2.x), max(par_corner_3.x, par_corner_4.x)),
		max(max(par_corner_1.y, par_corner_2.y), max(par_corner_3.y, par_corner_4.y)));
}

void prepare_seed_grid_rasterize_parallelogram(in bool close_up_case, in vec2 pos_orig, in vec2 ddx_orig, in vec2 ddy_orig, int seed_res, out vec2 pos_grid, out vec2 ddx_grid, out vec2 ddy_grid, out vec4 bounding_box)
{
	vec2 pos;
	vec2 ddx;
	vec2 ddy;

	if (close_up_case)
	{
		float node_size = 1.25 / float(seed_res);
		pos = pos_orig - vec2(node_size);
		ddx = vec2(2.0 * node_size, 0.0);
		ddy = vec2(0.0, 2.0 * node_size);
	}
	else
	{
		pos = pos_orig;
		ddx = ddx_orig;
		ddy = ddy_orig;
	}

	vec2 footprint_bbox_min;
	vec2 footprint_bbox_max;

	parallelogram_bounding_box(pos, ddx, ddy, footprint_bbox_min, footprint_bbox_max);

	ivec2 seed_grid_footprint_bb_min = ivec2(floor(vec2(ivec2(seed_res))*footprint_bbox_min));
	ivec2 seed_grid_footprint_bb_max = ivec2(ceil(vec2(ivec2(seed_res))*footprint_bbox_max));

	int max_grid_size = 10;

	ivec2 footprint_center = ivec2(vec2(ivec2(seed_res)) * (pos + vec2(0.5) * (ddx + ddy)));
	seed_grid_footprint_bb_min = clamp(seed_grid_footprint_bb_min, footprint_center - ivec2(max_grid_size / 2), footprint_center + ivec2(max_grid_size / 2));
	seed_grid_footprint_bb_max = clamp(seed_grid_footprint_bb_max, footprint_center - ivec2(max_grid_size / 2), footprint_center + ivec2(max_grid_size / 2));

	seed_grid_footprint_bb_min = clamp(seed_grid_footprint_bb_min, ivec2(-seed_res), ivec2(2 * seed_res));
	seed_grid_footprint_bb_max = clamp(seed_grid_footprint_bb_max, ivec2(-seed_res), ivec2(2 * seed_res));

	vec2 seed_res_multiplier = vec2(ivec2(seed_res));

	pos_grid = seed_res_multiplier * pos;
	ddx_grid = seed_res_multiplier * ddx;
	ddy_grid = seed_res_multiplier * ddy;
	bounding_box = vec4(vec2(seed_grid_footprint_bb_min), vec2(seed_grid_footprint_bb_max + ivec2(1)));
}

int encrypt_tea(in int v0, in int v1, in ivec4 xor_key, in int rounds)
{
	ivec4 tea_key = ivec4(0xa341316c, 0xc8013ea4, 0xad90777d, 0x7e95761e);
	int sum = 0;
	int delta = 0x9e3779b9;
	ivec4 key = tea_key ^ xor_key;

	for (int i = 0; i < rounds; i += 1)
	{
		sum += delta;
		v0 += ((v1 << 4) + key.x) ^ (v1 + sum) ^ ((v1 >> 5) + key.y);
		v1 += ((v0 << 4) + key.z) ^ (v0 + sum) ^ ((v0 >> 5) + key.w);
	}

	return v1;
}

int prepare_sampler(in int seed_res, in int i, in int j)
{
	int i_wrapped = (i + seed_res) % seed_res;
	int j_wrapped = (j + seed_res) % seed_res;
	return encrypt_tea(915927258, 1547188273, ivec4(i_wrapped, j_wrapped, 0, 0), 6);
}

#define RAND_MAX (1<<24)

float int32_to_float_0_1(in int a)
{
	int m = (a >> 9) & 0x007fffff;
	int i = 0x3F800000 | m;
	float f = intBitsToFloat(i);
	return f - 1.0;
};

vec2 int32_to_float_0_1(in ivec2 a)
{
	ivec2 m = (a >> ivec2(9)) & 0x007fffff;
	ivec2 i = ivec2(0x3F800000) | m;
	vec2 f = intBitsToFloat(i);
	return f - vec2(1.0);
};

float next(inout int seed)
{
	//seed = abs((1140671485 * seed + 12820163) % RAND_MAX);
	//return seed / float(RAND_MAX);
	seed = 1103515245 * seed + 12345;
	return int32_to_float_0_1(seed);
}

vec2 next2(inout int seed)
{
	ivec2 s = ivec2(1103515245, -1029531031) * ivec2(seed) + ivec2(12345, -740551042);
	vec2 r = int32_to_float_0_1(s);
	seed = s.y;
	return r;
}

float generate_sample1d(inout int seed)
{
	return next(seed);
}

vec2 generate_sample2d(inout int seed)
{
	vec2 s = next2(seed);
	float s1 = s.x;
	float s2 = s.y;
	//float s1 = next(seed);
	//float s2 = next(seed);
	return vec2(s1, s2);
}

vec2 generate_cell_position(inout int seed)
{
	return generate_sample2d(seed);
}

vec3 generate_flake_orientation(inout int seed, in float flake_orientation_roughness)
{
	vec2 uv = generate_sample2d(seed);
	float w = (1.0 - uv.x) / (1.0 - (1.0 - (flake_orientation_roughness*flake_orientation_roughness))*uv.x);
	w = clamp(w, 0.0, 1.0); // makes up for numeric instabilities and possible NaNs.
	return vec3(sqrt(1.0 - w) * cos(2.0*PI*uv.y), sqrt(1.0 - w) * sin(2.0*PI*uv.y), sqrt(w));
}

bool generate_cell_opaqueness(inout int seed, in float opaqueness_probability)
{
	float u = generate_sample1d(seed);
	return u < opaqueness_probability;
}

void generate_cell(inout int seed, in float flake_orientation_roughness, in float flake_coverage, out vec2 pos, out vec3 o, out bool is_opaque)
{
	pos = generate_cell_position(seed);
	o = generate_flake_orientation(seed, flake_orientation_roughness);
	is_opaque = generate_cell_opaqueness(seed, flake_coverage);
}

const float avg_flakes_in_leaf = 4.0;
const int flakes_in_leaf = int(avg_flakes_in_leaf);

struct flake_state_t
{
	int seed_res;
	float flake_coverage;
	float flake_orientation_roughness;
	float node_size;
	vec2 pos_orig;
	vec2 ddx_orig;
	vec2 ddy_orig;
};

struct voronoi_result_t
{
	vec3 voronoi_orientation;
	float best_voronoi_center_dist_sq;
};

struct stochastic_result_t
{
	float flakes_contributing;
	float flakes_in_footprint;
};

bool point_in_footprint(in vec2 p, in vec2 fp_pos, in vec2 fp_ddx, in vec2 fp_ddy)
{
	float det = fp_ddx.x * fp_ddy.y - fp_ddx.y * fp_ddy.x;
	float inv_det = 1.0 / det;
	float cos_ddx_ddy = dot(fp_ddx, fp_ddy) * 1.0 / sqrt(dot(fp_ddx, fp_ddx) * dot(fp_ddy, fp_ddy));
	bool very_thin_parallelogram = abs(cos_ddx_ddy) > 1.0 - 1e-6;

	if (very_thin_parallelogram)
		return false;

	vec2 prel = p - fp_pos;
	vec2 uv = inv_det * vec2(dot(vec2(-prel.y, prel.x), fp_ddy), dot(vec2(prel.y, -prel.x), fp_ddx));

	return all(lessThanEqual(vec2(0.0), uv)) && all(lessThanEqual(uv, vec2(1.0)));
}

vec3 Tangent2World(in vec3 iTS, in vec3 iNormal)
{
	vec3 res;

	vec3 up = abs(iNormal.z) < 0.9999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
	vec3 tX = normalize(cross(up, iNormal));
	vec3 tY = normalize(cross(iNormal, tX));

	res.x = tX.x*iTS.x + tY.x*iTS.y + iNormal.x*iTS.z;
	res.y = tX.y*iTS.x + tY.y*iTS.y + iNormal.y*iTS.z;
	res.z = tX.z*iTS.x + tY.z*iTS.y + iNormal.z*iTS.z;

	return res;
}

void stochastic_rasterize_accumulator(in flake_state_t state, inout stochastic_result_t result, in int i, in int j, in float cos_cone_angle, in vec3 view, in vec3 light, in vec3 normal, out bool cont)
{
	int s = prepare_sampler(state.seed_res, i, j);

	for (int k = 0; cont && k < flakes_in_leaf; k++)
	{
		vec2 cell_pos;
		vec3 o;
		bool is_opaque;

		generate_cell(s, state.flake_orientation_roughness, state.flake_coverage, cell_pos, o, is_opaque);

		if (is_opaque)
		{
			o = Tangent2World(o, normal);

			vec3 r = normalize(reflect(view, o));
			vec2 flake_center_uv_global = vec2(state.node_size) * (vec2(ivec2(i, j)) + vec2(cell_pos));
			bool flake_in_footprint = point_in_footprint(flake_center_uv_global, state.pos_orig, state.ddx_orig, state.ddy_orig);

			float flake_is_present = flake_in_footprint ? 1.0 : 0.0;
			result.flakes_in_footprint += flake_is_present;
			bool reflected_view_in_lightcone = dot(r, light) > cos_cone_angle;
			if (reflected_view_in_lightcone)
				result.flakes_contributing += flake_is_present;
		}
	}
	cont = true;
}

void voronoi_rasterize_accumulator(in flake_state_t state, inout voronoi_result_t result, in int i, in int j, out bool cont)
{
	int s = prepare_sampler(state.seed_res, i, j);

	cont = true;

	for (int k = 0; cont && k < flakes_in_leaf; k++)
	{
		vec2 cell_pos;
		vec3 o;
		bool is_opaque;

		generate_cell(s, state.flake_orientation_roughness, state.flake_coverage, cell_pos, o, is_opaque);
		vec2 cell_center_uv_global = vec2(state.node_size) * (vec2(ivec2(i, j)) + vec2(cell_pos));

		vec2 footprint_center = state.pos_orig + 0.5 *  (state.ddx_orig + state.ddy_orig);
		vec2 prel = footprint_center - cell_center_uv_global;
		float voronoi_center_dist_sq = dot(prel, prel);

		bool current_cell_is_closer = voronoi_center_dist_sq < result.best_voronoi_center_dist_sq;

		if (current_cell_is_closer)
		{
			result.best_voronoi_center_dist_sq = voronoi_center_dist_sq;
			result.voronoi_orientation = is_opaque ? o : vec3(0.0);
		}
	}
}

float cross_vec2(in vec2 a, in vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

void reorient(inout vec2 pos, inout vec2 ddx, inout vec2 ddy)
{
	if (cross_vec2(ddy, ddx) > 0.0) { vec2 tmp_ddy = ddy; ddy = ddx; ddx = tmp_ddy; }

	if (ddy.y < 0.0) { vec2 tmp_ddy = ddy; pos = pos + ddy; ddy = ddx; ddx = -tmp_ddy; }
	if (ddy.y < 0.0) { vec2 tmp_ddy = ddy; pos = pos + ddy; ddy = ddx; ddx = -tmp_ddy; }

	if (ddx.y <= 0.0) { vec2 tmp_ddy = ddy; pos = pos + ddx; ddy = -ddx; ddx = tmp_ddy; }
	if (ddx.y <= 0.0) { vec2 tmp_ddy = ddy; pos = pos + ddx; ddy = -ddx; ddx = tmp_ddy; }
}

void stochastic_rasterize(in flake_state_t state, in vec2 pos, in vec2 ddx, in vec2 ddy, in vec2 min_bb, in vec2 max_bb, in float cos_cone_angle, in vec3 view, in vec3 light, in vec3 normal, in stochastic_result_t initial, out stochastic_result_t result)
{
	reorient(pos, ddx, ddy);

	float delta_ddx = ddx.x / abs(ddx.y);
	float delta_ddy = ddy.x / abs(ddy.y);

	vec2 sum = ddy + ddx;

	float min_x = min(pos.x, min(pos.x + ddy.x, pos.x + sum.x));
	min_x = max(min_x, min_bb.x);

	float max_x = max(pos.x, max(pos.x + ddx.x, pos.x + sum.x));
	max_x = min(max_x, max_bb.x);

	float min_y = floor(max(min_bb.y, pos.y));
	float max_y = ceil(min(max_bb.y, pos.y + sum.y));

	float ddy_left_bound = pos.x + (min_y - pos.y + (ddy.x < 0.0 ? 1.0 : 0.0)) * delta_ddy;
	float ddx_left_bound = pos.x + ddy.x + (min_y - (pos.y + ddy.y) + (ddx.x < 0.0 ? 1.0 : 0.0)) * delta_ddx;

	float ddy_right_bound = pos.x + ddx.x + (min_y - (pos.y + ddx.y) + (ddy.x > 0.0 ? 1.0 : 0.0)) * delta_ddy;
	float ddx_right_bound = pos.x + (min_y - pos.y + (ddx.x > 0.0 ? 1.0 : 0.0)) * delta_ddx;

	result = initial;

	int i = 0;
	int max_i = -1;

	int j = int(min_y);

	bool cont;

	do
	{
		if (i >= max_i)
		{
			float boundary_left = max(ddy_left_bound, ddx_left_bound);
			boundary_left = max(boundary_left, min_x);
			i = int(floor(boundary_left));

			float boundary_right = min(ddy_right_bound, ddx_right_bound);
			boundary_right = min(boundary_right, max_x);
			max_i = int(ceil(boundary_right));

			ddy_left_bound += delta_ddy;
			ddx_left_bound += delta_ddx;
			ddy_right_bound += delta_ddy;
			ddx_right_bound += delta_ddx;
		}

		stochastic_rasterize_accumulator(state, result, i, j, cos_cone_angle, view, light, normal, cont);

		i++;
		if (i >= max_i) j++;

	} while (cont && j < int(max_y));
}

void stochastic_hemisphere_rasterize_accumulator(in flake_state_t state, inout vec3 stochasticHemisphereFlakesOrientationresult, in int i, in int j, in float cos_cone_angle, in vec3 view, in vec3 light, in vec3 normal, out bool cont)
{
	int s = prepare_sampler(state.seed_res, i, j);

	for (int k = 0; cont && k < flakes_in_leaf; k++)
	{
		vec2 cell_pos;
		vec3 o;
		bool is_opaque;

		generate_cell(s, state.flake_orientation_roughness, state.flake_coverage, cell_pos, o, is_opaque);

		o = Tangent2World(o, normal);
		vec3 r = normalize(reflect(view, o));

		float val = dot(r, light);
		stochasticHemisphereFlakesOrientationresult += step(0.0, val) * r;
	}
	cont = true;
}

void stochastic_hemisphere_rasterize(in flake_state_t state, in vec2 pos, in vec2 ddx, in vec2 ddy, in vec2 min_bb, in vec2 max_bb, in float cos_cone_angle, in vec3 view, in vec3 light, in vec3 normal, out vec3 stochasticHemisphereFlakesOrientationresult)
{
	reorient(pos, ddx, ddy);

	float delta_ddx = ddx.x / abs(ddx.y);
	float delta_ddy = ddy.x / abs(ddy.y);

	vec2 sum = ddy + ddx;

	float min_x = min(pos.x, min(pos.x + ddy.x, pos.x + sum.x));
	min_x = max(min_x, min_bb.x);

	float max_x = max(pos.x, max(pos.x + ddx.x, pos.x + sum.x));
	max_x = min(max_x, max_bb.x);

	float min_y = floor(max(min_bb.y, pos.y));
	float max_y = ceil(min(max_bb.y, pos.y + sum.y));

	float ddy_left_bound = pos.x + (min_y - pos.y + (ddy.x < 0.0 ? 1.0 : 0.0)) * delta_ddy;
	float ddx_left_bound = pos.x + ddy.x + (min_y - (pos.y + ddy.y) + (ddx.x < 0.0 ? 1.0 : 0.0)) * delta_ddx;

	float ddy_right_bound = pos.x + ddx.x + (min_y - (pos.y + ddx.y) + (ddy.x > 0.0 ? 1.0 : 0.0)) * delta_ddy;
	float ddx_right_bound = pos.x + (min_y - pos.y + (ddx.x > 0.0 ? 1.0 : 0.0)) * delta_ddx;

	int i = 0;
	int max_i = -1;

	int j = int(min_y);

	bool cont;

	do
	{
		if (i >= max_i)
		{
			float boundary_left = max(ddy_left_bound, ddx_left_bound);
			boundary_left = max(boundary_left, min_x);
			i = int(floor(boundary_left));

			float boundary_right = min(ddy_right_bound, ddx_right_bound);
			boundary_right = min(boundary_right, max_x);
			max_i = int(ceil(boundary_right));

			ddy_left_bound += delta_ddy;
			ddx_left_bound += delta_ddx;
			ddy_right_bound += delta_ddy;
			ddx_right_bound += delta_ddx;
		}

		stochastic_hemisphere_rasterize_accumulator(state, stochasticHemisphereFlakesOrientationresult, i, j, cos_cone_angle, view, light, normal, cont);

		i++;
		if (i >= max_i) j++;

	} while (cont && j < int(max_y));
}

void contributing_flakes_in_footprint_stochastic_hemisphere(in float flake_orientation_roughness, in float cos_cone_angle, in float flake_coverage, in float cells_per_area, in vec2 pos_orig, in vec2 ddx_orig, in vec2 ddy_orig, in vec3 view, in vec3 light, in vec3 normal, out vec3 stochasticHemisphereFlakesOrientation)
{
	int seed_res = max(4, int(0.5 * sqrt(cells_per_area)));
	float node_size = 1.0 / float(seed_res);

	vec2 pos_grid;
	vec2 ddx_grid;
	vec2 ddy_grid;
	vec4 bounding_box;

	prepare_seed_grid_rasterize_parallelogram(false, pos_orig, ddx_orig, ddy_orig, seed_res, pos_grid, ddx_grid, ddy_grid, bounding_box);

	flake_state_t state;
	state.seed_res = seed_res;
	state.flake_coverage = flake_coverage;
	state.flake_orientation_roughness = flake_orientation_roughness;
	state.node_size = node_size;
	state.pos_orig = pos_orig;
	state.ddx_orig = ddx_orig;
	state.ddy_orig = ddy_orig;

	vec3 stochasticHemisphereFlakesOrientationresult;
	stochastic_hemisphere_rasterize(state, pos_grid, ddx_grid, ddy_grid, bounding_box.xy, bounding_box.zw, cos_cone_angle, view, light, normal, stochasticHemisphereFlakesOrientationresult);

	stochasticHemisphereFlakesOrientation = vNormalize(stochasticHemisphereFlakesOrientationresult);

}

void voronoi_rasterize(in flake_state_t state, in vec2 pos, in vec2 ddx, in vec2 ddy, in vec2 min_bb, in vec2 max_bb, in voronoi_result_t initial, out voronoi_result_t result)
{
	reorient(pos, ddx, ddy);

	float delta_ddx = ddx.x / abs(ddx.y);
	float delta_ddy = ddy.x / abs(ddy.y);

	vec2 sum = ddy + ddx;

	float min_x = min(pos.x, min(pos.x + ddy.x, pos.x + sum.x));
	min_x = max(min_x, min_bb.x);

	float max_x = max(pos.x, max(pos.x + ddx.x, pos.x + sum.x));
	max_x = min(max_x, max_bb.x);

	float min_y = floor(max(min_bb.y, pos.y));
	float max_y = ceil(min(max_bb.y, pos.y + sum.y));

	float ddy_left_bound = pos.x + (min_y - pos.y + (ddy.x < 0.0 ? 1.0 : 0.0)) * delta_ddy;
	float ddx_left_bound = pos.x + ddy.x + (min_y - (pos.y + ddy.y) + (ddx.x < 0.0 ? 1.0 : 0.0)) * delta_ddx;

	float ddy_right_bound = pos.x + ddx.x + (min_y - (pos.y + ddx.y) + (ddy.x > 0.0 ? 1.0 : 0.0)) * delta_ddy;
	float ddx_right_bound = pos.x + (min_y - pos.y + (ddx.x > 0.0 ? 1.0 : 0.0)) * delta_ddx;

	result = initial;

	int i = 0;
	int max_i = -1;

	int j = int(min_y);

	bool cont;

	do
	{
		if (i >= max_i)
		{
			float boundary_left = max(ddy_left_bound, ddx_left_bound);
			boundary_left = max(boundary_left, min_x);
			i = int(floor(boundary_left));

			float boundary_right = min(ddy_right_bound, ddx_right_bound);
			boundary_right = min(boundary_right, max_x);
			max_i = int(ceil(boundary_right));

			ddy_left_bound += delta_ddy;
			ddx_left_bound += delta_ddx;
			ddy_right_bound += delta_ddy;
			ddx_right_bound += delta_ddx;
		}

		voronoi_rasterize_accumulator(state, result, i, j, cont);

		i++;
		if (i >= max_i) j++;

	} while (cont && j < int(max_y));
}

vec3 foremost_closeup_flake(in float flake_orientation_roughness, in float flake_coverage, in float cells_per_area, in vec2 pos_orig, in vec2 ddx_orig, in vec2 ddy_orig)
{
	int seed_res = max(4, int(0.5 * sqrt(cells_per_area)));
	float node_size = 1.0 / float(seed_res);

	flake_state_t state;
	state.seed_res = seed_res;
	state.flake_coverage = flake_coverage;
	state.flake_orientation_roughness = flake_orientation_roughness;
	state.node_size = node_size;
	state.pos_orig = pos_orig;
	state.ddx_orig = ddx_orig;
	state.ddy_orig = ddy_orig;

	vec2 pos_grid;
	vec2 ddx_grid;
	vec2 ddy_grid;
	vec4 bounding_box;

	prepare_seed_grid_rasterize_parallelogram(true, pos_orig, ddx_orig, ddy_orig, seed_res, pos_grid, ddx_grid, ddy_grid, bounding_box);

	voronoi_result_t initial;
	initial.voronoi_orientation = vec3(0.0);
	initial.best_voronoi_center_dist_sq = intBitsToFloat(0x7f800000); //inf
	voronoi_result_t result;

	voronoi_rasterize(state, pos_grid, ddx_grid, ddy_grid, bounding_box.xy, bounding_box.zw, initial, result);

	return result.voronoi_orientation;
}

void distribute_flake_roughness(in float total_flake_roughness, out float flake_orientation_roughness, out float flake_cos_cone_angle, out float flake_cone_roughness)
{
	float target_cone_angle = radians(7.0);
	float target_cone_solid_angle = 2.0 * PI * (1.0 - cos(target_cone_angle));
	float target_cone_roughness_sq = target_cone_solid_angle / (4.0 * PI - target_cone_solid_angle);
	float total_flake_roughness_sq = total_flake_roughness * total_flake_roughness;
	float flake_cone_roughness_sq = min(target_cone_roughness_sq, 0.5 * total_flake_roughness_sq);
	flake_cos_cone_angle = 1.0 - 2.0 * flake_cone_roughness_sq / (1.0 + flake_cone_roughness_sq);
	float min_cone_angle = radians(1.0);
	float max_cos_cone_angle = cos(min_cone_angle);
	flake_cos_cone_angle = clamp(flake_cos_cone_angle, 0.0, max_cos_cone_angle);

	float flake_orientation_roughness_sq = total_flake_roughness_sq - flake_cone_roughness_sq;
	flake_orientation_roughness = sqrt(flake_orientation_roughness_sq);

	flake_cone_roughness = flake_orientation_roughness;
}

float unsafe_smoothstep(float x)
{
	return x * x * (3.0 - 2.0 * x);
};

float unsafe_smoothstep(float a, float b, float x)
{
	return unsafe_smoothstep((x - a) / (b - a));
};

void model_weights(
	in float closeup_stochastic_transition_in,
	in float closeup_smooth_transition_in,
	in float stochastic_smooth_transition_in,
	in float flake_coverage,
	in float log_cells_in_footprint,
	inout float base_weight,
	inout float closeup_weight,
	inout float stochastic_weight,
	inout float smooth_weight,
	inout vec3 voronoi_cell_orientation,
	in float flake_orientation_roughness,
	in float cells_per_area,
	in vec2 footprint_uv,
	in vec2 footprint_uv_ddx,
	in vec2 footprint_uv_ddy
)
{
	float closeup_stochastic_transition = log(closeup_stochastic_transition_in);
	float closeup_smooth_transition = log(closeup_smooth_transition_in);
	float stochastic_smooth_transition = log(stochastic_smooth_transition_in);

	if (closeup_stochastic_transition >= closeup_smooth_transition - 0.1)
		closeup_stochastic_transition = closeup_smooth_transition - 0.1;

	if (stochastic_smooth_transition <= closeup_smooth_transition + 0.1)
		stochastic_smooth_transition = closeup_smooth_transition + 0.1;

	voronoi_cell_orientation = vec3(0.0);

	if (log_cells_in_footprint < closeup_smooth_transition) {
#ifndef SO_FLAKES_CLOSEUP_OFF
		voronoi_cell_orientation = foremost_closeup_flake(flake_orientation_roughness, flake_coverage, cells_per_area, footprint_uv, footprint_uv_ddx, footprint_uv_ddy);
		bool flake_hit = dot(voronoi_cell_orientation, voronoi_cell_orientation) > 0.0;
		float flake_hit_blend = flake_hit ? 1.0 : 0.0;

		if (log_cells_in_footprint < closeup_stochastic_transition) {
			// case 1 - closeup only
			closeup_weight = flake_hit_blend;
			base_weight = 1.0 - flake_hit_blend;
			stochastic_weight = 0.0;
		} else {
			// case 2 - closeup + stochastic
			stochastic_weight = unsafe_smoothstep(closeup_stochastic_transition, closeup_smooth_transition, log_cells_in_footprint);
			closeup_weight = flake_hit_blend * (1.0 - stochastic_weight);
			base_weight = (1.0 - flake_hit_blend) * (1.0 - stochastic_weight) + (1.0 - flake_coverage) * stochastic_weight;
		}
#else
		{
			closeup_weight = 0.0;
			stochastic_weight = 1.0;
			base_weight = 1.0 - flake_coverage;
		}
#endif // SO_FLAKES_CLOSEUP_OFF
		smooth_weight = 0.0;
	} else {
		closeup_weight = 0.0;

		if (log_cells_in_footprint < stochastic_smooth_transition) {
			// case 3 - stochastic + smooth
			smooth_weight = unsafe_smoothstep(closeup_smooth_transition, stochastic_smooth_transition, log_cells_in_footprint);
			stochastic_weight = 1.0 - smooth_weight;
		} else {
			// case 4 - smooth
			stochastic_weight = 0.0;
			smooth_weight = 1.0;
		}

		base_weight = 1.0 - flake_coverage;
	}

	stochastic_weight *= flake_coverage;
	smooth_weight *= flake_coverage;
}

void contributing_flakes_in_footprint_stochastic(in float flake_orientation_roughness, in float cos_cone_angle, in float flake_coverage, in float cells_per_area, in vec2 pos_orig, in vec2 ddx_orig, in vec2 ddy_orig, in vec3 view, in vec3 light, in vec3 normal, out float flakes_contributing, out float flakes_in_footprint)
{
	int seed_res = max(4, int(0.5 * sqrt(cells_per_area)));
	float node_size = 1.0 / float(seed_res);

	vec2 pos_grid;
	vec2 ddx_grid;
	vec2 ddy_grid;
	vec4 bounding_box;

	prepare_seed_grid_rasterize_parallelogram(false, pos_orig, ddx_orig, ddy_orig, seed_res, pos_grid, ddx_grid, ddy_grid, bounding_box);

	flake_state_t state;
	state.seed_res = seed_res;
	state.flake_coverage = flake_coverage;
	state.flake_orientation_roughness = flake_orientation_roughness;
	state.node_size = node_size;
	state.pos_orig = pos_orig;
	state.ddx_orig = ddx_orig;
	state.ddy_orig = ddy_orig;

	stochastic_result_t initial;
	initial.flakes_in_footprint = 0.0;
	initial.flakes_contributing = 0.0;

	stochastic_result_t result;
	stochastic_rasterize(state, pos_grid, ddx_grid, ddy_grid, bounding_box.xy, bounding_box.zw, cos_cone_angle, view, light, normal, initial, result);

	flakes_contributing = result.flakes_contributing;
	flakes_in_footprint = result.flakes_in_footprint;
}

void stochastic_flakes(in float flake_orientation_roughness, in float cos_cone_angle, in float expected_num_flakes_inside_footprint, in float cells_per_area, in vec2 footprint_pos, in vec2 footprint_pos_ddx, in vec2 footprint_pos_ddy, in float flake_coverage, in vec3 view, in vec3 light, in vec3 normal, out float flakes_contributing, out float flakes_in_footprint)
{
	contributing_flakes_in_footprint_stochastic(flake_orientation_roughness, cos_cone_angle, flake_coverage, cells_per_area, footprint_pos, footprint_pos_ddx, footprint_pos_ddy, view, light, normal, flakes_contributing, flakes_in_footprint);
}

#endif // SO_EVISUPBR_FLAKES
