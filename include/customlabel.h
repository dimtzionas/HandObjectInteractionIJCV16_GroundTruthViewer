#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>

class CustomLabel : public QLabel {
    Q_OBJECT
public:
    explicit CustomLabel( QWidget *parent = 0 );

    void mouseMoveEvent( QMouseEvent *ev );
    void mousePressEvent( QMouseEvent *ev );
    void mouseReleaseEvent( QMouseEvent * );
    void leaveEvent( QEvent * );

    int mouse_X;
    int mouse_Y;

signals:
    void mouse_position();
    void mouse_left();
    void mouse_pressed();
    void mouse_release();

public slots:

};

#endif // CUSTOMLABEL_H
