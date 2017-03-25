#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "allvars.h"
#include "proto.h"
#include "define.h"

/* Function;
 * (1) normalization
 */

void init_all()
{
 h0 = H0;
 Omega_m = OMEGA_M;
 Omega_v = OMEGA_V;
 Omega_b = OMEGA_B;
 ns = NS;
 Sigma_8 = SIGMA_8;

#ifdef EH_TK
 init_tk_eh();
#endif

#ifdef CAMB_TK
 init_tk_from_file();
#endif
 
 normalization();

}          /* end init_all */



