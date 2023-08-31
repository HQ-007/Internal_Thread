#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>
#include "opencv2/imgproc/imgproc_c.h"
using namespace std;
using namespace cv;

using namespace std;
using namespace cv;

#include <iostream>
#include <iostream>
#include"opencv2/opencv.hpp"
#include<math.h>
using namespace std;
using namespace cv;
#define ERROR 1234



//去除黑边
Mat RemoveBlackBorder(Mat& iplImg)
{
	int width = iplImg.size().width;
	int height = iplImg.size().height;
	int a = 0, b = 0, c = 0, d = 0;
	int i = 0, j = 0;


	if (iplImg.channels() == 3)	//彩色图片
	{
		//消除黑色边框：上
		for (j = 0; j < height; j++)
		{
			bool flag = false;
			for (i = 0; i < width; i++)
			{
				int tmpb, tmpg, tmpr;
				Vec3b bgr = iplImg.at<Vec3b>(j, i);
				tmpb = bgr[0];
				tmpg = bgr[1];
				tmpr = bgr[2];

				if (tmpb <= 30 && tmpg <= 30 && tmpr <= 30)
				{
					;
				}
				else
				{
					flag = true;
					a = j;
					break;
				}
			}
			if (flag) break;
		}
		//printf("上 a: %d\n", a);

		//消除黑色边框：下
		for (j = height - 1; j >= a; j--)
		{
			bool flag = false;
			for (i = 0; i < width; i++)
			{
				int tmpb, tmpg, tmpr;
				Vec3b bgr = iplImg.at<Vec3b>(j, i);
				tmpb = bgr[0];
				tmpg = bgr[1];
				tmpr = bgr[2];
				if (tmpb <= 30 && tmpg <= 30 && tmpr <= 30)
				{
					;
				}
				else
				{
					flag = true;
					b = j;
					break;
				}
			}

			if (flag) break;
		}



		//消除黑色边框：右
		for (i = width - 1; i >= c; i--)
		{
			bool flag = false;
			for (j = 0; j < height; j++)
			{
				int tmpb, tmpg, tmpr;
				Vec3b bgr = iplImg.at<Vec3b>(j, i);
				tmpb = bgr[0];
				tmpg = bgr[1];
				tmpr = bgr[2];
				if (tmpb <= 20 && tmpg <= 20 && tmpr <= 20)
				{
					;
				}
				else
				{
					flag = true;
					d = i;
					break;
				}
			}
			if (flag) break;
		}

	}



	//复制图像
	int w = d - c + 1, h = b - a + 1;
	Mat dstImg = Mat(iplImg, Rect(c, a, w, h));

	return dstImg;
}



//度数转换
double DegreeTrans(double theta)
{
	double res = theta / CV_PI * 180;
	return res;
}

//逆时针旋转图像degree角度（原尺寸）    
void rotateImage(Mat src, Mat& img_rotate, double degree)
{
	//旋转中心为图像中心    
	Point2f center;
	center.x = float(src.cols / 2.0);
	center.y = float(src.rows / 2.0);
	int length = 0;
	length = sqrt(src.cols * src.cols + src.rows * src.rows);
	//计算二维旋转的仿射变换矩阵  
	Mat M = getRotationMatrix2D(center, degree, 1);
	warpAffine(src, img_rotate, M, Size(length, length), 1, 0, Scalar(0, 0, 0));//仿射变换，背景色填充为黑色  
}

//通过霍夫变换计算角度
double CalcDegree(const Mat& srcImage, Mat& dst)
{
	Mat midImage, dstImage;

	//Canny(srcImage, midImage, 100, 200, 3);
	Canny(srcImage, midImage, 90, 180, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

	//通过霍夫变换检测直线
	vector<Vec2f> lines;
	HoughLines(midImage, lines, 2, CV_PI / 180, 300, 0, 0);//第5个参数就是阈值，阈值越大，检测精度越高
	//cout << lines.size() << endl;

	//由于图像不同，阈值不好设定，因为阈值设定过高导致无法检测直线，阈值过低直线太多，速度很慢
	//所以根据阈值由大到小设置了三个阈值，如果经过大量试验后，可以固定一个适合的阈值。

	if (!lines.size())
	{
		HoughLines(midImage, lines, 1, CV_PI / 180, 200, 0, 0);
	}
	//cout << lines.size() << endl;

	if (!lines.size())
	{
		HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);
	}
	//cout << lines.size() << endl;
	if (!lines.size())
	{
		cout << "没有检测到直线！" << endl;
		return ERROR;
	}

	float sum = 0;
	//依次画出每条线段
	int num = 0;
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];
		float theta = lines[i][1];

		Point pt1, pt2;


		//进行筛选，对离谱的直线进行剔除
		//只选角度最小的作为旋转角度
		if (theta / CV_PI * 180 > 85 && theta / CV_PI * 180 < 95)
		{

			//cout << theta << endl;
			double a = cos(theta), b = sin(theta);
			double x0 = a * rho, y0 = b * rho;
			pt1.x = cvRound(x0 + 1000 * (-b));
			pt1.y = cvRound(y0 + 1000 * (a));
			pt2.x = cvRound(x0 - 1000 * (-b));
			pt2.y = cvRound(y0 - 1000 * (a));
			sum += theta;
			num++;
		}

		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1); //Scalar函数用于调节线段颜色

		imshow("直线探测效果图", dstImage);
	}
	//float average = sum / lines.size(); //对所有角度求平均，这样做旋转效果会更好
	float average = sum / num; //对所有角度求平均，这样做旋转效果会更好


	cout << "average theta:" << average << endl;

	double angle = DegreeTrans(average) - 90;

	rotateImage(dstImage, dst, angle);
	imshow("直线探测效果图2", dstImage);
	waitKey(100);
	return angle;
}

