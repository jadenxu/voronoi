#ifndef POWER_DIA_H
#define POWER_DIA_H

#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Regular_triangulation_euclidean_traits_2.h>
#include <CGAL/Regular_triangulation_filtered_traits_2.h>
#include <CGAL/Regular_triangulation_2.h>
#include <CGAL/intersections.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Iso_rectangle_2	Iso_rectangle_2;
typedef CGAL::Regular_triangulation_filtered_traits_2<K>  Traits;
typedef CGAL::Regular_triangulation_2<Traits> RT;

using namespace cv;
using namespace std;

#include "wpoint.h"

class Power_dia
{
public:
	Power_dia(vector<wpoint>& pts, Mat* image, Point size);
	void draw_pd();
private:
	RT rt;
	Mat* image;
	Iso_rectangle_2 bbox;
};

#endif