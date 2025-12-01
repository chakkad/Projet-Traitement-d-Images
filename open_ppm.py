import netpbmfile
import numpy
from PIL import Image
def open_ppm(file):
    a = netpbmfile.imread(file)
    if file.endswith(".pbm"):
        a = numpy.logical_not(a)
    return Image.fromarray(a)
