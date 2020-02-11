close all
clear

x=imread('segmen_1.tif')
N=max(x(:));
image(x)
colormap(rand(N,3));
axis('image')

x=imread('segmen_2.tif')
N=max(x(:));
figure
image(x)
colormap(rand(N,3));
axis('image')


x=imread('segmen_3.tif')
N=max(x(:));
figure
image(x)
colormap(rand(N,3));
axis('image')