{
    "Effect" : "PostEffect_HRTAO_AllocateHashCell", 
	"Technique" : "R",
    "InputParameters" : 
    [
        { "Name": "positionNormals", "Type": "Image" },
        { "Name": "hashMapBufferKey", "Type": "UnorderedBuffer" },
        { "Name": "hashMapBufferContrib", "Type": "UnorderedBuffer" },
        { "Name": "hashMapVisualizationDataBuffer", "Type": "UnorderedBuffer" }
    ]
}
