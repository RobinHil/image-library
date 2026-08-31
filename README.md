# Image Library

A C++17 library for reading, writing and processing 8-bit grayscale and 24-bit
RGB images, with no external dependencies.

## Formats

| Format | Read | Write |
| --- | --- | --- |
| PGM (Portable GrayMap) | P2 (ASCII) and P5 (binary) | P5 (binary) |
| PPM (Portable PixMap) | P3 (ASCII) and P6 (binary) | P6 (binary) |
| TGA (Truevision) | uncompressed grayscale and RGB, 24-bit color-mapped | with or without RLE compression |
| MAI (in-house CMY format) | yes | no |

## Processing

Both `GrayImage` and `ColorImage` support:

- Allocation, clearing, and per-pixel access.
- Filled and outlined rectangles.
- Scaling, either nearest-neighbour (`simpleScale`) or bilinear
  (`bilinearScale`).

`ColorImage` adds Bresenham line drawing (`line`), and `Color::fromCMY` converts
a CMY triple into RGB, which is how the MAI format is decoded.

## Building

Requires a C++17 compiler and `make`. The code also builds cleanly under
C++20 and C++23, and with `-Wall -Wextra`.

```bash
cd Image
make
./main
```

`main` is a test harness: it runs the library over the images in `data/` and
writes the results into `data/tests/`, which it creates if needed.

The sample images are **not distributed with this repository** - they came from
a university course and are not mine to redistribute. Supply your own and place
them where `main.cpp` expects them (`data/GrayImage/`, `data/ColorImage/` and
`data/Maison/`), or read `main.cpp` and adapt the paths. The library itself has
no dependency on them.

```bash
make clean       # object files
make distclean   # object files, the binary, and data/tests/
```

## Usage

Creating and drawing on a grayscale image:

```cpp
GrayImage *img = new GrayImage(150, 300);
img->clear(255);
img->fillRectangle(1, 2, 50, 72, 0);

std::ofstream os("image.pgm", std::ios::binary);
img->writePGM(os);

delete img;
```

Reading a color image, scaling it, and writing it back as RLE-compressed TGA:

```cpp
std::ifstream is("input.ppm", std::ios::binary);
ColorImage *img = ColorImage::readPPM(is);

ColorImage *resized = img->bilinearScale(823, 400);

std::ofstream os("output.tga", std::ios::binary);
resized->writeTGA(os, true);

delete img;
delete resized;
```

Streams must be opened in binary mode, and both the reader factories and the
scaling methods return objects the caller owns and must `delete`.

## Classes

- `GrayImage` - 8-bit grayscale images.
- `ColorImage` - 24-bit RGB images.
- `Color` - a single RGB triple, with `fromCMY` and arithmetic operators used by
  the scaling code.

## Layout

```
Image/
  Image.hpp / Image.cpp   the library
  main.cpp                test harness
  Makefile
  Doxyfile                documentation config
  data/                   sample images (PGM, PPM, TGA, MAI)
```
