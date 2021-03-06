
# 
# Code for running multiple parallel instances of the simulation while varying
# a given parameter across a given range. All other parameters are taken from
# the parameter file specified as input.
# 

from joblib import Parallel, delayed
import multiprocessing
from sys import argv
from __future__ import divisioni
import math
import random

param, param_range, base_param_fp = argv[0:4]

'''
Linspace
'''
def linspace(start, stop, n):
    if n == 1:
        yield stop
        return
    h = (stop - start) / (n - 1)
    for i in range(n):
        yield start + h * i


'''
Creates latin hypercube sample of parameters
'''
def latinHyperCube(pRanges, num_cuts):
    pArr = []
    for p in pRanges:
        r = range(0,num_cuts)
        sorted(r, key=lambda *args: random.random())
        pArr.append(r) # add new dimension

    map(list, zip(*l))

        param_vals = list(linspace(p[0], p[1], num_cuts))
            # numbers of parameter values 
        

'''
    Creates and returns an array of random 45-letter seeds to be used in 
    simulations, writes results to a file.
'''
def createSeeds():
    return seedArr

'''
    Runs simulation with the specified parameter filepath and seed.
'''
def runSim(pParam, pRand):
    #TODO:
    outStr = simTime, numBac, numProd;
    return outStr

inputs = range(48)

def processInput(i):
    print i
    return i * i

num_cores = multiprocessing.cpu_count()

results = Parallel(n_jobs=num_cores)(delayed(processInput)(i) for i in inputs)

