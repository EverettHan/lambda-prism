void main(void)
{
  vec2 textCoord = vGetPosition().xy*0.5+0.5;

  vec4 ray;
  ray.xy = -vFma(textCoord.xy, cb_Camera.u_BufferToViewNearPlane.zw, cb_Camera.u_BufferToViewNearPlane.xy);
  ray.z = cb_Camera.u_NearFarLogFactor.x;
  ray.w = 0.0;
  ray =  cb_Camera.u_ViewInverseMatrix * ray;
  vec3 normRay = vNormalize(vec3(-ray.xy, ray.z));
  
  vec3 normal = cbBackground.Normal.xyz;
  float scale = vClamp(vDot(normal, normRay)*cbBackground.Ratio, 0.0, 1.0);
  
  vec4 col = vMix(cbBackground.ColorHorizon, cbBackground.ColorTop, scale);
  vSkyColor = col;
  
  gl_Position = vec4(vGetPosition(), 1.0);
}
