#---------------------------------------Transfer functions for CDM
#OPT += -DBBKS_TK
#OPT += -DEH_TK
OPT += -DCAMB_TK
#--------------------------------------- Select target computer
SYSTYPE="dlcheng"
#SYSTYPE="ITSC"
SYSTYPE="Mac"
#--------------------------------------- Adjust settings for target computer

ifeq ($(SYSTYPE),"Mac")
CC       =   gcc   
OPTIMIZE =   -O3 -Wall
GSL_LIBS=   -L/usr/local/Cellar/gsl/1.16/lib  -Wl
GSL_INCL =  -I/usr/local/Cellar/gsl/1.16/include
endif

ifeq ($(SYSTYPE),"dlcheng")
CC       =   gcc   
OPTIMIZE =   -O3 -Wall 
GSL_INCL =  -I/home/dalong/Install/gsl/include
GSL_LIBS =  -L/home/dalong/Install/gsl/lib
endif

ifeq ($(SYSTYPE),"ITSC")
CC       =   gcc   
OPTIMIZE =   -O3 -Wall
GSL_LIBS=   -L/usr/local/gsl-1.14/lib  -Wl,"-R /usr/local/gsl-1.14/lib" 
GSL_INCL =  -I/usr/local/gsl-1.14/include
endif

OPTIONS =  $(OPTIMIZE) $(OPT) 

EXEC   = Ps_lin

OBJS   = allvars.o init.o lin_ps.o norm.o lin_growth.o \
         tk_bbks.o main.o tk_eh.o tk_camb.o

INCL   = allvars.h proto.h define.h Makefile

CFLAGS = $(OPTIONS) $(GSL_INCL) 

LIBS   = $(GSL_LIBS) -lgsl -lgslcblas -lm 

$(EXEC): $(OBJS) 
	$(CC) $(OBJS) $(LIBS)  -o  $(EXEC)  

$(OBJS): $(INCL) 

clean:
	rm -f $(OBJS) $(EXEC) *.gch
