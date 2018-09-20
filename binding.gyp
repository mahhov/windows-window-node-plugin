{
  "targets": [
    {
      "target_name": "WindowNan",
      "sources": [
        "src/Wrapper.cc",
        "src/Window.cc",
        "src/Utility.cc",
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "libraries": [
        
      ]
    }
  ]
}
