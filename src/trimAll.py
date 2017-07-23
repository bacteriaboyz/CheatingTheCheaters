from sys import argv
import subprocess; # needed for accessing command line

script, name, numFrames, rad, maxVal = argv[0:5]

for i in range(int(numFrames)):
    f = open(name+'_trimmed_'+str(i)+'.vtk', 'w')
    args = ('./trim.rb', name+str(i)+'.vtk', rad, maxVal)
    popen = subprocess.Popen(args, stdout=subprocess.PIPE); # passes command to console
    #popen.wait(); # waits?
    output = popen.stdout.read(); # get console output
    f.write(output);
    f.close()
    print i
