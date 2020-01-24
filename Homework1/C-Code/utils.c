#include "utils.h"

uint8_t clipping(float pix_val){
	uint8_t val;
	if (pix_val > 255){
		val=255;
	}
	else if (pix_val < 0){
		val=0;
	}
	else{
		val=(uint8_t)pix_val;
	}
	return val;
}


void _2Dconv(float **filter, int fil_h, int fil_w,struct TIFF_img *in_img, struct TIFF_img *out_img){
	
	int32_t fil_cx=(fil_h-1)/2;
	int32_t fil_cy=(fil_w-1)/2;
	int32_t img_h=in_img->height;
	int32_t img_w=in_img->width;
	int32_t i,j,row,col,x,y;
	/* setting up channels */
	float *rconv[img_h], *gconv[img_h], *bconv[img_h];
	
	/* allocating memory for each channel */
  	for(i=0;i<img_h;i++){
          	rconv[i]=(float *)malloc(img_w * sizeof(float));
          	gconv[i]=(float *)malloc(img_w * sizeof(float));
          	bconv[i]=(float *)malloc(img_w * sizeof(float));
	}

	/* ensuring all channel values are not garbage values but zero instead */
	for(i=0;i<img_h;i++){
		for(j=0;j<img_w;j++){
			rconv[i][j]=0.0;
			gconv[i][j]=0.0;
			bconv[i][j]=0.0;
		}
	}

	for(i=0;i<img_h;i++){
		for(j=0;j<img_w;j++){
			for (x=-fil_cx;x<=fil_cx;x++){
				for(y=-fil_cy;y<=fil_cy;y++){
					row=i-x;
					col=j-y;
					if(row >=0 && row < img_h){
						if(col>=0 && col< img_w){
							rconv[i][j] = rconv[i][j] + filter[x+fil_cx][y+fil_cy] * in_img->color[0][row][col];
							gconv[i][j] = gconv[i][j] + filter[x+fil_cx][y+fil_cy] * in_img->color[1][row][col];
							bconv[i][j] = bconv[i][j] + filter[x+fil_cx][y+fil_cy] * in_img->color[2][row][col];
						}
					}
				}
			}
		}
	}
	for(i=0;i<img_h;i++){
		for(j=0;j<img_w;j++){
			/* Ensuring constraints */
			out_img->color[0][i][j]=clipping(rconv[i][j]);
			out_img->color[1][i][j]=clipping(gconv[i][j]);
			out_img->color[2][i][j]=clipping(bconv[i][j]);
		}
	}
	
	/* free channels */
	for(i=0;i<fil_h;i++){
          	free(rconv[i]);
		free(gconv[i]);
		free(bconv[i]);
 	 }

}

	
