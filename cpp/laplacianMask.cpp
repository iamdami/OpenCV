#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    Mat src = imread("../lena.jpg");
    Mat dst; 
    Mat kernel = (Mat_<float>(3, 3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);
    // Apply Laplacian filter mask
    cv::filter2D(src, dst, src.depth(), kernel);

    imshow("image", src);
    imshow("sharpened lena", dst);
    waitKey();
    return 0;
}
