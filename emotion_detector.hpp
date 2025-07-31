#ifndef EMOTION_DETECTOR_HPP
#define EMOTION_DETECTOR_HPP

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <string>

enum class DetectedEmotion { Happy, Sad, Neutral };

class EmotionDetector {
public:
    EmotionDetector(const std::string& modelPath);
    DetectedEmotion detectEmotion();

private:
    cv::dnn::Net net;
    cv::CascadeClassifier faceCascade;
};

#endif
