#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv/cv.h"
#include <bits/stdc++.h>


//#define INPUT_FILE              "../input.jpg"
#define OUTPUT_FOLDER_PATH      string("")

using namespace std;
using namespace cv;
char  *INPUT_FILE;
Point findIntersection(Point p1,Point p2,Point p3,Point p4) //finds and returns intersection point between two lines
{
  float xD1,yD1,xD2,yD2,xD3,yD3;
  float dot,deg,len1,len2;
  float segmentLen1,segmentLen2;
  float ua,ub,div;
  Point def;  //for default in case of invalid intersection
  def.x=0;
  def.y=INT_MAX;  
  // calculate differences
  xD1=p2.x-p1.x;
  xD2=p4.x-p3.x;
  yD1=p2.y-p1.y;
  yD2=p4.y-p3.y;
  xD3=p1.x-p3.x;
  yD3=p1.y-p3.y;

  // calculate the lengths of the two lines
  len1=sqrt(xD1*xD1+yD1*yD1);
  len2=sqrt(xD2*xD2+yD2*yD2);

  // calculate angle between the two lines.
  dot=(xD1*xD2+yD1*yD2); // dot product
  deg=dot/(len1*len2);

  // if abs(angle)==1 then the lines are parallell,
  // so no intersection is possible,return default
  if(abs(deg)==1)
    return def;

  // find intersection Pt between two lines
  Point pt;
  pt.x=0;
  pt.y=0;
  
  div=yD2*xD1-xD2*yD1;
  ua=(xD2*yD3-yD2*xD3)/div;
  ub=(xD1*yD3-yD1*xD3)/div;
  pt.x=p1.x+ua*xD1;
  pt.y=p1.y+ua*yD1;

  // calculate the combined length of the two segments
  // between Pt-p1 and Pt-p2
  xD1=pt.x-p1.x;
  xD2=pt.x-p2.x;
  yD1=pt.y-p1.y;
  yD2=pt.y-p2.y;
  segmentLen1=sqrt(xD1*xD1+yD1*yD1)+sqrt(xD2*xD2+yD2*yD2);

  // calculate the combined length of the two segments
  // between Pt-p3 and Pt-p4
  xD1=pt.x-p3.x;
  xD2=pt.x-p4.x;
  yD1=pt.y-p3.y;
  yD2=pt.y-p4.y;
  segmentLen2=sqrt(xD1*xD1+yD1*yD1)+sqrt(xD2*xD2+yD2*yD2);

  // if the lengths of both sets of segments are the same as
  // the lenghts of the two lines the point is actually
  // on the line segment.

  // if the point is on the line, return default
  if(abs(len1-segmentLen1)>0.01 || abs(len2-segmentLen2)>0.01)
    return def;

  // return the valid intersection
  return pt;
}

float calc_dist(Point a,Point b) //calculates the distance between two points
{
  float ret=sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
  return ret;
}

