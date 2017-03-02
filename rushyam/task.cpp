#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "iostream"
using namespace cv;
using namespace std;


int main()
{
  Mat edit=imread("test2.jpg");
  Mat edit1(edit.rows,edit.cols,CV_8UC3,Scalar(0,0,0));
  Mat edit2(edit.rows,edit.cols,CV_8UC3,Scalar(0,0,0));
  Mat img(edit.rows,edit.cols,CV_8UC1,Scalar(255));
  int i,j,k=0;
  for(i=0;i<img.rows;i++)
    {
      for(j=0;j<img.cols;j++)
	{
	 int x=edit.at<Vec3b>(i,j)[0]+edit.at<Vec3b>(i,j)[1]+edit.at<Vec3b>(i,j)[2];
	 img.at<uchar>(i,j)=x/3;
	}
    }
  
 for(i=img.rows-10;i>=0;i--)
    {
      k=0;
      for(j=0;j<img.cols;j++)
 	{
 	      if(img.at<uchar>(i,j)==0)
 	        k++;
      	} 
      if(k>=50)
 	break;
    }

  int y=i;
  cout<<y<<endl;
  namedWindow("graph",WINDOW_NORMAL);
  for(j=5;j<img.cols;j++)
    {
      k=0;
      for(i=5;i<img.rows;i++)
 	{
 	  if(img.at<uchar>(i,j)<=30)
 	    k++;
 	}
      if(k>=50)
 	break;
    }
  int x=j;
  cout<<x<<endl;
 for(i=0;i<img.rows;i++)
    {
      for(j=30;j<x-5;j++) 
 	{
 	  if(img.at<uchar>(i,j)<=100)
 	    {
 	      for(int a=0;a<2;a++)					
 	      	   img.at<uchar>(i,j+a)=0;
     
	    
 	    }
 	}
    }

  for(i=y+6;i<y+25;i++)
    {
      for(j=10;j<img.cols-40;j++)
 	{
 	  if(img.at<uchar>(i,j)<=100)
 	    {
 		img.at<uchar>(i+1,j)=0;
 	    }
 	}
    }
  for(i=0;i<y+5;i++)
    {
      for(j=x-5;j<img.cols;j++)
	{
	  img.at<uchar>(i,j)=255;
	}
    }
  
  for(i=0;i<img.rows;i++)
    {
      for(j=0;j<img.cols;j++)
	{
	  if(img.at<uchar>(i,j)==0)
	    {
	      edit1.at<Vec3b>(i,j)[2]=255;
              edit1.at<Vec3b>(i,j)[1]=255;
	      edit1.at<Vec3b>(i,j)[0]=0;
	    }
	}
    }
  for(i=0;i<img.rows;i++)
    {
      for(j=0;j<img.cols;j++)
  	{
	  if( edit1.at<Vec3b>(i,j)[1]!=255 && edit1.at<Vec3b>(i,j)[2]!=255)
	    {
	      for(int a=0;a<3;a++)
	      edit2.at<Vec3b>(i,j)[a]= edit.at<Vec3b>(i,j)[a];
	      continue;
	    }
	   for(int a=0;a<3;a++)
	     edit2.at<Vec3b>(i,j)[a]=0.4*edit.at<Vec3b>(i,j)[a]+0.6*edit1.at<Vec3b>(i,j)[a];
	}
    }
             
 
 imshow("graph",edit2);
 waitKey(0);
  return 0;
}  
