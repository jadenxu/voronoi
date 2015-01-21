#ifndef MY_LABEL_H
#define MY_LABEL_H

#include <QtGui/QLabel>
#include <QtGui/QMouseEvent>
#include <QtGui/QMessageBox>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

#include "voronoi_core/wpoint.h"

using namespace std;
using namespace cv;

class my_qlabel : public QLabel
{
	Q_OBJECT

public:
	my_qlabel(QWidget *parent);
	~my_qlabel();
	void show_image(Mat& simage);
	void draw_circle(Point x);
	void my_clear();
	void mousePressEvent(QMouseEvent *ev);
	void mouseMoveEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
	void find_voronoi_dia();
	void find_power_dia();
	void find_apollonius_dia();
	void generate_weight(Point cur);
	void my_changed();
	void voronoi_iteration();
	string status;
	bool circle_b;
	bool dynamic_b;

private:
	Mat image;
	Mat image_tem;
	bool draw_b;
	vector<wpoint> pts;
	int w,h;
	int times;
};

#endif // MY_LABEL_H
