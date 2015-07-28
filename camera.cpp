#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

#define HEIGHT 720
#define WIDTH 1200
#define W_OFFSET 18
#define H_OFFSET 28
#define WH_SIZE 1
#define HEADER_SIZE 54

#define RED_MAX = 255
#define RED_MIN = 240

#define GRN_MIN = 255
#define GRN_MAX = 240

#define BLU_MIN = 255
#define BLU_MAX = 240

// takes a picture using fswebcam and stores it in image.bmp
int createPic(void) {
    system("fswebcam -r 1200x720 image.bmp");
}

// analyzes pixel
int analyzePixels(unsigned char r, unsigned char g, unsigned char b) {
    int retVal = 0;
    if(r >= RED_MIN && r <= RED_MAX && retVal &&
      g >= GRN_MIN && g <= GRN_MAX && retVAL && b >= BLU_MIN && b <= BLU_MAX) {
        retVal = 1;
    }
    return retVal;
}

// analyzes the picture
void analyzePicture(unsigned char image[HEIGHT][WIDTH*3]) {
    unsigned char red, green, blue;
    int pass = 1;
    // cycles through the rows and columns and stores the average of the pixels
    for (r = 0; r < HEIGHT; r++) {
        for (c = 0; c < WIDTH; c++) {
            switch(pass) {
                case 1 : red = image[r][c];
                  break;
                case 2 : green = image[r][c];
                  break;
                case 3 : blue = image[r][c];
                  break;
            }
            if (pass == 3) {
                if(!analyzePixel(image[r][c])) {
                    image[r][c - 2] = image[r][c - 1] = image[r][c] = 0;
                }
                pass = 1;
            }
        }
    }
}

// open picture 
void openPic() {

    FILE *imageFile = fopen("image.bmp", "rw");
    char header[54];

    int widthTemp; // not using these because we're storing them into the command
    int heightTemp;

    fread(header, 1, 54, imageFile); // remove the offset off the first file

    unsigned char image[HEIGHT][WIDTH*3];
    fread(image, 1, HEIGHT * WIDTH * 3, imageFile);
    
    analyzePicture(image);

    fwrite(header, 1, 54, imageFile);
    fwrite(image, 1, HEIGHT * WIDTH * 3, imageFile);
}

void showPic() {
    system("fim -a image.bmp");
}

int main(void) {
    createPic();
    openPic();

    return 0;
}