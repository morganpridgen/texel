from distutils.core import setup, Extension
import glob

cpp = glob.glob("src/*.cpp")

texel = Extension(
  "texel",
  sources = cpp,
  language = "C++",
  libraries=["texel"]
)

setup(
  name = "texel",
  version = "1.0.0",
  description = "Python implementation of Texel",
  ext_modules = [texel]
)