#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num_rows = 5;
	double **tm = (double**) malloc(sizeof(double*)*num_rows);

	for(int i=0;i<num_rows;i++)
	{
		tm[i]=(double*) malloc(sizeof(double)*(i+1));
	}
	
	int k=0;

	for(int i=0;i<num_rows;i++)
	{
		for(int j=0;j<i+1;j++)
		{
			tm[i][j]=k;
			k+=1.1;
		}
	}
	for(int i=0;i<num_rows;i++)
	{
		for(int j=0;j<i+1;j++)
		{
			printf("%lf ",tm[i][j]);
		}
		printf("\n");
	}
	for(int i=0;i<num_rows;i++)
	{
		free(tm[i]);
	}

	free(tm);
	return 0;
}
