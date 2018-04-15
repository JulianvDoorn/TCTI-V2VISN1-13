#include "StudentPreProcessing.h"
#include "ImageFactory.h"

#include <iostream>
#include <cmath>
#include "basetimer.h"

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	BaseTimer* bt = new BaseTimer();
	bt->start();

	IntensityImage* retImage = ImageFactory::newIntensityImage(image);

	int w = image.getWidth();
	int h = image.getHeight();

	constexpr int weight = 1;

	const char kernel_x[3][3] = {
		{ 1 * weight, 0 * weight, -1 * weight },
		{ 2 * weight, 0 * weight, -2 * weight },
		{ 1 * weight, 0 * weight, -1 * weight }
	};

	const char kernel_y[3][3] = {
		{ 1 * weight, 2 * weight, 1 * weight },
		{ 0 * weight, 0 * weight, 0 * weight },
		{ -1 * weight, -2 * weight, -1 * weight }
	};

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int intens_x = 0;
			int intens_y = 0;
			int intens;

			intens_x += image.getPixel(x - 1, y - 1) * kernel_x[0][0];
			intens_x += image.getPixel(x - 1, y) * kernel_x[1][0];
			intens_x += image.getPixel(x - 1, y + 1) * kernel_x[2][0];
			intens_x += image.getPixel(x, y - 1) * kernel_x[0][1];
			intens_x += image.getPixel(x, y) * kernel_x[1][1];
			intens_x += image.getPixel(x, y + 1) * kernel_x[2][1];
			intens_x += image.getPixel(x + 1, y - 1) * kernel_x[0][2];
			intens_x += image.getPixel(x + 1, y) * kernel_x[1][2];
			intens_x += image.getPixel(x + 1, y + 1) * kernel_x[2][2];

			intens_y += image.getPixel(x - 1, y - 1) * kernel_y[0][0];
			intens_y += image.getPixel(x - 1, y) * kernel_y[1][0];
			intens_y += image.getPixel(x - 1, y + 1) * kernel_y[2][0];
			intens_y += image.getPixel(x, y - 1) * kernel_y[0][1];
			intens_y += image.getPixel(x, y) * kernel_y[1][1];
			intens_y += image.getPixel(x, y + 1) * kernel_y[2][1];
			intens_y += image.getPixel(x + 1, y - 1) * kernel_y[0][2];
			intens_y += image.getPixel(x + 1, y) * kernel_y[1][2];
			intens_y += image.getPixel(x + 1, y + 1) * kernel_y[2][2];

			intens =  std::sqrt( intens_x * intens_x + intens_y * intens_y);

			if (intens > 255) {
				intens = 255;
			}

			retImage->setPixel(x, y, intens);
		}
	}
	bt->stop();
	std::cout << "!!!!!Student Time: " << bt->elapsedMicroSeconds() << std::endl;
	return retImage;
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage* retImage = ImageFactory::newIntensityImage(image);

	for (int x = 0; x < retImage->getWidth(); x++) {
		for (int y = 0; y < retImage->getHeight(); y++) {
			retImage->setPixel(x, y, 255 - image.getPixel(x, y));
		}
	}

	return retImage;
}