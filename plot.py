# imports
import matplotlib.pylab as plt
import numpy as np
# initial size of plot window
plt.rcParams['figure.figsize'] = 15, 9

# input file
# import data
genPoints = np.loadtxt( 'genPoints.data')
rPlot = np.linspace(0,6,200)

#plt.figure(2)
nBins=len(genPoints)/10000.0
plt.hist(genPoints,nBins,normed=1)
plt.plot(rPlot, 2.0**5.0*rPlot**2.0*np.exp(-4.0*rPlot),label='Without Coulomb interaction',linewidth=5)
plt.xticks(fontsize=40)
plt.yticks(fontsize=40)
plt.legend()
## labels
plt.xlabel('Distance from nucleus [Bohr radius]', fontsize=50)
#plt.title('Histogram',fontsize=30)
print 'mean distance:'+str(np.mean(genPoints))
leg = plt.gca().get_legend()
ltext  = leg.get_texts()
plt.setp(ltext, fontsize=40) 

# display the plot
plt.show()

