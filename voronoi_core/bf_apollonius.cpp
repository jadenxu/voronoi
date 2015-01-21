#include "bf_apollonius.h"

bf_apollonius::bf_apollonius()
{
	
}

bf_apollonius::bf_apollonius(vector<wpoint>& i_pts, Mat* image)
{
	srand(time(0));

	for(int i = 0; i < i_pts.size(); i++)
	{
		pts.push_back(Vec3d(i_pts[i].x, i_pts[i].y, sqrt(i_pts[i].w)));
		colors.push_back(Vec3b(rand()%255, rand()%255, rand()%255));
	}

	this->image = image;

	sum.resize(pts.size());
}

void bf_apollonius::draw_bfa()
{
	for(int i = 0; i < sum.size(); i++)
	{
		sum[i] = Vec3d(0,0,0);
	}

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
			sum[min_ind] += Vec3d(j, i, 1);
		}
	}

	for(int i = 0; i < pts.size(); i++)
	{
		circle(*image, Point(pts[i](0), pts[i](1)) , 5 , Scalar(0,255,0), -1, 8);
		circle(*image, Point(pts[i](0), pts[i](1)) , pts[i](2) , Scalar(0,0,0), 1, CV_AA);
	}
}

double bf_apollonius::centralize()
{
	for(int i = 0; i < sum.size(); i++)
	{
		sum[i](0) = sum[i](0) / sum[i](2);
		sum[i](1) = sum[i](1) / sum[i](2);
	}

	double error = 0;
	for(int i = 0; i < pts.size(); i++)
	{
		error += sqrt((pts[i](0) - sum[i](0)) * (pts[i](0) - sum[i](0)) + (pts[i](1) - sum[i](1)) * (pts[i](1) - sum[i](1)));
		//cout<<sum[i](0)<<" "<<sum[i](1)<<" "<<pts[i].x<<" "<<pts[i].y<<endl;
		pts[i](0) = sum[i](0);
		pts[i](1) = sum[i](1);
	}
	error = error / pts.size();

	return error;
}