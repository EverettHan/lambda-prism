vec3 ComputeAlbedo()
{
    return cb_cbLdhBoxImpostor.u_color.rgb;
}

float ComputeOpacity()
{
    return cb_cbLdhBoxImpostor.u_color.a;
}

vec3 ComputeViewNormal()
{
    return vNormal;
}

