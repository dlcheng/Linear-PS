#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "allvars.h"
#include "proto.h"
#include "define.h"

double ps_lin(double k, double z)
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
 
 tk *= tk;

 double d = growth_factor(z) / growth_factor(0);
 d *= d;

 return norm_A * pow(k, ns) * tk * d;

}                /* end Ps_lin */