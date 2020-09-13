function [EqImg,CDF]=equalize(X)
    Xhist=hist(X(:),[0:255]);
    CDF=cumsum(Xhist)/sum(Xhist);
    minval=CDF(min(X(:)));
    maxval=CDF(max(X(:)));
    EqImg=uint8(255*((CDF(X)-minval)/(maxval-minval)));    
end

    
   