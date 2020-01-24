#include <stdio.h>
#include <math.h>
#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"
#include "utils.h"

void error(char *name);

int main (int argc, char **argv) 
{
  FILE *fp;
  struct TIFF_img input_img, output_img;
  int32_t i,j,m;
  int32_t fil_h;
  int32_t fil_w;
  int32_t x;
  double res;



  if ( argc != 2 ) error( argv[0] );



  /* open image file */
  if ( ( fp = fopen ( argv[1], "rb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file %s\n", argv[1] );
    exit ( 1 );
  }

  /* read image */
  if ( read_TIFF ( fp, &input_img ) ) {
    fprintf ( stderr, "error reading file %s\n", argv[1] );
    exit ( 1 );
  }

  /* close image file */
  fclose ( fp );



  /* check the type of image data */
  if ( input_img.TIFF_type != 'c' ) {
    fprintf ( stderr, "error:  image must be 24-bit color\n" );
    exit ( 1 );
  }

get_TIFF(&output_img, input_img.height, input_img.width, 'c');

  /* set up structure for output achromatic image */
  /* to allocate a full color image use type 'c' */
fil_h=input_img.height;
fil_w=input_img.width;

double (*temp)[fil_h][fil_w]=malloc(sizeof(double[3][fil_h][fil_w]));


	for (m = 0; m < 3; m++) {
		for (i = 0; i < fil_h; i++) {
			for (j = 0; j < fil_w; j++) {
				temp[m][i][j] = 0.01 * input_img.color[m][i][j]; 
				if (i > 0) {
					temp[m][i][j] += 0.9 * temp[m][i-1][j];
				} 
				if (j > 0) {
					temp[m][i][j] += 0.9 * temp[m][i][j-1];
				}
				if (i > 0 && j > 0) {
					temp[m][i][j] += -0.81 * temp[m][i-1][j-1];
				}
				
			}
		}
	}

	for (m = 0; m < 3; m++) {
		for (i = 0; i < fil_h; i++) {
			for (j = 0; j < fil_w; j++) {
				output_img.color[m][i][j]=clipping(temp[m][i][j]);
			}
		}
	}

  /* open output image file */
  if ( ( fp = fopen ( "iir.tif", "wb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file green.tif\n");
    exit ( 1 );
  }

  /* write output image */
  if ( write_TIFF ( fp, &output_img ) ) {
    fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
    exit ( 1 );
  }

  /* close green image file */
  fclose ( fp );
    

  /* de-allocate space which was used for the images */
  free_TIFF ( &(input_img) );
  free_TIFF ( &(output_img) );
	
  /*free all filter memory*/


  return(0);
}

void error(char *name)
{
    printf("usage:  %s  image.tiff \n\n",name);
    printf("this program reads in a 24-bit color TIFF image.\n");
    printf("It then horizontally filters the green component, adds noise,\n");
    printf("and writes out the result as an 8-bit image\n");
    printf("with the name 'green.tiff'.\n");
    printf("It also generates an 8-bit color image,\n");
    printf("that swaps red and green components from the input image");
    exit(1);
}

