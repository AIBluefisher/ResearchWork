#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <vector>


using namespace std;
using namespace cv;

#define __DEBUG__ 1



void startMatch(Mat img1, Mat img2, vector<KeyPoint>& kpts1, vector<KeyPoint>& kpts2)
{
    // feature detect
    Ptr<ORB> orb = ORB::create(500, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);

    orb->detect(img1, kpts1);
    orb->detect(img2, kpts2);

#ifdef __DEBUG__
    Mat outImg1;
    drawKeypoints(img1, kpts1, outImg1);
    Mat outImg2;
    drawKeypoints(img2, kpts2, outImg2);
#endif
    
    // descriptor compute
    Mat descriptor1, descriptor2;
    orb->compute(img1, kpts1, descriptor1);
    orb->compute(img2, kpts2, descriptor2);

    // feature match
    vector<DMatch> matches;
    BFMatcher matcher( NORM_HAMMING );
    matcher.match(descriptor1, descriptor2, matches);

    double minDist = 10000, maxDist = 0;
    for(int i = 0; i < descriptor1.rows; i++)
    {
        double dist = matches[i].distance;
        minDist = min(minDist, dist);
        maxDist = max(maxDist, dist);
    }

    // 筛选好的匹配点
    vector<DMatch> goodMatches;
    for(int i = 0; i < descriptor1. rows; i++)
    {
        if(matches[i].distance <= max(2 * minDist, 30.0) ) goodMatches.push_back(matches[i]);
    }
    
#ifdef __DEBUG__
    // draw match points
    Mat matchPoints;
    drawMatches(img1, kpts1, img2, kpts2, matches, matchPoints);
    imshow("match points", matchPoints);
#endif
}



int main()
{
    Mat img1 = imread("/home/chenyu/图片/david/B00.jpg");
    Mat img2 = imread("/home/chenyu/图片/david/B01.jpg");
    
    vector<KeyPoint> kpts1;
    vector<KeyPoint> kpts2;
    // feature detect
    Ptr<ORB> orb = ORB::create(500, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);
    
        orb->detect(img1, kpts1);
        orb->detect(img2, kpts2);
    
    #ifdef __DEBUG__
        Mat outImg1;
        drawKeypoints(img1, kpts1, outImg1);
        Mat outImg2;
        drawKeypoints(img2, kpts2, outImg2);
    #endif
        
        // descriptor compute
        Mat descriptor1, descriptor2;
        orb->compute(img1, kpts1, descriptor1);
        orb->compute(img2, kpts2, descriptor2);
    
        // feature match
        vector<DMatch> matches;
        BFMatcher matcher( NORM_HAMMING );
        matcher.match(descriptor1, descriptor2, matches);
    
        double minDist = 10000, maxDist = 0;
        for(int i = 0; i < descriptor1.rows; i++)
        {
            double dist = matches[i].distance;
            minDist = min(minDist, dist);
            maxDist = max(maxDist, dist);
        }
    
        // 筛选好的匹配点
        vector<DMatch> goodMatches;
        for(int i = 0; i < descriptor1. rows; i++)
        {
            if(matches[i].distance <= max(2 * minDist, 30.0) ) goodMatches.push_back(matches[i]);
        }
        
    #ifdef __DEBUG__
        // draw match points
        Mat matchPoints;
        drawMatches(img1, kpts1, img2, kpts2, matches, matchPoints);
        imshow("match points", matchPoints);
    #endif
    
    waitKey();
}