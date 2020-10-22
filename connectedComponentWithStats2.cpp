#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat src1 = imread("../images/keyboard.bmp", IMREAD_GRAYSCALE);

	Mat bin; 
	threshold(src1, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//otsu 알고리즘 사용해 임계값 자동 계산
	Mat labels, stats1, centroids1; 
	int cnt = connectedComponentsWithStats(bin, labels, stats1, centroids1); 
	// 연결 요소 계산해주는 함수. 개수 리턴. 통계내줌
	Mat dst;
	cvtColor(src1, dst, COLOR_GRAY2BGR);//색상을 BGR값으로 변환. 결과를 컬러로 보기 위함
	
	for (int i = 1; i < cnt; i++) { //레벨0은 배경이기 때문에 i=1
		double *p_c = centroids1.ptr<double>(i); //centroids1에 ptr로 접근한 값을 포인터에 넣어주기
		if (p_c[2] < 10) continue;
		//그레이스케일 한 것과 픽셀(1이 되는 개수)이 10보다 작으면 컨티뉴
//		if (*(p + 4) < 20) continue;
		//포인터에 넣어준 값(*p)은 p[4] 나 *(p+4) 중 어떤 것을 사용해도 같은 결과 출력
    
		circle(dst, Point(p_c[0],p_c[1]), i/2, Scalar(0, 0, 255), 2);
	}   //Scalar(0, 0, 255) 는 색 지정(빨간색), 2는 선의 두께

	imshow("dst", dst);

	waitKey();
	return 0;
}
