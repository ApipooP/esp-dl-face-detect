#include <stdio.h>
#include "human_face_detect_msr01.hpp"
#include "human_face_detect_mnp01.hpp"
#include "dl_tool.hpp"
#include <string>

// Select only one image header file. Uncomment to active.
// #include "mona.hpp"
#include "vanGogh.hpp"
// #include "people.hpp"


void inferenceOneStage(bool showLatency = true) {
    dl::tool::Latency latency;
    HumanFaceDetectMSR01 s1(0.3F, 0.5F, 10, 0.2F);

    if (showLatency) latency.start();
    std::list<dl::detect::result_t>& results = s1.infer((uint8_t*)IMAGE_ELEMENT, { IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNEL });
    if (showLatency) {
        latency.end();
        latency.print("Inference latency");
    }

    std::string boxArgs = "";
    int i = 0;
    for (std::list<dl::detect::result_t>::iterator prediction = results.begin(); prediction != results.end(); prediction++, i++) {
        for (int point = 0; point < 4; point++) {
            boxArgs += std::to_string(prediction->box[point]);
            if (point != 3) boxArgs += ", ";
        }
        if (std::next(prediction) != results.end()) boxArgs += ", ";
        printf("[%d] score: %f, box: [%d, %d, %d, %d]\n", i, prediction->score, prediction->box[0], prediction->box[1], prediction->box[2], prediction->box[3]);
    }
    printf("display_image.py arguments:\n-b \"(%s)\"\n\n", boxArgs.c_str());
}

void inferenceTwoStage(bool showLatency = true) {
    dl::tool::Latency latency;
    HumanFaceDetectMSR01 s1(0.1F, 0.5F, 10, 0.2F);
    HumanFaceDetectMNP01 s2(0.5F, 0.3F, 5);

    if (showLatency) latency.start();
    std::list<dl::detect::result_t>& candidates = s1.infer((uint8_t*)IMAGE_ELEMENT, { IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNEL });
    std::list<dl::detect::result_t>& results = s2.infer((uint8_t*)IMAGE_ELEMENT, { IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNEL }, candidates);
    if (showLatency) {
        latency.end();
        latency.print("Inference latency");
    }

    std::string boxArgs = "";
    std::string keypointsArgs = "";
    int i = 0;
    for (std::list<dl::detect::result_t>::iterator prediction = results.begin(); prediction != results.end(); prediction++, i++) {
        for (int point = 0; point < 4; point++) {
            boxArgs += std::to_string(prediction->box[point]);
            if (point != 3) boxArgs += ", ";
        }
        for (int point = 0; point < 10; point++) {
            keypointsArgs += std::to_string(prediction->keypoint[point]);
            if (point != 9) keypointsArgs += ", ";
        }
        if (std::next(prediction) != results.end()) {
            boxArgs += ", ";
            keypointsArgs += ", ";
        }

        printf("[%d] score: %f, box: [%d, %d, %d, %d]\n", i, prediction->score, prediction->box[0], prediction->box[1], prediction->box[2], prediction->box[3]);
        printf("    left eye: (%3d, %3d), ", prediction->keypoint[0], prediction->keypoint[1]);
        printf("right eye: (%3d, %3d)\n", prediction->keypoint[6], prediction->keypoint[7]);
        printf("    nose: (%3d, %3d)\n", prediction->keypoint[4], prediction->keypoint[5]);
        printf("    mouth left: (%3d, %3d), ", prediction->keypoint[2], prediction->keypoint[3]);
        printf("mouth right: (%3d, %3d)\n", prediction->keypoint[8], prediction->keypoint[9]);
    }
    printf("display_image.py arguments:\n -b \"(%s)\" -k \"(%s)\"\n\n", boxArgs.c_str(), keypointsArgs.c_str());
}

extern "C" void app_main(void) {
    inferenceOneStage(true);
    inferenceTwoStage(true);
}