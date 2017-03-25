#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_spline.h>

#include "allvars.h"
#include "proto.h"
#include "define.h"

#ifdef CAMB_TK

static gsl_interp_accel *sp_tk_acc;
static gsl_spline *sp_tk;              /* spline of tk */
static double *kk;                     /* the k bins */
static double *tkk;                    /* the transfer function of all matter */

static double kf_max;                  /* the maximum k in the transfer function file */
static double kf_min;                  /* the minimum k */
static int Num_l;                      /* line number of the file */

void init_tk_from_file()
{
   char filename[500] = CAMB_FILE;
   FILE * fp;
   fp = fopen(filename, "r");

   int i;
   double temp_k, temp_tkc, temp_tkb, other_1, other_2, other_3, other_4; 
   double fb;  /* fractino baryon */

   Num_l = line_num(fp);
   fb = Omega_b / Omega_m;
   kk  = (double *)malloc(Num_l * sizeof(double));
   tkk = (double *)malloc(Num_l * sizeof(double));
   sp_tk_acc = gsl_interp_accel_alloc();
   sp_tk     = gsl_spline_alloc(gsl_interp_cspline, Num_l);

   rewind(fp);

   for(i=0; i<Num_l; i++)
   	 {
      fscanf(fp, "%lf %lf %lf %lf %lf %lf %lf\n", &temp_k, &temp_tkc, &temp_tkb, 
                                                  &other_1, &other_2, &other_3, &other_4);
      kk[i] = temp_k;
      tkk[i] = temp_tkc * (1. - fb) + temp_tkb * fb;

      if(i == 0)
      	kf_min = temp_k;

      if(i == Num_l - 1)
      	kf_max = temp_k;
   	 } 

   gsl_spline_init(sp_tk, kk, tkk, Num_l);

   fclose(fp);
}  /* end init_tk_from_file */

int line_num(FILE *fp)
{
  int ch, number_of_lines = 0;

  do
  {
   ch = fgetc(fp);
   if(ch == '\n')
     number_of_lines++;
   
  }while(ch != EOF);
   
 return number_of_lines;
}      /* end line_num */

double tk_camb(double k)
{
  if(k < kf_min)
  	return 1.;

  if(k > kf_max)
  	return large_k_extrapolation(k);        /* or neglect all the modes larger than kf_max ~ 100 h/Mpc */

  return gsl_spline_eval(sp_tk, k, sp_tk_acc);
}  /* end tk_from_file */


/* k > kmax, using power law tk=A*k^a for estimation */
double large_k_extrapolation(double k)
{
  double a = log(tkk[Num_l-1]/tkk[Num_l-2]) / log(kk[Num_l-1]/kk[Num_l-2]);

  double result = tkk[Num_l-1] * pow(k/kf_max, a);

  return result;
}  /* end large_k_extrapolation */

#endif
