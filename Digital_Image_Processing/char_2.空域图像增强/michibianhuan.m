im = imread('./pics/sat.bmp');
im = im(:,:,1);
imshow(im);
im = double(im)./255;
im = im.^5;
im = uint8(im.*255);
figure;imshow(im);