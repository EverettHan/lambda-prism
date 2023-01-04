
//--------------------------------
// Tweakables
//--------------------------------

//-----------------------------------------------------------------------------------------
//  Pixel Shader
//-----------------------------------------------------------------------------------------


float ComputeDepth() : COLOR 
{
    return 1.;
}

//-----------------------------------------------------------------------------------------
//  Techniques
//-----------------------------------------------------------------------------------------


technique WeightedAverageDepth_NV40
{
    pass p0 
    {		
        FragmentProgram = compile fp40 ComputeDepth();
    }
}

technique WeightedAverageDepth_GLSL
{
    pass p0 
    {		
        FragmentProgram = compile glslf ComputeDepth();
    }
}

technique WeightedAverageDepth_NV30
{
    pass p0 
    {		

        FragmentProgram = compile fp30 ComputeDepth();
    }
}

technique WeightedAverageDepth_ARB
{
    pass p0 
    {		

        FragmentProgram = compile arbfp1 ComputeDepth();
    }
}
