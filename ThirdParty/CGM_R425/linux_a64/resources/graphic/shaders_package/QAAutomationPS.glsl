void ProcessFinalColor(inout vec4 ioFinalColor) { 
      vec3 color = basicComputeAlbedo();    
      ioFinalColor.a = basicComputeOpacity();  
      mat4 viewMat = vGetViewMatrix();
      vec3 light1 = normalize((viewMat*vec4(0.0,0.0,1.0,0.0)).xyz);    
      vec3 light2 = normalize((viewMat*vec4(0.0,-1.0,-1.0,0.0)).xyz);     
      vec3 light3 = normalize((viewMat*vec4(0.0,1.0,-1.0,0.0)).xyz); 
      vec3 viewNorm = vGetViewNormal();
      float ambientCoef = 0.11;
      ioFinalColor.rgb = 2.0 * color * (ambientCoef + 0.44*clamp(dot(viewNorm, light1), 0.0, 1.0) + 0.22*clamp(dot(viewNorm, light2), 0.0, 1.0) + 0.22*clamp(dot(viewNorm, light3), 0.0, 1.0));    
}
