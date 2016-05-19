#include "viewer.h"
#include "ui_mainwindow.h"



void Viewer::update_all( int new_frame_id ){
    update_frame_id( new_frame_id );
    update_all( );
}


void Viewer::update_all( ){

    update_current_paths();
    update_image();
    update_display();
    update_list();

    ui->myLabel_Img_CurrID->setText( QString::number( current_frame_id ).rightJustified( id_padding, '0', false ) );
    ui->frame_id_edit->setPlainText( current_frame_id_short_str );
    ui->myLabel_ImgFullPath->setText( path_display );
}


void Viewer::update_display(){

    if ( current_img.empty())
        return;
    current_img = source_img.clone();
    read_annotations();

    update_annotations();

    cv::Mat tmpCvRGB;
    cv::cvtColor( current_img, tmpCvRGB, CV_BGR2RGB );

    // create selection box
    if ( ctrl_click || shift_click ) {
        cv::Rect rect( cv::Point( sel_mouse_x, sel_mouse_y ), cv::Point( ui->myLabel_IMG->mouse_X, ui->myLabel_IMG->mouse_Y ));
        cv::rectangle( tmpCvRGB, rect, cv::Scalar( 0, 0, 0 ));
    }

    qt_img = QImage((uchar*)tmpCvRGB.data, tmpCvRGB.cols, tmpCvRGB.rows, QImage::Format_RGB888 );

    if ( ui->myLabel_IMG->size().width()  != current_img.cols &&
         ui->myLabel_IMG->size().height() != current_img.rows )
        ui->myLabel_IMG->resize( current_img.cols, current_img.rows );


    ui->myLabel_IMG->clear();
    ui->myLabel_IMG->setPixmap( QPixmap::fromImage( qt_img ) );

}


void Viewer::update_list(){
    ui->finger_list->clear();
    ui->finger_x_coord->hide();
    ui->finger_y_coord->hide();
    ui->x_joints_label->hide();
    ui->y_joints_label->hide();
    ui->sel_joints_label->hide();

    QString side[] = { "Right", "Left " };
    QString fingers[] = { "Little ", "Ring   ", "Middle ", "Pointer", "Thumb  " };

    for ( int iii = 0; iii < annotations.size(); iii++ ) {
        if ( iii < 14 )
            ui->finger_list->addItem( side[0] + " hand - " + fingers[iii / 3] + "  finger - joint " + QString::number( iii % 3 ));
        else
            ui->finger_list->addItem( side[1] + " hand - " + fingers[( iii - 14 ) / 3] + "  finger - joint " + QString::number(( iii - 14 ) % 3 ));
    }
}


void Viewer::update_annotations(){

    int radius = joint_radius;

    for ( int iii = 0; iii < annotations.size(); iii++ ) {
        if ( annotations[iii].joint_x == 0  ||  annotations[iii].joint_y == 0 )
            continue;

        cv::Point center;
        center.x = round_to_int( annotations[iii].joint_x );
        center.y = round_to_int( annotations[iii].joint_y );

        if ( ui->finger_list->count() > iii && ui->finger_list->item( iii )->isSelected())
            cv::circle( current_img, center, radius, cv::Scalar( 0, 0, 255 ), radius * 2 );
        else
            cv::circle( current_img, center, radius, cv::Scalar( 0, 255, 0 ), radius * 2 );
    }

}


void Viewer::update_frame_id( int new_frame_id ){
    if ( new_frame_id < 0 )
        current_frame_id = 0;
    else if ( new_frame_id > (int)ground_truth_paths.size() - 1 )
        current_frame_id = (int)ground_truth_paths.size() - 1;
    else
        current_frame_id = new_frame_id;

    current_frame_id_string      = QString::number( ground_truth_paths[ current_frame_id ].second ).rightJustified( id_padding, '0', false );
    current_frame_id_short_str = QString::number( current_frame_id );

}


void Viewer::update_image(){

    if ( ui->radio_depth->isChecked())
        path_display = path_current_depth;
    else if ( ui->radio_rgb->isChecked())
        path_display = path_current_rgb;
    else if ( ui->radio_rgbd->isChecked())
        path_display = path_current_rgbd;

    source_img = cv::imread( path_display.toStdString() );
    current_img = source_img.clone();
}
