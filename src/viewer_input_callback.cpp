#include "viewer.h"
#include "ui_mainwindow.h"



void Viewer::keyPressEvent( QKeyEvent *my_key ){

    if ( my_key->key() == Qt::Key_Escape )
        this->close();
    else if ( is_sequence_loaded == false )
        return;
    else if ( my_key->key() == Qt::Key_Left && !ctrl_key )
        on_prev_button_clicked();
    else if ( my_key->key() == Qt::Key_Right && !ctrl_key )
        on_next_button_clicked();
    else if ( my_key->key() == Qt::Key_U )
        on_update_frame_id_clicked();
    else if ( my_key->key() == Qt::Key_R ) {
        ui->radio_rgb->setChecked( true );
        on_radio_rgb_clicked();
    }else if ( my_key->key() == Qt::Key_T ) {
        ui->radio_rgbd->setChecked( true );
        on_radio_rgbd_clicked();
    }else if ( my_key->key() == Qt::Key_D ) {
        ui->radio_depth->setChecked( true );
        on_radio_depth_clicked();
    }
}


void Viewer::keyReleaseEvent( QKeyEvent *my_key ){
    if ( my_key->key() == Qt::Key_Shift )
        shift_key = false;
}


void Viewer::mouse_position(){
    ui->myLabel_Mouse_X->setText( QString::number( ui->myLabel_IMG->mouse_X ) );
    ui->myLabel_Mouse_Y->setText( QString::number( ui->myLabel_IMG->mouse_Y ) );
    if ( ctrl_click || shift_click )
        update_display();
}


void Viewer::mouse_pressed(){
    if ( is_sequence_loaded == false )
        return;
}


void Viewer::mouse_release(){
    if ( annotations.size() == 0 )
        return;
    ui->finger_list->clearSelection();
    double best_dist = 999999999;
    int best_id = -1;
    // find the closest point to the clicked position
    for ( int i = 0; i < (int)annotations.size(); i++ ) {
        // calculate distance
        double dist = sqrt( pow((double)ui->myLabel_IMG->mouse_X - annotations[i].joint_x, 2 ) + pow((double)ui->myLabel_IMG->mouse_Y - annotations[i].joint_y, 2 ));
        if ( dist < best_dist ) {
            best_id = i;
            best_dist = dist;
        }
    }
    // select the closest point
    ui->finger_list->setCurrentRow( best_id, QItemSelectionModel::Toggle );
    update_display();

}


void Viewer::mouse_left(){
}
