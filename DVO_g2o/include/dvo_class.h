
#ifndef SIMPLE_DVO_DVO_CLASS_H
#define SIMPLE_DVO_DVO_CLASS_H


#include "opencv2/opencv.hpp"
#include "image_alignment.h"
#include "util.h"
#include "Optimizer.h"
#include "Converter.h"
#include <Eigen/Geometry>
#include <string>
#include <vector>
#include<iostream>
#include<fstream>
#include <time.h>
#include <boost/filesystem.hpp>


using namespace std;

enum TUM{
    TUM1,
    TUM2,
    TUM3
};


class DVO {
    private:
        cv::Mat img_prev, depth_prev;
        Eigen::Matrix3f K;
        // aligment module
        ImageAlignment backend;

        //pose optimizer
        Optimizer optimizer;


        // variable for file input
        string AssociationFilename;
        string DataPath;
        vector<string> vstrImageFilenamesRGB;
        vector<string> vstrImageFilenamesD;
        vector<double> vTimestamps;
        int prev_idx = -1;
        int nImages;

        // pose constraint 
        vector<int> KF_list;
        vector<vector<int>> Loop_list;

        ofstream logfile;


    private:
        void load_intrinsic(TUM type);
        void LoadImages(const string &strAssociationFilename);
        void setupLog();
        void LogInfo(int frame_idx, Eigen::Matrix4f T);

    public:
        DVO(string strAssociationFilename, string strDataPath, TUM type);
        ~DVO();
        Eigen::Matrix4f incr_Align_KF(int prev_KF_idx, int cur_KF_idx);
        Eigen::Matrix4f Align_two_Frame(int Frame1, int Frame2, Eigen::Matrix4f T_init);

        void build_graph(vector<int> KF_list, vector<vector<int>> Loop_Closure);
        void odom_only(int start_idx, int end_idx);
        
    
};
#endif //SIMPLE_DVO_DVO_CLASS_H