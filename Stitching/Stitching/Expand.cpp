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
//	infile.open("F:/小样本学习图片数据/xifang/org_img/train.txt");
//	string image_dir = "F:/小样本学习图片数据/xifang/org_img/train/";
//	while (infile)
//	{
//		infile >> name >> clas;
//		cout << i++ << endl;
//		string image_dir_name = image_dir + name;
//		Mat image = imread(image_dir_name, -1);
//
//		// 1、对图像进行水平镜像
//		string image_jingxiang = "F:/小样本学习图片数据/xifang/生成后的train图片/水平镜像/";
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
//		// 2、对图像进行切片，右上角切片
//		string image_qiepian_youshang = "F:/小样本学习图片数据/xifang/生成后的train图片/切片/右上角切片/";
//		string image_out_qiepian_youshang = image_qiepian_youshang + name;
//		//Rect bbox(0, 0, 224, 224);  // 左上角切片
//		Rect bbox1(image.cols - 1 - 224, 0, 224, 224);  // 右上角切片
//		//Rect bbox(0, image.rows - 1 - 224, 224, 224);  // 左下角切片
//		//Rect bbox(image.cols - 1 - 224, image.rows - 1 - 224, 224, 224);  // 右下角切片
//		//Rect bbox(image.cols/2- 112, image.rows/2 -112,224, 224);  // 中间切片
//
//		Mat img_qiepian_youshang = image(bbox1);
//		cv::resize(img_qiepian_youshang, img_qiepian_youshang, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_qiepian_youshang, img_qiepian_youshang);
//
//		// 3、对图像进行切片，右下角切片
//		string image_qiepian_youxia = "F:/小样本学习图片数据/xifang/生成后的train图片/切片/右下角切片/";
//		string image_out_qiepian_youxia = image_qiepian_youxia + name;
//		//Rect bbox(0, 0, 224, 224);  // 左上角切片
//		//Rect bbox(image.cols - 1 - 224, 0, 224, 224);  // 右上角切片
//		//Rect bbox(0, image.rows - 1 - 224, 224, 224);  // 左下角切片
//		Rect bbox2(image.cols - 1 - 224, image.rows - 1 - 224, 224, 224);  // 右下角切片
//		//Rect bbox(image.cols/2- 112, image.rows/2 -112,224, 224);  // 中间切片
//
//		Mat img_qiepian_youxia = image(bbox2);
//		cv::resize(img_qiepian_youxia, img_qiepian_youxia, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_qiepian_youxia, img_qiepian_youxia);
//
//		
//
//		// 7、镜像逆时针8度
//		string image_jiangxiang_ni8 = "F:/小样本学习图片数据/xifang/生成后的train图片/旋转_镜像/镜像逆时针8度/";
//		string image_out_jiangxiang_ni8 = image_jiangxiang_ni8 + name;
//		Mat img_jiangxiang_ni8 = rotateImage(img_jingxiang, -8);
//		cv::resize(img_jiangxiang_ni8, img_jiangxiang_ni8, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_jiangxiang_ni8, img_jiangxiang_ni8);
//
//		// 8、镜像顺时针8度
//		string image_jiangxiang_shun8 = "F:/小样本学习图片数据/xifang/生成后的train图片/旋转_镜像/镜像顺时针8度/";
//		string image_out_jiangxiang_shun8 = image_jiangxiang_shun8 + name;
//		Mat img_jiangxiang_shun8 = rotateImage(img_jingxiang, 8);
//		cv::resize(img_jiangxiang_shun8, img_jiangxiang_shun8, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_jiangxiang_shun8, img_jiangxiang_shun8);
//
//		// 9、原图逆时针8度
//		string image_yuantu_ni8 = "F:/小样本学习图片数据/xifang/生成后的train图片/旋转_镜像/原图逆时针8度/";
//		string image_out_yuantu_ni8 = image_yuantu_ni8 + name;
//		Mat img_yuantu_ni8 = rotateImage(image, -8);
//		cv::resize(img_yuantu_ni8, img_yuantu_ni8, cv::Size(256, 256), cv::INTER_LINEAR);
//		imwrite(image_out_yuantu_ni8, img_yuantu_ni8);
//
//		// 10、原图顺时针8度
//		string image_yuantu_shun8 = "F:/小样本学习图片数据/xifang/生成后的train图片/旋转_镜像/原图顺时针8度/";
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
//	infile.open("F:/小样本学习图片数据/xifang/org_img/val.txt");
//	string image_dir = "F:/小样本学习图片数据/xifang/org_img/val/";
//	string image_out = "F:/小样本学习图片数据/xifang/org_img/val_resize/";
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
//// 对图像进行旋转
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
//// 对图像进行水平镜像
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
//// 对图像进行旋转函数，默认为顺时针方向
//Mat rotateImage(Mat img, int degree)
//{
//	degree = -degree;//warpAffine默认的旋转方向是逆时针，所以加负号表示转化为顺时针
//	double angle = degree * CV_PI / 180.; // 弧度  
//	double a = sin(angle), b = cos(angle);
//	int width = img.cols;
//	int height = img.rows;
//	int width_rotate = int(height * fabs(a) + width * fabs(b));
//	int height_rotate = int(width * fabs(a) + height * fabs(b));
//	//旋转数组map
//	// [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]
//	// [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]
//	float map[6];
//	Mat map_matrix = Mat(2, 3, CV_32F, map);
//	// 旋转中心
//	Point2d center = Point2d(width / 2, height / 2);
//	Mat map_matrix2 = map_matrix;
//	//2DRotationMatrix(center, degree, 1.0, &map_matrix2);//计算二维旋转的仿射变换矩阵
//	map_matrix2 = getRotationMatrix2D(center, degree, 1.0);
//	map[2] += (width_rotate - width) / 2;
//	map[5] += (height_rotate - height) / 2;
//	Mat img_rotate;
//	//对图像做仿射变换
//	//CV_WARP_FILL_OUTLIERS - 填充所有输出图像的象素。
//	//如果部分象素落在输入图像的边界外，那么它们的值设定为 fillval.
//	//CV_WARP_INVERSE_MAP - 指定 map_matrix 是输出图像到输入图像的反变换，
//	warpAffine(img, img_rotate, map_matrix, Size(width_rotate, height_rotate), 1, 0, 0);
//	return img_rotate;
//}
//
