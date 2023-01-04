vec2 gv2_tex;

vec3 ComputeObjectPosition()
{
#ifdef PDSFXInstancing //This macro will be defined if the instancing buffer is set
	int nPos = vGetInstanceID() * 2;
    vec4 v4Pos = vGetInstanceData(nPos  ); // x, y, z, scale
    vec4 v4Dat = vGetInstanceData(nPos+1); // texture.x, texture.y, dummy, dummy
    gv2_tex = v4Dat.xy;

	vec3 v3Pos = vGetAttribPosition();
	v3Pos *= v4Pos.w;
    return v3Pos + v4Pos.xyz;
#else
    return vec3(0.0);
#endif
}

void ComputeVaryingValues()
{
#if 0 // ndef GLES2Platform
    vec4 v4Col = vGetAttribColor(); // gl_FrontColor; // vGetColor();
	v4Col.a = cb_cbSMAResultsData.ResultsAlpha;
#else
    vec4 v4Col = vec4(1.0,1.0,1.0,cb_cbSMAResultsData.ResultsAlpha); // NRE
#endif

    float fDim = cb_cbSMAResultsData.ResultsDim;
    if( 0.0 != fDim )
    {
        // Get texture coordinate for the result value
        float fResX = gv2_tex.x * cb_cbSMAResultsData.ResultScale + cb_cbSMAResultsData.ResultShift;
        if( 4.0 > fDim )
            gv2_tex.x = clamp(fResX, 0.0, 1.0);
        else
            gv2_tex.x = fract(fResX);
        if( 1.0 == fDim || 5.0 == fDim )
        {
            gv2_tex.y = 0.0;
            v4Col.rgb *= vTexture(ContourMap1D, gv2_tex).rgb;
        }
        else //if( 2.0 == cb_cbSMAResultsData.ResultsDim )
        {
            gv2_tex.y *= cb_cbSMAResultsData.NoResultScale; // = clamp(gv2_tex.y,0.0,1.0);
            v4Col.rgb *= vTexture(ContourMap2D, gv2_tex).rgb;
        }
    }

    v4_color = v4Col;// * 0.9;
}
