#ifndef STARBURST_H
#define STARBURST_H

#include <QtGui/QMainWindow>
#include "ui_starburst.h"

class starburst : public QMainWindow
{
	Q_OBJECT

public:
	starburst(QWidget *parent = 0, Qt::WFlags flags = 0);
	~starburst();
	void create_actions();

public slots:
	void my_restart();
	void my_vd();
	void my_pd();
	void my_ad();
	void my_circle();
	void my_dynamic();
	void my_iv();

private:
	Ui::starburstClass ui;
};

#endif // STARBURST_H
