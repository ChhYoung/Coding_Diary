%% ��������
clc 
clear
%A1 = imread('./pics/Fig0905(a)(wirebond-mask).tif');
A1 = imread('./pics/Fig0911(a)(noisy_fingerprint).tif');

se1 = strel('disk',5);
A2 = imopen(A1,se1);
A3 = imclose(A1,se1);
subplot(2,2,1),imshow(A1),title('ԭʼͼ��');
subplot(2,2,2),imshow(A2),title('������');
subplot(2,2,3),imshow(A3),title('������');
%subplot(2,2,4),imshow(A4),title('A4');