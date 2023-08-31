//#include <iostream>
//#include <string>
//#include <fstream>
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//Mat rotateImage(Mat img, int degree);
//
//int main()
//{
//	String folder = "G:/ѵ�����ݼ�/test3/images/*.jpg";
//	vector<cv::String> imagePathList;
//	glob(folder, imagePathList);
//	cout << "�ļ����У�" << imagePathList.size() << endl;
//	
//	int index;
//	cout << "�ڼ���ͼƬ��ʼ��ת" << endl;
//	cin >> index;
//	int n;
//	cout << "��ת��������" << endl;
//	cin >> n;
//	cout << "����ɹ�����ʼ��ʱ" << endl;
//
//	for (int k = index; k <= n + index - 1; k++)
//	{
//		string filename = imagePathList[k - 1].substr(27);
//		string filepath = "G://ѵ�����ݼ�//test3//images//" + filename;
//		cout << "���ڽ���......." << filepath << endl;
//
//		Mat image1 = imread(filepath);
//		imshow("yuan", image1);
//		if (image1.empty())
//		{
//			cout << "No Image!" << endl;
//			system("pause");
//			return -1;
//		}
//		Mat image2 = Mat::zeros(image1.size(), image1.type());
//		image2 = rotateImage(image1, 180);
//		imshow("result", image2);
//
//		
//
//
//		string resultname = "G://ѵ�����ݼ�//test3//����//new1_"+ filename;
//		cout << resultname << endl;
//		imwrite(resultname, rotateImage(image1,180));
//
//	}
//
//
//	cout << "��ת�ɹ�" << endl;
//	waitKey();
//	return 0;
//}
//
//
//
//
////// ��ͼ�����ˮƽ����
////void main111(void)
////{
////	string image_dir = "D:/visualstudio 2013/project text/c++/c++/";
////	string image_out_dir = "D:/visualstudio 2013/project text/c++/";
////	string image_name = "people_400.jpg";
////	string image_dir_name = image_dir + image_name;
////	string image_out_dir_name = image_out_dir + image_name;
////
////	Mat image = imread(image_dir_name, -1);
////	Mat img_trans;
////	img_trans.create(image.size(), image.type());
////	for (int i = 0; i < image.rows; i++)
////	{
////		for (int j = 0; j < image.cols; j++)
////		{
////			img_trans.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, image.cols - 1 - j)[0];
////			img_trans.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, image.cols - 1 - j)[1];
////			img_trans.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, image.cols - 1 - j)[2];
////		}
////	}
////
////	imwrite(image_out_dir_name, img_trans);
////
////}
//
//
//// ��ͼ�������ת������Ĭ��Ϊ˳ʱ�뷽��
//Mat rotateImage(Mat img, int degree)
//{
//	Mat rotationMatrix = getRotationMatrix2D(Point2f(img.cols / 2, img.rows / 2), degree, 1.0);
//	Mat rotatedImage;
//	warpAffine(img, rotatedImage, rotationMatrix, img.size());
//	
//	return rotatedImage;
//}
//
