#ifndef PIXEL_MAGIC_H
#define PIXEL_MAGIC_H

#include <QtWidgets/QMainWindow>
#include <QDialog>
#include <QInputDialog>
#include <QPen>
#include <QBrush>
#include <QPaintEvent>
#include <QPainter>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qfiledialog.h>
#include <QMouseEvent>
#include <opencv2/opencv.hpp>
#include <cv.h>
using namespace cv;

#include "ui_pixel_magic.h"
#include "cvfun.h"
#include "piclabel.h"
class pixel_magic : public QMainWindow
{
	Q_OBJECT

public:
	pixel_magic(QWidget *parent = 0);
	~pixel_magic();

public:
	//void paintEvent(QPaintEvent *);
private:
	void reload_picture();

private:
	Ui::pixel_magicClass ui;
	QPushButton *load_pic, *save_pic, *rotate_pic, *h_reverse_pic, *v_reverse_pic, *rect_clip_pic, *round_clip_pic;
	PicLabel* pic_label[2];
	Mat pic_cv_data[2], pic_cv_data_rotate[2];
	//bool rect_clip_flag, round_clip_flag;
	//int clip_area_x1, clip_area_x2, clip_area_y1, clip_area_y2;
	QLabel* display;
private slots:
	void load_picture();
	void save_picture();
	void rotate_picture();
	void h_reverse_picture();
	void v_reverse_picture();
	void rect_clip_picture();
	void round_clip_picture();
protected:
	//void mousePressEvent(QMouseEvent * e);
	//void mouseMoveEvent(QMouseEvent *e);
	//void mouseReleaseEvent(QMouseEvent *e);
};

static QImage Mat2QImage(Mat image);

#endif // PIXEL_MAGIC_H
