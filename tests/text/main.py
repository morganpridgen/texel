import texel
from math import *

texel.init()
d = texel.Display("test")
texel.loadFont("font.png")
text = texel.Texture("Hello!", isText=True)

tX, tY, tW, tH, tR = 320, 180, 1, 1, 0
t = 0

while d.refresh():
  t += 1
  tR = t / 64
  if t > 120:
    tX = 320 + 64 * cos(t * (0.0174) / 2)
    tY = 180 + 64 * sin(t * (0.0174) / 2)
  if t > 240:
    tW = 1 + cos(t * (0.0174)) / 2
    tH = 1 + sin(t * (0.0174)) / 2
  
  text.setColorMod(texel.Color(sin(tR) / 2 + 0.5, cos(tR) / 2 + 0.5, (0 - sin(tR)) / 2 + 0.5))
  text.render(tX, tY, tW, tH, tR)

del(t)
del(d)
texel.end()