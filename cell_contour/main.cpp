//
//  main.cpp
//  cell_contour
//
//  Created by Calvin CK Tai on 6/19/18.
//  Copyright © 2018 intern. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
int main()
{
    
    // 读取图片
    Mat image;
    image = imread("/Users/cktai/desktop/cell.jpeg");
    
    // 将图片灰化
    Mat gray;
    cvtColor(image,gray,COLOR_BGR2GRAY);

//    // 膨胀处理
//    Mat dilated;
//    Mat element = getStructuringElement(MORPH_ELLIPSE,Size(2,2),Point(-1,-1));
//
//    dilate(gray,dilated,element);
//    namedWindow("Dilated",WINDOW_AUTOSIZE);
//    imshow("Dilated",dilated);
    
    // 取轮廓
    Mat bin_image;
    threshold(gray,bin_image,128,255,THRESH_OTSU);
    std::vector<std::vector<Point>> contours;
    std::vector<Vec4i>hierarchy;
    findContours(bin_image,contours,hierarchy,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
    std::vector<Rect> boundRect(contours.size());
    
    for (int i=0; i < contours.size(); i++)
    {
        boundRect[i] = boundingRect(Mat(contours[i]));
    }
    
    // 描绘轮廓
    Mat result;
    image.copyTo(result);
    namedWindow("Unmarked result",WINDOW_AUTOSIZE);
    imshow("Result unmarked",result);
    drawContours(result,contours,-1, Scalar(0,255,0));
    for (int i=0; i<contours.size();i++){
        rectangle(result,boundRect[i].tl(),boundRect[i].br(), Scalar(0,255,0), 1, 8, 0);
    }
    
    // 矩形
    

    // 写出结果
    namedWindow("Contours", WINDOW_AUTOSIZE);
    imshow("Contours", result);
    imwrite("/Users/cktai/desktop/result.jpeg",result);
    
    waitKey(0);
    return 0;
}
