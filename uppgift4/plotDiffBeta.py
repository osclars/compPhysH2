
# imports
import matplotlib.pylab as plt
import numpy as np
# initial size of plot window
plt.rcParams['figure.figsize'] = 15, 9

# input file
# import data
beta6 = np.loadtxt( 'betadata/alfas06.data')
beta7 = np.loadtxt( 'betadata/alfas07.data')
beta8 = np.loadtxt( 'betadata/alfas08.data')
beta9 = np.loadtxt( 'betadata/alfas09.data')
beta10 = np.loadtxt( 'betadata/alfas10.data')

#plt.figure(2)
plt.plot(beta6,label=r'$\beta=0.6$')
plt.plot(beta7,label=r'$\beta=0.7$')
plt.plot(beta8,label=r'$\beta=0.8$')
plt.plot(beta9,label=r'$\beta=0.9$')
plt.plot(beta10, label= r'$\beta=1.0$')
plt.xticks(fontsize=40)
plt.yticks(fontsize=40)
## labels
plt.xlabel('Number of iterations', fontsize=50)
plt.ylabel('Value of alpha', fontsize=50)
#plt.title('Histogram',fontsize=30)
plt.legend()
leg = plt.gca().get_legend()
ltext  = leg.get_texts()
plt.setp(ltext, fontsize=30) 

# display the plot
plt.show()

