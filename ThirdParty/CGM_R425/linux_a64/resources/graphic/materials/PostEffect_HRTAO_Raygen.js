{
    "Effect" : "PostEffect_HRTAO_Raygen", 
	  "Technique" : "R",
    "InputParameters" : 
	[ 
        { "Name": "hashMapBuffer", "Type" : "UnorderedBuffer" },
        { "Name": "hashMapBufferKey", "Type": "UnorderedBuffer" },
        { "Name": "changeListBuffer", "Type": "UnorderedBuffer" },
        { "Name": "touchedCellsBuffer", "Type": "UnorderedBuffer" },
        { "Name": "cutPointBuffer", "Type": "UnorderedBuffer" },
        { "Name": "prefixSumOutputBuffer", "Type": "UnorderedBuffer" },
        { "Name": "visibilityBuffer", "Type": "UnorderedBuffer" },
        { "Name": "cellIndices", "Type": "Texture" },
        { "Name": "ObjDesc", "Type": "UnorderedBuffer" },
        { "Name": "ObjFormat", "Type": "UnorderedBuffer" },
        { "Name": "Vertices", "Type": "UnorderedBuffer" },
        { "Name": "Indices", "Type": "UnorderedBuffer" },
        { "Name": "MaterialBuffer", "Type": "UnorderedBuffer" },
        { "Name": "PerMatrixCbOffsets", "Type": "UnorderedBuffer" },
        { "Name": "positionNormals", "Type": "Image" },
        { "Name": "gBufferAdditionalData", "Type": "Image" }
    ]
}
