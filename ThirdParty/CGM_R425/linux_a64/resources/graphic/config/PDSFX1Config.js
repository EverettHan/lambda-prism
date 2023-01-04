{
  "PDSFX1Config": {
    "BlacklistedWords": [
      "_PDSFX",
      "_vPriv",
      "_sb",
      "gl_"
    ],
    "MacroNameCharacters":"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890",
    "MacroContentCharacters":"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz .,;:1234567890+-*/%&|()[]<>=!?",
    "VertexOptionTriggers": [
      {"option":"_PDSFX1_VS_CommonValues", "trigger":"ComputeCommonValues"},
      {"option":"_PDSFX1_VS_Position", "trigger":"ComputeObjectPosition"},
      {"option":"_PDSFX1_VS_Normal", "trigger":"ComputeObjectNormal"},
      {"option":"_PDSFX1_VS_Tangent", "trigger":"ComputeObjectTangent"},
      {"option":"_PDSFX1_VS_Binormal", "trigger":"ComputeObjectBinormal"},
      {"option":"_PDSFX1_VS_TangentSpace", "trigger":"ProcessViewTangentSpace"},
      {"option":"_PDSFX1_VS_TexCoord0", "trigger":"ComputeObjectTexCoord0"},
      {"option":"_PDSFX1_VS_TexCoord1", "trigger":"ComputeObjectTexCoord1"},
      {"option":"_PDSFX1_VS_TexCoord2", "trigger":"ComputeObjectTexCoord2"},
      {"option":"_PDSFX1_VS_PointSize", "trigger":"ComputePointSize"},
      {"option":"_PDSFX1_VS_ClipSpacePos", "trigger":"ProcessClipSpacePosition"},
      {"option":"_PDSFX1_VS_Varyings", "trigger":"ComputeVaryingValues"}
    ],
    "GeometryOptionTriggers": [
      {"option":"_PDSFX1_GS_CommonValues", "trigger":"ComputeCommonValues"},
      {"option":"_PDSFX1_GS_ClipSpacePos", "trigger":"ProcessClipSpacePosition"},
      {"option":"_PDSFX1_GS_Varyings", "trigger":"ComputeVaryingValues"},
      {"option":"_PDSFX1_GS_OutputStreams", "trigger":"ComputeCustomStreams"}
    ],
    "FragmentOptionTriggers": [
      {"option":"_PDSFX1_FS_CommonValues", "trigger":"ComputeCommonValues"},
      {"option":"_PDSFX1_FS_Discard", "trigger":"ComputeDiscard"},
      {"option":"_PDSFX1_FS_Position", "trigger":"ComputeViewPosition"},
      {"option":"_PDSFX1_FS_Normal", "trigger":"ComputeViewNormal"},
      {"option":"_PDSFX1_FS_Albedo", "trigger":"ComputeAlbedo"},
      {"option":"_PDSFX1_FS_F0", "trigger":"ComputeSpecularReflectance"},
      {"option":"_PDSFX1_FS_Roughness", "trigger":"ComputeRoughness"},
      {"option":"_PDSFX1_FS_Transparency", "trigger":"ComputeTransparency"},
      {"option":"_PDSFX1_FS_Emissive", "trigger":"ComputeEmissive"},
      {"option":"_PDSFX1_FS_AdvancedBRDFUser", "trigger":"ProcessBRDFParameters"},
      {"option":"_PDSFX1_FS_Opacity", "trigger":"ComputeOpacity"},
      {"option":"_PDSFX1_FS_Capping", "trigger":"ProcessCappingParameters"},
      {"option":"_PDSFX1_FS_FinalColor", "trigger":"ProcessFinalColor"}
    ]
  }
}
