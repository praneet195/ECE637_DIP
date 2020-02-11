#include "utils.h"

void CheckThreshold(struct pixel s,struct pixel p,double T,unsigned char **img,int width,int height,int *M,struct pixel c[4]){

     	if (p.n >= 0 && p.n <width && p.m>=0 && p.m<height){
                if (abs(img[s.m][s.n] - img[p.m][p.n]) <= T) {
                c[*M].m = p.m;
                c[*M].n = p.n;
                (*M)++;
                }
        }

}

void ConnectedNeighbors(struct pixel s,double T,unsigned char **img,int width,int height,int *M,struct pixel c[4]) {
        *M = 0;
	
	struct pixel p1,p2,p3,p4;

	p1.m=s.m-1;
	p1.n=s.n;

	p2.m=s.m+1;
	p2.n=s.n;

	p3.m=s.m;
	p3.n=s.n+1;

	p4.m=s.m;
	p4.n=s.n-1;

	CheckThreshold(s,p1,T,img,width,height,M,c);
	CheckThreshold(s,p2,T,img,width,height,M,c);
	CheckThreshold(s,p3,T,img,width,height,M,c);
	CheckThreshold(s,p4,T,img,width,height,M,c);


}

void ConnectedSet(struct pixel s,double T,unsigned char **img,int width,int height,int ClassLabel,unsigned int **seg,int *NumConPixels) {
	struct px_linked_list *head_px, *next_px, *tmp_px;
	struct pixel c[4];
	int M;
	int i;

	(*NumConPixels) = 0;

	head_px = (struct px_linked_list *)malloc(sizeof(struct px_linked_list));
	head_px->px.m = s.m;
	head_px->px.n = s.n;
	head_px->next_px = NULL;
	next_px = head_px;

	/*Checking to end loop */

	while (head_px != NULL) {
		if (seg[head_px->px.m][head_px->px.n] != ClassLabel) {
			
			seg[head_px->px.m][head_px->px.n] = ClassLabel;
			(*NumConPixels)++;
			ConnectedNeighbors(head_px->px, T, img, width, height, &M, c);
			for (i = 0; i < M; i++) {
				if (seg[c[i].m][c[i].n] != ClassLabel) {
					tmp_px = (struct px_linked_list *)malloc(sizeof(struct px_linked_list));
					tmp_px->px.m = c[i].m;
					tmp_px->px.n = c[i].n;
					tmp_px->next_px = NULL;
					next_px->next_px = tmp_px;
					next_px = tmp_px;
				}
			}
		}
		tmp_px = head_px->next_px;
		free(head_px);
		head_px = tmp_px;
	}
}