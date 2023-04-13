import os, sys
import ROOT
from optparse import OptionParser
import glob
import math
import json


f=open("/afs/cern.ch/work/p/prsaha/public/Tprime_analysis/flashgg_legacy_runII_UL_v1/CMSSW_10_6_8/src/flashgg/Systematics/data/Muon2018_RunABCD_SF_ID_lowPt.json")

data = json.load(f)

for i in data['NUM_MediumID_DEN_genTracks']['abseta_pt'][0]:
   print(i)

f.close()

