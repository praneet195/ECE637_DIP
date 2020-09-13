imgsp = imread('img14sp.tif');
imggn = imread('img14gn.tif');
imgg = imread('img14g.tif');
imgbl = imread('img14bl.tif');


Y = imgsp;

X = imgbl;

[r, c] = size(Y);
M = floor(r / 20);
N = floor(c / 20);
B = M * N;
Z = zeros(B, 49);
Y_col = zeros(B , 1);

i = 1;
for j = 1:M
   for k = 1:N
       Z(i,:) = reshape(X(20*j - 3:20*j + 3, 20*k - 3:20*k + 3)', [1, 49]);
       Y_col(i) = Y(20 * j, 20 * k);
       i = i + 1;
    end
end

R_zz = (Z'*Z) / B;
r_zy = (Z'*Y_col) / B;

theta_sr =inv(R_zz)*r_zy;

theta = reshape(theta_sr,[7 7]);

imgout = conv2(X,theta);

figure;
imshow(uint8(imgout));

