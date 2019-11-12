#coding=utf-8 
from PIL import Image

img = Image.open("rt3.ppm")
img.save("rt3.png")
img.show()