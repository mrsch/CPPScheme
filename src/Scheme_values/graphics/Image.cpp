#include "Scheme_values/graphics/Image.hpp"

#include "Environment.hpp"
#include "Scheme_values/Scheme_value.hpp"

#include <iostream>

Image::Image(const std::string& filename)
  : image(filename.c_str()), display(image, filename.c_str())
{
}

Image::Image(int width, int height) : image(width, height, 1, 3, 0)
{
}

Image::Image(const CImg<unsigned char>& image)
  : image(image), display(image, "copy")
{
}

Image Image::rotate(float angle) const
{
  return Image(image.get_rotate(angle));
}

Image Image::flip() const
{
  return Image(image.get_mirror('x'));
}

Eval_result Image::eval(const Env_ptr& /* env */)
{
  return Scheme_value{*this};
}

void Image::show()
{
  if (display.is_closed()) {
    display.show();
  }

  display.display(image);
}

std::string Image::as_string()
{
  return "Image";
}
