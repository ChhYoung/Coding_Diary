#  彩色图像处理

[TOC]

### 1. 颜色基础知识：

- 特性：色调，饱和度，亮度

> 色调：观察者接收的主要颜色,光的主波长。
>
> 饱和度：颜色的纯度，混合色中白光的数量 ,区别颜色的深浅程度，混入白光越少，饱和度越高。

- 视网膜对光的感知：

锥细胞：颜色敏感， 杆细胞：亮度敏感

锥细胞比例： 红：65%  绿：33%  蓝：2%

- 加色混色模型：

> rgb三色光叠加实现
>
> 适用于显示器等发光体的显示

![](pics/加色模型.png)

- 减色混色模型:

> 减色基：青，品红，黄
>
> 白光中减去某个基色得到，如： 白光 - 绿 = 品红
>
> 适用于彩色打印，印刷行业等

![](pics/减色模型.png)

- CIE色度图：

红色：x轴； 绿色：y轴；没有z轴，蓝色比例为：z = 1-x-y

![](./pics/CIE1.png)
![](./pics/CIE2.png)

**注解:**
- 越接近C点，颜色越不纯
- 任意直线上的颜色可由两端点混合得到
- 任意三角形内的可以由三个顶点混合得到

### 2.颜色空间
#### 2.1 RGB空间
r,g,b分别位于立方体的三个轴，其中O点为(0,0,0)的rgb即为黑色，顶点为(1,1,1)的rgb即为白色。

灰色为：黑色 到 白色的直线

![](pics/rgb空间.png)

越接近红色则在红色方向上的灰度级就越高，同理

![](./pics/rgb分量.png)

```matlab
I = imread('./pics/Fig6.08.jpg');
R = I(:,:,1);
G = I(:,:,2);
B = I(:,:,3);
subplot(2,2,1),imshow(I),title('原始图像');
subplot(2,2,2),imshow(R),title('红色分量');
subplot(2,2,3),imshow(G),title('绿色分量');
subplot(2,2,4),imshow(B),title('蓝色分量');
```
得到结果
![](pics/rgb分量2.png)

#### 2.2 CMY和CMYK 彩色空间
CMY(青，品红，黄)
CMYK(青，品红，黄，黑)

**用途**：纸上沉积颜料的设备，如打印机，复印机，引入K也是因为打印机主要也是黑色为主

#### 2.3 HSI彩色空间

HSI: 色调，饱和度，亮度
将色调，饱和度，亮度分开以避免光照明暗(亮度)的干扰

**特点：**
- I分量于图像的颜色无关
- H,S分量与人感受颜色密切相关
- 在HSI模型中，在红光中掺入白光，饱和度减少，色调不变，亮度增加

H: 色调由角度表示(0：红),(120：绿),(240：蓝)
S:  饱和度由半径长度表示，中心饱和度为0，边缘饱和度为1
I：亮度由柱坐标高度表示
![](./pics/HS.png)
![](./pics/HSI.png)

#### 2.4 其他彩色空间
YIQ : Y亮度，IQ色调，用于北美彩色电视广播
YUV : Y亮度，UV色调，用于欧洲电视广播
YCbCr : JPEG采用的彩色空间，Y亮度，Cb,Cr由UV调整得到

### 3. 彩色空间的转换
#### 3.1 RGB到CMY彩色空间
将RGB和CMY都归一化到`[0,1]`
$ [C,M,Y]^T = [1,1,1]^T - [R,G,B]^T $
#### 3.2 RGB到HSI彩色空间
![](pics/RGB2HSI.png)

#### 3.3 HSI到RGB颜色空间
![](./pics/hsi2rgb.png)

#### 3.4 RGB与YIQ
![](pics/rgbyiq.png)

#### 3.5 RGB与YUV
![](pics/rgbyuv.png)

#### 3.5 RGB与YCbCr
![](pics/rgbycbcr.png)

### 4.伪彩色处理
将一个无色灰度图映射到彩色空间中

**处理方法**
- 强度分层
- 灰度级到彩色转换

#### 4.1 强度分层技术

令[0,L-1]表示灰度级，0为黑色，L-1表示白色，延强度轴，将其划分成P个平面，P+1个间隔，将灰度级与颜色层对应

例：

![](./pics/强度分层.png)

![](./pics/强度分层2.png)

![](./pics/强度分层3.png)

#### 4.2 灰度级到彩色的三分量转换

点到点，三个映射，[R,G,B] = f(g)

例如 ： 

 ![](./pics/灰度转换.png)



### 5.全彩色图像处理

两种方法：

- 单独处理彩色空间得每一个通道，再合成结果图像
- 将颜色分开成彩色空间上的一个点，即一个向量，$[R,G,B]^T$

### 6.彩色变换

- RGB CMY HSI 相互转换会使图像的亮度发生变化
- 补色： 环上对立的另一种色调，可类比灰度反转

![](./pics/补色.png)

- 彩色分层：在彩色图像中分离特定颜色的目标

将ROI以外的区域映射为常数，以下为两种ROI选取方法

![](./pics/彩色分层.png)

彩色分层实例代码

```matlab
% 原始红色的RGB坐标为(0.6863, 0.1608, 0.1922)
W = 0.2549;
I = imread('./pics/caomei.bmp');
I = double(I);
I = I/255;
[m n c] = size(I);
R = I(:,:,1);
G = I(:,:,2);
B = I(:,:,3);
for x = 1:m
	for y = 1:n
		if(abs(R(x,y)-0.6863) > W/2)
			R(x,y) = 0.5;G(x,y) = 0.5; B(x,y) = 0.5;
		end
		if(abs(G(x,y)-0.1608) > W/2)
			R(x,y) = 0.5;G(x,y) = 0.5; B(x,y) = 0.5;
		end
		if(abs(B(x,y)-0.1922) > W/2)
			R(x,y) = 0.5;G(x,y) = 0.5; B(x,y) = 0.5;
		end
	end
end
I1(:,:,1) = R;
I1(:,:,2) = G;
I1(:,:,3) = B;
I1 = I1*255;
I1 = uint8(I1);
subplot(1,2,1),imshow(I);
subplot(1,2,2),imshow(I1);
```

![](./pics/彩色分层.bmp)


- 彩色图像亮度调整

对于RBG空间，用相同的变换函数映射每个分量

对于HSI空间，仅仅改变亮度分量

彩色平衡： 对特定的分量进行平衡
![](./pics/彩色平衡.png)



### 7.彩色图像平滑与锐化

在RGB中可对三个颜色分量图分别处理，在HSI中可只处理亮度分量

按照灰度图中的一些方法。

### 8.彩色分割

- HSI 彩色空间分割
- RGB彩色空间分割

**HSI 彩色空间分割**:

H色调图像描述颜色，S饱和度图像做模板分离ROI，借助HS两个图像来进行分割

![](./pics/HSI分割.png)

**RGB彩色空间分割:**

依据RGB空间的距离关系来分割，更直接效果更好

![](./pics/RGB分割.png)

### 9.常见问题

**9.1 常见彩色模型及应用场景**

- RBG 用在彩色监视器和彩色摄影机等邻域
- CMY 用在彩色打印机
- HSI 常用在图像处理上

**9.2 为什么彩色图像要经过RGB到HSI的转换才能处理**

直接在RGB上对RGB三个分量进行处理，就可能引起三个分量不同程度变化，导致出现色差问题，颜色上有严重失真。先将RGB转换为HSI，用HSI仅对亮度进行处理，再转换为RGB，避免对RGB处理时产生的失真问题