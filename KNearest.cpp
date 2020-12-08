#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/ml.hpp>
using namespace std;
using namespace cv;
using namespace cv::ml;
 
int main()
{
Mat train_features(5, 2, CV_32FC1);
Mat labels(5, 1, CV_32FC1);
 
// input coordinate of to train_features
train_features.at<float>(0, 0) = 10, train_features.at<float>(0, 1) = 10;
train_features.at<float>(1, 0) = 10, train_features.at<float>(1, 1) = 20;
train_features.at<float>(2, 0) = 20, train_features.at<float>(2, 1) = 10;
train_features.at<float>(3, 0) = 30, train_features.at<float>(3, 1) = 30;
train_features.at<float>(4, 0) = 40, train_features.at<float>(4, 1) = 30;
 
// input labels
labels.at<float>(0, 0) = 1;
labels.at<float>(1, 0) = 1;
labels.at<float>(2, 0) = 1;
labels.at<float>(3, 0) = 2;
labels.at<float>(4, 0) = 2;
 
// learning process
Ptr<ml::KNearest> knn = ml::KNearest::create();
Ptr<ml::TrainData> trainData = ml::TrainData::create(train_features, ROW_SAMPLE, labels);
knn->train(trainData);
 
// test process
Mat sample(1, 2, CV_32FC1);
Mat predictedLabels;
 
// input test data
sample.at<float>(0, 0) = 28, sample.at<float>(0, 1) = 28;
knn->findNearest(sample, 2, predictedLabels); // 2 is # of neighbor used, if k increase, classificaton can be enhancing.
 
float prediction = predictedLabels.at<float>(0, 0);
cout << "Test Sample's Label = " << prediction << endl;
 
return 0;
}
