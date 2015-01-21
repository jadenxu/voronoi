#include "my_qlabel.h"
#include "voronoi_core/voronoi_dia.h"
#include "voronoi_core/power_dia.h"
#include "voronoi_core/apollonius_dia.h"
#include "voronoi_core/bf_voronoi.h"
#include "voronoi_core/bf_apollonius.h"

my_qlabel::my_qlabel(QWidget *parent)
	: QLabel(parent)
{
	w = 700;
	h = 1100;
	Mat new_img(w, h, CV_8UC3);
	new_img = Scalar(255,255,255);
	image = new_img;
	show_image(image);

	status = "pd";
	circle_b = true;
	draw_b = false;
	dynamic_b = false;
	times = 0;
}

void my_qlabel::show_image(Mat& simage)
{
	Mat tem;
	cvtColor(simage,tem,CV_BGR2RGB);
	QImage img;
	img = QImage(tem.data, tem.cols, tem.rows, tem.cols*3, QImage::Format_RGB888);
	this->setPixmap(QPixmap::fromImage(img));
	this->resize(this->pixmap()->size());
}

void my_qlabel::draw_circle(Point x)
{
	int thickness = -1;
	int lineType = 8;
	int radius = 5;
	circle(image, x , radius , Scalar(0,255,0), thickness, lineType);

	show_image(image);
}

void my_qlabel::mousePressEvent(QMouseEvent* ev)
{
	draw_b = true;
	draw_circle(Point(ev->x(), ev->y()));
	pts.push_back(wpoint(ev->x(), ev->y()));
}

void my_qlabel::mouseMoveEvent(QMouseEvent *ev)
{
	if(draw_b)
	{
		wpoint p = pts[pts.size()-1];
		pts[pts.size()-1].w = (double)(p.x - ev->x()) * (p.x - ev->x()) + (p.y - ev->y()) * (p.y - ev->y());

		my_changed();
	}
	else if(dynamic_b)
	{
		generate_weight(Point(ev->x(), ev->y()));
		
		image.copyTo(image_tem);
		my_changed();
	}
}

void my_qlabel::mouseReleaseEvent(QMouseEvent* ev)
{
	my_changed();
	
	draw_b = false;
}

void my_qlabel::my_clear()
{
	Mat new_img(w, h, CV_8UC3);
	new_img = Scalar(255,255,255);
	image = new_img;
	show_image(image);

	pts.clear();
	draw_b = false;
	times = 0;
}

void my_qlabel::generate_weight(Point cur)
{
	double max;
	for(int i = 0; i < pts.size(); i++)
	{
		pts[i].w = ((double)(cur.x - pts[i].x) * (cur.x - pts[i].x) + (cur.y - pts[i].y) * (cur.y - pts[i].y)) / 2;
		if(i == 0 || max < pts[i].w)
			max = pts[i].w;
	}

	double sum = 0;;
	for(int i = 0; i < pts.size(); i++)
	{
		pts[i].w = (1.2 * max - pts[i].w) * 2.5;
		sum += pts[i].w;
	}
	sum = sum / pts.size();

	for(int i = 0; i < pts.size(); i++)
	{
		if(pts[i].w < sum / 3.0)
			pts[i].w = 0;
	}
}

void my_qlabel::my_changed()
{
	image.copyTo(image_tem);
	if(status == "vd")
		find_voronoi_dia();
	else if(status == "pd")
		find_power_dia();
	else
		find_apollonius_dia();

	if(circle_b)
	{
		for(int i = 0; i < pts.size(); i++)
			circle(image_tem, Point(pts[i].x, pts[i].y) , sqrt(pts[i].w) , Scalar(0,0,0), 1, CV_AA);
	}

	show_image(image_tem);
}

void my_qlabel::find_voronoi_dia()
{
	Voronoi_dia vd(pts, &image_tem, Point(h,w));
	vd.draw_vd();
	//vd.find_small();
}

void my_qlabel::find_power_dia()
{
	Power_dia pd(pts, &image_tem, Point(h,w));
	pd.draw_pd();
}

void my_qlabel::find_apollonius_dia()
{
	Apollonius_dia ad(pts, &image_tem, Point(h,w));
	ad.draw_ad();
}

void my_qlabel::voronoi_iteration()
{
	image.copyTo(image_tem);
	double error = 100;
	if(status == "vd")
	{
		bf_voronoi bfv(pts, &image_tem);
		times++;
		for(int i = 0; i < times; i++)
		{
			bfv.draw_bfv();
			error = bfv.centralize();
		}
		cout<<error<<endl;
		show_image(image_tem);
	}
	else if(status == "ad")
	{
		bf_apollonius bfa(pts, &image_tem);
		times++;
		for(int i = 0; i < times; i++)
		{
			bfa.draw_bfa();
			error = bfa.centralize();
		}
		cout<<error<<endl;
		show_image(image_tem);
	}
}

my_qlabel::~my_qlabel()
{

}
