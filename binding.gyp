{
  "targets": [
    {
      "target_name": "WindowNan",
      "sources": [
        "src/Wrapper.cc",
        "src/UtilityWrapper.cc",
        "src/WindowWrapper.cc",
        "src/KeyCatcherWrapper.cc",
        "src/Utility.cc",
        "src/Window.cc",
        "src/KeyCatcher.cc",
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"],
      "libraries": [
        
      ]
    }
  ]
}
