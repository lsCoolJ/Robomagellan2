// scp pi@172.22.157.127:/home/pi/Robomagellan2/image2.bmp .
// scp camera.cpp pi@172.22.157.127:/home/pi/Robomagellan2/
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

#define HEIGHT 480
#define WIDTH 640
#define W_OFFSET 18
#define H_OFFSET 28
#define WH_SIZE 1
#define HEADER_SIZE 54

#define RESOLUTION "640x480"

#define RED_MAX 255
#define RED_MIN 210

#define GRN_MIN 90
#define GRN_MAX 150

#define BLU_MIN 0
#define BLU_MAX 55

// takes a picture using fswebcam and stores it in image.bmp
void createPic(void) {
    system("fswebcam -r 640x480 image.jpg");
}

// analyzes pixel
int analyzePixel(unsigned char r, unsigned char g, unsigned char b) {
    int retVal = 0;
    if((r > RED_MIN && r < RED_MAX) &&
      (g > GRN_MIN && g < GRN_MAX) &&
      (b > BLU_MIN && b < BLU_MAX)) {
        retVal = 1;
    }
    return retVal;
}

// Ben's method that he wrote
void analyzePicture() {
    unsigned char header[HEADER_SIZE];
    int picSize;
    FILE *picture = fopen("image.jpg", "r");
    FILE *picture2 = fopen("image2.jpg", "w");

    // Read in the header
    fread(header, sizeof(char), HEADER_SIZE, picture);

    // Declare array
    unsigned char img[HEIGHT][WIDTH*3];
    picSize = HEIGHT * WIDTH * 3;

    // Read in the image
    fread(img, sizeof(char), picSize, picture);

    int r, c;
//    for(r = 0; r < HEIGHT; r++) {
//        for(c = 0; c < WIDTH * 3; c = c + 3) {
//            img[r][c] = 0x00;
            // int check = analyzePixel(img[r][c], img[r][c+1], img[r][c+2]);
            // if(check == 0) {
            //     img[r][c] = 0x00;
            //     img[r][c+1] = 0x00;
            //     img[r][c+2] = 0x00;
            // } else {
            //     img[r][c] = 0xFF;
            //     img[r][c+1] = 0xFF;
            //     img[r][c+2] = 0xFF;
            // }
//        }
//    }

    for (r = 0; r < HEIGHT; r++) {
       for (c = 0; c < WIDTH * 3; c += 3) {
           char temp = img[r][c];
           img[r][c] = img[r][c+1];
           img[r][c+1] = temp; 
       }

    } 

    fwrite(header, sizeof(char), HEADER_SIZE, picture2);
    fwrite(img, sizeof(char), HEIGHT * WIDTH * 3, picture2);

    fclose(picture);
    fclose(picture2);
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
// void openPic() {

//     FILE *imageFile = fopen("image.bmp", "r");
//     FILE *image2 = fopen("image2.bmp", "w");
//     char header[54];

//     int widthTemp; // not using these because we're storing them into the command
//     int heightTemp;

//     fread(header, 1, 54, imageFile); // remove the offset off the first file

//     unsigned char image[HEIGHT][WIDTH*3];
//     fread(image, 1, HEIGHT * WIDTH * 3, imageFile);
    
// //    analyzePicture(image);

//     unsigned char red, green, blue;
//     int pass = 1;
//     int r, c;

//     // cycles through the rows and columns and stores the average of the pixels
//     for (r = 0; r < HEIGHT; r++) {
//         for (c = 0; c < WIDTH * 3; c++) {
//             switch(pass) {
//                 case 1 : red = image[r][c];
//                   break;
//                 case 2 : green = image[r][c];
//                   break;
//                 case 3 : blue = image[r][c];
//                   break;
//             }
//             // if (pass == 3) {
//                 // if(!analyzePixel(red, green, blue)) {
//             image[r][c] = 0;
// //                    image[r][c - 2] = image[r][c - 1] = image[r][c] = 0;
//                 // }
//             //     pass = 1;
//             // }
//             pass++;
//         }
//     }

//     fwrite(header, 1, 54, image2);
//     fwrite(image, 1, HEIGHT * WIDTH * 3, image2);
// }

void showPic() {
    system("fim -a image2.bmp");
}

int main(void) {
    createPic();
    analyzePicture();
    //openPic();
    showPic();
    return 0;
}