#include <stdio.h>
#include "typeutil.h"
#include "tiff.h"

uint8_t clipping(float pix_val);
void _2Dconv(float **filter,int fil_h,int fil_w,struct TIFF_img *in_img,struct TIFF_img *out_img);


