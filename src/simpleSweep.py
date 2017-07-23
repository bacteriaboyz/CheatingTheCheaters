from joblib import Parallel, delayed
import multiprocessing
from sys import argv
import subprocess; # needed for accessing command line
import random
import string

def random_generator(size=45, chars=string.ascii_uppercase + string.digits):
        return ''.join(random.choice(chars) for x in range(size))

script, name, iters, vary = argv[0:4]

seeds = [random_generator() for i in range(int(iters))]

print seeds

def runSim(i):
        nameRun = name + str(i)
        if vary == 'vary':
                nameRun = nameRun + 'V'
                param = nameRun + '.txt'
        else:
                nameRun = nameRun + 'R'
                param = name + '.txt'

        args = ('./idontknow', nameRun, param, seeds[i])
        popen = subprocess.Popen(args, stdout=subprocess.PIPE); # passes command to console
        popen.wait(); # waits?
        output = popen.stdout.read(); # get console output
        return output

num_cores = multiprocessing.cpu_count()

results = Parallel(n_jobs=num_cores)(delayed(runSim)(i) for i in range(int(iters)))
