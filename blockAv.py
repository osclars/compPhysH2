import matplotlib.pylab as plt
import numpy as np

data=np.loadtxt('energy.data')[:,0]

# Largest block size to test
maxBS = 500
# Create block sizes for calculation
blockSizes= range(2,maxBS, 10)

# calculate variance of all date without blocks, (to calculte s later)
dataVar = np.var(data)
s = np.array([])
#loop for differnt blocksizes
for blockSize in blockSizes:
    meanDataBlock=np.array([])

    for i in range(len(data[::blockSize])):
        #calculate block means
        meanDataBlock=np.append(meanDataBlock , np.mean(data[i * blockSize:(i+1) * blockSize]))

    # calculte and store s for current block size
    s = np.append(s, blockSize*np.var(meanDataBlock)/ dataVar)
    #print "S:%f \t blocksize:%d\n" %(s, blockSize)
plt.ion()
plt.plot(blockSizes,s, '*',markersize=20)
plt.plot([0,maxBS],[11,11])
plt.xlabel('Blocksize', fontsize=50)
plt.ylabel('S-value', fontsize=50)
plt.xticks(fontsize=40)
plt.yticks(fontsize=40)
plt.show()
