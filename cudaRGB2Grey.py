# RGB to Greyscale image conversion
# Pongpeera Sukasem         ID. 5988040 Section 1
# Poomdharm Benjasirimonkol ID. 5988056 Section 1

import pycuda.driver as cuda
import pycuda.autoinit
from pycuda.compiler import SourceModule
import numpy as np
import cv2
import time
import tkinter
from tkinter.filedialog import askopenfilename

# 1) Input & initialization
# 1.1) Read in the image using OpenCV, converting the image into an array
# Receive input image location using file dialog
tkinter.Tk().withdraw()  # Keeps the root window from appearing
filename = askopenfilename()  # Shows an "Open" dialog box and return the path to the selected file
print(filename)
# Read in the image using the obtained path
img = cv2.imread(filename, cv2.IMREAD_COLOR)
print("Image size:", img.shape[1], " * ", img.shape[0])

# 1.2) Calculate & print out the grid size to be used
# Block size is also determined here (usually 32 * 32)
block = 32
gridX = int(img.shape[1]/block+1)
gridY = int(img.shape[0]/block+1)
print("Determined grid size: ", gridX, " * ", gridY, " blocks")
print("Determined block size: ", block, " * ", block, " threads per block")

# 1.3) Create an output "image" (numpy array) with size of input
out = np.empty_like(img[:, :, 0])

# Start the CUDA process timer
start = time.time()

# 2) RGB to greyscale conversion process via CUDA
# 2.1) Allocate memory to device
# nbytes determines the size (in bytes) of the input & output images
# = cudaMalloc((void **)&img_gpu, img.nbytes); in C/C++
img_gpu = cuda.mem_alloc(img.nbytes)
# = cudaMalloc((void **)&out_gpu, out.nbytes); in C/C++
out_gpu = cuda.mem_alloc(out.nbytes)

# 2.2) Copy the memory from host (CPU) to device (GPU)
# = cudaMemcpy(img_gpu, img, img.nbytes, cudaMemcpyHostToDevice); in C/C++
cuda.memcpy_htod(img_gpu, img)

# 2.3) Create a kernel function module (written in C/C++)
module = SourceModule("""
//Greyscale conversion
__global__ void rgb2grey(unsigned char *outImage, unsigned char *inImage, int rows, int cols) {
    //Derive the row and column based on thread configuration
    int i = blockIdx.y*blockDim.y + threadIdx.y;
    int j = blockIdx.x*blockDim.x + threadIdx.x;
    //Limit calculations for valid indices
    if (i < rows && j < cols) {
        //Get 1d coordinate for the grayscale image
        int rgbOffset = (i*cols + j) * 3;
        //Get RGB values
        unsigned char blue = inImage[rgbOffset];
        unsigned char green = inImage[rgbOffset + 1];
        unsigned char red = inImage[rgbOffset + 2];
        //Convert and save greyscale value using CIE 601 formula
        float grey = 0.114*blue + 0.587*green + 0.299*red;
        outImage[i*cols + j] = (unsigned char)grey;
    }
}
""")

# 2.4) Load the created kernel function module into memory via PyCUDA
rgb2grey = module.get_function("rgb2grey")

# 2.5) Assign sizes of grids & blocks
# grid  = dim3 DimGrid(gridX, gridY); in C/C++
# block = dim3 DimBlock(block,block); in C/C++. 32 * 32 threads per block by default
DimGrid = (gridX, gridY, 1)
DimBlock = (block, block, 1)
# 2.6) Execute the kernel function in device
# out_gpu & img_gpu are Device Allocation pointers (kernel function inputs)
# img.shape[1] = cols converted to int32 (default was int8)
# img.shape[0] = rows converted to int32 (default was int8)
# block & grid assigned by DimGrid & DimBlock values
rgb2grey(out_gpu, img_gpu, np.int32(img.shape[0]), np.int32(img.shape[1])
         , block=DimBlock, grid=DimGrid)

# 2.7) Copy the memory from device (GPU) back to host (CPU)
# cudaMemcpy(out, out_gpu, out.nbytes, cudaMemcpyDeviceToHost); in C/C++
cuda.memcpy_dtoh(out, out_gpu)

# 2.8) Free the device memory
# = cudaFree(img_gpu); & cudaFree(out_gpu); in C/C++
img_gpu.free()
out_gpu.free()

# End the process timer & print out the total time used in CUDA
end = time.time()
print("Total time spent in CUDA: ", end-start, " seconds")

# 3) Output display & write into image file
# 3.1) Save the output image to storage
cv2.imwrite('Output.jpg', out)
# 3.2) Display input & output images
cv2.imshow("Input", img)
cv2.imshow("Output", out)
cv2.waitKey(0)
cv2.destroyAllWindows()


