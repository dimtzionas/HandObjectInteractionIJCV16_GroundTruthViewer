#include "viewer.h"
#include "ui_mainwindow.h"

bool pairCompare( const std::pair<QString, int>& firstElem, const std::pair<QString, int>& secondElem ){
    return firstElem.second < secondElem.second;

}


void Viewer::update_base_paths(){
    path_base = ui->path_to_load->toPlainText();
    if ( path_base.endsWith( "/" ) == false )
        path_base += "/";

    path_rgb      = QString( path_base + "rgb"         + "/" );
    path_rgbd     = QString( path_base + "rgbd"        + "/" );
    path_depth = QString( path_base + "depth_viz"   + "/" );
    path_annotations     = QString( path_base + "joints_2D_GT" + "/" );

    QStringList myStringListFromPath;
    QRegExp regex( "/" );
    myStringListFromPath = path_base.split( regex, QString::SkipEmptyParts );
}


void Viewer::update_path_array(){

    QDir currDir = path_annotations;

    ground_truth_paths.clear();

    QString filterStr = QString( "*.txt" );

    currDir.setNameFilters( QStringList() << ( filterStr ) );

    QFileInfoList files = currDir.entryInfoList();
    foreach( QFileInfo file, files ){
        if ( !file.isDir()) {
            QString filename  = file.fileName();
            int position = filename.section( ".", 0, 0 ).toInt();
            ground_truth_paths.push_back( std::pair<QString, int>( file.canonicalPath(), position ) );
        }
    }
    std::sort( ground_truth_paths.begin(), ground_truth_paths.end(), pairCompare );
}


void Viewer::update_current_paths(){
    path_current_rgb         = QString( path_rgb      + current_frame_id_string + ".png" );
    path_current_rgbd        = QString( path_rgbd     + current_frame_id_string + ".png" );
    path_current_depth    = QString( path_depth + current_frame_id_string + ".png" );
    path_current_annotations        = QString( path_annotations     + current_frame_id_string + ".txt" );
}
