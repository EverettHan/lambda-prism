{
	"Effect" : "PostEffect_DecalTranspar", 
	"Technique" : "PostProcess", 
  "InputParameters" : 
	[
    { "Name" : "backBuffer", "Type" : "Texture" },
    { "Name" : "DecalTransparZMap", "Type" : "Image" },
    { "Name" : "DecalTransparData", "Type" : "UnorderedBuffer" },
    { "Name" : "s_Tail", "Type" : "Texture" },
    { "Name" : "s_TailDepth", "Type" : "Texture" }
  ]
}
