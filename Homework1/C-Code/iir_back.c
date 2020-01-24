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
  struct TIFF_img input_img, output_img,h_filter;
  int32_t i,j;
  int32_t fil_h=256;
  int32_t fil_w=256;
  int32_t x;
  double res;

  if ( argc != 2 ) error( argv[0] );


  /*double *f_low_pass[fil_h][fil_w];*/

 /* for (i=0;i<fil_h;i++){
	  for(j=0;j<fil_w;j++){
		  f_low_pass[i][j]=(double *)malloc(sizeof(double));
		  f_low_pass[i][j]=1.0/81;
  }
  }
*/


  double *iir[fil_h];
 for(i=0;i<fil_h;i++){
	  iir[i]=(double *)malloc(fil_w * sizeof(double));
  }

 if ( ( fp = fopen ( "new.tif", "rb" ) ) == NULL ) {
    fprintf ( stderr, "cannot open file h_out.tif\n" );
    exit ( 1 );
  }

  if ( read_TIFF ( fp, &h_filter ) ) {
    fprintf ( stderr, "error reading file %s\n", argv[1] );
    exit ( 1 );
  }

  fclose(fp);
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
printf("Here");
  for(i=0;i<fil_h;i++){
	  for(j=0;j<fil_w;j++){
		  res=(1.0/(255))*(double)h_filter.mono[i][j];
		  iir[i][j]=res;
		  if (h_filter.mono[i][j]!=0){
			  printf("%lf,%d,%d\n",iir[i][j],i,j);
		  }
	}
	
  }

printf("Now");


  conv2d(&input_img,&output_img,fil_h,fil_w,iir);
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

  for(i=0;i<fil_h;i++){
	  free(iir[i]);
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

