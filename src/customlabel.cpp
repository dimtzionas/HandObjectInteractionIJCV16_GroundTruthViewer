#include "customlabel.h"

CustomLabel::CustomLabel( QWidget *parent ) :
    QLabel( parent ){
}


void CustomLabel::mouseMoveEvent( QMouseEvent *ev ){
    this->mouse_X = ev->x();
    this->mouse_Y = ev->y();
    emit mouse_position();
}


void CustomLabel::mousePressEvent( QMouseEvent *ev ){
    emit mouse_pressed();
}


void CustomLabel::leaveEvent( QEvent * ){
    emit mouse_left();
}


void CustomLabel::mouseReleaseEvent( QMouseEvent * ){
    emit mouse_release();
}
