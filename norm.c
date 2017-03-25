#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_integration.h>

#include "allvars.h"
#include "proto.h"
#include "define.h"


double f_k(double k, void *param) /* defined as tk^2 * k^(2+ns) * W_k^2 */
{
#ifdef BBKS_TK
 double tk = tk_bbs(k);
#endif

#ifdef EH_TK
 double tk = tk_eh(k);
#endif

#ifdef CAMB_TK
 double tk = tk_camb(k);
#endif

 double k_ns = pow(k , 2+ns);
 double wk,k8;

 k8 = 8.0 * k;                    /* R = 8 Mpc/h */
 tk = tk * tk;

 if(k8 < 1e-4)
   wk = 1.0 / 3.0 * (1.0 - 0.1 * k8 * k8);
 else
   wk = sin(k8) / k8 / k8 / k8 - cos(k8) / k8 / k8;

 wk = wk * wk;

 return tk * k_ns * wk;
}                                  /* end f_k */

void normalization()
{
 int WORKSIZE = 10000;
 double d_growth = growth_factor(0.0);
 d_growth *= d_growth;

 double c = 4.5 * d_growth / Pi_square;

 gsl_function F;
 gsl_integration_workspace *workspace;
 double result,abserr;

 workspace = gsl_integration_workspace_alloc(WORKSIZE);

 F.function = &f_k;
 gsl_integration_qagiu(&F, 0, 0, 1e-9, WORKSIZE, workspace, &result, &abserr);

 gsl_integration_workspace_free(workspace);

 norm_A = Sigma_8 * Sigma_8 / c / result;
}                                   /* end normalization */