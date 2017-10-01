#ifndef SCHEME_VALUES_GRAPHICS_IMAGE_HPP
#define SCHEME_VALUES_GRAPHICS_IMAGE_HPP

#include "Utils.hpp"

#include <CImg.h>
#include <string>

#include <iostream>

using namespace cimg_library;

class Image
{
public:
  explicit Image(const std::string& filename);
  explicit Image(int width, int height);
  explicit Image(const CImg<unsigned char>& image);
  ~Image()
  {
    std::cout << "Image destructed" << '\n';
  }

  Image rotate(float angle) const;
  Image rotate(float angle, int x, int y) const;
  Image flip() const;
  Image above(const Image& other) const;
  Image beside(const Image& other) const;
  void save(const std::string& filename);

  std::string as_string();
  Eval_result eval(const Env_ptr& env);
  void show();

private:
  CImg<unsigned char> image;
};

#endif // SCHEME_VALUES_GRAPHICS_IMAGE_HPP
