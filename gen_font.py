import pygame
from pygame.locals import *

fonts = [[None, 22], ["unifont.ttf", 15]]

pygame.init()
for i in range(len(fonts)):
  font = pygame.font.Font(fonts[i][0], fonts[i][1])
  renderString = ""
  for j in range(32, 127): renderString = "".join([renderString, chr(j)])
  testChr = font.render("?", 0, (255, 255, 255))
  charSize = testChr.get_size()[1]
  print(charSize)
  outSurf = pygame.Surface((charSize * len(renderString), charSize), SRCALPHA)
  colors = [[0xff, 0xff, 0xff], [0x08, 0xa0, 0x00], [0x20, 0xf0, 0x00], [0xa0, 0xff, 0x40]]
  #outSurf.blit(font.render(renderString, 0, colors[0], pygame.Color(0, 0, 0, 0)), (0, 0))
  for j in range(32, 127): outSurf.blit(font.render(chr(j), 0, colors[0], pygame.Color(0, 0, 0, 0)), ((j - 32) * charSize, 0))
  for j in range(outSurf.get_size()[0]):
    for k in range(outSurf.get_size()[1]):
      if outSurf.get_at((j, k)) == (0, 0, 0): outSurf.set_at((j, k), (0, 0, 0, 0))
      #if outSurf.get_at((j, k)) == (0xff, 0xff, 0xff): outSurf.set_at((j, k), (0, 0, 0))
  pygame.image.save(outSurf, "fonttemplate%i.png" % (i + 1))
pygame.quit()