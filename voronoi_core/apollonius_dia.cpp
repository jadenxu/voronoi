#include "apollonius_dia.h"

Apollonius_dia::Apollonius_dia(vector<wpoint>& pts, Mat* image, Point size)
{
	for(int i = 0; i < pts.size(); i++)
	{
		ag.insert(GT::Site_2(GT::Point_2(pts[i].x, pts[i].y), sqrt(pts[i].w)));	
	}

	this->image = image;

	bbox = KC::Iso_rectangle_2(0,0,size.x,size.y);
}

void Apollonius_dia::draw_ad()
{
	Cropped_Apollonius_dia c_ad(bbox);
	ag.draw_dual(c_ad);
	for(int i = 0; i < c_ad.evector.size(); i++)
	{
		GT::Segment_2 s = c_ad.evector[i];
		line(*image, Point(s.source().x(), s.source().y()), Point(s.target().x(), s.target().y()), Scalar(255,0,0), 1, CV_AA);
	}
}