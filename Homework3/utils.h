#include <stdio.h>
#include <math.h>

#include "tiff.h"
#include "allocate.h"
#include "randlib.h"
#include "typeutil.h"

struct pixel {
	int m;
	int n;
};

struct px_linked_list {
	struct pixel px;
	struct px_linked_list *next_px;
};

void ConnectedNeighbors(struct pixel s,double T,unsigned char **img,int width,int height,int *M,struct pixel c[4]);

void ConnectedSet(struct pixel s,double T,unsigned char **img,int width,int height,int ClassLabel,unsigned int **seg,int *NumConPixels);

void CheckThreshold(struct pixel s,struct pixel p,double T, unsigned char **img,int width,int height,int *M,struct pixel c[4]);





