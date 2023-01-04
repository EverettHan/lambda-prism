{
    "First":
    [
      {
          "Action": "Clear",
          "ClearColor": [0.4, 0.6, 0.8, 1],
          "ClearZ": 1,
          "StencilRef": 0,
          "DepthStencilTargets": ["BackBuffer"],
          "RenderTargets": ["BackBuffer"]
      },
    {
        "Action": "RenderSceneGraph",
        "Filters": ["Transparent"],
        "Sort": "StateSort",
        "DepthStencilTarget": "BackBuffer",
        "RenderTargets": ["BackBuffer"]
    },
      {
          "Action": "RenderSceneGraph",
          "Filters": ["Opaque"],
          "Sort": "StateSort",
          "DepthStencilTarget": "BackBuffer",
          "RenderTargets": ["BackBuffer"]
      }
   
    ],
    "Other":
    [
        {
            "Action": "RenderSceneGraph",
            "Filters": ["Transparent"],
            "Sort": "StateSort",
            "DepthStencilTarget": "BackBuffer",
            "RenderTargets": ["BackBuffer"]
        },
        {
            "Action": "RenderSceneGraph",
            "Filters": ["Opaque"],
            "Sort": "StateSort",
            "DepthStencilTarget": "BackBuffer",
            "RenderTargets": ["BackBuffer"]
        }
       
    ]
}
