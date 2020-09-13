close all;

A_inv = [0.2430,0.8560,-0.0440;-0.3910,1.1650,0.0870;0.0100,-0.0080,0.5630];

d65_wp = [0.3127,0.3290,0.3583];

ee_wp = [0.3333,0.3333,0.3333];

rgb_709 = [0.640,0.330,.030;0.300,0.600,0.100;0.150,0.060,0.790;0.640,0.330,.030];

rgb_cie = [0.73467,0.26533,0.0;0.27376,0.71741,0.00883;0.16658,0.00886,0.82456;0.73467,0.26533,0.0];

reflect=load("reflect.mat")
data = load("data.mat");

lambda = [400:10:700];


plot(lambda,data.x);
hold on;
plot(lambda,data.y);
hold on;
plot(lambda,data.z);
legend('x_{0}(\lambda)', 'y_{0}(\lambda)', 'z_{0}(\lambda)');
title('Color Matching Functions vs. Wavelength','FontSize',20);
xlabel('Wavelength (nm)','FontSize',20);
xyz=[data.x;data.y;data.z];

lms=A_inv*xyz;

l=lms(1,:);
m=lms(2,:);
s=lms(3,:);

figure
plot(lambda,l);
hold on;
plot(lambda,m);
hold on;
plot(lambda,s);
legend('l_{0}(\lambda)', 'm_{0}(\lambda)', 's_{0}(\lambda)');
title('Color Matching Functions vs. Wavelength','FontSize',20);
xlabel('Wavelength (nm)','FontSize',20);


figure
plot(lambda,data.illum1);
hold on;
plot(lambda,data.illum2);
legend('D_{65}', 'Fluorescent');
title('D_{65} and Fluorescent Spectrums vs. Wavelength','FontSize',20);
xlabel('Wavelength (nm)','FontSize',20);

x = data.x(:) ./ (data.x(:)+data.y(:)+data.z(:));
y = data.y(:) ./ (data.x(:)+data.y(:)+data.z(:));


figure
plot(x,y);
hold on;
plot(rgb_cie(:,1),rgb_cie(:,2));
text(rgb_cie(:,1), rgb_cie(:,2), 'RGB_{CIE}');
hold on;
plot(rgb_709(:,1),rgb_709(:,2));
text(rgb_709(:,1), rgb_709(:,2), 'RGB_{709}');
hold on;
plot(d65_wp(1),d65_wp(2));
text(d65_wp(1), d65_wp(2), 'D_{65}');
hold on;
plot(ee_wp(1),ee_wp(2));
text(ee_wp(1), ee_wp(2), 'EE');
title('Different RGB Primaries Chromaticity Plot')

R = reflect.R;

d_65 = data.illum1;

d_65_permute= permute(d_65,[ 3 1 2]);

I=zeros(170,256,31);

for i=1:31,
    I(:,:,i)=R(:,:,i)*d_65_permute(:,:,i);
end

XYZ=zeros(170,256,3);

for i=1:170,
    for j=1:256,
        I_permute=permute(I(i,j,:),[1 3 2]);
        XYZ(i,j,:)=I_permute*[data.x;data.y;data.z]';
    end
end

k_rgb = inv(rgb_709(1:3,:)') * [d65_wp(1)/d65_wp(2) 1 d65_wp(3)/d65_wp(2)]';

M_709 = rgb_709(1:3,:)' * diag(k_rgb);


rgb = zeros(170,256,3);
for i=1:170,
    for j=1:256,
        XYZ_permute=permute(XYZ(i,j,:),[1 3 2]);
        rgb(i,j,:) = M_709 \ XYZ_permute';
    end
end


rgb(rgb(:)>1) =1;
rgb(rgb(:)<0)=0;



gamma_rgb = 255 * ((rgb).^(1/2.2));

figure
image(uint8(gamma_rgb));




d_65 = data.illum2;

d_65_permute= permute(d_65,[ 3 1 2]);

I=zeros(170,256,31);

for i=1:31,
    I(:,:,i)=R(:,:,i)*d_65_permute(:,:,i);
end

XYZ=zeros(170,256,3);

for i=1:170,
    for j=1:256,
        I_permute=permute(I(i,j,:),[1 3 2]);
        XYZ(i,j,:)=I_permute*[data.x;data.y;data.z]';
    end
end

k_rgb = inv(rgb_709(1:3,:)') * [d65_wp(1)/d65_wp(2) 1 d65_wp(3)/d65_wp(2)]';
M_709 = rgb_709(1:3,:)' * diag(k_rgb);


rgb = zeros(170,256,3);
for i=1:170,
    for j=1:256,
        XYZ_permute=permute(XYZ(i,j,:),[1 3 2]);
        rgb(i,j,:) = M_709 \ XYZ_permute';
    end
end


rgb(rgb(:)>1) =1;
rgb(rgb(:)<0)=0;


gamma_rgb = 255 * ((rgb).^(1/2.2));

figure
image(uint8(gamma_rgb));


[x, y] = meshgrid(0:0.005:1);
z = 1 - y - x;

RGB_709 = [0.64 0.3 0.15;0.33 0.6 0.06;0.03 0.1 0.79];
M_7092 = RGB_709 * eye(3);

[m, n] = size(x);
XYZ = zeros(m,n,3);

XYZ(:,:,1) = x;
XYZ(:,:,2) = y;
XYZ(:,:,3) = z;

rgb = zeros(m,n,3);

for p = 1:m
	for q = 1:n
		rgb(p,q,:) = M_7092 \ permute(XYZ(p,q,:), [1 3 2])';
		if any(rgb(p,q,:) < 0)
			rgb(p,q,:) = [1, 1, 1];
		end
	end
end


gc_rgb = ((rgb).^(1/2.2));

figure;
image([0:0.005:1], [0:0.005:1], gc_rgb);
axis('xy');
hold on;

x1 = data.x(:) ./ (data.x(:) + data.y(:) + data.z(:));
y1 = data.y(:) ./ (data.x(:) + data.y(:) + data.z(:));
plot(x1, y1,'r');
