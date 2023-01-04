{
    "ShaderBuilder": {
        /*Version is used by the shader cache */
        "Version": "1.0",
        /*"ShaderLibrary": "Disk",*/
        /*Declaration of all the keywords reserved to PrivateShaders */
        "Keywords": [
            "_SB", "VertexOut","VertexIn", "EmitVertex", "EndPrimitive"
        ],
        /*Shaders which can contain keywords*/
        "PrivateShaders": [
            "lighting",
            "compositing",
            "ibl",
            "ShaderBuilderUberVS_1.1",
            "ShaderBuilderUberGS_1.1",
            "ShaderBuilderUberPS_1.1",
            "ShaderBuilderUberES_1.1",
            "ShaderBuilderUberCS_1.1",
            "ShaderBuilderUberVertexProcessing_1.1",
            "ShaderBuilderUberVertexProcessing_1.2",
            "ShaderBuilderUberVertexProcessing_rt",
            "ShaderBuilderUberGS_1.2",
            "ShaderBuilderUberPS_1.2",
            "ShaderBuilderUberHitGroup_1.2",
            "streams",
            "varyings",
            "fullScreenQuadVS",
            "prototypes",
            "ShadowsPS",
            "ShadowsVS",
            "ShadowsGS",
            "SkyVS",
            "SkyPS",
            "streams",
            "streams_rt",
            "ubos",
            "sampleGS",
            "PostEffect_DOF_BokehGS",
            "DrawTextVS",
            "Capping",
            "TextVS_Default_pdsfx",
            "PostEffect_FullScreenQuadx2GS",
            "PostEffect_FullScreenQuadx6GS",
            "PostEffect_SSAO_GS",
            "OcclusionVS",
            "OcclusionGS",
            "OcclusionPS",
            "OcclusionPackResultVS",
            "Basic3D_Stereo_GS",
            "EVisuPBR_HG"
        ],
        /*internals are automtically concatenated to all shader stage*/
        "Internals": [
            "OptionGrammar",
            "intrinsicsAbstraction",
            "helpers",
            "fresnel_dielectric",
            "specular_antialiasing",
            "distribution_modified_lambert",
            "distribution_ggx",
            "distribution_inverted_ashikhmin",
            "brdf",
            "mapping_info",
            "mapping_planar",
            "mapping_cubic",
            "mapping_spherical",
            "mapping_spherical_normalized",
            "mapping_cylindrical",
            "mapping_infinite_cylindrical",
            "mapping_infinite_cylindrical_normalized",
            "mapping_infinite_cylindrical_normalized_angle_pres"
        ],
        /*File to load when a stage does not compile*/
        "FallBackShader": "error",
        /*Default Shader Options added every where*/
        "DefaultOptions": [
            { "name": "SHADER_BUILDER", "value": 1 }
        ],
        /*If empty string dump\load disabled - else will look in the temp directory to find it*/
        "Dump_CacheFileName": "",
        "Init_CacheFileName": ""
    }
}
