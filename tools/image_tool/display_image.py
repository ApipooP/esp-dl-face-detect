import cv2
import numpy
import argparse

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Model generator tool')
    parser.add_argument('-i', '--image', help='path to image')
    parser.add_argument('-o', '--output', help='path to output')
    parser.add_argument('-b', '--box', help='box coordinate in \"(x1, y1, x2, y2)\"', default='None')
    parser.add_argument('-k', '--keypoints', help='keypoints \"(x1, y1, x2, y2, ... , xn, yn)\"', default='None')
    args = parser.parse_args()

    if args.image is None:
        parser.print_help()
        quit()

    image = cv2.imread(args.image)
    output = args.output
    keypoints = eval(args.keypoints)
    if args.box != 'None':
        boxarg = eval(args.box)
        boxes = []
        for i in range(0, len(boxarg)//4):
            boxes.append((boxarg[0 + i*4], boxarg[1 + i*4],
                          boxarg[2 + i*4], boxarg[3 + i*4]))

        for box in boxes:
            image = cv2.rectangle(
                image, (box[0], box[1]), (box[2], box[3]), (255, 0, 0), 2)

    if keypoints:
        keypoints = numpy.reshape(keypoints, (-1, 2))
        for keypoint in keypoints:
            image = cv2.circle(image, tuple(keypoint), 2, (0, 255, 0), 2)

    if output is not None:
        cv2.imwrite(output, image)
    else:
        cv2.imshow('example', image)
        cv2.waitKey(0)
