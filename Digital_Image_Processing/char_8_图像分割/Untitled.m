clear aall;close all;
im = imread('./pics/0084.jpg');
im = rgb2gray(im)
subplot(2,3,1),imshow(im),title('ԭͼ');
h = ones(5,5)/25;
im = imfilter(im,h);
subplot(2,3,2),imhist(im),title('ֱ��ͼ');
im_bw = imbinarize(im,105/255);
subplot(2,3,3),imshow(im_bw),title('����ȫ����ֵ');

T = graythresh(im);
im_bw = imbinarize(im,T);
subplot(2,3,4);imshow(im_bw),title('OTSU');
