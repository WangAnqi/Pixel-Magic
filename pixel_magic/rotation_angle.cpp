#include "rotation_angle.h"

Rotation_Angle::Rotation_Angle(QWidget * parent) : QDialog(parent) {
	setWindowTitle(tr("Input rotation angle"));
	resize(200, 120);
}

Rotation_Angle::~Rotation_Angle() {
	
}
