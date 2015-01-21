#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<time.h>

#include "wpoint.h"

using namespace cv;
using namespace std;

class bf_relax
{
public:
	bf_relax(vector<wpoint>& i_pts, Mat* image);
	void draw_bfr();
	double centralize();
private:
	vector<Vec3d> pts;
	Mat* image;
	vector<Vec3b> colors;
};