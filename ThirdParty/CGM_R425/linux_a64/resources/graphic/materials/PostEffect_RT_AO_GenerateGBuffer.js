{
    "Effect" : "PostEffect_RT_AO_GenerateGBuffer", 
	"Technique" : "Default",
    "InputParameters" :
	[
        { "Name" : "GBuffer", "Type" : "Image" },
	    { "Name" : "NormalMap", "Type" : "Texture" },
        { "Name" : "ZMap", "Type" : "Texture" },
        { "Name" : "WorldPosMap", "Type" : "Texture" }
    ]
}
