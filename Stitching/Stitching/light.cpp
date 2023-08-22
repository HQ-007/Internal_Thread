#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	Mat src, dst;
	src = imread("G:/照片.jpg");
	if (!src.data) {
		cout << "could not load image..4." << endl;
		return -1;
	}
	char input_win[] = "input image";
	namedWindow(input_win, WINDOW_AUTOSIZE);
	imshow(input_win, src);

	//对比度跟亮度的调整
	int height = src.rows;
	int width = src.cols;
	dst = Mat::zeros(src.size(), src.type());
	float alpha = 1.3;
	float beta = 10;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (src.channels() == 3)
			{
				int b = src.at<Vec3b>(row, col)[0];
				int g = src.at<Vec3b>(row, col)[1];
				int r = src.at<Vec3b>(row, col)[2];

				dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b * alpha + beta);
				dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g * alpha + beta);
				dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r * alpha + beta);

			}
			else if (src.channels() == 1)
			{
				float v = src.at<uchar>(row, col);
				dst.at<uchar>(row, col) = saturate_cast<uchar>(v * alpha + beta);
			}
		}
	}
	char output_title[] = "contrast and brightness change demo";
	namedWindow(output_title, WINDOW_NORMAL);
	imshow(output_title, dst);
	imwrite("G:/照片2.jpg", dst);
	waitKey(0);
	return 0;
}
