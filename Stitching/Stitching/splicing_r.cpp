//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <time.h>
//#include "opencv2/imgproc/imgproc_c.h"
//#include<math.h>
//#include <numeric>
//using namespace std;
//using namespace cv;
//
//using namespace std;
//using namespace cv;
//
//#include <iostream>
//#include <opencv2/opencv.hpp>
//#include <time.h>
//#include "opencv2/imgproc/imgproc_c.h"
//using namespace std;
//using namespace cv;
//
//using namespace std;
//using namespace cv;
//
//void light(Mat image1, Mat image2)
//{
//	// 计算两张图像的平均亮度值
//	Scalar mean1 = mean(image1);
//	Scalar mean2 = mean(image2);
//
//	// 计算亮度差异值
//	double brightness_diff = mean1[0] - mean2[0];
//
//	// 调整第二张图像的亮度值
//	image2.convertTo(image2, -1, 1, brightness_diff);
//
//	// 显示调整后的图像
//	/*imshow("Image1", img1);
//	imshow("Image2", img2);
//	waitKey(0);*/
//
//}
//
////图像融合的去裂缝处理操作
//bool OptimizeSeam(int start_x, int end_x, Mat& WarpImg, Mat& DstImg)
//{
//	double Width = (end_x - start_x);//重叠区域的宽度  
//
//	//图像加权融合，通过改变alpha修改DstImg与WarpImg像素权重，达到融合效果
//	double alpha = 1.0;
//	for (int i = 0; i < DstImg.rows; i++)
//	{
//		for (int j = start_x; j < end_x; j++)
//		{
//			for (int c = 0; c < 3; c++)
//			{
//				//如果图像WarpImg像素为0，则完全拷贝DstImg
//				if (WarpImg.at<Vec3b>(i, j)[c] == 0)
//				{
//					alpha = 1.0;
//				}
//				else
//				{
//					double l = Width - (j - start_x); //重叠区域中某一像素点到拼接缝的距离
//					alpha = l / Width;
//				}
//				DstImg.at<Vec3b>(i, j)[c] = DstImg.at<Vec3b>(i, j)[c] * alpha + WarpImg.at<Vec3b>(i, j)[c] * (1.0 - alpha);
//			}
//		}
//	}
//
//	return true;
//}
//
//
//
////去黑边
//Mat RemoveBlackBorder(Mat& iplImg)
//{
//	int width = iplImg.size().width;
//	int height = iplImg.size().height;
//	int d = 0;
//	int i = 0, j = 0;
//
//
//	if (iplImg.channels() == 3)	//彩色图片
//	{
//
//		//消除黑色边框：右
//		for (i = width - 1; i >= 0; i--)
//		{
//			bool flag = false;
//			for (j = 0; j < height; j++)
//			{
//				int tmpb, tmpg, tmpr;
//				Vec3b bgr = iplImg.at<Vec3b>(j, i);
//				tmpb = bgr[0];
//				tmpg = bgr[1];
//				tmpr = bgr[2];
//				if (tmpb <= 20 && tmpg <= 20 && tmpr <= 20)
//				{
//					;
//				}
//				else
//				{
//					flag = true;
//					d = i;
//					break;
//				}
//			}
//			if (flag) break;
//		}
//
//
//		//printf("右 d: %d\n", d);
//	}
//
//	//复制图像
//	int w = d, h = height;
//	Mat dstImg = Mat(iplImg, Rect(0, 0, d, h));
//	//Mat result = Mat(dstImg, (Rect(0, 10, 340, 640)));
//
//	return dstImg;
//}
//
////计算拼接的位置
//pair<double, double>sift_offset(Mat image_left, Mat image_right, bool draw)
//{
//	//创建SIFT特征检测器
//	int Hessian = 50000;
//	cv::Ptr<cv::Feature2D> feature = cv::SIFT::create(Hessian);  // 提取pointNum个特征点
//
//
//	//进行图像特征检测、特征描述
//	vector<KeyPoint>keypoint_left, keypoint_right;
//	Mat descriptor_left, descriptor_right;
//	feature->detectAndCompute(image_left, Mat(), keypoint_left, descriptor_left);
//	feature->detectAndCompute(image_right, Mat(), keypoint_right, descriptor_right);
//
//	//使用FLANN算法进行特征描述子的匹配
//	//FlannBasedMatcher matcher;
//
//	//使用暴力匹配算法进行特征描述子的匹配
//	BFMatcher matcher;
//	vector<DMatch>matches;
//	matcher.match(descriptor_left, descriptor_right, matches);
//
//
//	double Max = 0.0;
//	double Min = 100;
//	for (int i = 0; i < matches.size(); i++)
//	{
//		//float distance –>代表这一对匹配的特征点描述符（本质是向量）的欧氏距离，数值越小也就说明两个特征点越相像。
//		double dis = matches[i].distance;
//		if (dis > Max)
//		{
//			Max = dis;
//		}
//
//	}
//
//	//筛选出匹配程度高的关键点
//	vector<DMatch>goodmatches;
//	vector<Point2f>goodkeypoint_left, goodkeypoint_right;
//	for (int i = 0; i < matches.size(); i++)
//	{
//		double dis = matches[i].distance;
//		if (dis < 0.6 * Max)
//		{
//			/*
//			以右图做透视变换
//			左图->queryIdx:查询点索引（查询图像）
//			右图->trainIdx:被查询点索引（目标图像）
//			*/
//			//注：对image_right图像做透视变换，故goodkeypoint_left对应queryIdx，goodkeypoint_right对应trainIdx
//			//int queryIdx –>是测试图像的特征点描述符（descriptor）的下标，同时也是描述符对应特征点（keypoint)的下标。
//			goodkeypoint_left.push_back(keypoint_left[matches[i].queryIdx].pt);
//			//int trainIdx –> 是样本图像的特征点描述符的下标，同样也是相应的特征点的下标。
//			goodkeypoint_right.push_back(keypoint_right[matches[i].trainIdx].pt);
//			goodmatches.push_back(matches[i]);
//		}
//	}
//
//	//绘制特征点
//	if (draw)
//	{
//		Mat result;
//		drawMatches(image_left, keypoint_left, image_right, keypoint_right, goodmatches, result,
//			cv::Scalar(0, 0, 255), cv::Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
//
//		/*drawMatches(image_left, keypoint_left, image_right, keypoint_right, goodmatches, result,
//			cv::Scalar(0, 0, 255), Scalar(0, 0, 255),);*/
//			/*namedWindow("特征匹配", WINDOW_NORMAL);
//			imshow("特征匹配", result);*/
//
//		Mat temp_left = image_left.clone();
//		for (int i = 0; i < goodkeypoint_left.size(); i++)
//		{
//			circle(temp_left, goodkeypoint_left[i], 10, Scalar(0, 255, 0), 1);
//		}
//		/*namedWindow("goodkeypoint_left", WINDOW_NORMAL);
//		imshow("goodkeypoint_left", temp_left);*/
//
//		Mat temp_right = image_right.clone();
//		for (int i = 0; i < goodkeypoint_right.size(); i++)
//		{
//			circle(temp_right, goodkeypoint_right[i], 10, Scalar(0, 0, 255), 1);
//		}
//		/*namedWindow("goodkeypoint_right", WINDOW_NORMAL);
//		imshow("goodkeypoint_right", temp_right);*/
//	}
//
//	//findHomography计算单应性矩阵至少需要4个点
//	/*
//	计算多个二维点对之间的最优单映射变换矩阵H（3x3），使用MSE或RANSAC方法，找到两平面之间的变换矩阵
//	*/
//	//if (goodkeypoint_left.size() < 4 || goodkeypoint_right.size() < 4) return false;
//
//
//	//获取图像right到图像left的投影映射矩阵，尺寸为3*3
//	//注意顺序，srcPoints对应goodkeypoint_right，dstPoints对应goodkeypoint_left
//
//
//	vector<unsigned char>listpoints;
//	Mat H = findHomography(goodkeypoint_right, goodkeypoint_left, RANSAC, 7, listpoints);
//
//	std::vector< DMatch > goodgood_matches;
//	for (int i = 0; i < listpoints.size(); i++)
//	{
//		if ((int)listpoints[i])
//		{
//
//			goodgood_matches.push_back(goodmatches[i]);
//		}
//
//	}
//
//	Mat copysrcImage1 = image_left.clone();
//	Mat copysrcImage2 = image_right.clone();
//	Mat Homgimg_matches;
//	drawMatches(copysrcImage1, keypoint_left, copysrcImage2, keypoint_right,
//		goodgood_matches, Homgimg_matches, Scalar::all(-1), Scalar::all(-1),
//		vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
//
//
//
//	/*cout << "goodgood_matches大小：" << goodgood_matches.size() << endl;
//	cout << "good_matches大小：" << goodmatches.size() << endl;*/
//	imshow("去除误匹配点后;", Homgimg_matches);
//
//	//waitKey(2000);
//
//
//	//透视变换左上角(0,0,1)
//	Mat V2 = (Mat_<double>(3, 1) << 0.0, 0.0, 1.0);
//	Mat V1 = H * V2;
//	Point left_top;
//	left_top.x = V1.at<double>(0, 0) / V1.at<double>(2, 0);
//	left_top.y = V1.at<double>(0, 1) / V1.at<double>(2, 0);
//	if (left_top.x < 0)left_top.x = 0;
//
//	//透视变换左下角(0,src.rows,1)
//	V2 = (Mat_<double>(3, 1) << 0.0, image_left.rows, 1.0);
//	V1 = H * V2;
//	Point left_bottom;
//	left_bottom.x = V1.at<double>(0, 0) / V1.at<double>(2, 0);
//	left_bottom.y = V1.at<double>(0, 1) / V1.at<double>(2, 0);
//	if (left_bottom.x < 0)left_bottom.x = 0;
//
//	int start_x = min(left_top.x, left_bottom.x);//重合区域起点
//	int end_x = image_left.cols;//重合区域终点
//
//	/*cout <<"left_bottom.y:" << left_bottom.y << endl;
//	cout <<"left_top.y:" << left_top.y << endl;*/
//	double verticalOffset;
//	cout << "verticalOffset原始" << H.at<double>(1, 2) << endl;
//	if (H.at<double>(1, 2) < 0)
//	{
//		verticalOffset = -(H.at<double>(1, 2)) + 1;
//	}
//	else
//	{
//		verticalOffset = -(H.at<double>(1, 2)) - 1;
//	}
//
//
//	// 输出上下偏差
//	std::cout << "Vertical offset: " << verticalOffset << std::endl;
//
//
//	return make_pair(start_x, verticalOffset);//返回起始位置和上下的偏差
//
//}
//
//
//
//
//
////计算相邻两幅图像上下的偏差
//Point offsety(Mat imgsrc1, Mat imgsrc2)
//{
//	Mat image1, image2;
//	if (imgsrc1.cols >= imgsrc2.cols)
//	{
//		Mat img2;
//		copyMakeBorder(imgsrc2, img2, 0, 0, 0, imgsrc1.cols - imgsrc2.cols, BORDER_CONSTANT, (0, 0, 0));
//		image1 = imgsrc1;
//		image2 = img2;
//	}
//	else
//	{
//		Mat img1;
//		copyMakeBorder(imgsrc1, img1, 0, 0, 0, imgsrc2.cols - imgsrc1.cols, BORDER_CONSTANT, (0, 0, 0));
//		image1 = img1;
//		image2 = imgsrc2;
//	}
//
//
//	/*转灰度图像*/
//	Mat image1_gray, image2_gray;
//	cvtColor(image1, image1_gray, COLOR_BGR2GRAY);
//	cvtColor(image2, image2_gray, COLOR_BGR2GRAY);
//
//	//相位相关计算偏移量
//	Mat grayL64F, grayR64F;
//	image1_gray.convertTo(grayL64F, CV_64F);
//	image2_gray.convertTo(grayR64F, CV_64F);
//	Point shiftPt = phaseCorrelate(grayL64F, grayR64F);
//	return shiftPt;
//}
//
//
//
//Mat Image_Stitching(Mat imgsrc1, Mat imgsrc2, double image_x, double &image_y)
//{
//
//
//	Mat image1, image2;
//	if (imgsrc1.cols >= imgsrc2.cols)
//	{
//		/*Mat img2(imgsrc2.rows, imgsrc1.cols, imgsrc1.type());
//		Mat roright = img2(Rect(0, 0, imgsrc2.cols, imgsrc2.rows));
//		imgsrc2.copyTo(roright);*/
//		Mat img2;
//		copyMakeBorder(imgsrc2, img2, 0, 0, 0, imgsrc1.cols - imgsrc2.cols, BORDER_CONSTANT, (0, 0, 0));
//		image1 = imgsrc1;
//		image2 = img2;
//	}
//	else
//	{
//		/*Mat img1(imgsrc1.rows, imgsrc2.cols, imgsrc2.type());
//		Mat roleft = img1(Rect(0, 0, imgsrc1.cols, imgsrc1.rows));
//		imgsrc1.copyTo(roleft);*/
//
//		Mat img1;
//		copyMakeBorder(imgsrc1, img1, 0, 0, 0, imgsrc2.cols - imgsrc1.cols, BORDER_CONSTANT, (0, 0, 0));
//		image1 = img1;
//		image2 = imgsrc2;
//	}
//
//	imshow("zuo", image1);
//	imshow("you", image2);
//
//
//	/*转灰度图像*/
//	Mat image1_gray, image2_gray;
//	cvtColor(image1, image1_gray, COLOR_BGR2GRAY);
//	cvtColor(image2, image2_gray, COLOR_BGR2GRAY);
//
//	//相位相关计算偏移量
//	Mat grayL64F, grayR64F;
//	image1_gray.convertTo(grayL64F, CV_64F);
//	image2_gray.convertTo(grayR64F, CV_64F);
//	Point shiftPt = phaseCorrelate(grayL64F, grayR64F);
//	cout << "shiftPt" << shiftPt << endl;
//	//int img_y;// = shiftPt.y;
//	//if (shiftPt.x > 50||shiftPt.x<-30)
//	//{
//	//	img_y = shiftPt.y;//上下的偏移量
//	//}
//	//else
//	//{
//	//	img_y = image_y;
//	//}
//
//	//模板匹配求解拼接处位置
//	int y1 = 50;
//	int y2 = 300;
//	int x1 = 1;
//	int x2 = 50;
//	/*int y1 = 50;
//	int y2 = 400;
//	int x1 = 1;
//	int x2 = 100;*/
//
//	Mat temp = image2_gray(Range(y1, y2), Range(x1, x2));
//	/*结果矩阵图像,大小，数据类型*/
//	//Mat res(image1_gray.rows - temp.rows + 1, image2_gray.cols - temp.cols + 1, CV_32FC1);
//	Mat res(image1_gray.cols - temp.cols + 1, image2_gray.rows - temp.rows + 1, CV_32FC1);
//	/*模板匹配，采用归一化相关系数匹配*/
//	matchTemplate(image1_gray, temp, res, TM_CCOEFF_NORMED);
//	/*cout << image1_gray.cols - temp.cols + 1 << endl;
//	cout << image2_gray.rows - temp.rows + 1 << endl;*/
//	/*结果矩阵阈值化处理*/
//	threshold(res, res, 0.7, 1, THRESH_TOZERO);
//	//imshow("res", res);
//
//
//	double minVal, maxVal, threshold = 0.7;
//	/*查找最大值及位置*/
//	Point minLoc, maxLoc;
//	minMaxLoc(res, &minVal, &maxVal, &minLoc, &maxLoc);
//
//	cout << maxVal << endl;
//	cout << "maxLoc.x" << maxLoc.x << endl;
//	cout << "maxLoc.y" << maxLoc.y << endl;
//
//
//	//int img_y = image_y;
//
//	image1 = imgsrc1;
//	image2 = imgsrc2;
//	//int x = image_x;
//
//	int img_y;//偏移量
//	
//	int img_x;//（重合起始位置）
//	if (maxVal == 0)
//	{
//		img_x = image_x;//重合位置
//		img_y = image_y;
//	}
//	else
//	{
//		img_x = maxLoc.x;
//		img_y = y1 - maxLoc.y;
//	}
//	image_y = img_y;
//	cout << "图像的上下偏差为：" << img_y << endl;
//	cout << "图像的拼接处为：" << img_x << endl;
//	/*图像拼接*/
//
//	Mat image_left;
//	Mat image_right;
//
//
//	//相当于透视变换的结果
//	Mat result1 = Mat::zeros(cvSize(image1.cols + image2.cols, image1.rows), image1.type());
//
//	//两种情况，如果向上偏移(以左图为基准，只对右图进行操作)
//	if (img_y < 0)
//	{
//		img_y = abs(img_y);
//		image_left = image1;
//		Rect m_rect_right = Rect(0, 0, image2.cols, image2.rows - img_y);
//		image_right = image2(m_rect_right);
//		image_right.copyTo(Mat(result1, Rect(img_x, img_y, image_right.cols, image_right.rows)));
//		imshow("result1", result1);
//		Mat result = result1.clone();
//		image_left.copyTo(Mat(result, Rect(0, 0, image_left.cols, image_left.rows)));
//
//		OptimizeSeam(img_x, image1.cols, result1, result);
//
//		namedWindow("name", WINDOW_NORMAL);
//		imshow("name", result);
//		return result;
//	}
//	//左图像下或不偏移的情况
//	else
//	{
//		img_y = abs(img_y);
//		image_left = image1;
//		//Rect m_rect_right = Rect(0, img_y+3, image2.cols, image2.rows - img_y-3);
//		Rect m_rect_right = Rect(0, img_y, image2.cols, image2.rows - img_y);
//		image_right = image2(m_rect_right);
//		image_right.copyTo(Mat(result1, Rect(img_x, 0, image_right.cols, image_right.rows)));
//		imshow("result1", result1);
//		Mat result = result1.clone();
//		image_left.copyTo(Mat(result, Rect(0, 0, image_left.cols, image_left.rows)));
//		OptimizeSeam(img_x, image1.cols, result1, result);
//		namedWindow("name", WINDOW_NORMAL);
//		imshow("name", result);
//		return result;
//	}
//
//
//
//
//	//cout << "result_y" << result.rows << endl;
//	/*image_left.copyTo(Mat(result, Rect(0, 0, x, image_left.rows)));
//	image_right.copyTo(Mat(result, Rect(x - 1, 0, image_right.cols, image_right.rows)));*/
//
//	//OptimizeSeam(result, result, result, x);
//	//OptimizeSeam(x, image1.cols, result, result);
//	//namedWindow("name", WINDOW_NORMAL);
//	//imshow("name", result1);
//	//return result1;
//
//}
//
//
//
//int main()
//{
//
//	int index;
//	cout << "第几张图片开始拼接" << endl;
//	cin >> index;
//	stringstream stream;
//	string str;
//	stream << index;
//	stream >> str;
//	//第一张图片
//	//string firstname = "增强//" + str1 + ".jpg";
//	//string firstname = "图片//" + str1 + ".jpg";
//	//string firstname = "E://内螺纹拍摄照片//拍摄6//水平校正后裁剪增强//" + str + ".jpg";
//	//string firstname = "D://内螺纹拍摄照片//裁剪过后//裁剪四//倾斜校正加增强操作//" + str1 + ".jpg";
//	//string firstname = "E://内螺纹拍摄照片//拍摄8//相同亮度增强//" + str1 + ".jpg";
//	//string firstname = "E://内螺纹拍摄照片//偏离中心//校正//" + str + ".jpg";
//	//string firstname = "E://内螺纹拍摄照片//大螺纹//校正//" + str + ".jpg";
//	//string firstname = "E://内螺纹拍摄照片//金属螺母//水平校正2//" + str + ".jpg";
//	//string firstname = "E://内螺纹拍摄照片//光滑物件//裁剪白边//" + str + ".jpg";
//	//string firstname = "E://内螺纹拍摄照片//拍摄十九//拼接结果//" + str1 + ".jpg";
//	//string firstname = "E://内螺纹拍摄照片//不垂直//校正//" + str + ".jpg";
//	string firstname = "G://内螺纹拍摄照片//1//倾斜校正增强//" + str + ".jpg";
//	Mat left = imread(firstname);
//	Mat base = left;
//	/*Mat img_left= Mat::zeros(cvSize(left.cols, 570),left.type());
//	left.copyTo(Mat(img_left, Rect(0, 50, left.cols, left.rows)));*/
//	//Mat base = left;
//	//结果图片
//	Mat  stitchedImage;
//
//
//	int n;
//	cout << "请输入想拼接的图片数量（大于1小于18）" << endl;
//	cin >> n;
//	cout << "输入成功，开始计时" << endl;
//
//	double image_y = 0;//最后一张图片与总图片的上下偏差
//	for (int k = index + 1; k <= index + n - 1; k++) {
//		stringstream stream1;
//		string str1;
//		stream1 << k - 1;
//		stream1 >> str1;
//		//string filename = "E://内螺纹拍摄照片//偏离中心//校正//" + str1 + ".jpg";
//		//string filename = "E://内螺纹拍摄照片//金属螺母//水平校正2//" + str1 + ".jpg";
//		//string filename = "E://内螺纹拍摄照片//光滑物件//裁剪白边//" + str1 + ".jpg";
//		//string filename = "E://内螺纹拍摄照片//拍摄6//水平校正后裁剪增强//" + str1 + ".jpg";
//		//string filename = "E://内螺纹拍摄照片//大螺纹//校正//" + str1 + ".jpg";
//		//string filename = "E://内螺纹拍摄照片//不垂直//校正//" + str1 + ".jpg";
//		string filename = "G://内螺纹拍摄照片//1//倾斜校正增强//" + str1 + ".jpg";
//		stringstream stream2;
//		string str2;
//		stream2 << k;
//		stream2 >> str2;
//		//string filename1 = "E://内螺纹拍摄照片//偏离中心//校正//" + str2 + ".jpg";
//		//string filename1 = "E://内螺纹拍摄照片//大螺纹//校正//" + str2 + ".jpg";
//		//string filename1 = "E://内螺纹拍摄照片//金属螺母//水平校正2//" + str2 + ".jpg";
//		//string filename1 = "E://内螺纹拍摄照片//光滑物件//裁剪白边//" + str2 + ".jpg";
//		//string filename1 = "E://内螺纹拍摄照片//拍摄6//水平校正后裁剪增强//" + str2 + ".jpg";
//		//string filename1 = "E://内螺纹拍摄照片//不垂直//校正//" + str2 + ".jpg";
//		string filename1 = "G://内螺纹拍摄照片//1//倾斜校正增强//" + str2 + ".jpg";
//		cout << "正在拼接......." << filename1 << endl;
//		Mat right = imread(filename1);
//		/*	Mat img_right = Mat::zeros(cvSize(right.cols, 570), right.type());
//			right.copyTo(Mat(img_right, Rect(0, 50, right.cols, right.rows)));*/
//		if (left.empty() || right.empty())
//		{
//			cout << "No Image!" << endl;
//			system("pause");
//			return -1;
//		}
//
//		//计算拼接处的位置
//		Mat index = imread(filename);//相邻两张图片的上下偏差
//		Point p = offsety(index, right);
//		double image_x = 0;//拼接处的位置
//		//double offsetx = right.cols - offset(index, right, true).first;
//		if (p.x < -30)
//		{
//			image_x = left.cols - index.cols + abs(p.x);
//		}
//		else
//		{
//			image_x = left.cols - (right.cols - sift_offset(index, right, true).first);//两个图像的拼接处
//		}
//
//		cout << "p:" << p << endl;
//		double image_y1 = 0;
//		if (p.x < -30 || p.x>30)
//		{
//			image_y1 = p.y; //相邻两个图像的上下偏差
//		}
//		else
//		{
//			image_y1 = sift_offset(index, right, false).second;
//		}
//
//		image_y += image_y1;
//		//image_y = 2;
//		cout << "image_y1: " << image_y1 << endl;
//		cout << "image_y: " << image_y << endl;
//		cout << "image_x:" << image_x << endl;
//
//		light(base, right);
//
//		stitchedImage = Image_Stitching(left, right, image_x, image_y);
//		//stitchedImage = Image_Stitching(left, right, image_x);
//		stitchedImage = RemoveBlackBorder(stitchedImage);
//		//img_left = stitchedImage;
//		left = stitchedImage;
//
//	}
//
//	cout << "拼接成功" << endl;
//	stitchedImage = RemoveBlackBorder(stitchedImage);
//	namedWindow("ResultImage", WINDOW_NORMAL);
//	stitchedImage = RemoveBlackBorder(stitchedImage);
//	imshow("ResultImage", stitchedImage);
//
//
//	stringstream stream3;
//	string str3;
//	stream3 << index;
//	stream3 >> str3;
//	//保存文件名
//	//string resultname = "E://内螺纹拍摄照片//大螺纹//拼接结果//" + str3 + ".jpg";
//	//string resultname = "E://内螺纹拍摄照片//拍摄6//拼接结果//" + str3 + ".jpg";
//	//string resultname = "E://内螺纹拍摄照片//偏离中心//拼接结果//" + str3 + ".jpg";
//	//string resultname = "E://内螺纹拍摄照片//金属螺母//拼接结果//" + str3 + ".jpg";
//	//string resultname = "E://内螺纹拍摄照片//不垂直//拼接结果//" + str3 + ".jpg";
//	//imwrite(resultname, stitchedImage);
//	string resultname = "G://内螺纹拍摄照片//1//拼接结果//" + str3 + ".jpg";
//	imwrite(resultname, stitchedImage);
//	waitKey();
//	return 0;
//
//
//
//}
//
//
