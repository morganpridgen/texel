import texel
from math import *

texel.init()
d = texel.Display("test")
arrow = texel.Texture("arrow.png", 16, 16)
ctrl = texel.Controller()
x, y, r = 320, 180, 0

while d.refresh():
  ctrl.update()
  r = atan2(ctrl.joyY(), ctrl.joyX())
  if ctrl.click(texel.CtrlS): ctrl.rumble(0.85, 0.25)
  if ctrl.release(texel.CtrlS): ctrl.rumble(0.25, 0.25)
  if ctrl.press(texel.CtrlS):
    x += 4 * cos(r)
    y += 4 * sin(r)
  
  texel.drawRect(x, y, 2, 2, texel.Color(1, 1, 1))
  arrow.render(x, y, 1, 1, r)
  texel.drawRect(ctrl.mouseX(), ctrl.mouseY(), 8, 8, texel.Color(1, 1, 1))

del(ctrl)
del(arrow)
del(d)
texel.end()