#Makefile

#UGL Coding
BASE = /Users/wanbaep2/Desktop
LOC = $(BASE)/Derivatives
EFILE = $(BASE)/FIN513/Homework/HW7/Result

#Home Coding
#BASE = /Users/park-wanbae/Desktop
#LOC = $(BASE)/MFE/2018-1/Derivatives
ETC = $(LOC)/etc
OPTION = $(LOC)/option
OBJS = u_math.o
INCLS = -I$(ETC) -I$(OPTION)
CFLAGS = -std=c++11 -o
#EFILE = $(BASE)/MFE/2018-1/FIN513/Homework/HW6/Result

all: swap
etc_:
	g++ $(INCLS) -c $(ETC)/u_math.cpp

swap: etc_
	g++ $(INCLS) $(CFLAGS) FIN513_HW7 FIN513_HW7.cpp ou_process.cpp \
							snowball_swap.cpp $(OBJS)

clear:
	rm -f ou_process.o
	rm -f snowball_swap.o
	rm -f u_math.o
