void ProcessFinalColor(inout vec4 ioFinalColor)
{
	vec3 PosInWorld = (vGetViewInverseMatrix() * vec4(vGetViewPosition(),1.0)).xyz;
	// when posInWorld.x=-width/2 => texCoord.u=0; 
	// when posInWorld.x = width/2 => texCoord.u=1
	vec3 texCoord = clamp(PosInWorld / (cb_cbTexture3DTest.BoxSize * 0.5),-1.0,1.0); // -1 to 1
	texCoord = (texCoord + vec3(1.0,1.0,1.0))*0.5; // 0 to 1
	ioFinalColor = vec4(texture(Texture3DTestTexture, texCoord ).rgb,1.0);
}
