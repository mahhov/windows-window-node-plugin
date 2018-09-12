{
  "targets": [
    {
      "target_name": "WindowNan",
      "sources": [
        "src/WindowNan.cc",
        "src/Window.cc",
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "libraries": [
        
      ]
    }
  ]
}
