#include "Window.hpp"

Window::Window(int height, int width) :
	height_(height),
	width_(width)
{

}

Window::~Window() {}

int Window::getHeight() const { return height_; }

int Window::getWidth() const { return width_; }
