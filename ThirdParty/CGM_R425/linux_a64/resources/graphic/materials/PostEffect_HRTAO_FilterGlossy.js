{
  "Effect" : "PostEffect_HRTAO_FilterGlossy", 
	"Technique" : "Default",
  "InputParameters" : 
    [
        { "Name": "positionNormals", "Type": "Image" },
      { "Name": "cellIndices", "Type": "Image" },
      { "Name": "resultDiffuse", "Type": "Image" },
      { "Name": "resultGlossy", "Type": "Image" },
      { "Name": "outputImageDiffuse", "Type": "Image" },
      { "Name": "outputImageGlossy", "Type": "Image" },
      { "Name": "outputImageDiffusePrev", "Type": "Image" },
      { "Name": "outputImageGlossyPrev", "Type": "Image" }
    ]
}
