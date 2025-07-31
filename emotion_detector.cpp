#include "emotion_detector.hpp"
#include <iostream>

EmotionDetector::EmotionDetector(const std::string& modelPath) {
    net = cv::dnn::readNetFromONNX(modelPath);
    faceCascade.load(cv::samples::findFile("haarcascade_frontalface_default.xml"));
}

DetectedEmotion EmotionDetector::detectEmotion() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera.\n";
        return DetectedEmotion::Neutral;
    }

    cv::Mat frame, gray;
    for (int i = 0; i < 30; ++i) {
        cap >> frame;
        if (frame.empty()) continue;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(gray, faces);
        if (!faces.empty()) {
            cv::Mat face = gray(faces[0]);
            cv::resize(face, face, cv::Size(64, 64));
            face.convertTo(face, CV_32F, 1.0 / 255.0);
            cv::Mat blob = cv::dnn::blobFromImage(face);
            net.setInput(blob);
            cv::Mat out = net.forward();
            double conf;
            cv::Point maxLoc;
            cv::minMaxLoc(out.reshape(1,1), nullptr, &conf, nullptr, &maxLoc);

            int idx = maxLoc.x;
            cap.release();

            // idx mapping: 3=Happy, 4=Sad, 2=Neutral etc.
            if (idx == 3) return DetectedEmotion::Happy;
            if (idx == 4) return DetectedEmotion::Sad;
            if (idx == 2) return DetectedEmotion::Neutral;
            return DetectedEmotion::Neutral;
        }
    }

    cap.release();
    return DetectedEmotion::Neutral;
}
