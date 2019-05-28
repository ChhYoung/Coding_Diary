clear all;close all;
I = imread('./pics/Fig1016(a)(building_original).tif');
rotI = imrotate(I,33,'crop');
%rotI = I;
%imshow(rotI);
BW = edge(rotI,'canny');
imshow(BW);
% hough�任����r theta�ռ�
[H,theta, rho] = hough(BW);

% ����r theta�ռ�ͼ
figure
imshow(imadjust(mat2gray(H)),[],...
       'XData',theta,...
       'YData',rho,...
       'InitialMagnification','fit');
xlabel('\theta (degrees)')
ylabel('\rho')
axis on
axis normal 
hold on
colormap(gca,hot)  

% �ҵ��ཻ���ĵ�
P = houghpeaks(H,5,'threshold',ceil(0.3*max(H(:))));
x = theta(P(:,2));
y = rho(P(:,1));
plot(x,y,'s','color','black');

% �ҵ�xy�ռ�
lines = houghlines(BW,theta,rho,P,'FillGap',5,'MinLength',7);

% ��ԭͼ����ʾ
figure,imshow(rotI),hold on
max_len = 0;
for k=1:length(lines)
    xy = [lines(k).point1;lines(k).point2];
    plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');
    
    % �����ߵ������յ�
    plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','yellow');
    plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red');
    
    len = norm(lines(k).point1-lines(k).point2);
    if(len > max_len)
        max_len = len;
        xy_long = xy;
    end
end

plot(xy_long(:,1),xy_long(:,2),'LineWidth',2,'Color','red');