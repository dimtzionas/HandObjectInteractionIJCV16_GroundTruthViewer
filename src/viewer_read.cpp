#include "viewer.h"
#include "ui_mainwindow.h"


void Viewer::read_annotations(){

    QFile fileIN( path_current_annotations );

    fileIN.open( QIODevice::ReadOnly );
    if ( fileIN.size() == 0 ) {
        error_manager( 2 );
        fileIN.close();
        return;
    }

    annotations.clear();
    QTextStream myStreamIN( &fileIN );

    while ( !myStreamIN.atEnd()) {
        AnnotationPatch temp;
        int dummyInt;
        myStreamIN >> dummyInt;
        myStreamIN >> temp.joint_x;
        myStreamIN >> temp.joint_y;
        annotations.push_back( temp );
    }

    fileIN.close();

}
