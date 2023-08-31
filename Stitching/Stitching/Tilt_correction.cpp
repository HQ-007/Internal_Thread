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



//ȥ���ڱ�
Mat RemoveBlackBorder(Mat& iplImg)
{
	int width = iplImg.size().width;
	int height = iplImg.size().height;
	int a = 0, b = 0, c = 0, d = 0;
	int i = 0, j = 0;


	if (iplImg.channels() == 3)	//��ɫͼƬ
	{
		//������ɫ�߿���
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
		//printf("�� a: %d\n", a);

		//������ɫ�߿���
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



		//������ɫ�߿���
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



	//����ͼ��
	int w = d - c + 1, h = b - a + 1;
	Mat dstImg = Mat(iplImg, Rect(c, a, w, h));

	return dstImg;
}



//����ת��
double DegreeTrans(double theta)
{
	double res = theta / CV_PI * 180;
	return res;
}

//��ʱ����תͼ��degree�Ƕȣ�ԭ�ߴ磩    
void rotateImage(Mat src, Mat& img_rotate, double degree)
{
	//��ת����Ϊͼ������    
	Point2f center;
	center.x = float(src.cols / 2.0);
	center.y = float(src.rows / 2.0);
	int length = 0;
	length = sqrt(src.cols * src.cols + src.rows * src.rows);
	//�����ά��ת�ķ���任����  
	Mat M = getRotationMatrix2D(center, degree, 1);
	warpAffine(src, img_rotate, M, Size(length, length), 1, 0, Scalar(0, 0, 0));//����任������ɫ���Ϊ��ɫ  
}

//ͨ������任����Ƕ�
double CalcDegree(const Mat& srcImage, Mat& dst)
{
	Mat midImage, dstImage;

	//Canny(srcImage, midImage, 100, 200, 3);
	Canny(srcImage, midImage, 90, 180, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

	//ͨ������任���ֱ��
	vector<Vec2f> lines;
	HoughLines(midImage, lines, 2, CV_PI / 180, 300, 0, 0);//��5������������ֵ����ֵԽ�󣬼�⾫��Խ��
	//cout << lines.size() << endl;

	//����ͼ��ͬ����ֵ�����趨����Ϊ��ֵ�趨���ߵ����޷����ֱ�ߣ���ֵ����ֱ��̫�࣬�ٶȺ���
	//���Ը�����ֵ�ɴ�С������������ֵ�����������������󣬿��Թ̶�һ���ʺϵ���ֵ��

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
		cout << "û�м�⵽ֱ�ߣ�" << endl;
		return ERROR;
	}

	float sum = 0;
	//���λ���ÿ���߶�
	int num = 0;
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0];
		float theta = lines[i][1];

		Point pt1, pt2;


		//����ɸѡ�������׵�ֱ�߽����޳�
		//ֻѡ�Ƕ���С����Ϊ��ת�Ƕ�
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

		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1); //Scalar�������ڵ����߶���ɫ

		imshow("ֱ��̽��Ч��ͼ", dstImage);
	}
	//float average = sum / lines.size(); //�����нǶ���ƽ������������תЧ�������
	float average = sum / num; //�����нǶ���ƽ������������תЧ�������


	cout << "average theta:" << average << endl;

	double angle = DegreeTrans(average) - 90;

	rotateImage(dstImage, dst, angle);
	imshow("ֱ��̽��Ч��ͼ2", dstImage);
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
	////USM����ǿ�㷨
	//addWeighted(src, 1.5, blur, -0.5, 0, src);
	//imshow("��ǿ��", src);
	Mat dst;
	//��б�ǶȽ���
	degree = CalcDegree(src, dst);
	if (degree == ERROR)
	{
		cout << "����ʧ�ܣ�" << endl;
	}
	rotateImage(src, dst, degree);
	cout << "angle:" << degree << endl;
	imshow("��ת������", dst);
	Mat resulyImage = dst(Rect(100, 10, 350, 500));
	//Mat resulyImage = dst(Rect(0, 0, src.cols, src.rows)); //��������֪ʶ�����ƺ��ı��ĳ����ٲü�����
	//Mat resulyImage = dst(Rect(230, 0, 250,500 )); //��������֪ʶ�����ƺ��ı��ĳ����ٲü�����
	//Mat resulyImage = dst(Rect(100, 10, 350, 630)); //��������֪ʶ�����ƺ��ı��ĳ����ٲü�����
	//Mat resulyImage = dst(Rect(180, 0, 250,500 )); //��������֪ʶ�����ƺ��ı��ĳ����ٲü�����
	//Mat resulyImage = dst(Rect(100, 20, 300, 680));
	imshow("�ü�֮��", resulyImage);
	Mat blur;
	GaussianBlur(resulyImage, blur, Size(0, 0), 5);
	//USM����ǿ�㷨
	addWeighted(resulyImage, 1.5, blur, -0.5, 0, resulyImage);
	copyMakeBorder(resulyImage, resulyImage, 50, 0, 0, 0, BORDER_CONSTANT, (0, 0, 0));
	//resulyImage=RemoveBlackBorder(resulyImage);
	imshow("��ǿ֮��", resulyImage);
	return resulyImage;
}
int main()
{
	String folder = "G:/������������Ƭ/53/*.jpg";
	vector<cv::String> imagePathList;
	glob(folder, imagePathList);
	cout << "�ļ����У�" << imagePathList.size() << endl;
	//cout << imagePathList[0].substr(23) << endl;
	int index;
	cout << "�ڼ���ͼƬ��ʼУ��" << endl;
	cin >> index;
	int n;
	cout << "У����������" << endl;
	cin >> n;
	cout << "����ɹ�����ʼ��ʱ" << endl;

	for (int k = index; k <= n + index - 1; k++)
	{
		string filename = imagePathList[k - 1].substr(20);
		string filepath = "G://������������Ƭ//53//" + filename;
		//string filename = "D://������������Ƭ//�ü�����//�ü���//" + str1 + ".jpg";
		//string filename = "E://������������Ƭ//����ʮ��//" + str1 + ".jpg";
		//string filename = "E://������������Ƭ//����7//�ױߺ�ü�//" + str1 + ".jpg";
		//string filename = "E://������������Ƭ//ƫ������//" + str1 + ".jpg";
		//string filename = "E://������������Ƭ//������ĸ//�ü��ױ�//" + str1 + ".jpg";
		//string filename = "E://������������Ƭ//������//�ü��ױ�//" + str1 + ".jpg";
		//string filename = "E://������������Ƭ//����ֱ//�ü��ױ�//" + str1 + ".jpg";
		//string filename = "E://������������Ƭ//����6//ˮƽУ��//" + str1 + ".jpg";
		//string filename = "D://������������Ƭ//new1//" + str1 + ".jpg";
		cout << "���ڽ���......." << filepath << endl;

		Mat image1 = imread(filepath);

		if (image1.empty())
		{
			cout << "No Image!" << endl;
			system("pause");
			return -1;
		}
		imshow("result", ImageRecify(image1));

		//�����ļ���
		//string resultname = "E://������������Ƭ//�����//��ȡ����//" + str2 + ".jpg";
		//string resultname = "D://������������Ƭ//�ü�����//�ü���//��бУ������ǿ����//" + str2 + ".jpg";
		//string resultname = "E://������������Ƭ//����ʮ��//У��//" + str2 + ".jpg";
		//string resultname = "E://������������Ƭ//����7//ˮƽУ����ü���ǿ//" + str2 + ".jpg";
		//string resultname = "E://������������Ƭ//ƫ������//У��//" + str2 + ".jpg";
		//string resultname = "E://������������Ƭ//������ĸ//ˮƽУ��2//" + str2 + ".jpg";
		//string resultname = "E://������������Ƭ//����ֱ//У����//" + str2 + ".jpg";
		//string resultname = "E://������������Ƭ//����6//ˮƽУ����ü���ǿ//" + str2 + ".jpg";

		stringstream stream3;
		string str3;
		stream3 << k;
		stream3 >> str3;

		string resultname = "G://������������Ƭ//53//��бУ����ǿ//" + str3 + ".jpg";
		cout << resultname << endl;
		imwrite(resultname, ImageRecify(image1));

	}


	cout << "�����ɹ�" << endl;
	waitKey();
	return 0;

}


