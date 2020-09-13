#include <stdio.h>
#include <math.h>

#include "tiff.h"
#include "allocate.h"
#include "median.h"

int main (int argc, char **argv) {
	FILE *fp;
	struct TIFF_img tiff;
	unsigned int** filtered;
	int i, j;

	if (argc != 3) {
		error(argv[0]);
	}

	/* open image file */
	if ((fp = fopen(argv[1], "rb")) == NULL) {
		fprintf(stderr, "cannot open file %s\n", argv[1]);
		exit(1);
	}

	/* read image */
	if (read_TIFF(fp, &tiff)) {
		fprintf(stderr, "error reading file %s\n", argv[1]);
		exit(1);
	}

	/* close image file */
	fclose(fp);

	/* check the type of image data */
	if (tiff.TIFF_type != 'g') {
		fprintf(stderr, "error: image must be grayscale\n");
		exit(1);
	}

	filtered = filter(tiff);
	for (i = 0; i < tiff.height; i++) {
		for (j = 0; j < tiff.width; j++) {
		tiff.mono[i][j] = filtered[i][j];
		}
	}

	/* Free segment map */
	free_img((void *)filtered);

	/* open image file */
	if ((fp = fopen(argv[2], "wb")) == NULL) {
		fprintf(stderr, "cannot open file %s\n", argv[3]);
		exit(1);
	}

	/* write image */
	if (write_TIFF(fp, &tiff)) {
		fprintf(stderr, "error writing TIFF file %s\n", argv[3] );
		exit(1);
	}

	/* close image file */
	fclose(fp);

	/* de-allocate space which was used for the tiff */
	free_TIFF(&tiff);

	return(0);
}

void error(char *name) {
    printf("usage:  %s image.tiff output.tiff\n\n", name);
	printf("Filter an image with a weighted median fitler\n");
    exit(1);
}

unsigned int** medianfilter(struct TIFF_img in) {
	int i, j, m, n, k, x;
	int sum1, sum2, fil_sum;
	int tmp;
	int data[25], weights[25];

					
	#Create empty filtered image
	unsigned int** fil_img = (unsigned int**) get_img(in.width,
														in.height,
														sizeof(unsigned int));
	
	for (i = 2; i < in.height - 2; i++) {
		for (j = 2; j < in.width - 2; j++) {
			for(x=0;x<25;x++){
				data[x]=0;
				fil_sum=0;
				if(x>5){
					if (x>5 && x<19) && (x%5 == 1 || x%5==2 || x%5 == 3){
						weights[x]=2;
						fil_sum+=weights[x];
					}
				}
				else{
						weights[x]=1;
						fil_sum+=weights[x];
				}

			k = 0;
			for (m = i - 2; m < i + 3; m++) {
				for (n = j - 2; n < j + 3; n++) {
					data[k] = in.mono[m][n];
					k++;
				}
			}
			for (m = 0; m < 25; m++) {
				for (n = m + 1; n < 25; n++) {
					if (data[m] < data[n]) {
						tmp = data[m];
						data[m] = data[n];
						data[n] = tmp;

						tmp = weights[m];
						weights[m] = weights[n];
						weights[n] = tmp;
					}
				}
			}
			sum1 = weights[0];
			sum2 = 34 - sum1;
			for (m = 0; m < 25; m++) {
				if (sum1 > sum2) {
					fil_img[i][j]= data[m];
			}
			sum1 += weights[m+1];
			sum2 -= weights[m+1];
			}
			fil_img[i][j] = data[m];
		}
	}

	
}

