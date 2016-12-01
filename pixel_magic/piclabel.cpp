#include "piclabel.h"

PicLabel::PicLabel(QWidget * parent) : QLabel(parent) {
	rect_clip_flag = false;
	round_clip_flag = false;
	clip_area_x1 = 0;
	clip_area_x2 = 0;
	clip_area_y1 = 0;
	clip_area_y2 = 0;
}

PicLabel::~PicLabel() {
	
}

void PicLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);//先调用父类的paintEvent为了显示'背景'!!!
	QPainter p(this);
	//QPainter p(pic_label[0]);
	//QBrush brush(Qt::black);
	QPen pen(Qt::black);//, 10, Qt::DashDotLine
	p.setPen(pen);
	//p.setBrush(brush);
	QRect rect(clip_area_x1, clip_area_y1, clip_area_x2 - clip_area_x1, clip_area_y2 - clip_area_y1);
	if (rect_clip_flag)
	{
		p.drawRect(rect);
		
	}
	else if (round_clip_flag)
	{
		p.drawEllipse(rect);
	}
}

void PicLabel::mousePressEvent(QMouseEvent * e)
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
	else if (e->button() == Qt::RightButton)
	{
		this->setMouseTracking(false);
		clip_area_x1 = 0;
		clip_area_x2 = 0; 
		clip_area_y1 = 0;
		clip_area_y2 = 0;
		update();
	}

	//display->setText(str);
}
void PicLabel::mouseMoveEvent(QMouseEvent *e)
{
	if (!rect_clip_flag && !round_clip_flag)
	{
		return;
	}
	QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";
	//display->setText(str);

	//if (e->button() == Qt::LeftButton)
	//{
	//display->setText(str);
	clip_area_x2 = max(clip_area_x1, e->x());
	clip_area_y2 = max(clip_area_y1, e->y());
	clip_area_x1 = min(clip_area_x1, e->x());
	clip_area_y1 = min(clip_area_y1, e->y());
	update();
	//}
}
void PicLabel::mouseReleaseEvent(QMouseEvent *e)
{
	if (!rect_clip_flag && !round_clip_flag)
	{
		return;
	}

	QString str = "(" + QString::number(e->x()) + "," + QString::number(e->y()) + ")";

	if (e->button() == Qt::LeftButton)
	{
		this->setMouseTracking(false);
		//display->setText(str);
		clip_area_x2 = max(clip_area_x1, e->x());
		clip_area_y2 = max(clip_area_y1, e->y());
		clip_area_x1 = min(clip_area_x1, e->x());
		clip_area_y1 = min(clip_area_y1, e->y());
		update();
	}

}

void PicLabel::clear_pic_label()
{
	this->setMouseTracking(false);
	clip_area_x1 = 0;
	clip_area_x2 = 0;
	clip_area_y1 = 0;
	clip_area_y2 = 0;
	//rect_clip_flag = false;
	//round_clip_flag = false;
	update();
}