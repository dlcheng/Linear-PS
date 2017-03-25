#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "allvars.h"
#include "proto.h"
#include "define.h"

int main()
{
 	
 double kmin = 1e-2;
 double kmax = 20;
 int    N = 20;

 double kdis = (log10(kmax) - log10(kmin))/ (double) N;
	
 int i;
 
 double k;	
	
 init_all();

 for(i=0; i<N; i++)
   {	
   k = log10(kmin) + (i + 0.5) * kdis;	
   k = pow(10, k);
   printf("%.6e	%.6e\n", k , ps_lin(k, 0.5));	
   }
   
  return 0; 
}         /* end main */	
