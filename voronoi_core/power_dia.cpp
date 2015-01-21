#include "power_dia.h"

Power_dia::Power_dia(vector<wpoint>& pts, Mat* image, Point size)
{
	for(int i = 0; i < pts.size(); i++)
	{
		RT::Weighted_point p(RT::Point(pts[i].x, pts[i].y), RT::Weight(pts[i].w));
		rt.insert(p);
	}

	this->image = image;

	bbox = Iso_rectangle_2(0,0,size.x, size.y);
}

void Power_dia::draw_pd()
{
	RT::Edge_iterator eit;
	for(eit = rt.edges_begin(); eit != rt.edges_end(); ++eit)
	{
		CGAL::Object o = rt.dual(eit);
		CGAL::Object obj;
		if (CGAL::object_cast<K::Segment_2>(&o))
		{
			obj = o;
		}
		else if (CGAL::object_cast<K::Ray_2>(&o)) 
		{
			const K::Ray_2* r = CGAL::object_cast<K::Ray_2>(&o);
			obj = CGAL::intersection(*r,bbox);
		}
		else if(CGAL::object_cast<K::Line_2>(&o))
		{
			const K::Line_2* l = CGAL::object_cast<K::Line_2>(&o);
			obj = CGAL::intersection(*l,bbox);
		}
		const K::Segment_2* s = CGAL::object_cast<K::Segment_2>(&obj);
		if(s)
			line(*image, Point(s->source().x(), s->source().y()), Point(s->target().x(), s->target().y()), Scalar(255,0,0), 1, CV_AA);
	}
}