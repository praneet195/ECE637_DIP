function [check]=checkerboard2(gray)
    mat=[255 255 0 0;255 255 0 0;0 0 255 255;0 0 255 255];
    gray_row=ones(16,256)*gray;
    check_row=repmat(mat,4,64);
    cg_row=[check_row;gray_row];
    check=repmat(cg_row,8,1);
    check=uint8(check);
end