#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<iostream>

using namespace cv;
using namespace std;
RNG rng(12345);

 Mat src_gray;
int thresh = 100;
void thresh_callback(int, void* )
{Mat a=imread("source.jpg",1);
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
   threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
  findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
  vector<vector<Point> > contours_poly( contours.size() );
  vector<Rect> boundRect( contours.size() );
   vector<Point2f>center( contours.size() );
    vector<float>radius( contours.size() );
  for( size_t i = 0; i < contours.size(); i++ )
  {
       approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
    boundRect[i] = boundingRect( Mat(contours_poly[i]) );
     minEnclosingCircle( contours_poly[i], center[i], radius[i] );
  }
   Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
  for( size_t i = 0; i< contours.size(); i++ )
  {
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    rectangle( a, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0 );}
    namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", a );
}
Mat dilation(Mat a,Mat b)
{int r=a.rows,c=a.cols;
  int i,j,k,l;
  for(i=1;i<r-1;i++)
    for(j=1;j<c-1;j++)
      {
	if(a.at<uchar>(i,j)==0)
	 for(k=i-1;k<=i+1;k++)
	    for(l=j-1;l<=j+1;l++)
	      { 
		    if(a.at<uchar>(k,l)==255)
                     b.at<uchar>(i,j)=255;
	 
	      }}
	return b;
} 
int main(int,char** argv)
{int z=0;int miny=9999;
  int maxx=-999999;

	  Point pt1, pt2;
	  Mat img = imread(argv[1], 1);
 int offset_x = 2;
    int offset_y = 2;
    cv::  Rect roi;
    roi.x = offset_x;
    roi.y = offset_y;
    roi.width = img.size().width - (offset_x*2);
    roi.height = img.size().height - (offset_y*2);
    Mat src;
    cvtColor(img(roi),src,CV_BGR2GRAY );
    float line1[2][2];
    Mat dst, cdst,cann;
     Canny(src, dst, 50, 200, 3); 
    cvtColor(dst, cdst, CV_GRAY2BGR); 
 
    vector<Vec2f> lines;
       HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 );
       for( size_t i = 0; i < lines.size(); i++ )
    { float rho = lines[i][0], theta = lines[i][1];
     if(theta==0)
	    {
	      if(miny>fabs(rho)&&rho!=0)
		{
	miny=rho;
		  line1[0][0]=theta;
		  line1[0][1]=rho;
		  }}
       if(theta>=CV_PI*90/180&&(theta<=CV_PI*90/180+.5))
	    {if(maxx<rho)
		{
		  maxx=rho;
                  line1[1][0]=theta;
		  line1[1][1]=rho;
		}}}


    for(int i=0;i<dst.rows;i++)
      for(int j=0;j<dst.cols;j++)
	{if(j-(line1[0][1]-5)>=0&&i-(line1[1][1]+5)<=0)
	    src.at<uchar>(i,j)=src.at<uchar>(0,0);
	}
    Canny(src, dst, 50, 200, 3);
    dst=dilation(dst,dst.clone());
    src_gray=dst;
     imwrite("source.jpg",img(roi));
    thresh_callback(0,0);
    waitKey();
    return 0;
}
