# <center>空域图像增强

### 1. 灰度变换
![](pics/增强方法.png)
#### 1.1 图像反转
设图像灰度级[0,L-1]，变换S=L-1-r
```matlab
im = imread('./pics/hofi.bmp');
imshow(im);
im = 255 - im;
figure;
imshow(im);
```
#### 1.2 对数变换
$S = c\log(1+r)$
 C为常数，r>=0
一种灰度压缩方式，用于当原图灰度范围太大时
#### 1.3 幂次变换
$S = Cr^Y$
C,Y为常数，
r为归一化的精度
Y < 1时，提高灰度级
Y > 1时，降低灰度级
```matlab
C = 1;
Y = 5;
im = imread('sat.bmp');
im = im(:,:,1);
imshow(im);
im = double(im)./255
im = im.^5;
im = uint8(im.*255);
figure;imshow(im);
```

































