#include <stdio.h>
#include <iostream>
#include <string>


// takes a picture using fswebcam and stores it in image.bmp
int create_pic(void) {
    system("fswebcam -r 1200x720 image.bmp");
}

// open picture
int open_pic(void) {
    system("fim -a image.bmp");
}

int main(void) {
    create_pic();
    open_pic();
    return 0;
}