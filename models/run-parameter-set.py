#!/usr/bin/env python3

import subprocess

b_min=0
b_max=2
file = open("mod_parameters.txt",'r')
parameters=[]
parameters_names=[]
num_parameters=7
for i in range(num_parameters):
    line=file.readline();
    parameters+=[line.split()[1]]
    parameters_names+=[line.split()[0]]

SLOPE1=(0.16-float(parameters[3]))/(0.158-0.17)

command='./trento-music.sh'+" "+str(b_min)+" "+str(b_max)+" "+parameters[2]+" "+parameters[3]+" "+parameters[4]+" "+parameters[6]+" "+parameters[5]+" "+str(SLOPE1)
subprocess.run(command, shell=True)