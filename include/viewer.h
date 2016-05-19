#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>
#include <QDir>
#include <QImageWriter>
#include <QTextStream>
#include <opencv2/opencv.hpp>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QDebug>
#include <fstream>

struct AnnotationPatch {
    double joint_x;
    double joint_y;
};

namespace Ui {
    class MainWindow;
}

class Viewer : public QMainWindow {
    Q_OBJECT

public:
    // constructors/destructors
    explicit Viewer( QWidget *parent = 0 );
    ~Viewer();

private:

    // base paths
    QString path_annotations;
    QString path_base;
    QString path_depth;
    QString path_rgb;
    QString path_rgbd;

    // frame paths
    QString path_current_annotations;
    QString path_current_depth;
    QString path_display;
    QString path_current_rgb;
    QString path_current_rgbd;

    // configuration variables
    int joint_radius;
    int frames_start;
    int frame_step;
    int frames_total;
    int id_padding;

    // frame variables
    int current_frame_id;
    QString current_frame_id_string;
    QString current_frame_id_short_str;
    QVector<std::pair<QString, int> > ground_truth_paths;
    bool is_sequence_loaded;

    // drawing variables
    cv::Mat current_img;
    QImage qt_img;
    cv::Mat source_img;

    // interaction variables
    bool ctrl_click;
    bool ctrl_key;
    int sel_mouse_x;
    int sel_mouse_y;
    bool shift_click;
    bool shift_key;

    // annotations of the frame
    QVector<AnnotationPatch> annotations;

    Ui::MainWindow *ui;

    void colorize_black();
    void error_manager( int type );
    void read_annotations();
    int round_to_int( double num );
    void update_all();
    void update_all( int new_frame_id );
    void update_annotations();
    void update_base_paths();
    void update_current_paths();
    void update_display();
    void update_frame_id( int new_frame_id );
    void update_image();
    void update_list();
    void update_path_array();

private slots:
    void on_next_button_clicked();
    void on_prev_button_clicked();
    void on_update_frame_id_clicked();
    void on_radio_rgb_clicked();
    void on_radio_depth_clicked();
    void on_radio_rgbd_clicked();
    void mouse_position();
    void mouse_left();
    void mouse_pressed();
    void mouse_release();
    void keyPressEvent( QKeyEvent *my_key );
    void keyReleaseEvent( QKeyEvent *my_key );
    void new_path_selected();
    void on_finger_list_currentRowChanged( int current_row );
    void on_finger_list_itemSelectionChanged();
    void on_browse_path_clicked();

};

#endif // VIEWER_H
