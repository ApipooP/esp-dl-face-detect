# ESP-DL Human Face Detecion

This is a part of *2102642 Computer Vision* final project.
This project is based on [ESP-DL](https://github.com/espressif/esp-dl)
[Human Face Detection](https://github.com/espressif/esp-dl/tree/master/examples/human_face_detect) example. The image used in the experiment can be changed by
using the header file generated from `tools/image_tool/convert_to_u8.py`.
Each run will be timed on both one-stage detection (find only the face bounding boxes)
and two-stages detection (bounding boxes and facial keypoints such as eyes, nose, mouths)
to evaluate the performance.

## Requirements

- ESP32/ESP32-S2/ESP32-S3
- ESP-IDF 4.4.x

## How to Run the Project

1. Open Terminal and go to `esp-dl-face-detect/human_face_detect`, the directory where this project is stored:

        cd ~/esp-dl-face-detect/human_face_detect

2. Set SoC target:

        idf.py set-target [SoC]
    
    Replace [SoC] with your target, such as `esp32`, `esp32s2`, and `esp32s3`.

3. Flash the program and launch IDF monitor to obtain the fractional and coordinate values of detection results:

        idf.py flash monitor

    Note: In some board variants of the ESP32, you might have to pull the GPIO0 low in order
    to set the chip in flash mode. In most board, this can be done by pressing the IO0/BOOT button.

4. The tool `display_image.py` stored in `tools/image_tool/` allows you to directly view the image of detection results. According to instructions, run the following command:

        python display_image.py -i ../human_face_detect/image.jpg -b "(x1, y1, x2, y2)" -k "(x1, y1, x2, y2, ... , xn, yn)"

    See more how to use the `display_image.py` in the `tools/image_tool/README.md`.
