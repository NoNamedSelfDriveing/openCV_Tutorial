#include <iostream>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

int main()
{
    char *outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

    if (api->Init(NULL, "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    Pix *image = pixRead("0.tif");
    api->SetImage(image);

    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    api->End();
    delete [] outText;
    pixDestroy(&image);

    return 0;
}
