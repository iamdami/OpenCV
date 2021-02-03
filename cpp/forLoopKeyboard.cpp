
int main()
{
	Mat src1 = imread("../images/keyboard.bmp", IMREAD_GRAYSCALE);
	//키보드 이미지 그레이스케일로 읽어오기
	if (src1.empty()) {
		cerr << "Image Load Failed" << endl;
		return -1;
	} //소스파일 비어있으면 로드 실패 문구 띄우기

	imshow("src1", src1);//키보드 이미지 그레이스케일한 이미지 출력
	Mat bin; //bin 행렬 변수 생성
	threshold(src1, bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
	//otsu 알고리즘 사용해 임계값 자동 계산
	Mat labels, stats1, centroids1; //행렬 변수 생성
	int cnt = connectedComponentsWithStats(bin, labels, stats1, centroids1); 
	// 연결 요소 계산해주는 함수. 개수 리턴. 통계내줌
	Mat dst; //dst 행렬 변수 생성
	cvtColor(src1, dst, COLOR_GRAY2BGR);//색상을 BGR값으로 변환. 결과를 컬러로 보기 위함

	for (int i = 1; i < cnt; i++) { //레벨0은 배경이기 때문에 i=1
		int *p = stats1.ptr<int>(i); //stats에 ptr로 접근한 값을 포인터에 넣어주기
		if (p[4] < 10) continue;
		//그레이스케일 한 것과 픽셀(1이 되는 개수)이 10보다 작으면 컨티뉴
//		if (*(p + 4) < 20) continue;
		//포인터에 넣어준 값(*p)은 p[4] 나 *(p+4) 중 어떤 것을 사용해도 같은 결과 출력
		rectangle(dst, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 0, 255), 2);
		//p[0]과 p[1]은 각각 사각형의 x좌표와 y좌표.
		//p[2]와 p[3]은 각각 width와 height.
	}   //Scalar(0, 0, 255) 는 색 지정(빨간색), 2는 선의 두께
	cout << "Stats:\n " << stats1 << endl;//stats 값 출력
	cout << "centroids:\n " << centroids1 << endl;//centroids값 출력
	imshow("dst", dst); //dst 출력

	waitKey();
	return 0;
}
