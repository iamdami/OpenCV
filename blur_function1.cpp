#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


int main()
{
	Mat image = imread("../images/lena.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data); //영상파일 예외 처리

	blur(image, blur_img, Size(9, 9));//블러 마스크 사이즈 9X9
	GaussianBlur(image, gausBlur, Size(9, 9), 2.0, 2.0);//가우시안블러 마스크 사이즈 9X9
	//시그마 값 x, y 모두 2.0
	imshow("blur_img", blur_img); imshow("Gau", gausBlur); //openCV 제공 blur함수 이용

	waitKey();
	return 0;
}
