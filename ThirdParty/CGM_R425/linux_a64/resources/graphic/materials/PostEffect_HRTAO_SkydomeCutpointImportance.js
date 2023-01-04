{
  "Effect" : "PostEffect_HRTAO_SkydomeCutpointImportance", 
	"Technique" : "Default",
  "InputParameters" : 
  [
    { "Name": "hdrEnv", "Type": "Texture" },
    { "Name": "prefixSumOutputBuffer", "Type": "UnorderedBuffer" },
    { "Name": "prefixSumPartitionsBuffer", "Type": "UnorderedBuffer" },
    { "Name": "cutPointBuffer", "Type": "UnorderedBuffer" },
    { "Name": "metadataBuffer", "Type": "UnorderedBuffer" },
    { "Name": "visibilityBuffer", "Type": "UnorderedBuffer" }
  ]
}
