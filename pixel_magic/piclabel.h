#pragma once
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QRect>
#include <cmath>
using namespace std;
class PicLabel : public QLabel {
	Q_OBJECT

public:
	PicLabel(QWidget * parent = Q_NULLPTR);
	~PicLabel();
	void clear_pic_label();
public:
	bool rect_clip_flag, round_clip_flag;
	int clip_area_x1, clip_area_x2, clip_area_y1, clip_area_y2;
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
private:
	
};
