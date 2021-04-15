#include "opencv2/opencv.hpp"


int main()
{
    cv::Mat srcMat;


    srcMat = cv::imread( IMG_PATH);
    cv::Rect block(cv::Point(650, 120), cv::Point(1411, 684));
    cv::Mat tmp(srcMat, block);
    
    cv::Mat dstMat(srcMat.rows, srcMat.cols, srcMat.type(), (0,0,0));
    cv::Mat tmp2(dstMat, block);

    tmp.copyTo(tmp2);
    cv::imwrite( OUTPUT_IMG_PATH, dstMat);
}