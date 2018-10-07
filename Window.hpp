#ifndef WINDOW_H
#define WINDOW_H

class Window {

private:

	int height_;
	int width_;

public:

	Window(int, int);
	~Window();

	int getHeight() const;
	int getWidth() const;

};

#endif