std::pair <int,int> find_origin()
{

  Mat src=imread(INPUT_FILE);
  Mat odst,odst2;
  
  Canny(src,odst,50,200,3);

  
  cvtColor(odst,odst2,CV_GRAY2BGR);
  vector<Vec4i> lines;
  vector<Vec2f> lines2;
  

  HoughLines(odst,lines2,0.25,CV_PI/180,120,0,0);
  
  vector<Point > o_store;

  for(size_t i=0;i<lines2.size();i++)
    {
      float rho =lines2[i][0] ,theta=lines2[i][1];
      Point pt1,pt2;
      double a =cos(theta),b=sin(theta);
      double x0=a*rho,y0=b*rho;

      pt1.x=cvRound(x0+1000*(-b));
      pt1.y=cvRound(y0+1000*(a));

      pt2.x = cvRound(x0 - 1000*(-b));
      pt2.y = cvRound(y0 - 1000*(a));
      
      line(odst,pt1,pt2,255,1,CV_AA);
      
    }

  HoughLinesP(odst,lines,1,CV_PI/180,100,120,10);
  
  if(lines.size()>0)
    {
      Point tmp;
      for(size_t i=0;i<lines.size()-1;i++)
	{
	  for(size_t j=i+1;j<lines.size();j++)
	    {
	      Vec4i l=lines[i];
	      Vec4i l2=lines[j];


	      
	      Point a;
	      a.x=l[0];
	      a.y=l[1];
	      Point b;
	      b.x=l[2];
	      b.y=l[3];


	      Point c;
	      c.x=l2[0];
	      c.y=l2[1];
	      Point d;
	      d.x=l2[2];
	      d.y=l2[3];

	      tmp=findIntersection(a,b,c,d);
	      o_store.push_back(tmp);
	    }
	}
    }

    for(size_t i=0;i<lines.size();i++)
    {
      Vec4i l=lines[i];
      line(odst2,Point(l[0],l[1]),Point(l[2],l[3]),Scalar(255,0,0),3,CV_AA);
      
    }
  
  Vec3b t;
  t[0]=0;
  t[1]=0;
  t[2]=255;
  for(int i=0;i<o_store.size();i++)
    {

      if(o_store[i].y<odst2.rows && o_store[i].x<odst2.cols)
	odst2.at<Vec3b>(o_store[i].y,o_store[i].x)= t;
    }
  pair<int ,int > ret;
  float min_dist=INT_MAX;
  cout<<"min_dist"<<min_dist<<endl;
  ret.first=0;
  ret.second=odst2.cols;
  
  for(int i=0;i<o_store.size();i++)
    {
      if(min_dist>calc_dist(o_store[i],Point(0,odst2.rows)))
	{
	  if(o_store[i].x >8 && o_store[i].x<(odst2.cols-8) && o_store[i].y<(odst2.rows-8) && o_store[i].y>8)
	    {
	      min_dist=calc_dist(o_store[i],Point(0,odst2.rows));
	      ret.first=o_store[i].y;
	      ret.second=o_store[i].x;
	    }
	}
    }

  return ret;

}

int main(int argc, char** argv)
{
  INPUT_FILE=argv[1];
  pair <int ,int > origin =find_origin();

  Mat large = imread(INPUT_FILE);
  Mat rgb=large;

  
  Mat small;
  cvtColor(rgb, small, CV_BGR2GRAY);
  
  // morphological gradient
  Mat grad,grad2;
  Mat morphKernel = getStructuringElement(MORPH_CROSS, Size(3,3));



  morphologyEx(small, grad, MORPH_GRADIENT, morphKernel);
  
  imshow("gradient",grad);
  waitKey(100);
  
  
  // binarize
  Mat bw;

  threshold(grad, bw,125, 255.0, THRESH_BINARY);
    
  // connect horizontally oriented regions
  Mat connected;
  morphKernel = getStructuringElement(MORPH_CROSS, Size(2, 2));
  morphologyEx(bw, connected, MORPH_CLOSE, morphKernel);
    
 
  // find contours
  Mat mask = Mat::zeros(bw.size(), CV_8UC1);
  vector<vector<Point > > contours;
  vector<Vec4i> hierarchy;
  
  findContours(connected, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
  imshow("connected",connected);
  waitKey(200);
  
  // filter contours
  for(int idx = 0; idx >= 0; idx = hierarchy[idx][0])
    {
      Rect rect = boundingRect(contours[idx]);
      Mat maskROI(mask, rect);
      maskROI = Scalar(0, 0, 0);
      // fill the contour
      drawContours(mask, contours, idx, Scalar(255, 255, 255), CV_FILLED);
      // ratio of non-zero pixels in the filled region
      double r = (double)countNonZero(maskROI)/(rect.width*rect.height);

      if (r > .20 /* assume at least 45% of the area is filled if it contains text */
	              &&
	  (rect.height > 3 && rect.width > 3) /* constraints on region size */
	  /* these two conditions alone are not very robust. better to use something 
	     like the number of significant peaks in a horizontal projection as a third condition */
	  && rect.height*rect.width<0.2*(rgb.cols*rgb.rows) )
	{
	  if(rect.x<origin.second || rect.y>origin.first)
	    rectangle(rgb, rect, Scalar(0, 255, 0), 1);
	}
    }

  Point cent;
  cent.x=origin.second;
  cent.y=origin.first;
  
  circle(rgb,cent,3,Scalar(0,0,255),2,8,0);
  
  imwrite(OUTPUT_FOLDER_PATH + string("rgb.jpg"), rgb);
  cout<<endl<<"detected origin (x,y) :"<<origin.second<<","<<origin.first<<endl;
  imshow("output",rgb);
  waitKey(0);
  return 0;
}
