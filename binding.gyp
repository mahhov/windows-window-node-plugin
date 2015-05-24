{
  "targets": [
    {
      "target_name": "WindowNan",
      "sources": [
        "WindowNan.cc",
        "Window.cc",
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "libraries": [
        
      ]
    }
  ]
}
