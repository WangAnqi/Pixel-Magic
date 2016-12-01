#include "pixel_magic.h"

pixel_magic::pixel_magic(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("Pixel Magic");

	this->resize(600, 400);
	this->centralWidget();

	pic_label[0] = new PicLabel(this);

	load_pic = new QPushButton("Open", this);
	load_pic->setGeometry(10, 10, 40, 30);
	load_pic->setFont(QFont("Times", 10));
	connect(load_pic, SIGNAL(clicked()), this, SLOT(load_picture()));

	save_pic = new QPushButton("Save", this);
	save_pic->setGeometry(60, 10, 40, 30);
	save_pic->setFont(QFont("Times", 10));
	save_pic->setEnabled(false);
	connect(save_pic, SIGNAL(clicked()), this, SLOT(save_picture()));

	rotate_pic = new QPushButton("Rotate", this);
	rotate_pic->setGeometry(110, 10, 55, 30);
	rotate_pic->setFont(QFont("Times", 10));
	rotate_pic->setEnabled(false);
	connect(rotate_pic, SIGNAL(clicked()), this, SLOT(rotate_picture()));

	h_reverse_pic = new QPushButton("Reverse(h)", this);
	h_reverse_pic->setGeometry(175, 10, 80, 30);
	h_reverse_pic->setFont(QFont("Times", 10));
	h_reverse_pic->setEnabled(false);
	connect(h_reverse_pic, SIGNAL(clicked()), this, SLOT(h_reverse_picture()));

	v_reverse_pic = new QPushButton("Reverse(v)", this);
	v_reverse_pic->setGeometry(265, 10, 80, 30);
	v_reverse_pic->setFont(QFont("Times", 10));
	v_reverse_pic->setEnabled(false);
	connect(v_reverse_pic, SIGNAL(clicked()), this, SLOT(v_reverse_picture()));

	rect_clip_pic = new QPushButton("Rect Clip", this);
	rect_clip_pic->setGeometry(355, 10, 75, 30);
	rect_clip_pic->setFont(QFont("Times", 10));
	rect_clip_pic->setEnabled(false);
	connect(rect_clip_pic, SIGNAL(clicked()), this, SLOT(rect_clip_picture()));
	

	round_clip_pic = new QPushButton("Round Clip", this);
	round_clip_pic->setGeometry(440, 10, 80, 30);
	round_clip_pic->setFont(QFont("Times", 10));
	round_clip_pic->setEnabled(false);
	connect(round_clip_pic, SIGNAL(clicked()), this, SLOT(round_clip_picture()));
	

	display = new QLabel(this);

}

pixel_magic::~pixel_magic()
{

}

void pixel_magic::load_picture()
{
	QString filename = QFileDialog::getOpenFileName(this,
		tr("choose one picture"), "",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	//QPixmap pix = QPixmap(filename);
	if (filename.isEmpty())
	{
		return;
	}
	pic_cv_data[0] = imread(filename.toLocal8Bit().data(), -1);
	/*Mat tmp_pic = pic_cv_data[0].clone();
	QImage img = Mat2QImage(tmp_pic);
	QPixmap pix = QPixmap::fromImage(img);
	int pix_width = pix.width();
	int pix_height = pix.height();

	pic_label[0]->setPixmap(pix);
	this->resize(pix_width + 90, pix_height + 90);
	pic_label[0]->setGeometry(50, 50, pix_width, pix_height);*/
	reload_picture();

	save_pic->setEnabled(true);
	rotate_pic->setEnabled(true);
	h_reverse_pic->setEnabled(true);
	v_reverse_pic->setEnabled(true);
	rect_clip_pic->setEnabled(true);
	round_clip_pic->setEnabled(true);
}

void pixel_magic::reload_picture()
{
	Mat tmp_pic = pic_cv_data[0].clone();
	QImage img = Mat2QImage(tmp_pic);
	QPixmap pix = QPixmap::fromImage(img);
	int pix_width = pix.width();
	int pix_height = pix.height();

	pic_label[0]->setPixmap(pix);
	this->resize(max(pix_width + 90, 600), max(pix_height + 90, 400));
	pic_label[0]->setGeometry(50, 50, pix_width, pix_height);
	return;
}

void pixel_magic::save_picture()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Close File"),"", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
	{
		return;
	}
	imwrite(filename.toStdString(), pic_cv_data[0]);
}

void pixel_magic::rotate_picture()
{
	//input_rot_angle_dlg = new Rotation_Angle();
	//input_rot_angle_dlg->show();
	bool ok;
	double rotation_angle = QInputDialog::getDouble(this, tr("Input Rotation Angle"), tr("clockwise rotation angle:"),
		0, -2147483647, 2147483647, 2, &ok);
	if (ok)
	{
		//display->setText(QString(tr("%4")).arg(rotation_angle));
		//display->setGeometry(600, 10, 40, 30);

		pic_cv_data[0] = angleRotate(pic_cv_data[0], rotation_angle);
		reload_picture();
	}

	return;
}

void pixel_magic::h_reverse_picture()
{
	pic_cv_data[0] = horizon_reverse(pic_cv_data[0]);
	reload_picture();
	return;
}

void pixel_magic::v_reverse_picture()
{
	pic_cv_data[0] = vertical_reverse(pic_cv_data[0]);
	reload_picture();
	return;
}

