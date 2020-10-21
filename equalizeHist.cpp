#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(void)
{
    Mat src = imread("../images/obama.jpg", IMREAD_COLOR);

    Mat src_ycrcb;
    cvtColor(src, src_ycrcb, COLOR_BGR2YCrCb); //RGB에서 YCbCr로 변환

    vector<Mat> ycrcb_planes;
    split(src_ycrcb, ycrcb_planes); //YCrCb 채널 분할

    equalizeHist(ycrcb_planes[0], ycrcb_planes[0]); //0번째인 Y에 히스토그램 평활화 수행

    Mat dst_ycrcb; 
    merge(ycrcb_planes, dst_ycrcb); //평활화된 벡터 합치기

    Mat dst;
    cvtColor(dst_ycrcb, dst, COLOR_YCrCb2BGR); //합쳐진 영상을 다시 RGB로 변환

    imshow("src", src);
    imshow("dst", dst);

    waitKey(0);
    return 0;
}
