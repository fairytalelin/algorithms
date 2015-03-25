#include<stdio.h>
#include<stdlib.h>
#include<float.h>

void optimal_bst(float e[7][7],int root[6][6],float const *p,float const *q, int n)
{
  float w[n+1][n+1];
  int i,j,l,r,t;
  for(i = 1; i <= n + 1; i++)
  {
    e[i][i-1] = q[i-1];
    w[i][i-1] = q[i-1];
  }
  for(l = 1; l <= n; l++)
    for(i = 1; i <= n-l+1;i++)
    {
      j = i + l - 1;
      e[i][j] = FLT_MAX;
      w[i][j] = w[i][j-1] + p[j] + q[j];
      for(r = i; r <= j; r++)
      {
        t = e[i][r-1] + e[r+1][j] + w[i][j];
        if(t < e[i][j])
        {
          e[i][j] = t;
          root[i][j] = r;
        }
      }
    }
}

int main(void)
{
  float p[] = {0,0.15,0.10,0.05,0.10,0.20};
  float q[] = {0.05,0.10,0.05,0.05,0.05,0.10};
  float e[7][7];
  int root[6][6];
  optimal_bst(e,root,p,q,5);
  int i,j;
  for(i = 0; i < 6; i++)
  {
    for(j = 0; j < 6;j++)
      printf("%d ",root[i][j]);
    putchar('\n');
  }
}
