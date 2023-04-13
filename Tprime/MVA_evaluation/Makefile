.PHONY: clean vars

ROOTCINT      = $(ROOTSYS)/bin/rootcint
ROOTCFLAGS    = $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

ifdef SCRAM_ARCH
  CXX         := $(shell scramv1 tool info gcc-cxxcompiler | grep CXX= | sed s/CXX=//)
else
  ifdef CXXCOMPILER
    CXX         := $(CXXCOMPILER)
  else
    CXX         := c++
  endif
endif

ROOT6 = $(shell $(ROOTSYS)/bin/root-config --version)
ifneq ($(findstring 6.,$(ROOT6)),)
ROOT6         = "yes"
else
ROOT6         = "no"
endif

CXXFLAGS      = -g -O0 -Wall -fPIC -pipe
LD            = $(CXX)
LDFLAGS       = -g
SOFLAGS       = -shared

CXXFLAGS     += $(ROOTCFLAGS)
GLIBS         = $(filter-out -lz, $(ROOTGLIBS)) -lTMVA -lTMVAGui -lRooFitCore -lRooFit -lProof
EXTHEADERS    = -I..

all: sel
	@echo "Full build successful."

sel: MVA_score.cc 
	$(LD) $(GLIBS) $(CXXFLAGS) -lMinuit $< -o sel  MVAnalysis.cc

clean:
	rm -rf  tools.o sel

vars:
ifndef CMSSW_BASE
    $(error CMSSW_BASE is undefined, please run cmsenv somewhere)
endif

