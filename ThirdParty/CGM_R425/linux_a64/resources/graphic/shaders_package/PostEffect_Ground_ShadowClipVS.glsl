void main(void)
{
  // input is a triangle for pass fullscreen : {(-1,-1, 0.99),(-1,3, 0.99),(3,-1, 0.99)}
  vec4 localPos = vec4(vGetPosition().xy, 0, 1);
  localPos.xy -= vec2(0.5); // To center the triangle on (0,0)
  localPos.xy *= 10.0;     // to have a kind of inifnite plane
  
  // Draw the triangle as kinf of infinite ambiance ground
  vec4 viewPosition = cb_GroundShadow_Auto.u_GroundWorldViewMatrix * localPos;
  
  gl_Position = _sbCbCamera.ProjMatrix * viewPosition;
}
