#ifndef ALLVAR_H
 #include "allvars.h"
#endif

void init_all();

double ps_lin(double k, double z);

double f_k(double k, void *param);
void normalization();

double growth_factor(double z);
double linear_growth_factor(double a);
double dimensionless_growth_factor(double a);
double hubble_a(double a);
double factor_x(double a);
double integ_kernel(double a, void * param);
double integ_kernel_factor(double a);

double tk_bbks(double k);

#ifdef EH_TK
void init_tk_eh();
double tk_eh(double k_0);
double tf_press_less(double q, double a , double b);
#endif

#ifdef CAMB_TK
void init_tk_from_file();
int line_num(FILE *fp);
double tk_camb(double k);
double large_k_extrapolation(double k);
#endif


