#include <iostream>
#include <vector>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/X.h>
#include "bmp.hpp"

int main(const int argc, const char** argv) {
	if (argc != 2) {
		std::cerr << "no filename" << std::endl;
		return 0;
	}
	auto display = XOpenDisplay(NULL);
	if (display == NULL) {
		std::cerr << "failed to open a display" << std::endl;
		return 0;
	}
	auto root = DefaultRootWindow(display);
	XWindowAttributes attr;
	XGetWindowAttributes(display, root, &attr);
	auto width = attr.width;
	auto height = attr.height;
	auto ximage = XGetImage(
		display, root,
		0,0, width, height,
		AllPlanes, ZPixmap);
	bmp::grid pixmap(
		height, std::vector<bmp::vec3>(
			width));
	auto redmask = ximage->red_mask;
	auto greenmask = ximage->green_mask;
	auto bluemask = ximage->blue_mask;
	for (std::size_t y = 0; y < height; y++) {
		for (std::size_t x = 0; x < width; x++) {
			auto pixel = XGetPixel(ximage, x, y);
			auto blue = pixel & bluemask;
			auto green = (pixel & greenmask) >> 8;
			auto red = (pixel & redmask) >> 16;
			pixmap[height-y-1][x] = bmp::vec3(red, green, blue);
		}
	}
	bmp::bmp_image image(pixmap);
	image.save(argv[1]);
	XDestroyImage(ximage);
	XCloseDisplay(display);
	return 0;
}
