#define BOOST_TEST_MODULE cv_example
#include <boost/test/unit_test.hpp>
#include "opencv2/opencv.hpp"

using namespace std;

bool equal(const cv::Mat & a, const cv::Mat & b)
{
    if ( (a.rows != b.rows) || (a.cols != b.cols) )
        return false;
    cv::Scalar s = sum( a - b );
    cout<<s<<endl;
    return (s[0]==0) && (s[1]==0) && (s[2]==0);
}

BOOST_AUTO_TEST_SUITE(cv_example);
BOOST_AUTO_TEST_CASE(resize)
{
    cv::Mat srcMat;
    cv::Mat dstMat;

    cv::Mat ansMat;

    srcMat = cv::imread( IMG_PATH);

    cv::resize( srcMat, dstMat, cv::Size(srcMat.cols / 2, srcMat.rows / 2) );

    // cv::imwrite( RESIZED_IMG_PATH, dstMat);
    ansMat = cv::imread( RESIZED_IMG_PATH);

    BOOST_CHECK( equal( ansMat, dstMat ));

}


BOOST_AUTO_TEST_CASE(cvtColor)
{
    cv::Mat srcMat;
    cv::Mat dstMat;

    cv::Mat ansMat;

    srcMat = cv::imread( IMG_PATH);

    cv::cvtColor(srcMat, dstMat, cv::COLOR_BGR2YUV);
    // cv::imwrite( YUV_IMG_PATH, dstMat);

    ansMat = cv::imread(YUV_IMG_PATH);

    BOOST_CHECK( equal( ansMat, dstMat ));

}

BOOST_AUTO_TEST_SUITE_END();