#include "Scheme_values/graphics/Image.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

#include <iostream>

Image::Image(const std::string& filename) : image(filename.c_str())
{
}

Image::Image(int width, int height) : image(width, height, 1, 3, 0)
{
}

Image::Image(const CImg<unsigned char>& image) : image(image)
{
}

Image Image::rotate(float angle) const
{
  return Image(image.get_rotate(angle));
}

Image Image::rotate(float angle, int x, int y) const
{
  auto res = image.get_rotate(angle, x, y, 0);
  // TODO: Scale by sqrt(2)
  return Image(res);
}

Image Image::flip() const
{
  return Image(image.get_mirror('x'));
}

Image Image::above(const Image& other) const
{
  // TODO: Calc and use ratio between images to resize
  CImg<unsigned char> result(image.width(), image.height(), 1, 3, 0);

  auto image_1 = image;
  auto image_2 = other.image;

  image_1.resize(image_1.width(), image_1.height() / 2.0);
  image_2.resize(image_2.width(), image_2.height() / 2.0);

  auto image_1_height = image_1.height();

  result.draw_image(0, 0, 0, image_1);
  result.draw_image(0, image_1_height, 0, image_2);

  return Image(result);
}

Image Image::beside(const Image& other) const
{
  // TODO: Calc and use ratio between images to resize
  CImg<unsigned char> result(image.width(), image.height(), 1, 3, 0);

  auto image_1 = image;
  auto image_2 = other.image;

  image_1.resize(image_1.width() / 2.0, image_1.height());
  image_2.resize(image_2.width() / 2.0, image_2.height());

  auto image_1_width = image_1.width();

  result.draw_image(0, 0, 0, image_1);
  result.draw_image(image_1_width, 0, 0, image_2);

  return Image(result);
}

void Image::show()
{
  display.display(image);
}

void Image::save(const std::string& filename)
{
  image.save(filename.c_str());
}

std::string Image::as_string() const
{
  return "Image";
}
