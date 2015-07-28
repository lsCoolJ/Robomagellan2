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

#define RED_MAX 255
#define RED_MIN 200

#define GRN_MIN 255
#define GRN_MAX 200

#define BLU_MIN 255
#define BLU_MAX 200

// takes a picture using fswebcam and stores it in image.bmp
int createPic(void) {
    system("fswebcam -r 1200x720 image.bmp");
}

// analyzes pixel
int analyzePixel(unsigned char r, unsigned char g, unsigned char b) {
    int retVal = 0;
    if((r > RED_MIN) && (r < RED_MAX) &&
      (g > GRN_MIN) && (g < GRN_MAX) &&
      (b > BLU_MIN && b < BLU_MAX)) {
        retVal = 1;
    }
    return retVal;
}

// analyzes the picture
// void analyzePicture(unsigned char image[HEIGHT][WIDTH*3]) {
//     unsigned char red, green, blue;
//     int pass = 1;
//     int r, c;
//     // cycles through the rows and columns and stores the average of the pixels
//     for (r = 0; r < HEIGHT; r++) {
//         for (c = 0; c < WIDTH; c++) {
//             switch(pass) {
//                 case 1 : red = image[r][c];
//                   break;
//                 case 2 : green = image[r][c];
//                   break;
//                 case 3 : blue = image[r][c];
//                   break;
//             }
//             if (pass == 3) {
//                 if(!analyzePixel(red, green, blue)) {
//                     image[r][c - 2] = image[r][c - 1] = image[r][c] = 0;
//                 }
//                 pass = 1;
//             }
//         }
//     }
// }

// open picture 
void openPic() {

    FILE *imageFile = fopen("image.bmp", "rw");
    char header[54];

    int widthTemp; // not using these because we're storing them into the command
    int heightTemp;

    fread(header, 1, 54, imageFile); // remove the offset off the first file

    unsigned char image[HEIGHT][WIDTH*3];
    fread(image, 1, HEIGHT * WIDTH * 3, imageFile);
    
//    analyzePicture(image);

    unsigned char red, green, blue;
    int pass = 1;
    int r, c;

    // cycles through the rows and columns and stores the average of the pixels
    for (r = 0; r < HEIGHT; r++) {
        for (c = 0; c < WIDTH * 3; c++) {
            switch(pass) {
                case 1 : red = image[r][c];
                  break;
                case 2 : green = image[r][c];
                  break;
                case 3 : blue = image[r][c];
                  break;
            }
            if (pass == 3) {
                // if(!analyzePixel(red, green, blue)) {
                    image[r][c - 2] = image[r][c - 1] = image[r][c] = 0;
                // }
                pass = 1;
            }
            pass++;
        }
    }

    fwrite(header, 1, 54, imageFile);
    fwrite(image, 1, HEIGHT * WIDTH * 3, imageFile);
}

void showPic() {
    system("fim -a image.bmp");
}

int main(void) {
    createPic();
    openPic();
    showPic();
    return 0;
}