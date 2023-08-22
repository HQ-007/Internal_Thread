//#include <iostream>
//#include <string>
//#include <fstream>
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
//Mat addSaltNoise(const Mat srcImage, int n);
//Mat rotateImage(Mat img, int degree);
//
//void main()
//{
//	int i = 0;
//	string name, clas;
//	ifstream infile;
//	infile.open("F:/С����ѧϰͼƬ����/xifang/org_img/train.txt");
//	string image_dir = "F:/С����ѧϰͼƬ����/xifang/org_img/train/";
//	while (infile)
//	{
//		infile >> name >> clas;
//		cout << i++ << endl;
//		string image_dir_name = image_dir + name;
//		Mat image = imread(image_dir_name, -1);
//
//		// 1����ͼ�����ˮƽ����
//		string image_jingxiang = "F:/С����ѧϰͼƬ����/xifang/���ɺ��trainͼƬ/ˮƽ����/";
//		string image_out_jingxiang = image_jingxiang + name;
//		Mat img_jingxiang;
//		img_jingxiang.create(image.size(), image.type());
//		for (int i = 0; i < image.rows; i++)
//		{
//			for (int j = 0; j < image.cols; j++)
//			{
//				img_jingxiang.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, image.cols - 1 - j)[0];
//				img_jingxiang.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, image.cols - 1 - j)[1];
//				img_jingxiang.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, image.cols - 1 - j)[2];
//			}
//		}
//		imwrite(image_out_jingxiang, img_jingxiang);
//
//		// 2����ͼ�������Ƭ�����Ͻ���Ƭ
//		string image_qiepian_youshang = "F:/С����ѧϰͼƬ����/xifang/���ɺ��trainͼƬ/��Ƭ/���Ͻ���Ƭ/";
//		string image_out_qiepian_youshang = image_qiepian_youshang + name;
//		//Rect bbox(0, 0, 224, 224);  // ���Ͻ���Ƭ
//		Rect bbox1(image.cols - 1 - 224, 0, 224, 224);  // ���Ͻ���Ƭ
//		//Rect bbox(0, image.rows - 1 - 224, 224, 224);  // ���½���Ƭ
//		//Rect bbox(image.cols - 1 - 224, image.rows - 1 - 224, 224, 224);  // ���½���Ƭ
//		//Rect bbox(image.cols/2- 112, image.rows/2 -112,224, 224);  // �м���Ƭ
//
//		Mat img_qiepian_youshang = image(bbox1);
//		cv::resize(img_qiepian_youshang, img_qiepian_youshang, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_qiepian_youshang, img_qiepian_youshang);
//
//		// 3����ͼ�������Ƭ�����½���Ƭ
//		string image_qiepian_youxia = "F:/С����ѧϰͼƬ����/xifang/���ɺ��trainͼƬ/��Ƭ/���½���Ƭ/";
//		string image_out_qiepian_youxia = image_qiepian_youxia + name;
//		//Rect bbox(0, 0, 224, 224);  // ���Ͻ���Ƭ
//		//Rect bbox(image.cols - 1 - 224, 0, 224, 224);  // ���Ͻ���Ƭ
//		//Rect bbox(0, image.rows - 1 - 224, 224, 224);  // ���½���Ƭ
//		Rect bbox2(image.cols - 1 - 224, image.rows - 1 - 224, 224, 224);  // ���½���Ƭ
//		//Rect bbox(image.cols/2- 112, image.rows/2 -112,224, 224);  // �м���Ƭ
//
//		Mat img_qiepian_youxia = image(bbox2);
//		cv::resize(img_qiepian_youxia, img_qiepian_youxia, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_qiepian_youxia, img_qiepian_youxia);
//
//		
//
//		// 7��������ʱ��8��
//		string image_jiangxiang_ni8 = "F:/С����ѧϰͼƬ����/xifang/���ɺ��trainͼƬ/��ת_����/������ʱ��8��/";
//		string image_out_jiangxiang_ni8 = image_jiangxiang_ni8 + name;
//		Mat img_jiangxiang_ni8 = rotateImage(img_jingxiang, -8);
//		cv::resize(img_jiangxiang_ni8, img_jiangxiang_ni8, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_jiangxiang_ni8, img_jiangxiang_ni8);
//
//		// 8������˳ʱ��8��
//		string image_jiangxiang_shun8 = "F:/С����ѧϰͼƬ����/xifang/���ɺ��trainͼƬ/��ת_����/����˳ʱ��8��/";
//		string image_out_jiangxiang_shun8 = image_jiangxiang_shun8 + name;
//		Mat img_jiangxiang_shun8 = rotateImage(img_jingxiang, 8);
//		cv::resize(img_jiangxiang_shun8, img_jiangxiang_shun8, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_jiangxiang_shun8, img_jiangxiang_shun8);
//
//		// 9��ԭͼ��ʱ��8��
//		string image_yuantu_ni8 = "F:/С����ѧϰͼƬ����/xifang/���ɺ��trainͼƬ/��ת_����/ԭͼ��ʱ��8��/";
//		string image_out_yuantu_ni8 = image_yuantu_ni8 + name;
//		Mat img_yuantu_ni8 = rotateImage(image, -8);
//		cv::resize(img_yuantu_ni8, img_yuantu_ni8, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_yuantu_ni8, img_yuantu_ni8);
//
//		// 10��ԭͼ˳ʱ��8��
//		string image_yuantu_shun8 = "F:/С����ѧϰͼƬ����/xifang/���ɺ��trainͼƬ/��ת_����/ԭͼ˳ʱ��8��/";
//		string image_out_yuantu_shun8 = image_yuantu_shun8 + name;
//		Mat img_yuantu_shun8 = rotateImage(image, 8);
//		cv::resize(img_yuantu_shun8, img_yuantu_shun8, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_yuantu_shun8, img_yuantu_shun8);
//
//		
//
//
//	}
//}
//
//
//
//
//
//// resize
//void main000(void)
//{
//	int i = 0;
//	string name, clas;
//	ifstream infile;
//	infile.open("F:/С����ѧϰͼƬ����/xifang/org_img/val.txt");
//	string image_dir = "F:/С����ѧϰͼƬ����/xifang/org_img/val/";
//	string image_out = "F:/С����ѧϰͼƬ����/xifang/org_img/val_resize/";
//	while (infile)
//	{
//		infile >> name >> clas;
//		cout << i++ << endl;
//		string image_dir_name = image_dir + name;
//		string image_out_name = image_out + name;
//		Mat image = imread(image_dir_name, -1);
//		Mat img_trans = image;
//		cv::resize(img_trans, img_trans, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_name, img_trans);
//
//	}
//
//
//}
//
//
//
//// ��ͼ�������ת
//void main222(void)
//{
//	string image_dir = "D:/visualstudio 2013/project text/c++/c++/";
//	string image_out_dir = "D:/visualstudio 2013/project text/c++/";
//	string image_name = "people_400.jpg";
//	string image_dir_name = image_dir + image_name;
//	string image_out_dir_name = image_out_dir + image_name;
//
//	int degree = 180;
//	Mat image = imread(image_dir_name, -1);
//	Mat img_trans = rotateImage(image, degree);
//	cv::resize(img_trans, img_trans, cv::Size(256, 256), cv::INTER_LINEAR);
//
//	imwrite(image_out_dir_name, img_trans);
//}
//
//
//
//
//// ��ͼ�����ˮƽ����
//void main111(void)
//{
//	string image_dir = "D:/visualstudio 2013/project text/c++/c++/";
//	string image_out_dir = "D:/visualstudio 2013/project text/c++/";
//	string image_name = "people_400.jpg";
//	string image_dir_name = image_dir + image_name;
//	string image_out_dir_name = image_out_dir + image_name;
//
//	Mat image = imread(image_dir_name, -1);
//	Mat img_trans;
//	img_trans.create(image.size(), image.type());
//	for (int i = 0; i < image.rows; i++)
//	{
//		for (int j = 0; j < image.cols; j++)
//		{
//			img_trans.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, image.cols - 1 - j)[0];
//			img_trans.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, image.cols - 1 - j)[1];
//			img_trans.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, image.cols - 1 - j)[2];
//		}
//	}
//
//	imwrite(image_out_dir_name, img_trans);
//
//}
//
//
//// ��ͼ�������ת������Ĭ��Ϊ˳ʱ�뷽��
//Mat rotateImage(Mat img, int degree)
//{
//	degree = -degree;//warpAffineĬ�ϵ���ת��������ʱ�룬���ԼӸ��ű�ʾת��Ϊ˳ʱ��
//	double angle = degree * CV_PI / 180.; // ����  
//	double a = sin(angle), b = cos(angle);
//	int width = img.cols;
//	int height = img.rows;
//	int width_rotate = int(height * fabs(a) + width * fabs(b));
//	int height_rotate = int(width * fabs(a) + height * fabs(b));
//	//��ת����map
//	// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
//	// [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]
//	float map[6];
//	Mat map_matrix = Mat(2, 3, CV_32F, map);
//	// ��ת����
//	Point2d center = Point2d(width / 2, height / 2);
//	Mat map_matrix2 = map_matrix;
//	//2DRotationMatrix(center, degree, 1.0, &map_matrix2);//�����ά��ת�ķ���任����
//	map_matrix2 = getRotationMatrix2D(center, degree, 1.0);
//	map[2] += (width_rotate - width) / 2;
//	map[5] += (height_rotate - height) / 2;
//	Mat img_rotate;
//	//��ͼ��������任
//	//CV_WARP_FILL_OUTLIERS - ����������ͼ������ء�
//	//�������������������ͼ��ı߽��⣬��ô���ǵ�ֵ�趨Ϊ fillval.
//	//CV_WARP_INVERSE_MAP - ָ�� map_matrix �����ͼ������ͼ��ķ��任��
//	warpAffine(img, img_rotate, map_matrix, Size(width_rotate, height_rotate), 1, 0, 0);
//	return img_rotate;
//}
//
