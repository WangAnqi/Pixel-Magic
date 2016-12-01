#include<cvfun.h>
Mat angleRotate(Mat& src, double angle)
{
	double alpha = angle * CV_PI / 180;
	double rotateMat[3][3] = {
		{cos(alpha), -sin(alpha), 0},
		{sin(alpha), cos(alpha), 0},
		{0,0,1}};
	int nSrcRows = src.rows;
	int nSrcCols = src.cols;

	double a1 = nSrcCols * rotateMat[0][0];
	double b1 = nSrcCols * rotateMat[1][0];
	double a2 = nSrcCols * rotateMat[0][0] + nSrcRows * rotateMat[0][1];
	double b2 = nSrcCols * rotateMat[1][0] + nSrcRows * rotateMat[1][1];
	double a3 = nSrcRows * rotateMat[0][1];
	double b3 = nSrcRows * rotateMat[1][1];

	double kxMin = min(min(min(double(0.0), a1), a2), a3);
	double kxMax = max(max(max(double(0.0), a1), a2), a3);
	double kyMin = min(min(min(double(0.0), b1), b2), b3);
	double kyMax = max(max(max(double(0.0), b1), b2), b3);

	int nRows = abs(kxMax - kxMin);
	int nCols = abs(kyMax - kyMin);
	cv::Mat dst(nRows, nCols, src.type(), cv::Scalar::all(0));
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			int x = (j + kxMin) * rotateMat[0][0] - (i + kyMin) * rotateMat[0][1];
			int y = -(j + kxMin) * rotateMat[1][0] + (i + kyMin) * rotateMat[1][1];
			if ((x >= 0) && (x < nSrcCols) && (y >= 0) && (y < nSrcRows))
			{
				dst.at<cv::Vec3b>(i, j) = src.at<cv::Vec3b>(y, x);
			}
		}
	}

	return dst;
}

Mat horizon_reverse(Mat &src)
{
	Mat dst;
	flip(src, dst, 1);
	return dst;
}

Mat vertical_reverse(Mat &src)
{
	Mat dst;
	flip(src, dst, 0);
	return dst;
}

Mat round_clip(Mat &src, Rect rect)
{
	int nRows = rect.height;
	int nCols = rect.width;
	double center_i = double(rect.height) / 2.0;
	double center_j = double(rect.width) / 2.0;
	cv::Mat dst(nRows, nCols, src.type(), cv::Scalar::all(0));
	for (int i = 0 ; i < nRows; i++)
	{
		for (int j = 0 ; j < nCols; j++)
		{
			double rate = double((i-center_i)*(i - center_i)) / double(nRows*nRows) + double((j-center_j)*(j-center_j))/double(nCols*nCols);
			if (rate <= double(0.25))
			{
				dst.at<cv::Vec3b>(i, j) = src.at<cv::Vec3b>(i + rect.y, j + rect.x);
			}
		}
	}
	return dst;
}