#include<iostream>
#include "vec3.h"
#include "color.h"

int ouputIndex = 1;

void outputSimpleImage() {
	// Image

	const int image_width = 256;
	const int image_height = 256;

	// Render

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			auto r = double(i) / (image_width - 1);
			auto g = double(j) / (image_height - 1);
			auto b = 0.25;

			color pixel_color(r, g, b);
			write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";
}


int main() {

	switch (ouputIndex)
	{
	case 1:
		outputSimpleImage();
		break;
	default:
		break;
	}

	return 0;
}



