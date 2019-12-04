import texel
from math import *

texel.init()
d = texel.Display("test")
box = texel.Texture("box.png", 0, 32, 8)

bX, bY, bW, bH, bR = 320, 180, 1, 1, 0
t = 0

while d.refresh():
  t += 1
  bR = t / 64
  if t > 120:
    bX = 320 + 32 * cos(t * (0.0174) / 2)
    bY = 180 + 32 * sin(t * (0.0174) / 2)
  if t > 240:
    bW = 1 + cos(t * (0.0174)) / 2
    bH = 1 + sin(t * (0.0174)) / 2
  
  box.setClip(((t // 8) % 4) * 8, 0, 8, 8)
  box.setColorMod(texel.Color(sin(bR) / 2 + 0.5, cos(bR) / 2 + 0.5, (0 - sin(bR)) / 2 + 0.5))
  box.render(bX, bY, bW * 4, bH * 4, bR)

del(t)
del(d)
texel.end()