const unsigned int X_MIN = 0;
const unsigned int X_MAX = 640;

const unsigned int Y_MIN = 0;
const unsigned int Y_MAX = 480;

const unsigned int HEADER_HEIGHT = 20;

const float PI = 3.141592653589;

const unsigned int GETIMAGE_METADATA_SIZE = 24;
const unsigned int GETIMAGE_BYTES_PER_PIXEL = 4;

float rad(unsigned int angle);
void write(int x, int y, char* str);
void redrawScore();
