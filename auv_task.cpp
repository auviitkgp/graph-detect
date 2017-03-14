#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace cv;

using namespace std;
int main(int argc, char *argv[])
{
	Mat img = imread(argv[1], 1);
	Mat img1 = imread(argv[1],1 );
	Mat grayimg= imread(argv[1], 0);
	Mat canny_output;
	int low_threshold=50;
	int high_threshold=100;
  Mat img_output;
	namedWindow("Output Image", WINDOW_AUTOSIZE);
	namedWindow("Canny", WINDOW_AUTOSIZE);
	Canny(img, canny_output, low_threshold, high_threshold);
	vector<Vec2f> lines;
	std::vector<Vec2f> o_lines;
	HoughLines(canny_output, lines, 0.01, CV_PI/180, 120);
	int count=0;
	for( size_t i = 0; i < lines.size(); i++ )
	{
  		float rho = lines[i][0], theta = lines[i][1];
  		double a = cos(theta), b = sin(theta);

  		float alpha=theta*180/CV_PI;
			if((fabs(alpha)==0 or fabs(alpha)==90 )){
				if (rho>7 and rho<img.rows-7) {
				o_lines.push_back(lines[i]);
				// cout<<"The lines parallel to axes have rho and angle: "<<o_lines[i]<<'\n';
				count++;
			}
	}
}

// The crux of the code lies in here.
// We separated the borders lines from the image which hampered in the processing of the HoughLines.
// Then we minimized the X coordinates of lines (Provided the lines have slope either Infinity or O)
// to find the X-axis and maximized the Y coordinates of lines to find the Y-axis. Hence we found the
// Origin.

Point pt1, pt2;
Point px1, py1, px2, py2;
Point origin;
px1.x=999999;
px1.y=1000;
py1.x=1000;
py1.y=-923;
	for( size_t i = 0; i<o_lines.size(); i++){

			float rho = o_lines[i][0], theta = o_lines[i][1];
			int j= (int)i;
			double a = cos(theta), b = sin(theta);

			float alpha=theta*180/CV_PI;
			double x0 = a*rho, y0 = b*rho;
  		pt1.x = cvRound(x0 + 1000*(-b));
  		pt1.y = cvRound(y0 + 1000*(a));
  		pt2.x = cvRound(x0 - 1000*(-b));
 			pt2.y = cvRound(y0 - 1000*(a));
 			//cout<<"This is x coord: "<<pt1<<'\n';
  		// cout<<"This is y coord: "<< pt2<<'\n';
			if(alpha==0){
				if(px1.x>pt1.x){
					px1.x=pt1.x;
				}
			}
				if(alpha==90){
					if(py1.y<pt2.y){
						py1.y=pt2.y;
						cout<<py1<<'\n';
					}
				}
			}

		px2.x=px1.x;
		px2.y=-1000;
		py2.y=py1.y;
		py2.x=-1000;
		cout<<py1<<'\n';
		cout<<px1<<'\n';
   	line( img1, px1, px2, Scalar(0,0,255), 1, 8);
		line(img1, py1, py2, Scalar(0,255,0), 1, 8);
		origin.x=px2.x;
		origin.y=py2.y;
		cout<<origin<<'\n';
		vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;
		if (origin.x>500){
			origin.x=img.cols/5;
		}
		if (origin.y<=0){
			origin.y=img.rows-img.rows/5;
		}
 		//  This Part of code was used to detect and print contours in an image.
		// 	This code is commented to show the flow of code.

		findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
		Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  	for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( 0, 255, 0 );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }
		 for(size_t i=0; i<contours.size(); i++){
		 cout<<contours[i]<<'\n';
	 }
	 Mat connect;

	 for(int i=0; i<contours.size(); i++ ){
		 int flag=0;
		 for(int j=0; j<contours[i].size(); j++){
			 if(contours[i][j].x-2>origin.x or contours[i][j].x==1 or contours[i][j].x+1==img.cols ){//contours[i][j].y<origin.y  ){
				// cout<<"This is the x coordinate of the contour points:  "<<contours[i][j].x<<'\n';
				//  cout<<"This is the y coordinate of the contour points:  "<<contours[i][j].y<<'\n';
				//  cout<< "This is the y coordinate of the origin point : "<<origin.y<<'\n';
				 //  cout<<"This is the x coordinate of the origin point :  "<<origin.x<<'\n';
				 flag=1;
				 break;
			 }
		 }
		 if(flag==0 ){
			 Rect boundRect= boundingRect( Mat(contours[i]) );
			 cout<<"This is the hierarchy matrix"<<hierarchy[i]<<'\n';
			 Scalar color= Scalar(0,255,0);
			 rectangle( img1, boundRect.tl(), boundRect.br(), color, 1, 8, 0 );
		 }
	 }

	 for(int i=0; i<contours.size(); i++ ){
		 int flag=0;
		 for(int j=0; j<contours[i].size(); j++){
			 if(contours[i][j].y+2<origin.y or contours[i][j].y==1 or contours[i][j].y+1==img.rows ){//contours[i][j].y<origin.y  ){
				 //cout<<"This is the x coordinate of the contour points:  "<<contours[i][j].x<<'\n';
				 //cout<<"This is the y coordinate of the contour points:  "<<contours[i][j].y<<'\n';
				//  cout<< "This is the y coordinate of the origin point : "<<origin.y<<'\n';
				 //  cout<<"This is the x coordinate of the origin point :  "<<origin.x<<'\n';
				 flag=1;
				 break;
			 }
		 }
		 if(flag==0 ){

			 Rect boundRect= boundingRect( Mat(contours[i]) );
			 cout<<"This is the hierarchy matrix"<<hierarchy[i]<<'\n';

			 Scalar color= Scalar(0,255,0);
			 rectangle( img1, boundRect.tl(), boundRect.br(), color, 1 );
		 }
	 }

	imshow("Contours", drawing);
	imshow("Original", grayimg);
	imshow("Canny", canny_output);
	imshow("Output Image", img1);
	waitKey(0);
	return 0;
}
