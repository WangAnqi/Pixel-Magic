#pragma once
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
class Rotation_Angle : public QDialog {
	Q_OBJECT

public:
	Rotation_Angle(QWidget * parent = 0);
	~Rotation_Angle();

private slots:
    
private:
	QLabel *clockwise_angle;
	QLabel *counterclock_angle;
	QLineEdit * angle_edit;
	QPushButton *ensure_btn;
};
