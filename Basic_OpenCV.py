import cv2
import numpy as np

import os
dir_path = os.path.dirname(os.path.realpath(__file__))

img = cv2.imread(dir_path+'\Original_5988040.jpg', 1)
top1 = img[0:189, 0:340].copy()
top2 = img[0:189, 340:680].copy()
top3 = img[0:189, 680:1020].copy()
mid1 = img[189:378, 0:340].copy()
mid2 = img[189:378, 340:680].copy()
mid3 = img[189:378, 680:1020].copy()
low1 = img[378:567, 0:340].copy()
low2 = img[378:567, 340:680].copy()
low3 = img[378:567, 680:1020].copy()

# --------------Category A: Color channel processing (2 groups)--------------
# Group 1: Grayscale
mid1[:,:,0] = 0
mid1[:,:,2] = 0

# Group 3: Color pair red & blue on middle row
mid3[:,:,1] = 0

# --------------Category B: Pixel-point operations (3 groups)--------------
weight = 100
for i in np.arange(0,3):
    top1[:, :, i] = cv2.add(top1[:, :, i], -weight)  # Group 1: Darker
    top2[:, :, i] = 255-top2[:, :, i]               # Group 2: Negative

# Group 3: Higher contrast on top row
weight = 4
for i in np.arange(0, 3):
    top3[:, :, i] = cv2.multiply(top3[:, :, i], weight)

# --------------Category C: Neighborhood operations (3 groups)--------------
# Group 1: Gaussian blur
low1 = cv2.GaussianBlur(low1,(15, 15),0)

# Group 2: Sobel edge detector
low2 = cv2.Sobel(low2,-1,1,0,ksize=3)

# Group 3: Salt & pepper noise & Median blur
def saltpepper_noise(image,prob):
    output = np.zeros(image.shape,np.uint8)
    thres = 1 - prob
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            rdn = np.random.random()
            if rdn < prob:
                output[i][j] = 0
            elif rdn > thres:
                output[i][j] = 255
            else:
                output[i][j] = image[i][j]
    return output


low3 = saltpepper_noise(low3, .03)
low3 = cv2.medianBlur(low3, 15)

# --------------Stacking the parts of image--------------
top1 = np.hstack((top1, top2, top3))
mid1 = np.hstack((mid1, mid2, mid3))
low1 = np.hstack((low1, low2, low3))
top1 = np.vstack((top1, mid1, low1))

cv2.imwrite(dir_path+'\Transformed_5988040.jpg', top1)
cv2.imshow('top1', top1)

cv2.waitKey(0)
cv2.destroyAllWindows()
