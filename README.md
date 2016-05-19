Hand 2D Ground Truth viewer
=================

A tool to view the data set and the ground truth created for the project **"Capturing Hands in Action using Discriminative Salient Points and Physics Simulation"** published in IJCV (2016). The datasets can be obtained freely in the project page http://files.is.tue.mpg.de/dtzionas/Hand-Object-Capture/ 


Dependencies
----

Opencv and QT 4 and CMake

Build
----

    mkdir build
    cd build
    cmake ..
    make

Run
----

    cd bin
    ./viewer

In the gui window, click in the browse button and select the base folder of the dataset. For example: for dataset 01 you will have to select the subfolder inside called "1" that has the folders "rgb", "rgb", etc. below it.

    |-01
      |- 1 <-- folder to choose
         |- rgb
         |- rgbd
         |- joints_2D_GT
         |- depth_viz
         |- annotations
         |- detections
         |- pcl


