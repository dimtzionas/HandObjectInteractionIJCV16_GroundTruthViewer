#include "viewer.h"
#include "ui_mainwindow.h"

void Viewer::error_manager( int type ){

    QMessageBox messageBox;

    switch ( type ) {
    case 1:
        messageBox.critical( 0, "Error", "The folder doesn't exist or doesn't contain a valid annotation" );
        break;
    case 2:
        messageBox.critical( 0, "Error", "The annotation file is empty." );
        break;
    case 3:
        messageBox.critical( 0, "Error", "The annotation folder is empty." );
        break;
    default:
        break;
    }
}
