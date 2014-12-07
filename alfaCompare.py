# imports
import matplotlib.pylab as plt
import numpy as np
import sys
# initial size of plot window
plt.rcParams['figure.figsize'] = 15, 9

# input file
# import data
if (len(sys.argv) ==2):
    filename = str(sys.argv[1])
else:
    filename = 'savedData/alfaCompare.data'

data = np.loadtxt(filename)
alfa = data[:,0]
energy = data[:,1]
errorbar = data[:,2]

#plt.figure(2)
plt.plot(alfa,energy,'*', markersize = 20)

#plt.errorbar(alfa, energy, yerr=errorbar)

# fit data to line
xFit = np.linspace(0,alfa[-1])
#only use data after fitStartStep
tmp=np.polyfit(alfa,energy,4)
# convenient for plotting 
p=np.poly1d(tmp)
#check fitted line
#plt.plot(xFit,p(xFit))

plt.xticks(fontsize=40)
plt.yticks(fontsize=40)

## labels
plt.xlabel('Value of alpha', fontsize=50)
plt.ylabel('Energy [a.u.]', fontsize=50)

#plt.legend()
#leg = plt.gca().get_legend()
#ltext  = leg.get_texts()
#plt.setp(ltext, fontsize=30) 

# display the plot
plt.show()