void pixel_magic::rect_clip_picture()
{
	if (!pic_label[0]->rect_clip_flag)
	{
		rect_clip_pic->setDefault(true);
		rotate_pic->setEnabled(false);
		h_reverse_pic->setEnabled(false);
		v_reverse_pic->setEnabled(false);
		round_clip_pic->setEnabled(false);
	}
	else
	{
		rect_clip_pic->setDefault(false);
		rotate_pic->setEnabled(true);
		h_reverse_pic->setEnabled(true);
		v_reverse_pic->setEnabled(true);
		round_clip_pic->setEnabled(true);

		if (pic_label[0]->clip_area_x1 != 0 || pic_label[0]->clip_area_y1 != 0 || pic_label[0]->clip_area_x2 != 0 || pic_label[0]->clip_area_y2 != 0)
		{
			Rect clip_rect(pic_label[0]->clip_area_x1, pic_label[0]->clip_area_y1, pic_label[0]->clip_area_x2 - pic_label[0]->clip_area_x1, pic_label[0]->clip_area_y2 - pic_label[0]->clip_area_y1);
			Mat tmp_mat(pic_cv_data[0], clip_rect);
			pic_cv_data[0] = tmp_mat;
			reload_picture();
			pic_label[0]->clear_pic_label();
		}
	}
	pic_label[0]->rect_clip_flag = !pic_label[0]->rect_clip_flag;

}

void pixel_magic::round_clip_picture()
{
	if (!pic_label[0]->round_clip_flag)
	{
		round_clip_pic->setDefault(true);
		rotate_pic->setEnabled(false);
		h_reverse_pic->setEnabled(false);
		v_reverse_pic->setEnabled(false);
		rect_clip_pic->setEnabled(false);
	}
	else
	{
		round_clip_pic->setDefault(false);
		rotate_pic->setEnabled(true);
		h_reverse_pic->setEnabled(true);
		v_reverse_pic->setEnabled(true);
		rect_clip_pic->setEnabled(true);

		if (pic_label[0]->clip_area_x1 != 0 || pic_label[0]->clip_area_y1 != 0 || pic_label[0]->clip_area_x2 != 0 || pic_label[0]->clip_area_y2 != 0)
		{
		    Rect clip_rect(pic_label[0]->clip_area_x1, pic_label[0]->clip_area_y1, pic_label[0]->clip_area_x2 - pic_label[0]->clip_area_x1, pic_label[0]->clip_area_y2 - pic_label[0]->clip_area_y1);
		    pic_cv_data[0] = round_clip(pic_cv_data[0], clip_rect);
		    reload_picture();
		    pic_label[0]->clear_pic_label();
		}
	}
	pic_label[0]->round_clip_flag = ! pic_label[0]->round_clip_flag;
}

/*
void pixel_magic::mousePressEvent(QMouseEvent * e)
{
	//QString filename = QFileDialog::getSaveFileName(this, tr("Close File"), "", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (!rect_clip_flag && !round_clip_flag)
	{
		return;
	}

	QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";

	if (e->button() == Qt::LeftButton)
	{
		this->setMouseTracking(true);
		clip_area_x1 = e->x();
		clip_area_y1 = e->y();
	}
	else if(e->button() == Qt::RightButton)
	{
		this->setMouseTracking(false);
	}

	display->setText(str);
}
void pixel_magic::mouseMoveEvent(QMouseEvent *e)
{
	if (!rect_clip_flag && !round_clip_flag)
	{
		return;
	}
	QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
	display->setText(str);

	//if (e->button() == Qt::LeftButton)
	//{
		display->setText(str);
		clip_area_x2 = max(clip_area_x1, e->x());
		clip_area_y2 = max(clip_area_y1, e->y());
		clip_area_x1 = min(clip_area_x1, e->x());
		clip_area_y1 = min(clip_area_y1, e->y());
		update();
	//}
}
void pixel_magic::mouseReleaseEvent(QMouseEvent *e)
{
	if (!rect_clip_flag && !round_clip_flag)
	{
		return;
	}

	QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";

	if (e->button() == Qt::LeftButton)
	{
		this->setMouseTracking(false);
		display->setText(str);
		clip_area_x2 = max(clip_area_x1, e->x());
		clip_area_y2 = max(clip_area_y1, e->y());
		clip_area_x1 = min(clip_area_x1, e->x());
		clip_area_y1 = min(clip_area_y1, e->y());
		update();
	}
	
}
*/

/*
void pixel_magic::paintEvent(QPaintEvent *)
{
	//QString filename = QFileDialog::getSaveFileName(this, tr("Close File"), "", tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	/*QPainter p(this);
	//QPainter p(pic_label[0]);
	//QBrush brush(Qt::black);
	QPen pen(Qt::black);//, 10, Qt::DashDotLine
	p.setPen(pen);
	//p.setBrush(brush);
	QRect rect(clip_area_x1, clip_area_y1, clip_area_x2 - clip_area_x1, clip_area_y2 - clip_area_y1);
	if (rect_clip_flag)
	{
		p.drawRect(rect);
		reload_picture();
	}
	else if(round_clip_flag)
	{
		p.drawEllipse(rect);
		reload_picture();
	}
}
*/


static QImage Mat2QImage(Mat image)
{
	QImage img;

	if (image.channels() == 3) {
	    cvtColor(image, image, CV_BGR2RGB);
		img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
			image.cols*image.channels(), QImage::Format_RGB888);
	}
	else if (image.channels() == 1) {
		img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
			image.cols*image.channels(), QImage::Format_ARGB32);
	}
	else {
		img = QImage((const unsigned char *)(image.data), image.cols, image.rows,
			image.cols*image.channels(), QImage::Format_RGB888);
	}

	return img;
}