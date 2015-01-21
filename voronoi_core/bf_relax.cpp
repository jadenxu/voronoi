#include "bf_relax.h"

bf_relax::bf_relax(vector<wpoint>& i_pts, Mat* image)
{
	srand(time(0));

	for(int i = 0; i < i_pts.size(); i++)
	{
		pts.push_back(Vec3d(i_pts[i].x, i_pts[i].y));
		colors.push_back(Vec3b(rand()%255, rand()%255, rand()%255));
	}

	this->image = image;
}

void bf_relax::draw_bfr()
{
	for(int i = 0; i < image->rows; i++)
	{
		for(int j = 0; j < image->cols; j++)
		{
			double min_ind = 0;
			double min = 0;
			for(int k = 0; k < pts.size(); k++)
			{
				double dis = sqrt((double)(i - pts[k](1)) * (i - pts[k](1)) + (j - pts[k](0)) * (j - pts[k](0))) - pts[k](2);
				if(k == 0 || dis < min)
				{
					min = dis;
					min_ind = k;
				}
			}
			image->at<Vec3b>(i,j) = colors[min_ind];
		}
	}

	for(int i = 0; i < pts.size(); i++)
	{
		circle(*image, Point(pts[i](0), pts[i](1)) , 5 , Scalar(0,255,0), -1, 8);
		circle(*image, Point(pts[i](0), pts[i](1)) , pts[i](2) , Scalar(0,0,0), 1, CV_AA);
	}
}

double bf_relax::centralize()
{

	double error = 0;
	for(int i = 0; i < pts.size(); i++)
	{
	}
	error = error / pts.size();

	return error;
}