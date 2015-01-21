#ifndef APOLLONIUS_DIA_H
#define APOLLONIUS_DIA_H

#include<iostream>
#include<fstream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Apollonius_graph_2.h>
#include <CGAL/Apollonius_graph_traits_2.h>
#include <CGAL/Circular_arc_2.h>
#include <CGAL/Line_arc_2.h>
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Hyperbola_2.h>

#include "wpoint.h"

using namespace cv;
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel KC;
typedef CGAL::Apollonius_graph_traits_2<KC>   GT;
typedef CGAL::Apollonius_graph_2<GT>          AG;

struct Cropped_Apollonius_dia
{
	vector<GT::Segment_2> evector;
	KC::Iso_rectangle_2 a_bbox;

	Cropped_Apollonius_dia(KC::Iso_rectangle_2& bbox):a_bbox(bbox){}

	template <class RSL>
	void crop_ad(const RSL& rsl)
	{
		CGAL::Object obj = CGAL::intersection(rsl, a_bbox);
		const KC::Segment_2* s =  CGAL::object_cast<GT::Segment_2>(&obj);
		if(s)
			evector.push_back(*s);
	}

	void operator<<(const GT::Ray_2& ray){crop_ad(ray);}
	void operator<<(const GT::Line_2& line){crop_ad(line);}
	void operator<<(const GT::Segment_2& seg){evector.push_back(seg);}
};

class Apollonius_dia
{
public:
	Apollonius_dia(vector<wpoint>& pts, Mat* image, Point size);
	void draw_ad();
private:
	AG ag;
	Mat* image;
	KC::Iso_rectangle_2 bbox;
};

#endif