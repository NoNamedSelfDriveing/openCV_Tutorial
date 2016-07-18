# LoadImage

openCV에서 이미지를 불러오고 출력

---

# 소스코드

```
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
   string imageName("potato.jpg");

    if( argc > 1 )
    {
        imageName = argv[1];
    }

    Mat image;
    image = imread(imageName, IMREAD_COLOR);

    if( image.empty() )
    {
        cout << "Could not open or find the Image" << std::endl;
        return -1;
    }

    namedWindow("Display Potato", WINDOW_AUTOSIZE);
    imshow("Display Potato", image);

    waitKey(0);
    return 0;
}
```
---

#  소스 설명

## inlcude

core, imgcodecs, highgui 을 include 한다<br>
- core        : opencv의 핵심적인 알고리즘 함수를 지원한다.<br>
- imgcodecs   : 이미지를 읽고 쓸수 있는 함수를 지원한다.<br>
- highgui     : 화면에 표시할수 있는 다양한 함수를 지원한다.<br>

---

## Mat

openCV의 다차원 단 채널(gray), 다 채널(RGB) 배열 지원 클래스이다.<br>
추후 openCV 구조체에 대해서 설명할 때 자세하게 조사할 예정이다. <br>

---

## imread

이미지를 읽는 함수로 imgcodecs에 선언되어 있다.<br>

### C++
    Mat imread(const String& filename, int flags=IMREAD_COLOR )

### C
    IplImage* cvLoadImage(const char* filename, int iscolor=CV_LOAD_IMAGE_COLOR )
    CvMat* cvLoadImageM(const char* filename, int iscolor=CV_LOAD_IMAGE_COLOR )

### Python
    cv2.imread(filename[, flags]) → retval


### 인자
인자로는 file의 path를 나타내는 filename과<br>
이미지 읽기 방식인 flags가 존재 한다.<br>


### flags

- CV_LOAD_IMAGE_ANYDEPTH - set된 경우 대응하는 깊이의 비트(8/16/32) 이미지를 읽는다.
- CV_LOAD_IMAGE_COLOR - set된 경우 컬러이미지로 읽는다.
- CV_LOAD_IMAGE_GRAYSCALE - set된 경우 gray 이미지로 읽는다.


- 0 < flags - 3채널 컬러 이미지로 읽는다.
- 0 = flags - gray로 읽는다.
- 0 > flags - 원본 이미지로 읽는다.

---

## namedWindow

화면을 표시할 윈도우를 생성한다. <br>

### C++
    void namedWindow(const string& winname, int flags=WINDOW_AUTOSIZE )

### C
    int cvNamedWindow(const char* name, int flags=CV_WINDOW_AUTOSIZE )

### Python
    cv2.namedWindow(winname[, flags]) → None


### 인자
인자로는 윈도우의 이름인 name과 flags로 구성된다.<br>

### flags

- WINDOW_NORMAL - set된 경우 수동으로 창을 변경 할 수 있다.
- WINDOW_AUTOSIZE - set된 경우 자동으로 창을 표시되는 이미지에 맞춘다.
수동으로 창을 변경 불가능하다.
- WINDOW_OPENGL - set된 경우 openGL로 표시한다.

---

## imshow

이미지를 표시한다.<br>

### C++
    void imshow(const string& winname, InputArray mat)

### C
    cvShowImage(const char* name, const CvArr* image)

### Python
     cv.ShowImage(name, image) → None


### 인자
인자로는 표시할 윈도우이름인 name과 표시할 이미지인 image로 이루워진다.

---

## waitKey

키 입력을 기다린다.<br>

### C++
    int waitKey(int delay=0)

### C
    int cvWaitKey(int delay=0)

### Python
    cv.WaitKey(delay=0)

### 인자
인자로 얼마나 키를 기다릴지 설정하며 ms단위이다. <br>
인자에 0이 전달될 경우 입력이 될때 까지 무한정 블록된다.<br>

---
