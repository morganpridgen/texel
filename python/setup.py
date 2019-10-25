from distutils.core import setup, Extension

texel = Extension(
  "texel",
  sources = ["texelmodule.cpp", "txlsquare.cpp"],
  language = "C++",
  libraries=["texel"]
)

setup(
  name = "texel",
  version = "1.0.0",
  description = "Python implementation of Texel",
  ext_modules = [texel]
)