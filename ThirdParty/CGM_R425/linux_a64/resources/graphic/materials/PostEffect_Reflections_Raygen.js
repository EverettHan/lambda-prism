{
  "Effect" : "PostEffect_Reflections_Raygen", 
	"Technique" : "Default",
  "InputParameters" : 
	[ 
    { "Name": "positionNormals", "Type": "Image" },
    { "Name": "reflectionsOutput", "Type": "Image" },
    { "Name": "ObjDesc", "Type": "UnorderedBuffer" },
    { "Name": "ObjFormat", "Type": "UnorderedBuffer" },
    { "Name": "Vertices", "Type": "UnorderedBuffer" },
    { "Name": "Indices", "Type": "UnorderedBuffer" },
    { "Name": "MatBuffer", "Type": "UnorderedBuffer" }
  ]
}
