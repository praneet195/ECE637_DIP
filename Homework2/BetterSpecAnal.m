function res=BetterSpecAnal(X)
   n=64;
   x = 2*pi*((0:(n-1)) - n/2)/n;
   y = 2*pi*((0:(n-1)) - n/2)/n;
   window=hamming(n)*hamming(n)';
   img_res=size(X);
   img_w=img_res(2);
   img_h=img_res(1);
   % To ensure we create 25 non-overlapping regions
    start_w=(img_w-(5*n))/2;
    start_h=(img_h-(5*n))/2;
    res=zeros(n,n);
    for w=1:5
        for h=1:5
            z=X(start_h+(h-1)*n:start_h+h*n-1,start_w+(w-1)*n:start_w+w*n-1);
            z=fftshift(fft2(z.*window)).^2;
            res=res+log((1/n^2)*abs(z));
        end
    end
    res=res/25;
    figure
    mesh(x,y,res)
    colormap jet
    xlabel('\mu axis','FontSize',20)
    ylabel('\nu axis','FontSize',20)
    zlabel('log(PSD)','FontSize',20)
    title('Estimated Power Spectrum, N=64','FontSize',30)
    
            