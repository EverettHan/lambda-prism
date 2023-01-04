{
    "Opaque" : 
    {
        "enum": 
        [
            "VOLUME"
        ]
    },

    "Skin" : 
        {
            "enum": 
            [
                "SKIN"
            ]
        },

    "AlphaTest" : 
    {
      "enum": 
      [
          "ALPHATEST"
      ]
    },
    "Edge" : 
        {
            "enum" :
            [
                "OUTLINE",
                "EDGE",
                "HIDDEN_EDGE"
            ]
        },

    "Transparent" : 
        {
            "enum":
            [
                "TRANSPAR"
            ]
        },

    "Other" : 
        {
            "ranges":
            [
                {
                    "min" : "OTHER3D_2DMODE"
                    "max": "PRIORITY15p"
                },
                {
                    "min" : "HEDGE"
                    "max": "HOTHER"
                },
            ]

            
    
        },

    "Highlight" : 
    {
        "enum": 
        [
            "VOLUME",
            "SKIN",
            "ALPHATEST",
            "TRANSPAR",
            "OUTLINE",
            "EDGE",
            "HIDDEN_EDGE"
        ],

        "ranges":
        [
            {
                "min" : "OTHER3D_2DMODE"
                "max": "PRIORITY15p"
            },
            {
                "min" : "HEDGE"
                "max": "HOTHER"
            },
        ]
    },

    "PreHighlight" : 
    {
        "enum":
        [
        "FURTIVE",
        "FURTIVE_EDGE"
        ]
    }


}
