from distutils.core import setup, Extension

texel = Extension(
  "texel",
  sources = ["texelmodule.cpp", "txlsquare.cpp", "txlnoise.cpp", "txltriangle.cpp", "txlsawtooth.cpp"],
  language = "C++",
  libraries=["texel"]
)

setup(
  name = "texel",
  version = "1.0.0",
  description = "Python implementation of Texel",
  ext_modules = [texel]
)