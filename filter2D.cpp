#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

/*
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
}*/

int main()
{
	Mat image = imread("../images/lena.jpg", IMREAD_GRAYSCALE);
	CV_Assert(image.data); //영상파일 예외 처리


	float data[] = { //sharpening 1
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0,
	};
	float data1[] = { //sharpening 2
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1,
	};

	Mat mask(3, 3, CV_32F, data); //mask matrix
	Mat mask1(3, 3, CV_32F, data1);
	Mat blur_img, sharpening1, sharpening2;
	/*filter(image, blur1, mask); //사용자 정의 함수(회선 수행)
	filter(image, sharpen, mask1);
	blur1.convertTo(blur1, CV_8U);
	sharpen.convertTo(sharpen, CV_8U);
	//imshow("image", image); imshow("blur1", blur1); imshow("sharpen", sharpen);
	*/
	/*blur(image, blur_img, Size(9, 9));//블러 마스크 사이즈 9X9
	GaussianBlur(image, gausBlur, Size(9, 9), 2.0, 2.0);//가우시안블러 마스크 사이즈 9X9
	//시그마 값 x, y 모두 2.0
	imshow("blur_img", blur_img); imshow("Gau", gausBlur); //openCV 제공 blur함수 이용
	*/

	filter2D(image, sharpening1, CV_32F, mask);
	sharpening1.convertTo(sharpening1, CV_8U);//sharpening1 imshow 할 수 있게 변환
	imshow("sharpening1", sharpening1);

	filter2D(image, sharpening2, CV_32F, mask1);
	sharpening2.convertTo(sharpening2, CV_8U);//sharpening2 imshow 할 수 있게 변환
	imshow("sharpening2", sharpening2);

	waitKey();
	return 0;

}
