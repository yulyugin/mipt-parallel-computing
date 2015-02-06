UNAME := $(shell uname)

.DELETE_ON_ERROR:

ifneq ($(VERBOSE),yes)
MAKEFLAGS += -s
endif  # VERBOSE

OPTIONS=-halt-on-error

ifeq ($(UNAME), Linux)
LATEXCOMMAND=xelatex
RM=rm -f
GNUPLOT=gnuplot
else
LATEXCOMMAND=xelatex.exe
RM=rm.exe -f
GNUPLOT=wgnuplot.exe
endif

SRC_DIR=lectures

# find all lectures
LECTURES=$(patsubst $(SRC_DIR)/%.tex,%,$(wildcard $(SRC_DIR)/*.tex))

.PHONY: all clean $(LECTURES)

all: $(LECTURES)

amdahls-law.pdf: $(SRC_DIR)/amdahls-law.plt
	cd $(SRC_DIR) && $(GNUPLOT) amdahls-law.plt

efficiency: amdahls-law.pdf

$(LECTURES):
	cd $(SRC_DIR) && bash -c "while ( $(LATEXCOMMAND) $(OPTIONS) $@ ; grep -q 'Rerun to get' $@.log ) do true ; done"

clean:
	cd $(SRC_DIR) && $(RM) *.log *.aux *.nav *.out *.pdf *.snm *.toc *.vrb
