clear all;close all;
im = imread('./pics/zaosheng.bmp');
im = im(:,:,1);
out = medfilt2(im,[3 3]);
h = ones(3,3)/9;
out2 = imfilter(im,h);
subplot(1,3,1);imshow(im);title('ԭʼͼ��');
subplot(1,3,2);imshow(out);title('3X3��ֵ�˲�');
subplot(1,3,3);imshow(out2);title('3X3��ֵ�˲�');