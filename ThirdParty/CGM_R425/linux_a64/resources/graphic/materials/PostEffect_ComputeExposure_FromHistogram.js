{
	"Effect" : "PostEffect_ComputeExposure_FromHistogram", 
	"Technique" : "PostProcess", 
    "InputParameters" : [
      { "Name": "i_HistogramMap",     "Type": "Image" },
      { "Name": "i_ExposureMap",      "Type": "Image" },
      { "Name": "i_LastLuminanceMap", "Type": "Image" }
    ]
}
