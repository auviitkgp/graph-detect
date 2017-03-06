#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <queue>
#include <stack>
#include<math.h>
using namespace cv;
using namespace std;
 
stack<Point> s;
stack<Point> v;
stack<Point>a;
Point toppoint;

Mat canny_image = imread("C:\\Users\\Aakash Naik\\Desktop\\input2.jpg");
Mat canny_output = imread("C:\\Users\\Aakash Naik\\Desktop\\input2.jpg");
Mat canny_output2(canny_image.rows, canny_image.cols, 0);
Mat canny_output3(canny_image.rows, canny_image.cols, 0);
Mat canny_output4(canny_image.rows, canny_image.cols, 0);




int main()
{
	int bg_v = 238;
	namedWindow("output", WINDOW_AUTOSIZE);
	int sum_r = 0, sum_g = 0, sum_b = 0;
	for (int i = 0; i < canny_image.rows; i++)
	{
		for (int j = 0; j < canny_image.cols; j++)
		{
			sum_r += canny_image.at<Vec3b>(i, j)[2];
			sum_g += canny_image.at<Vec3b>(i, j)[1];
			sum_b += canny_image.at<Vec3b>(i, j)[0];
		}
	}
	sum_r = (int)(1.0*sum_r / (canny_image.rows*canny_image.cols));
	sum_g = (int)(1.0*sum_g / (canny_image.rows*canny_image.cols));
	sum_b = (int)(1.0*sum_b / (canny_image.rows*canny_image.cols));


	for (int i = 0; i < canny_image.rows; i++)
	{
		for (int j = 0; j < canny_image.cols; j++)
		{
			/*if ((abs(canny_image.at<Vec3b>(i, j)[2] - canny_image.at<Vec3b>(i, j)[0])) +(abs(canny_image.at<Vec3b>(i, j)[2] - canny_image.at<Vec3b>(i, j)[1])) +(abs(canny_image.at<Vec3b>(i, j)[1]-canny_image.at<Vec3b>(i, j)[0]))>40)
			{
			canny_image.at<Vec3b>(i, j)[2] = sum_r;
			canny_image.at<Vec3b>(i, j)[1] = sum_g;
			canny_image.at<Vec3b>(i, j)[0] = sum_b;

			}
			else*/
			{
				if (abs(canny_image.at<Vec3b>(i, j)[2] - canny_image.at<Vec3b>(i, j)[1]) > 17 || abs(canny_image.at<Vec3b>(i, j)[2] - canny_image.at<Vec3b>(i, j)[0]) > 17)
				{
					canny_image.at<Vec3b>(i, j)[2] = 255;
					canny_image.at<Vec3b>(i, j)[1] = 255;
					canny_image.at<Vec3b>(i, j)[0] = 255;
				}
				else

				if (canny_image.at<Vec3b>(i, j)[2] > 220)
				{
					canny_image.at<Vec3b>(i, j)[2] = 255;
					canny_image.at<Vec3b>(i, j)[1] = 255;
					canny_image.at<Vec3b>(i, j)[0] = 255;
				}
				else
				{
					canny_image.at<Vec3b>(i, j)[2] = 0;
					canny_image.at<Vec3b>(i, j)[1] = 0;
					canny_image.at<Vec3b>(i, j)[0] = 0;

				}

			}
		}
	}


	for (int i = 0; i < canny_output2.rows; i++)
	{
		int count_h = 0;
		int count_v = 0;

		for (int j = 0; j < canny_output2.cols; j++)
		{
			count_v = 0;
			if (canny_image.at<Vec3b>(i, j)[2] == 0)
			{

				count_v++;

				s.push(Point(i, j));
				v.push(Point(i, j));

				int q = 1;

				while (!s.empty())
				{
					toppoint = s.top();
					s.pop();
					if (toppoint.y + q < canny_image.cols)
					{
						if (canny_image.at<Vec3b>(toppoint.x, toppoint.y + q)[2] == 0)
						{

							s.push(Point(toppoint.x, toppoint.y + q));
							v.push(Point(toppoint.x, toppoint.y + q));
							count_v++;


						}
					}
				}

			}

			if (count_v > 20)
			{
				while (!v.empty())
				{
					Point point = v.top();

					canny_image.at<Vec3b>(point.x, point.y)[2] = 255;
					canny_image.at<Vec3b>(point.x, point.y)[1] = 255;
					canny_image.at<Vec3b>(point.x, point.y)[0] = 255;
					v.pop();
				}
			}
			else
			{
				while (!v.empty())
					v.pop();
			}
			///////////////////////////

			count_h = 0;
			if (canny_image.at<Vec3b>(i, j)[2] == 0)
			{

				count_h++;

				s.push(Point(i, j));
				v.push(Point(i, j));

				int q = 1;

				while (!s.empty())
				{
					toppoint = s.top();
					s.pop();
					if (toppoint.x + q < canny_image.rows)
					{
						if (canny_image.at<Vec3b>(toppoint.x + q, toppoint.y)[2] == 0)
						{

							s.push(Point(toppoint.x + q, toppoint.y));
							v.push(Point(toppoint.x + q, toppoint.y));
							count_h++;


						}
					}
				}

			}

			if (count_h > 20)
			{
				while (!v.empty())
				{
					Point point = v.top();
					canny_image.at<Vec3b>(point.x, point.y)[2] = 255;
					canny_image.at<Vec3b>(point.x, point.y)[1] = 255;
					canny_image.at<Vec3b>(point.x, point.y)[0] = 255;
					v.pop();
				}
			}
			else
			{
				while (!v.empty())
					v.pop();
			}


		}
	}
	
	




	
	int array[600][2];
	for (int i = 0; i < canny_image.rows; i++)
	{
		for (int j = 0; j < canny_image.cols; j++)
		{
			int count = 0;
			for (int p = -1; p < 2; p++)
			{
				for (int q = -1; q < 2; q++)
				{
					if (i + p>0 && i + p<canny_image.rows&&j + q>0 && j + q < canny_image.cols)
					{
						if (canny_image.at<Vec3b>(i + p, j + q)[2] == 255)
						{
							count++;
						}
					}
				}
			}
			if (count == 8)
			{
				canny_image.at<Vec3b>(i, j)[2] = 255;
				canny_image.at<Vec3b>(i, j)[1] = 255;
				canny_image.at<Vec3b>(i, j)[0] = 255;
			}
		}
	}

	int k = 0, r = 0;
	for (int i = 0; i < canny_image.rows; i++)
	{
		for (int j = 0; j < canny_image.cols; j++)
		{
			int count = 0;


			for (int p = -2; p < 3; p++)
			{
				for (int q = -2; q < 3; q++)
				{
					if (i + p>=0 && i + p<canny_image.rows&&j + q>=0 && j + q < canny_image.cols)
					{
						if (canny_image.at<Vec3b>(i + p, j + q)[2] == 0)
						{
							count++;
						}
					}
				}
			}

			if (count > 10)
			{
				canny_image.at<Vec3b>(i, j)[2] = 180;
				canny_image.at<Vec3b>(i, j)[1] = 253;
				canny_image.at<Vec3b>(i, j)[0] = 11;
				array[k][0] = i;
				array[k][1] = j;
				k++;

			}
		}
	}

	
	for (int i = 0; i < canny_image.rows; i++)
	{

		for (int j = 0; j < canny_image.cols; j++)
		{   
			//cout << "check";
			Point max, min;
			max.x = i;
			max.y = j;
			min.x = i;
			min.y = j;
			if (canny_image.at<Vec3b>(i, j)[2] == 180 && canny_image.at<Vec3b>(i, j)[1] == 253 && canny_image.at<Vec3b>(i, j)[0] == 11)
			{
				
				a.push(Point(i, j));


				//cout << "(" << min.x << "," << min.y << ");" << "(" << max.x << "," << max.y << ")out" << '\n';
				while (!a.empty())
				{

					toppoint = a.top();

					a.pop();
					
					canny_image.at<Vec3b>(i, j)[2] = 0;
					canny_image.at<Vec3b>(i, j)[1] = 0;
					canny_image.at<Vec3b>(i, j)[0] = 0;
					for (int k = -2; k < 3; k++)
					{
						for (int q = -2; q < 3; q++)
						{
							if ( toppoint.x+ k>=0 && toppoint.x + k<canny_image.rows&&toppoint.y + q>=0 && toppoint.y + q < canny_image.cols)
							if (canny_image.at<Vec3b>(toppoint.x +   k, toppoint.y + q)[2] == 155)
							{
								//cout << "karn" << '\n';
								a.push(Point(toppoint.x +  k, toppoint.y +q));

								canny_image.at<Vec3b>(toppoint.x +  k, toppoint.y +  q)[2] = 0;
								canny_image.at<Vec3b>(toppoint.x +  k, toppoint.y +  q)[1] = 0;
								canny_image.at<Vec3b>(toppoint.x +  k, toppoint.y +  q)[0] = 0;
								if (toppoint.x + k>max.x)
									max.x = toppoint.x +  k;
								if (toppoint.y + q > max.y)
									max.y = toppoint.y +  q;
								if (toppoint.x + k < min.x)
									min.x = toppoint.x +  k;
								if (toppoint.y + q < min.y)
									min.y = toppoint.y +  q;

							}

						}

					}


				}
		         const Scalar color(0, 255, 0);
				 int swap;
				 swap = max.x;
				 max.x = max.y;
				 max.y = swap;

				 swap = min.x;
				 min.x = min.y;
				 min.y = swap;
				//cout << "(" << min.x << "," << t << ");" << "(" << max.x << "," << max.y << ")" << '\n';
				 rectangle( canny_output, max,  min, color, 2, 8, 0);	//last 3 are thickness, linetype and shift 
			}

		}
	}
	


imshow("output", canny_output);
	waitKey(0);
	return 0;

}