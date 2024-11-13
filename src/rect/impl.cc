#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
        
    cv::Mat gray_image;
    cv::cvtColor(input, gray_image, cv::COLOR_BGR2GRAY);

    
    cv::Mat binary_image;
    cv::threshold(gray_image, binary_image, 127, 255, cv::THRESH_BINARY);

    
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary_image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    
    std::vector<std::vector<cv::Point>> rect_contours;

    
    for (const auto& contour : contours) {
        double epsilon = 0.02 * cv::arcLength(contour, true);
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contour, approx, epsilon, true);

        if (approx.size() == 4) {
            rect_contours.push_back(approx);
        }
    }

    
    if (rect_contours.empty()) {
        return res;
    }

    
    cv::Rect bounding_rect = cv::boundingRect(rect_contours[0]);
    cv::RotatedRect min_area_rect = cv::minAreaRect(rect_contours[0]);

    res = std::make_pair(bounding_rect, min_area_rect);

    
    return res;
}