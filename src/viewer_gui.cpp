#include "viewer.h"
#include "ui_mainwindow.h"




void Viewer::new_path_selected(){

    try{
        update_base_paths();
        QDir currDir = path_annotations;
        if ( currDir.exists() == false ) {
            error_manager( 1 );
            return;
        }
        if ( currDir.count() == 2 ) {
            error_manager( 3 );
            return;
        }
        update_path_array();

        QString filterStr = QString( "*.txt" );
        currDir.setNameFilters( QStringList() << ( filterStr ) );
        QStringList fileList = currDir.entryList();
        frames_total = fileList.size();
        ui->myLabel_Img_TotalNumb->setText( QString::number( frames_total ) );
        ui->myGroupBox->setEnabled( true );
        update_all( frames_start );
        is_sequence_loaded = true;

    }
    catch ( ... ) {
        error_manager( 1 );
    }

}


void Viewer::on_next_button_clicked(){
    update_all( current_frame_id + frame_step );
}


void Viewer::on_prev_button_clicked(){
    update_all( current_frame_id - frame_step );
}


void Viewer::on_update_frame_id_clicked(){
    update_all( ui->frame_id_edit->toPlainText().toInt() );
}


void Viewer::on_radio_rgb_clicked(){
    update_all();
}


void Viewer::on_radio_rgbd_clicked(){
    update_all();
}


void Viewer::on_radio_depth_clicked(){
    update_all();
}


void Viewer::colorize_black(){
    cv::Mat temp = cv::Mat::zeros( ui->myLabel_IMG->height(), ui->myLabel_IMG->width(), CV_8UC3 );

    ui->myLabel_IMG->setPixmap( QPixmap::fromImage( QImage((uchar*)temp.data, temp.cols, temp.rows, QImage::Format_RGB888 ) ) );
}

void Viewer::on_finger_list_currentRowChanged( int current_row ){
    if ( current_row == -1 )
        return;
    ui->finger_x_coord->show();
    ui->finger_y_coord->show();
    ui->x_joints_label->show();
    ui->y_joints_label->show();
    ui->sel_joints_label->show();
    ui->finger_x_coord->setText( QString::number( round_to_int( annotations[current_row].joint_x )));
    ui->finger_y_coord->setText( QString::number( round_to_int( annotations[current_row].joint_y )));

}


void Viewer::on_finger_list_itemSelectionChanged(){
    update_display();
}


int Viewer::round_to_int( double num ){
    return std::floor( num + 0.5 );
}


void Viewer::on_browse_path_clicked(){
    QString path = ui->path_to_load->toPlainText();
    QString folder = QFileDialog::getExistingDirectory( this, tr( "Select Folder" ), path);

    if ( folder != "" ) {
        ui->path_to_load->setPlainText( folder );
        new_path_selected();
    }

}
