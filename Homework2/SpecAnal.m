
% Clear memory and close existing figures
clear
close all

% This line reads in a gray scale TIFF image. 
% The matrix img contains a 2-D array of 8-bit gray scale values.

[img] = imread('img04g.tif');

% This line sets the colormap, displays the image, and sets the
% axes so that pixels are square.
% "map" is the corresponding colormap used for the display. 
% A gray scale pixel value is treated as an index into the 
% current colormap so that the pixel at location (i,j)
% has the color [r,g,b] = map(img(i,j),:) .

map=gray(256);
colormap(map);
image(img)
axis('image')

X = double(img)/255;

% Select an NxN region of the image and store it in the variable "z"

i=100;
j=100;

N = 64;
z = X(i:(N+i-1), j:(N+j-1));


% Compute the power spectrum for the NxN region
Z = (1/N^2)*abs(fft2(z)).^2;

% Use fftshift to move the zero frequencies to the center of the plot
Z = fftshift(Z);

% Compute the logarithm of the Power Spectrum.
Zabs = log( Z );


% Plot the result using a 3-D mesh plot and label the x and y axises properly. 

x = 2*pi*((0:(N-1)) - N/2)/N;
y = 2*pi*((0:(N-1)) - N/2)/N;
figure 
mesh(x,y,Zabs)
colormap jet
xlabel('\mu axis','FontSize',20)
ylabel('\nu axis','FontSize',20)
zlabel('log(PSD)','FontSize',20)
title('Power Spectrum, N=64','FontSize',30)

N = 128;
z = X(i:(N+i-1), j:(N+j-1));


% Compute the power spectrum for the NxN region
Z = (1/N^2)*abs(fft2(z)).^2;

% Use fftshift to move the zero frequencies to the center of the plot
Z = fftshift(Z);

% Compute the logarithm of the Power Spectrum.
Zabs = log( Z );


% Plot the result using a 3-D mesh plot and label the x and y axises properly. 

x = 2*pi*((0:(N-1)) - N/2)/N;
y = 2*pi*((0:(N-1)) - N/2)/N;
figure 
mesh(x,y,Zabs)
colormap jet
xlabel('\mu axis','FontSize',20)
ylabel('\nu axis','FontSize',20)
zlabel('log(PSD)','FontSize',20)
title('Power Spectrum, N=128','FontSize',30)


N = 256;
z = X(i:(N+i-1), j:(N+j-1));


% Compute the power spectrum for the NxN region
Z = (1/N^2)*abs(fft2(z)).^2;

% Use fftshift to move the zero frequencies to the center of the plot
Z = fftshift(Z);

% Compute the logarithm of the Power Spectrum.
Zabs = log( Z );


% Plot the result using a 3-D mesh plot and label the x and y axises properly. 

x = 2*pi*((0:(N-1)) - N/2)/N;
y = 2*pi*((0:(N-1)) - N/2)/N;
figure 
mesh(x,y,Zabs)
colormap jet
xlabel('\mu axis','FontSize',20)
ylabel('\nu axis','FontSize',20)
zlabel('log(PSD)','FontSize',20)
title('Power Spectrum, N=256','FontSize',30)



N=64;
x = 2*pi*((0:(N-1)) - N/2)/N;
y = 2*pi*((0:(N-1)) - N/2)/N;
res=BetterSpecAnal(X);
figure
mesh(x,y,res)
colormap jet
xlabel('\mu axis','FontSize',20)
ylabel('\nu axis','FontSize',20)
zlabel('log(PSD)','FontSize',20)
title('Estimated Power Spectrum, N=64','FontSize',30)







img_x = -0.5 + (0.5+0.5)*rand(512);

img_x_scaled=255*(img_x+0.5);
figure
colormap(map);
imshow(uint8(img_x_scaled))




y=zeros(512,512);

for i=1:512
    for j=1:512
        y(i,j)=3*img_x(i,j);
        if i>1
            y(i,j)=y(i,j)+0.99* y(i-1,j);
        end
        if j>1
            y(i,j)=y(i,j)+0.99* y(i,j-1);
        end
        if i>1 && j>1
            y(i,j)=y(i,j)-0.9801* y(i-1,j-1);
        end
    end
end

figure
colormap(map);
imshow(uint8(y+127));













N=64;
x = 2*pi*((0:(N-1)) - N/2)/N;

res=BetterSpecAnal(y);
y = 2*pi*((0:(N-1)) - N/2)/N;
res=res/25;
figure
mesh(x,y,res)
colormap jet
xlabel('\mu axis','FontSize',20)
ylabel('\nu axis','FontSize',20)
zlabel('log(PSD)','FontSize',20)
title('Estimated Power Spectrum, N=64','FontSize',30)







u=-pi:0.1:pi;
v=-pi:0.1:pi;

[U,V]=meshgrid(u,v);

Sy=abs(3./((1-0.99*exp(-1i*U)).*(1-0.99*exp(-1i*V)))).^2*(1/12);

figure
mesh(U,V,log(Sy));
colormap jet
xlabel('\mu axis','FontSize',20)
ylabel('\nu axis','FontSize',20)
zlabel('log(PSD)','FontSize',20)
title('Power Spectrum Theoretical, N=64','FontSize',30)










