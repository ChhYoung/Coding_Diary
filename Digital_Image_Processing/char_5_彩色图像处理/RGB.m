I = imread('./pics/Fig6.08.jpg');
R = I(:,:,1);
G = I(:,:,2);
B = I(:,:,3);
subplot(2,2,1),imshow(I),title('ԭʼͼ��');
subplot(2,2,2),imshow(R),title('��ɫ����');
subplot(2,2,3),imshow(G),title('��ɫ����');
subplot(2,2,4),imshow(B),title('��ɫ����');