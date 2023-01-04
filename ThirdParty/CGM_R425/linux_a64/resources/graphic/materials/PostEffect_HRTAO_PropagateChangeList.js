{
    "Effect" : "PostEffect_HRTAO_PropagateChangeList", 
	"Technique" : "R",
    "InputParameters" : 
    [
        { "Name": "cellIndices", "Type": "Texture" },
        { "Name": "changeListABuffer", "Type": "UnorderedBuffer" },
        { "Name": "hashMapKeysBuffer", "Type": "UnorderedBuffer" },
        { "Name": "hashMapContribsBuffer", "Type": "UnorderedBuffer" },
        { "Name": "changeListBBuffer", "Type": "UnorderedBuffer" },
        { "Name": "headsListBuffer", "Type": "UnorderedBuffer" }
    ]
}
