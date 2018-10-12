#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<vector>
#include <algorithm>

using namespace cv;
using namespace std;


int TubeIdentification(Mat inputmat)
{

	int yx[7][2] =
	{
		{ inputmat.rows * 1 / 6, inputmat.cols * 1 / 2 },
		{ inputmat.rows * 1 / 3, inputmat.cols * 3 / 4 },
		{ inputmat.rows * 2 / 3, inputmat.cols * 3 / 4 },
		{ inputmat.rows * 5 / 6, inputmat.cols * 1 / 2 },
		{ inputmat.rows * 2 / 3, inputmat.cols * 1 / 4 },
		{ inputmat.rows * 1 / 3, inputmat.cols * 1 / 4 },
		{ inputmat.rows * 1 / 2, inputmat.cols * 1 / 2 },
	};


	int number[7] = { 0,0,0,0,0,0,0 };

	for (int i = 0; i < 7; i++)
	{
		uchar intensity = inputmat.at<uchar>(yx[i][0], yx[i][1]);

		if (intensity == 255)
			number[i] = 1;
	}


	int zero[7] = { 1,1,1,1,1,1,0 };
	int one[7] = { 0,1,1,0,0,0,0 };
	int two[7] = { 1,1,0,1,1,0,1 };
	int three[7] = { 1,1,1,1,0,0,1 };
	int four[7] = { 0,1,1,0,0,1,1 };
	int five[7] = { 1,0,1,1,0,1,1 };
	int six[7] = { 1,0,1,1,1,1,1 };
	int seven[7] = { 1,1,1,0,0,0,0 };
	int eight[7] = { 1,1,1,1,1,1,1 };
	int nine[7] = { 1,1,1,1,0,1,1 };



	if (std::equal(std::begin(number), std::end(number), std::begin(zero), std::end(zero)))
		return 0;

	if (std::equal(std::begin(number), std::end(number), std::begin(one), std::end(one)))
		return 1;

	if (std::equal(std::begin(number), std::end(number), std::begin(two), std::end(two)))
		return 2;

	if (std::equal(std::begin(number), std::end(number), std::begin(three), std::end(three)))
		return 3;

	if (std::equal(std::begin(number), std::end(number), std::begin(four), std::end(four)))
		return 4;

	if (std::equal(std::begin(number), std::end(number), std::begin(five), std::end(five)))
		return 5;

	if (std::equal(std::begin(number), std::end(number), std::begin(six), std::end(six)))
		return 6;

	if (std::equal(std::begin(number), std::end(number), std::begin(seven), std::end(seven)))
		return 7;

	if (std::equal(std::begin(number), std::end(number), std::begin(eight), std::end(eight)))
		return 8;

	if (std::equal(std::begin(number), std::end(number), std::begin(nine), std::end(nine)))
		return 9;



	else return -9999;

}

static int value = -9999;

int main(int, char**)
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
	//	cvtColor(frame, edges, CV_BGR2GRAY);
	//	GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
	//	Canny(edges, edges, 0, 30, 3);
	//	imshow("edges", edges);

		cv::Mat src = frame;
		cv::Mat dst; 	//旋转角度	
		double angle = 90;
		cv::Size src_sz = src.size();
		cv::Size dst_sz(src_sz.height, src_sz.width);
		int len = std::max(src.cols, src.rows); 	//指定旋转中心	
		cv::Point2f center(len / 2., len / 2.);		//获取旋转矩阵（2x3矩阵）	
		cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0); 	//根据旋转矩阵进行仿射变换	
		cv::warpAffine(src, dst, rot_mat, dst_sz); 	//显示旋转效果	



		string dir = "D:\\resources\\number.jpg";
		imwrite(dir, dst);


		Point2f a(src_sz.height / 2, src_sz.width / 6);
		circle(dst, a, 10, 470,10,8,0);
		Point2f b(src_sz.height *3/4, src_sz.width *1/3);
		circle(dst, b, 10, 470, 10, 8, 0);
		Point2f c(src_sz.height *3/4, src_sz.width *2/3);
		circle(dst, c, 10, 80, 10, 8, 0);
		Point2f d(src_sz.height *1/2, src_sz.width *5/6);
		circle(dst, d, 10, 80, 10, 8, 0);
		Point2f e(src_sz.height *1/4, src_sz.width *2/3);
		circle(dst, e, 10, 80, 10, 8, 0);
		Point2f f(src_sz.height *1/4, src_sz.width *1/3);
		circle(dst, f, 10, 470, 10, 8, 0);
		Point2f g(src_sz.height /2, src_sz.width / 2);
		circle(dst, g, 10, 80, 10, 8, 0);
		cv::imshow("result", dst); 	

	//	imshow("image_org", image_org);  // read RGB image
		Mat image_gry = imread("D:\\resources\\number.jpg", IMREAD_GRAYSCALE);
		if (image_gry.empty()) // read RGB image
			return -1;
//		imshow("image_gry", image_gry);

		Mat image_bin;
		threshold(image_gry, image_bin, 50, 255, THRESH_BINARY); // convert to binary image
//		imshow("image_bin", image_bin);

		Mat image_ero;
		Mat element = getStructuringElement(MORPH_RECT, Size(2 * 2 + 1, 2 * 2 + 1));
		erode(image_bin, image_ero, element);
//		imshow("image_ero", image_ero);

		Mat image_dil;
		Mat element1 = getStructuringElement(MORPH_RECT, Size(20, 20)); // 膨胀
		dilate(image_ero, image_dil, element1);
		imshow("image_dil", image_dil);


		value = TubeIdentification(image_dil);
		
		if (value == 1 || value == 2 || value == 3)
			break;

		if (waitKey(30) >= 0) break;
	}

	cout << value;
	waitKey(0);
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}

