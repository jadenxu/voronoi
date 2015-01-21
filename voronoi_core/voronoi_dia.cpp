#include "voronoi_dia.h"

Voronoi_dia::Voronoi_dia(vector<wpoint>& pts, Mat* image, Point size)
{
	for(int i = 0; i < pts.size(); i++)
	{
		vd.insert(Site_2(pts[i].x,pts[i].y));
	}

	this->image = image;

	bbox = Iso_rectangle_2(0,0,size.x, size.y);
}

void Voronoi_dia::draw_vd()
{
	DT dt = vd.dual();
	DT::Vertex_iterator vit;
	for(vit = dt.vertices_begin(); vit != dt.vertices_end(); ++vit)
	{
		circle(*image, Point(vit->point().x(), vit->point().y()) , 5 , Scalar(0,255,0), -1, 8);
	}

	DT::Edge_iterator eit;
	for ( eit = dt.edges_begin() ; eit !=dt.edges_end(); ++eit) 
	{
		CGAL::Object o = dt.dual(eit);
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

void Voronoi_dia::find_small()
{
	double f_total = 500.0 * 500.0;
	double f_avg = f_total / vd.number_of_faces();

	VD::Face_iterator fit;
	vector<VD::Face_iterator> small_faces;
	for(fit = vd.faces_begin(); fit != vd.faces_end(); fit++)
	{
		if(!fit->is_unbounded())
		{
			Ccb_halfedge_circulator ec_start = fit->ccb();
			Ccb_halfedge_circulator ec = ec_start;
			vector<Point_2> pts;
			do 
			{
				pts.push_back(ec->source()->point());
			} while ( ++ec != ec_start );
			CGAL::Polygon_2<K> pl(pts.begin(), pts.end());
			if(pl.area() < f_avg / 5.0)
			{
				small_faces.push_back(fit);
				DT::Vertex_handle p = fit->dual();
				circle(*image, Point(p->point().x(),p->point().y()) , 5 , Scalar(0,0,255), -1, CV_AA);
			}
		}
		
	}
}

double Voronoi_dia::centralize()
{
	vector<Point> new_pts;
	VD::Face_iterator fit;
	double sum_x = 0;
	double sum_y = 0;
	for(fit = vd.faces_begin(); fit != vd.faces_end(); ++fit)
	{
		Ccb_halfedge_circulator ec_start = fit->ccb();
		Ccb_halfedge_circulator ec = ec_start;
		vector<Point_2> pts;
		do 
		{
			CGAL::Object obj;
			if(ec->has_source() && ec->has_target())
			{
				K::Segment_2 s(ec->source()->point(), ec->target()->point());
				obj = CGAL::intersection(s,bbox);
			}
			else if(ec->has_source() && !ec->has_target())
			{
				K::Point_2 p1 = ec->twin()->face()->dual()->point();
				K::Point_2 p2 = ec->face()->dual()->point();
				K::Point_2 p_mid((p1.x() + p2.x()) / 2.0, (p1.y() + p2.y()) / 2.0);
				K::Ray_2 r(ec->source()->point(), p_mid);
				obj = CGAL::intersection(r,bbox);
			}
			else if(!ec->has_source() && ec->has_source())
			{
				K::Point_2 p1 = ec->twin()->face()->dual()->point();
				K::Point_2 p2 = ec->face()->dual()->point();
				K::Point_2 p_mid((p1.x() + p2.x()) / 2.0, (p1.y() + p2.y()) / 2.0);
				K::Ray_2 r(ec->target()->point(), p_mid);
				obj = CGAL::intersection(r,bbox);
			}
			else
			{
				K::Point_2 p1 = ec->twin()->face()->dual()->point();
				K::Point_2 p2 = ec->face()->dual()->point();
				K::Point_2 p_mid((p1.x() + p2.x()) / 2.0, (p1.y() + p2.y()) / 2.0);
				K::Line_2 l1(p1,p2);
				K::Line_2 l = l1.perpendicular(p_mid);
				obj = CGAL::intersection(l,bbox);
			}
			const K::Segment_2* inter = CGAL::object_cast<K::Segment_2>(&obj);
			if(inter)
				pts.push_back(inter->source());
		} while ( ++ec != ec_start );

		double cen_x = 0;
		double cen_y = 0;
		for(int i = 0; i < pts.size(); i++)
		{
			cen_x += pts[i].x();
			cen_y += pts[i].y();
		}
		circle(*image, Point(cen_x / pts.size() , cen_y / pts.size()) , 3 , Scalar(255,255,0), -1, 8);
		/*sum_x += abs(cen_x / pts.size() - fit->dual()->point().x());
		sum_y += abs(cen_y / pts.size() - fit->dual()->point().y());
		new_pts.push_back(Point(cen_x / pts.size(), cen_y / pts.size()));*/
	}

	/*vd.clear();
	for(int i = 0; i < new_pts.size(); i++)
	{
		vd.insert(Site_2(new_pts[i].x, new_pts[i].y));
		circle(*image, Point(new_pts[i].x, new_pts[i].y) , 2 , Scalar(255,255,0), -1, 8);
	}
	cout<<vd.number_of_faces()<<endl;

	sum_x = sum_x / new_pts.size();
	sum_y = sum_y / new_pts.size();

	return sqrt(sum_x * sum_x + sum_y * sum_y);*/
	return 0;
}