#include "StudentPreProcessing.h"

#include "ImageFactory.h"

#include <opencv2/imgproc/imgproc.hpp>

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	IntensityImage* retImage = ImageFactory::newIntensityImage(image);
	
	cv::Mat input;
	
	// PIXEL PER PIXEL COPY
	int w = image.getWidth();
	int h = image.getHeight();

	input.create(h, w, CV_8UC1);

	for (int x = 0; x < input.cols; x++) {
		for (int y = 0; y < input.rows; y++) {
			input.at<uchar>(y, x) = image.getPixel(x, y);
		}
	}
	// END PIXEL PER PIXEL COPY

	cv::Mat output;

	cv::Sobel(input, output, CV_8U, 1, 1, 5);
	
	// PIXEL PER PIXEL COPY TO INTENSITYIMAGE

	int type = output.type();
	if (type != CV_8UC1) {
		throw std::exception("OpenCV Mat source image not of type CV_8UC1!");
	}

	retImage->set(output.cols, output.rows);

	for (int x = 0; x < output.cols; x++) {
		for (int y = 0; y < output.rows; y++) {
			retImage->setPixel(x, y, output.at<uchar>(y, x));
		}
	}

	// END PIXEL PER PIXEL COPY TO INTENSITYIMAGE

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