{
  "targets": [{
    "target_name": "gst",
    "cflags_cc!": ["-fno-rtti"],
    "sources": [
      "src/addon.cc",
      "src/player.cc"
    ],
    "libraries": [
      "<!@(pkg-config --libs gstreamer-player-1.0)"
    ],
    "include_dirs": [
      "<!(node -e \"require('nan')\")",
    ],
    "cflags": [
      "<!@(pkg-config --cflags gstreamer-player-1.0)"
    ]
  }]
}
