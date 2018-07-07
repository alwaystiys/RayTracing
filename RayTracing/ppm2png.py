#coding=utf-8 
from PIL import Image

img = Image.open("example.ppm")
img.save("example.png")
img.show()