cv::Mat adjustBrightnessAndContrast(cv::Mat src, double alpha, int beta)
{
	cv::Mat dst;
	src.convertTo(dst, -1, alpha, beta);
	return dst;
}

Mat ImageRecify(Mat image1)
{
	double degree;
	Mat src = image1;
	//Mat src = adjustBrightnessAndContrast(image1, 1, 1);
	//Mat blur;
	//GaussianBlur(src, blur, Size(0, 0), 5);
	////USM锐化增强算法
	//addWeighted(src, 1.5, blur, -0.5, 0, src);
	//imshow("增强后", src);
	Mat dst;
	//倾斜角度矫正
	degree = CalcDegree(src, dst);
	if (degree == ERROR)
	{
		cout << "矫正失败！" << endl;
	}
	rotateImage(src, dst, degree);
	cout << "angle:" << degree << endl;
	imshow("旋转调整后", dst);
	Mat resulyImage = dst(Rect(100, 10, 350, 500));
	//Mat resulyImage = dst(Rect(0, 0, src.cols, src.rows)); //根据先验知识，估计好文本的长宽，再裁剪下来
	//Mat resulyImage = dst(Rect(230, 0, 250,500 )); //根据先验知识，估计好文本的长宽，再裁剪下来
	//Mat resulyImage = dst(Rect(100, 10, 350, 630)); //根据先验知识，估计好文本的长宽，再裁剪下来
	//Mat resulyImage = dst(Rect(180, 0, 250,500 )); //根据先验知识，估计好文本的长宽，再裁剪下来
	//Mat resulyImage = dst(Rect(100, 20, 300, 680));
	imshow("裁剪之后", resulyImage);
	Mat blur;
	GaussianBlur(resulyImage, blur, Size(0, 0), 5);
	//USM锐化增强算法
	addWeighted(resulyImage, 1.5, blur, -0.5, 0, resulyImage);
	copyMakeBorder(resulyImage, resulyImage, 50, 0, 0, 0, BORDER_CONSTANT, (0, 0, 0));
	//resulyImage=RemoveBlackBorder(resulyImage);
	imshow("增强之后", resulyImage);
	return resulyImage;
}
int main()
{
	String folder = "G:/内螺纹拍摄照片/53/*.jpg";
	vector<cv::String> imagePathList;
	glob(folder, imagePathList);
	cout << "文件夹有：" << imagePathList.size() << endl;
	//cout << imagePathList[0].substr(23) << endl;
	int index;
	cout << "第几张图片开始校正" << endl;
	cin >> index;
	int n;
	cout << "校正到多少张" << endl;
	cin >> n;
	cout << "输入成功，开始计时" << endl;

	for (int k = index; k <= n + index - 1; k++)
	{
		string filename = imagePathList[k - 1].substr(20);
		string filepath = "G://内螺纹拍摄照片//53//" + filename;
		//string filename = "D://内螺纹拍摄照片//裁剪过后//裁剪四//" + str1 + ".jpg";
		//string filename = "E://内螺纹拍摄照片//拍摄十九//" + str1 + ".jpg";
		//string filename = "E://内螺纹拍摄照片//拍摄7//白边后裁剪//" + str1 + ".jpg";
		//string filename = "E://内螺纹拍摄照片//偏离中心//" + str1 + ".jpg";
		//string filename = "E://内螺纹拍摄照片//金属螺母//裁剪白边//" + str1 + ".jpg";
		//string filename = "E://内螺纹拍摄照片//大螺纹//裁剪白边//" + str1 + ".jpg";
		//string filename = "E://内螺纹拍摄照片//不垂直//裁剪白边//" + str1 + ".jpg";
		//string filename = "E://内螺纹拍摄照片//拍摄6//水平校正//" + str1 + ".jpg";
		//string filename = "D://内螺纹拍摄照片//new1//" + str1 + ".jpg";
		cout << "正在矫正......." << filepath << endl;

		Mat image1 = imread(filepath);

		if (image1.empty())
		{
			cout << "No Image!" << endl;
			system("pause");
			return -1;
		}
		imshow("result", ImageRecify(image1));

		//保存文件名
		//string resultname = "E://内螺纹拍摄照片//拍摄九//截取轮廓//" + str2 + ".jpg";
		//string resultname = "D://内螺纹拍摄照片//裁剪过后//裁剪四//倾斜校正加增强操作//" + str2 + ".jpg";
		//string resultname = "E://内螺纹拍摄照片//拍摄十九//校正//" + str2 + ".jpg";
		//string resultname = "E://内螺纹拍摄照片//拍摄7//水平校正后裁剪增强//" + str2 + ".jpg";
		//string resultname = "E://内螺纹拍摄照片//偏离中心//校正//" + str2 + ".jpg";
		//string resultname = "E://内螺纹拍摄照片//金属螺母//水平校正2//" + str2 + ".jpg";
		//string resultname = "E://内螺纹拍摄照片//不垂直//校正二//" + str2 + ".jpg";
		//string resultname = "E://内螺纹拍摄照片//拍摄6//水平校正后裁剪增强//" + str2 + ".jpg";

		stringstream stream3;
		string str3;
		stream3 << k;
		stream3 >> str3;

		string resultname = "G://内螺纹拍摄照片//53//倾斜校正增强//" + str3 + ".jpg";
		cout << resultname << endl;
		imwrite(resultname, ImageRecify(image1));

	}


	cout << "矫正成功" << endl;
	waitKey();
	return 0;

}


