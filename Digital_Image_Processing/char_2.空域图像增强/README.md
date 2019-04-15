# <center>空域图像增强

### 1. 灰度变换
![](pics/增强方法.png)
####2. 图像反转
设图像灰度级[0,L-1]，变换S=L-1-r
```matlab
im = imread('./pics/hofi.bmp');
imshow(im);
im = 255 - im;
figure;
imshow(im);
```


































