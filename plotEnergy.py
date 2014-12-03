#--------------Plot Energy----------
# imports
import matplotlib.pylab as plt
import numpy as np
# initial size of plot window
#plt.rcParams['figure.figsize'] = 15, 9

# input file
# import data
plotMax = 800
tmp = np.loadtxt('energy.data')
energy = tmp[:,0]
meanEnergy = tmp[:,1]
meanEnergyPrime = np.gradient(meanEnergy)
plt.plot(meanEnergyPrime[:plotMax],label='Derivative of mean local energy',linewidth=3)
plt.plot(energy[:plotMax],label='Local energy')
plt.plot(meanEnergy[:plotMax],label='Mean local energy',linewidth=3)
plt.xticks(fontsize=40)
plt.yticks(fontsize=40)

plt.xlabel('Simulation steps', fontsize=50)
plt.ylabel('Ground state energy [a.u.]', fontsize=50)
plt.grid()
plt.legend(loc='best')
leg = plt.gca().get_legend()
ltext  = leg.get_texts()
plt.setp(ltext, fontsize=30) 

# display the plot
plt.show()

