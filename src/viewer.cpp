#include "viewer.h"
#include "ui_mainwindow.h"

#include <customlabel.h>

Viewer::Viewer( QWidget *parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ){
    ui->setupUi( this );
    connect( ui->myLabel_IMG, SIGNAL( mouse_position()),  this, SLOT( mouse_position())  );
    connect( ui->myLabel_IMG, SIGNAL( mouse_left()),      this, SLOT( mouse_left())      );
    connect( ui->myLabel_IMG, SIGNAL( mouse_pressed()),   this, SLOT( mouse_pressed())   );
    connect( ui->myLabel_IMG, SIGNAL( mouse_release()),   this, SLOT( mouse_release())   );
    ui->myLabel_IMG->setMouseTracking( true );
    colorize_black();
    ui->myGroupBox->setEnabled( false );
    is_sequence_loaded = false;
    ctrl_key = false;
    ctrl_click = false;
    shift_click = false;
    shift_key = false;
    ui->finger_x_coord->hide();
    ui->finger_y_coord->hide();
    ui->x_joints_label->hide();
    ui->y_joints_label->hide();
    ui->sel_joints_label->hide();

    //load settings
    QSettings settings( "../config/config.ini", QSettings::IniFormat );
    settings.beginGroup( "General" );
    frame_step = settings.value( "frame_step", 1 ).toInt();
    frames_start = settings.value( "start_frame", 0 ).toInt();
    id_padding = settings.value( "name_0padding", 3 ).toInt();
    settings.endGroup();
    settings.beginGroup( "Display" );
    joint_radius = settings.value( "joint_radius" ).toInt();
    settings.endGroup();

}


Viewer::~Viewer(){
    delete ui;
}



