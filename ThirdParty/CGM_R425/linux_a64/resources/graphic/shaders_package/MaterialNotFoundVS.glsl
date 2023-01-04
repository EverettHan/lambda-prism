void main()
{
	vec4 localPosition = vec4(vGetPosition(), 1.0);
	vec4 worldPosition = vGetWorldMatrix()*localPosition;

  gl_Position  = vGetViewProjMatrix()*worldPosition;
}
