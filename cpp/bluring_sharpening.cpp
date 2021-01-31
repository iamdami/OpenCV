#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void filter(Mat img, Mat& dst, Mat mask) //회선 수행 함수
{
	dst = Mat(img.size(), CV_32F, Scalar(0)); //회선 결과 저장 행렬
	Point h_m = mask.size() / 2; //마스크 중심 좌표

	for (int i = h_m.y; i < img.rows - h_m.y; i++) { //입력 행렬 반복 순회
		for (int j = h_m.x; j < img.cols - h_m.x; j++)
		{
			float sum = 0;
			for (int u = 0; u < mask.rows; u++) { //마스크 원소 순회
				for (int v = 0; v < mask.cols; v++)
				{
					int y = i + u - h_m.y;
					int x = j + v - h_m.x;
					sum += mask.at<float>(u, v) * img.at<uchar>(y, x);
					//회선 수식
				}
			}
			dst.at<float>(i, j) = sum; //회선 누적값 출력화소 저장
		}
	}
}


int main()
{
	Mat image = imread("../images/lena.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data); //영상파일 예외 처리

	float data[] = { //bluring mask 
		1 / 9.f, 1 / 9.f, 1 / 9.f,
		1 / 9.f, 1 / 9.f, 1 / 9.f,
		1 / 9.f, 1 / 9.f, 1 / 9.f,
	};
	float data1[] = { //sharpening mask
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0,
	};

	Mat mask(3, 3, CV_32F, data); //mask matrix
	Mat mask1(3, 3, CV_32F, data1);
	Mat blur1, blur2, sharpen, blur_img, gausBlur;
	filter(image, blur1, mask); //사용자 정의 함수(회선 수행)
	filter(image, sharpen, mask1);
	blur1.convertTo(blur1, CV_8U);
	sharpen.convertTo(sharpen, CV_8U);
	imshow("image", image); imshow("blur1", blur1); imshow("sharpen", sharpen);

	waitKey();
	return 0;
}
