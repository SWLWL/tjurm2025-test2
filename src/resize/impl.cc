#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    cv::Mat ans(new_rows,new_cols,input.type());
    for(int y=0;y<new_rows;y++){
        for(int x=0;x<new_cols;x++){
            double old_x=(double)x/(double)scale;
            double old_y=(double)y/(double)scale;

            int x1=(int)old_x;
            int y1=(int)old_y;
            int x2=x1+1;
            int y2=y1+1;

            if (x1 >= input.cols) x1 = input.cols - 1;
            if (y1 >= input.rows) y1 = input.rows - 1;
            if (x2 >= input.cols) x2 = input.cols - 1;
            if (y2 >= input.rows) y2 = input.rows - 1;

            for (int channel = 0; channel < 3; channel++) {
                
                double v1 = input.at<cv::Vec3b>(y1, x1)[channel];
                double v2 = input.at<cv::Vec3b>(y1, x2)[channel];
                double v3 = input.at<cv::Vec3b>(y2, x1)[channel];
                double v4 = input.at<cv::Vec3b>(y2, x2)[channel];

                double h1 = (x2 - old_x) * v1 + (old_x - x1) * v2;
                double h2 = (x2 - old_x) * v3 + (old_x - x1) * v4;
                double new_value = (y2 - old_y) * h1 + (old_y - y1) * h2;
                ans.at<cv::Vec3b>(y, x)[channel] = static_cast<uchar>(new_value);
            }
        }
    }

    return ans;

}