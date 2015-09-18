
import os
import pprint

#os.system("fswebcam -r 640x480 test.jpg")

from PIL import Image

def main():

    img = Image.open('test.jpg', 'r')

   # print pprint.pprint(img)

    width, height = img.size
    imgNew = Image.new('RGB', (width, height), "black")
    pixels = imgNew.load()

    #print width,height
    img = img.convert('RGB')

    #colors = img.getcolors()
  #  print pprint.pprint(img)
    r, g, b = img.getpixel((1,1))

    count = 0

    widthPixels = [0] * width
    greatestIndex = -1
    for i in range(width):
       widthPixels[i] = 0;
       for j in range(height):
           r, g, b = img.getpixel((i, j))
           if r <= 255 and r >= 210 and g <= 150 and g >= 30 and b >= 0 and b <= 100: # g 90 # b 155
              pixels[i, j] = (255, 255, 255) 
              # print i,j
              #if i in widthPixels:
              widthPixels[i] = widthPixels[i] + 1
              #else:
              #    widthPixels[i] = 1
              count+=1
          # print r, g, b
    #print colors
    maxWidth = max(widthPixels)
    for i in range(width):
        if widthPixels[i] == maxWidth:
            greatestIndex = i
            break
    print greatestIndex 
    imgNew.save("new.jpg")
    
    

main()
