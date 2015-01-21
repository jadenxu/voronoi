#include "starburst.h"

starburst::starburst(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	create_actions();
	setCentralWidget(ui.label);
	this->setWindowTitle("Starburst");
	this->resize(1100,700);
	ui.actionCircle->setChecked(true);
	ui.actionPower->setChecked(true);
}

void starburst::create_actions()
{
	connect(ui.actionVoronoi, SIGNAL(triggered()), this, SLOT(my_vd()));
	connect(ui.actionPower, SIGNAL(triggered()), this, SLOT(my_pd()));
	connect(ui.actionApollonius, SIGNAL(triggered()), this, SLOT(my_ad()));
	connect(ui.actionCircle, SIGNAL(triggered()), this, SLOT(my_circle()));
	connect(ui.actionDynamic, SIGNAL(triggered()), this, SLOT(my_dynamic()));
	connect(ui.actionRestart, SIGNAL(triggered()), this, SLOT(my_restart()));
	connect(ui.actionIteration, SIGNAL(triggered()), this, SLOT(my_iv()));
}

void starburst::my_iv()
{
	ui.label->voronoi_iteration();
}

void starburst::my_vd()
{
	ui.actionApollonius->setChecked(false);
	ui.actionPower->setChecked(false);
	ui.label->status = "vd";

	ui.actionCircle->setChecked(false);
	ui.label->circle_b = false;

	ui.label->my_changed();
}

void starburst::my_pd()
{
	ui.actionApollonius->setChecked(false);
	ui.actionVoronoi->setChecked(false);
	ui.label->status = "pd";

	ui.actionCircle->setChecked(true);
	ui.label->circle_b = true;

	ui.label->my_changed();
}

void starburst::my_ad()
{
	ui.actionVoronoi->setChecked(false);
	ui.actionPower->setChecked(false);
	ui.label->status = "ad";

	ui.actionCircle->setChecked(true);
	ui.label->circle_b = true;

	ui.label->my_changed();
}

void starburst::my_circle()
{
	if(ui.actionVoronoi->isChecked())
	{
		ui.actionCircle->setChecked(false);
		ui.label->circle_b = false;
	}
	else
	{
		ui.label->circle_b = (!ui.label->circle_b);
	}

	ui.label->my_changed();
}

void starburst::my_dynamic()
{
	if(ui.actionVoronoi->isChecked())
	{
		ui.actionDynamic->setChecked(false);
		ui.label->dynamic_b = false;
	}
	else
	{
		ui.label->dynamic_b = (!ui.label->dynamic_b);
	}

	ui.label->my_changed();
}

void starburst::my_restart()
{
	ui.label->my_clear();
}

starburst::~starburst()
{

}
