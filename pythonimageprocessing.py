import os
import pprint

os.system("fswebcam -r 640x480 test.jpg")

from PIL import Image

def main():

    img = Image.open('test.jpg', 'r')
    print pprint.pprint(img)

    width, height = img.size

    print width,height
    img = img.convert('RGB')

    #colors = img.getcolors()
  #  print pprint.pprint(img)
    r, g, b = img.getpixel((1,1))

    count = 0

    for i in range(width):
       for j in range(height):
           r, g, b = img.getpixel((i, j))
           if r <= 255 and r >= 210 and g <= 150 and g >= 90 and b >= 0 and b <= 155:
              # print i,j
              count+=1
          # print r, g, b
    #print colors
    print count

main()
