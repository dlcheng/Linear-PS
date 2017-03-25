/* 
Attention:
(1) the code uses natural unit in the calculation, 1 length = 1 Mpc/h
*/

/* COSMOLOGICAL PARAMETERS */
#define H0         0.7                          /* H(today) = H0 * 100km/s/Mpc */
#define T_CMB      2.728                        /* CMB average temperature in unit of Kelvin */
#define OMEGA_M    0.3                          /* the matter energy density in unit of critical density today */
#define OMEGA_B    0.049                        /* the baryon energy density in unit of critical density today */
#define OMEGA_V    0.7                          /* the vaccum energy density in unit of cirtical density today */
#define NS         0.96                         /* the power law index of primordial power spectrum */
#define SIGMA_8    0.8                          /* fluctuation of matter excess fraction in sphere of 8 Mpc/h today */

#ifdef CAMB_TK
#define CAMB_FILE  "./Input/planck_transfer.dat"
#endif

/* CONSTANTS */
#define Pi         3.1415926535897932384626433832795028842              /* pi */
#define Pi_square  9.86960440108935861883449099987615113531             /* pi^2 */

                
