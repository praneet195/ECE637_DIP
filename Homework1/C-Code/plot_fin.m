u=-pi:0.1:pi;
v=-pi:0.1:pi;

%Without meshgrid
u=u+0.0000001;
v=v+0.0000001;
new_u=sin(4.5*u)./sin(0.5*u);
new_v=sin(4.5*v)./sin(0.5*v);
res=new_u' * new_v;

res=(1/81)*res;
fig0 = figure(1);
surf(u,v,abs(res))
colormap jet
xlabel('\mu','FontSize',50);
ylabel('\nu','FontSize',50);
zlabel('|H(\mu,\nu)|','FontSize',50);



[U,V] = meshgrid(u,v);
h=(1/81)*(sin(4.5*U)./sin(0.5*U)).*(sin(4.5*V)./sin(0.5*V));
fig1 = figure(2);
surf(U,V,abs(h))
colormap jet
xlabel('\mu','FontSize',50);
ylabel('\nu','FontSize',50);
zlabel('|H(\mu,\nu)|','FontSize',50);




h=(1/25)*(sin(2.5*U)./sin(0.5*U)).*(sin(2.5*V)./sin(0.5*V));
fig2 = figure(3);
surf(U,V,abs(h))
colormap jet
xlabel('\mu','FontSize',50);
ylabel('\nu','FontSize',50);
zlabel('|H(\mu,\nu)|','FontSize',50);

lamda=1.5;
g = 1 + lamda*(1 - h);
fig3 = figure(4);
surf(U,V,abs(g));
colormap jet
xlabel('\mu','FontSize',50);
ylabel('\nu','FontSize',50);
zlabel('|G(\mu,\nu)|','FontSize',50);


h = 0.01./(1-0.9*exp(-1i*U)-0.9*exp(-1i*V)+0.81*exp(-1i*(U+V)));
fig4 = figure(5);
surf(U,V,abs(h));
colormap jet
xlabel('\mu','FontSize',50);
ylabel('\nu','FontSize',50);
zlabel('|H(\mu,\nu)|','FontSize',50);



% PSF
x = zeros(256,256);
y = zeros(256,256);
x(128,128) = 1;

for m = 1:256
	for n = 1:256
		y(m,n) = 0.01*x(m,n);
		if (m > 1)
			y(m,n) = y(m,n) + 0.9*y(m-1,n);
		end
		if (n > 1)
			y(m,n) = y(m,n) + 0.9*y(m,n-1);
		end
		if (m > 1 && n > 1)
			y(m,n) = y(m,n) - 0.81*y(m-1,n-1);
		end
	end
end

y(y(:) > 255) = 255;
y(y(:) < 0) = 0;



%Comparing FFT of images sharpened at different values of lambda 
img   = imread('fir-sharp-output02.tif');
img   = fftshift(img(:,:,1));
F     = fft2(img);
figure;
imagesc(100*log(1+abs(fftshift(F)))); colormap(gray); 
title('magnitude spectrum');


img   = imread('fir-sharp-output08.tif');
img   = fftshift(img(:,:,1));
F     = fft2(img);
figure;
imagesc(100*log(1+abs(fftshift(F)))); colormap(gray); 
title('magnitude spectrum');

img   = imread('fir-sharp-output15.tif');
img   = fftshift(img(:,:,1));
F     = fft2(img);
figure;
imagesc(100*log(1+abs(fftshift(F)))); colormap(gray); 
title('magnitude spectrum');

