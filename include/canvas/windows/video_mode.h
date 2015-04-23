// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef CANVAS_WINDOWS_VIDEO_MODE_H_
#define CANVAS_WINDOWS_VIDEO_MODE_H_

#include <cstdint>
#include <vector>

namespace ca {

struct VideoMode {
  // Get the current desktop video mode.
  static VideoMode getDesktopMode();

  // Retrieve all the video modes supported in fullscreen mode.
  static std::vector<VideoMode> getFullscreenModes();

  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t bitsPerPixel = 0;

  VideoMode(uint32_t width, uint32_t height, uint32_t bitsPerPixel = 32)
    : width(width), height(height), bitsPerPixel(bitsPerPixel) {}

  // Check whether this mode is valid.
  bool isValid() const;
};

// Operators

bool operator==(const VideoMode& left, const VideoMode& right);
bool operator<(const VideoMode& left, const VideoMode& right);

}  // namespace ca

#endif  // CANVAS_WINDOWS_VIDEO_MODE_H_
