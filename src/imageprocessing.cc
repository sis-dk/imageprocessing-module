
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <nan.h>
#include <v8.h>

using namespace std;
using namespace cv;

using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;
using std::pow;
using std::sqrt;
using v8::Function;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

Mat resize(Mat image, int width = 1024, int height = 768) {
    if (image.size[0] < 768 && image.size[1] < 1024) {
        return image;
    }
    int h = image.size[0];
    int w = image.size[1];
    float r1 = (float)height / h;
    float r2 = (float)width / w;

    tuple<int, int> dim;

    if (width == 0) {
        dim = make_tuple(w * r1, height);
    }

    else if (height == 0) {
        dim = make_tuple(width, h *r2);
    }

    else {
        if (r1 < r2) {
            dim = make_tuple(w * r1, height);
        }
        else {
            dim = make_tuple(width, h * r2);
        }
    }
    Mat resized = image;

    resize(image, resized, Size(get<0>(dim), get<1>(dim)), 0, 0);

    return resized;
}

pair<int, int> find_points(Mat image, int x = 384, int y = 512) {
    int h = image.size[0];
    int w = image.size[1];

    int pt1 = (y - (w/2));
    int pt2 = (x - (h/2));

    return make_pair(pt1, pt2);
}

Mat merge_images(Mat image, int pt1, int pt2) {
    int height = 768;
    int width = 1024;

    Mat background(height, width, CV_8UC3, Scalar(0, 0, 0));

    image.copyTo(background(Rect (pt1, pt2, image.size[1], image.size[0])));

    return background;
}

string ResizeImageC() {

    string imagePath = "/Users/sisir/cosmos/repo/experiments/imageprocessor-module/high-res.jpg";
    
    Mat image;
    image = imread(imagePath, cv::IMREAD_COLOR);

    if(! image.data ) {
        return "Could not open or find the image";
    }

    Mat resized = resize(image);
    pair <int, int> points = find_points(resized);
    Mat merged = merge_images(resized, get<0>(points), get<1>(points));
    imwrite("/Users/sisir/Downloads/imagemerged.jpeg", merged);
    return imagePath;
}

NAN_METHOD(ResizeImage) {
  const std::string s = ResizeImageC();
  info.GetReturnValue().Set(New<v8::String>(s).ToLocalChecked());
}

NAN_MODULE_INIT(Init) {
  NAN_EXPORT(target, ResizeImage);
}

NODE_MODULE(imageprocessing, Init)