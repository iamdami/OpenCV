#include "opencv2/opencv.hpp"
#include <iostream>
 
using namespace cv;
using namespace std;
 
void overlayImage(Mat& src, const Mat& over, const Point& pos)
{
    CV_Assert(src.type() == CV_8UC3);
    CV_Assert(over.type() == CV_8UC4);
 
    int sx = std::max(pos.x, 0);
    int sy = std::max(pos.y, 0);
    int ex = std::min(pos.x + over.cols, src.cols);
    int ey = std::min(pos.y + over.rows, src.rows);
 
    for (int y = sy; y < ey; y++) {
        int y2 = y - pos.y; // y coordinate in overlay image
 
        Vec3b* pSrc = src.ptr<Vec3b>(y);
        const Vec4b* pOvr = over.ptr<Vec4b>(y2);
 
        for (int x = sx; x < ex; x++) {
            int x2 = x - pos.x; // x coordinate in overlay image
 
            float alpha = (float)pOvr[x2][3] / 255.f;
 
            if (alpha > 0.f) {
                pSrc[x][0] = saturate_cast<uchar>(pSrc[x][0] * (1.f - alpha) 
                        + pOvr[x2][0] * alpha);
                pSrc[x][1] = saturate_cast<uchar>(pSrc[x][1] * (1.f - alpha) 
                        + pOvr[x2][1] * alpha);
                pSrc[x][2] = saturate_cast<uchar>(pSrc[x][2] * (1.f - alpha) 
                        + pOvr[x2][2] * alpha);
            }
        }
    }
}
 
int main()
{
    Mat src = imread("PutPic.jpg", IMREAD_COLOR);
    Mat cat = imread("cat.png", IMREAD_UNCHANGED);
 
    if (src.empty() || cat.empty()) {
        cerr << "Image load failed!" << endl;
        return -1;
    }
 
    CascadeClassifier face_cascade("haarcascade_frontalface_default.xml");
 
    if (face_cascade.empty()) {
        cerr << "Failed to open (face) xml file!" << endl;
        return -1;
    }
 
    vector<Rect> faces;
    face_cascade.detectMultiScale(src, faces);
 
    for (Rect face : faces) {
        float fx = float(face.width) / cat.cols;
 
        Mat tmp;
        resize(cat, tmp, Size(), fx, fx);
 
        Point pos(face.x, face.y - face.height / 3);
        overlayImage(src, tmp, pos);
    }
 
    imshow("src", src);
 
    waitKey(0);
    return 0;
}
