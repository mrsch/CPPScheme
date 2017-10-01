#ifndef SCHEME_VALUES_GRAPHICS_WINDOW_HPP
#define SCHEME_VALUES_GRAPHICS_WINDOW_HPP

#include <SFML/Window.hpp>

class Window
{
public:
  Window() : window(sf::VideoMode(800, 600), "My window")
  {
  }

  sf::Window window;
};

#endif // SCHEME_VALUES_GRAPHICS_WINDOW_HPP
