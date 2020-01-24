#include <stdio.h>
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
  int32_t i,j;
  int32_t fil_h=9;
  int32_t fil_w=9;
  float *f_low_pass[fil_h];

  if ( argc != 2 ) error( argv[0] );

  /* allocating memory for filter */
  for(i=0;i<fil_h;i++){
	  f_low_pass[i]=(float *)malloc(fil_w * sizeof(float));
  }
 /* assigning filter values */
  for(i=0;i< fil_h;i++){
	  for(j=0;j<fil_w;j++){
		f_low_pass[i][j]=1.0/81;
	  }
  }

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

  /* set up structure for output achromatic image */
  /* to allocate a full color image use type 'c' */
  get_TIFF ( &output_img, input_img.height, input_img.width, 'c' );

  /* Convolution Function called from utils.c */
  _2Dconv(f_low_pass,fil_h,fil_w,&input_img,&output_img);

  /* open output image file */
  if ( ( fp = fopen ( "firlow-pass-output.tif", "wb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file green.tif\n");
    exit ( 1 );
  }

  /* write output image */
  if ( write_TIFF ( fp, &output_img ) ) {
    fprintf ( stderr, "error writing TIFF file %s\n", argv[2] );
    exit ( 1 );
  }

  /* close output image file */
  fclose ( fp );
    
  /* de-allocate space which was used for the images */
  free_TIFF ( &(input_img) );
  free_TIFF ( &(output_img) );
	
  /* free filter memory */
  for(i=0;i<fil_h;i++){
	  free(f_low_pass[i]);
  }
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

