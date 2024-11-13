#include "impls.h"
#include <algorithm>

float compute_iou(const cv::Rect& a, const cv::Rect& b) {
    /**
     * 要求：
     *      有一个重要的指标叫做“交并比”，简称“IOU”，可以用于衡量
     * 两个矩形的重合程度，本练习要求自行学习交并比的计算方式，计算输入
     * 的两个矩形的交并比。
     * 
     * 提示：
     * (1) 注意OpenCV中规定的xy坐标系方向跟平常的xy坐标系不一样。
     * (2) 注意矩形的x, y, width, height四个属性在坐标系内的含义。
     * (3) 注意分母不要除以0（不过我们不会测试这一点）
     * 
     * 通过条件：
     * 运行测试点，显示通过就行，不通过会告诉你哪一组矩形错了。
    */
    // IMPLEMENT YOUR CODE HERE
    
    int a_x = a.x;
    int a_y = a.y;
    int a_width = a.width;
    int a_height = a.height;

    
    int b_x = b.x;
    int b_y = b.y;
    int b_width = b.width;
    int b_height = b.height;

    
    int intersection_x = std::max(a_x, b_x);
    int intersection_y = std::max(a_y, b_y);
    int intersection_width = std::min(a_x + a_width, b_x + b_width) - intersection_x;
    int intersection_height = std::min(a_y + a_height, b_y + b_height) - intersection_y;

    
    intersection_width = std::max(0, intersection_width);
    intersection_height = std::max(0, intersection_height);

    
    float intersection_area = static_cast<float>(intersection_width * intersection_height);

    
    float a_area = static_cast<float>(a_width * a_height);

    
    float b_area = static_cast<float>(b_width * b_height);

    
    float union_area = a_area + b_area - intersection_area;

    
    return intersection_area / union_area;
   
}