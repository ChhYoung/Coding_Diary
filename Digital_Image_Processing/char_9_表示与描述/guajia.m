clear;clf;clc;
f=imread('./pics/bone.bmp');
[sizeX,sizeY]=size(f);
K=f;
L=f;   %�Ǽܻ�ͼ
a=2;b=2;
while 1
    for a=2:(sizeX-1)
       for b=2:(sizeY-1)
           N=K(a,b-1)+K(a+1,b-1)+K(a+1,b)+K(a+1,b+1)+K(a,b+1)+K(a-1,b+1)+K(a-1,b)+K(a-1,b-1);
           T=(K(a+1,b-1)-K(a,b-1)==1)+(K(a+1,b)-K(a+1,b-1)==1)+(K(a+1,b+1)-K(a+1,b)==1)+(K(a,b+1)-K(a+1,b+1)==1)+(K(a-1,b+1)-K(a,b+1)==1)+(K(a-1,b)-K(a-1,b+1)==1)+(K(a-1,b-1)-K(a-1,b)==1)+(K(a,b-1)-K(a-1,b-1)==1);
           if (N>1)*(N<7)*(T==1)*(K(a+1,b)*K(a,b+1)*(K(a,b-1)+K(a-1,b))==0)
               L(a,b)=0;
           end
           if (N>1)*(N<7)*(T==1)*(K(a-1,b)*K(a,b-1)*(K(a,b+1)+K(a+1,b))==0)
             L(a,b)=0;
           end        
       end
    end
    if K==L
        break;
    end
    K=L;
end
Z=f-L;
figure(1)
imshow(f);title('ԭʼͼ��');
figure(2)
imshow(L);title('�Ǽܻ����');
figure(3)
imshow(Z);title('���Ǽܷ���ԭͼ��');
