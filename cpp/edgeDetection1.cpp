#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void sobel_derivative()
{
	Mat src = imread("../images/lena.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	// Mat_ 는 영상 쉽게 읽을 수 있게(Mat 상속받은 클래스)
	Mat mx = Mat_<float>({ 1, 3 }, { -1 / 2.f, 0, 1 / 2.f });
	Mat my = Mat_<float>({ 3, 1 }, { -1 / 2.f, 0, 1 / 2.f });

	cout << "mx = " << mx << endl;
	cout << "my = " << my << endl;

	float my1[] = { -1, -2, -1,
		             0,  0,  0,
		             1,  2,  1 };

	Mat dx, dy, dy1;
	Mat my1_filter(3, 3, CV_32F, my1);
	// 필터 쉽게 적용할 수 있는 함수
	filter2D(src, dx, -1, mx, Point(-1, -1), 0); //-1은 소스와 같은 데이터타입 쓰겠다는 것
	filter2D(src, dy, -1, my, Point(-1, -1), 128); //0과 128은 색상 농도(?)
	filter2D(src, dy1, CV_32F, my1_filter, Point(-1, -1));
	dy1.convertTo(dy1, CV_8U); // 영상을 그림으로 보기 위해 변환

	imshow("src", src);
	imshow("dx", dx); imshow("dy", dy);
	imshow("dy1", dy1);

	waitKey();
	destroyAllWindows();
}

void sobel_edge() // 소벨 직접 쓰는 것
{
	Mat src = imread("../images/lena.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat dx, dy; // 결과 담기
	Sobel(src, dx, CV_32FC1, 1, 0); // x방향으로
	Sobel(src, dy, CV_32FC1, 0, 1); // y방향으로

	Mat fmag, mag;
	magnitude(dx, dy, fmag); // dx와 dy 결과가 fmag에 들어감
	fmag.convertTo(mag, CV_8UC1); // 변환

	Mat edge = mag > 150; // 150보다 큰 것만 결과값 보기

	imshow("src", src);
	imshow("mag", mag);
	imshow("edge", edge);

	waitKey();
	destroyAllWindows();
}

void canny_edge()
{
	Mat src = imread("../images/lena.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
	Mat dst1, dst2;
	Canny(src, dst1, 50, 100);
	Canny(src, dst2, 50, 150);
	// 소스, 결과, 낮은 임계값, 높은 임계값

	imshow("src", src);
	imshow("dst1", dst1);
	imshow("dst2", dst2);

	waitKey();
	destroyAllWindows();
}

void laplacian_edge()
{
	Mat src, dst;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_32F;	// 결과 영상에 대한 깊이 CV_16S
	src = imread("../images/lena.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Mat abs_dst;
	Laplacian(src, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	// 소스, 결과, 결과 영상의 자료 타입, 커널 사이즈, 스케일, 델타
	convertScaleAbs(dst, abs_dst);
	// 영상 보기 위해 Uchar 형태로 변환

	imshow("Image", src);
	imshow("Laplacian", abs_dst);
	waitKey(0);
	destroyAllWindows();
}

int main()
{
	sobel_derivative();
	sobel_edge();
	laplacian_edge();
	canny_edge();

	return 0;
}
