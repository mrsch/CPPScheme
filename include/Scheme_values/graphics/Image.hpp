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
  Image flip() const;

  std::string as_string();
  Eval_result eval(const Env_ptr& env);
  void show();

private:
  CImg<unsigned char> image;
  CImgDisplay display;
};

#endif // SCHEME_VALUES_GRAPHICS_IMAGE_HPP
