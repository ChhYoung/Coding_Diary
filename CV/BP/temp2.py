import numpy as np
import cv2

def guideFilter(I, p, winSize, eps):

    mean_I = cv2.blur(I, winSize)      # I的均值平滑
    mean_p = cv2.blur(p, winSize)      # p的均值平滑

    mean_II = cv2.blur(I * I, winSize) # I*I的均值平滑
    mean_Ip = cv2.blur(I * p, winSize) # I*p的均值平滑

    var_I = mean_II - mean_I * mean_I  # 方差
    cov_Ip = mean_Ip - mean_I * mean_p # 协方差

    a = cov_Ip / (var_I + eps)         # 相关因子a
    b = mean_p - a * mean_I            # 相关因子b

    mean_a = cv2.blur(a, winSize)      # 对a进行均值平滑
    mean_b = cv2.blur(b, winSize)      # 对b进行均值平滑

    q = mean_a * I + mean_b
    return q


if __name__ == '__main__':
    eps = 0.01
    winSize = (5,5)
    image = cv2.imread(r'lena.png', cv2.IMREAD_ANYCOLOR)
    image = cv2.resize(image, None,fx=0.7, fy=0.7, interpolation=cv2.INTER_CUBIC)
    I = image/255.0        #将图像归一化
    p =I
    guideFilter_img = guideFilter(I, p, winSize, eps)

    # 保存导向滤波结果
    guideFilter_img  = guideFilter_img  * 255
    guideFilter_img [guideFilter_img  > 255] = 255
    guideFilter_img  = np.round(guideFilter_img )
    guideFilter_img  = guideFilter_img.astype(np.uint8)
    cv2.imshow("image",image)
    cv2.imshow("winSize_5", guideFilter_img )
    cv2.waitKey(0)
    cv2.destroyAllWindows()