#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<time.h>

#include "wpoint.h"

using namespace cv;
using namespace std;

class bf_apollonius
{
public:
	bf_apollonius();
	bf_apollonius(vector<wpoint>& i_pts, Mat* image);
	void draw_bfa();
	double centralize();
private:
	vector<Vec3d> pts;
	Mat* image;
	vector<Vec3b> colors;
	vector<Vec3d> sum;
};