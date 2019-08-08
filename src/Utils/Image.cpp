
#include "canvas/Utils/Image.h"

#include "nucleus/Logging.h"

#include "png.h"

#include <cmath>

#include "nucleus/MemoryDebug.h"

namespace ca {

namespace {

void readDataFromInputStream(png_structp png, png_bytep outBytes, png_size_t byteCountToRead) {
  png_voidp ioPtr = png_get_io_ptr(png);
  if (ioPtr == NULL) {
    LOG(Error) << "Could not read from stream. Invalid pointer.";
    return;
  }

  nu::InputStream* inputStream = static_cast<nu::InputStream*>(ioPtr);
  const size_t bytesRead = inputStream->read(outBytes, byteCountToRead);

  if (bytesRead != byteCountToRead) {
    LOG(Error) << "Could not read from stream. End of stream.";
  }
}

void parseRGBA(const Size size, U8* outPtr, const png_structp& png, const png_infop& info) {
  // const I32 width = size.width;
  const I32 height = size.height;

  const png_size_t bytesPerRow = png_get_rowbytes(png, info);

  for (I32 rowIdx = 0; rowIdx < height; ++rowIdx) {
    png_read_row(png, static_cast<png_bytep>(outPtr + rowIdx * bytesPerRow), NULL);
  }
}

}  // namespace

// static
Image Image::createAlpha(const Size& size, U8 intensity) {
  Image result;

  result.m_format = ImageFormat::Alpha;
  result.m_size = size;
  result.m_data.resize(size.width * size.height, intensity);

  return result;
}

Image::Image() = default;

Image::~Image() = default;

Image::Image(Image&& other) : m_format{std::move(other.m_format)}, m_size(std::move(other.m_size)), m_data(std::move(other.m_data)) {}

Image& Image::operator=(Image&& other) {
  m_format = std::move(other.m_format);
  m_size = std::move(other.m_size);
  m_data = std::move(other.m_data);

  return *this;
}

void Image::create(const Size& size, const Color& col) {
  if (size.width && size.height) {
    // Store the size of the image.
    m_size = size;

    // Resize the buffer to hold the image.
    auto bufferSize = size.width * size.height * 4;
    m_data.resize(bufferSize);

    // Fill the image with the specified color.
    U8* data = m_data.getData();
    U8* end = data + m_data.getSize();
    while (data < end) {
      *data++ = static_cast<U8>(std::round(col.r * 255.0f));
      *data++ = static_cast<U8>(std::round(col.g * 255.0f));
      *data++ = static_cast<U8>(std::round(col.b * 255.0f));
      *data++ = static_cast<U8>(std::round(col.a * 255.0f));
    }
  } else {
    // Store the size and clear out the data.
    m_size = {0, 0};
    m_data.clear();
  }
}

bool Image::loadFromStream(nu::InputStream* stream) {
  DCHECK(stream);

  enum { kPngSignatureLength = 8 };
  U8 pngSignature[kPngSignatureLength];

  if (stream->read(pngSignature, kPngSignatureLength) != kPngSignatureLength) {
    return false;
  }

  if (!png_check_sig(pngSignature, kPngSignatureLength)) {
    return false;
  }

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    return false;
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
    png_destroy_read_struct(&png, NULL, NULL);
    return false;
  }

  png_set_read_fn(png, stream, readDataFromInputStream);

  png_set_sig_bytes(png, kPngSignatureLength);

  png_read_info(png, info);

  png_uint_32 width = 0;
  png_uint_32 height = 0;
  int bitDepth = 0;
  int colorType = -1;
  png_uint_32 retval =
      png_get_IHDR(png, info, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);

  if (retval != 1) {
    return false;
  }

  // Prepare the data storage.
  m_size = Size(width, height);

  switch (colorType) {
#if 0
    case PNG_COLOR_TYPE_RGB:
      parseRGB(outImage, png, info);
      break;
#endif  // 0

    case PNG_COLOR_TYPE_RGB_ALPHA:
      m_format = ImageFormat::RGBA;
      m_data.resize(m_size.width * m_size.height * 4);
      parseRGBA(m_size, m_data.getData(), png, info);
      break;

    default:
      NOTREACHED() << "Invalid PNG ColorType enum value given.";
      png_destroy_read_struct(&png, &info, NULL);
      return false;
  }

  png_destroy_read_struct(&png, &info, NULL);

  return true;
}

void Image::setPixel(const Pos& pos, const Color& color) {
  U8* ptr = &m_data[pos.y * (m_size.width * 4) + (pos.x * 4)];
  *ptr++ = static_cast<U8>(round(color.r));
  *ptr++ = static_cast<U8>(round(color.g));
  *ptr++ = static_cast<U8>(round(color.b));
  *ptr++ = static_cast<U8>(round(color.a));
}

}  // namespace ca
