#include <stdio.h>
#include <math.h>
#include <string.h>
#include "tiff.h"
#include "allocate.h"
#include "medfilter.h"

int main (int argc, char **argv){
	FILE *fp;
	struct TIFF_img input_img;
	unsigned int** median_fil_img;
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
	if (read_TIFF(fp, &input_img)) {
		fprintf(stderr, "error reading file %s\n", argv[1]);
		exit(1);
	}
	/* close image file */
	fclose(fp);
	/* check the type of image data */
	if (input_img.TIFF_type != 'g') {
		fprintf(stderr, "error: image must be grayscale\n");
		exit(1);
	}
	median_fil_img = median_filter(input_img);
	for (i = 0; i < input_img.height; i++) {
		for (j = 0; j < input_img.width; j++) {
		input_img.mono[i][j] = median_fil_img[i][j];
		}
	}
	/* open image file */
	if ((fp = fopen(argv[2], "wb")) == NULL) {
		fprintf(stderr, "cannot open file %s\n", argv[3]);
		exit(1);
	}
	/* write image */
	if (write_TIFF(fp, &input_img)) {
		fprintf(stderr, "error writing TIFF file %s\n", argv[3] );
		exit(1);
	}
	/* close image file */
	fclose(fp);
	/* de-allocate space which was used for the tiff */
	free_TIFF(&input_img);
	return(0);
}

void error(char *name){
    printf("usage:  %s image.tiff output.tiff\n\n", name);
	printf("This program reads in a 24-bit color TIFF image.\n");
	printf("Then it filters the image with a weighted median fitler\n");
	printf("Then writes out the filtered image \n");
    exit(1);
}

unsigned int** median_filter(struct TIFF_img in) {
	int i, j;

	unsigned int** med_fil = (unsigned int**) get_img(in.width,
														in.height,
														sizeof(unsigned int));
	for (i = 2; i < in.height - 2; i++) {
		for (j = 2; j < in.width - 2; j++) {
			med_fil[i][j] = find_median(in, i, j);
		}
	}

	return med_fil;
}

unsigned int find_median(struct TIFF_img in, int i, int j){
	int m, n;
	int k=0;
	int sum1, sum2;
	int sum_w=0;
	int window[25];
	int weighted_fil[25] = {1, 1, 1, 1, 1,1, 2, 2, 2, 1,1, 2, 2, 2, 1,1, 2, 2, 2, 1,1, 1, 1, 1, 1};
	for (int m = 0; m < 25: m++){
		sum_w+=weighted_fil[m]
	}
	/* Get the window to which you want to apply filter */
	for (m = i - 2; m < i + 3; m++) {
		for (n = j - 2; n < j + 3; n++) {
			window[k] = in.mono[m][n];
			k++;
		}
	}
	/* Sort window values, with them sort the median filter weighted values as well */
	for (m = 0; m < 25; m++) {
		for (n = m + 1; n < 25; n++) {
			if (window[m] < window[n]) {
				
				window[m] = window[m] + window[n];
				window[n] = window[m] - window[n];
				window[m] = window[m] - window[n];
				
				weighted_fil[m] = weighted_fil[m] + weighted_fil[n];
				weighted_fil[n] = weighted_fil[m] - weighted_fil[n];
				weighted_fil[n] = weighted_fil[m] - weighted_fil[n];
		}
	}
	sum1 = weighted_fil[0];
	sum2 = sum_w - sum1;
	for (m = 0; m < 25; m++) {
		if (sum1 > sum2) {
			return window[m];
		}
		sum1 += weighted_fil[m+1];
		sum2 -= weighted_fil[m+1];
	}
	return window[m];
}


