#
#
#	Date 		: 			2016-9-14
# 	Author 		: 			lampson
# 	Input 		: 			A set of numbers and labels
#	Output 		: 			A classifier
#
#

import numpy as np
import scipy as sp
from weakClassifier import weakClassifier

import pdb

X = np.array([[1,2,3,4],[5,6,7,8]])
Y = np.array([1,1,-1,-1])


Y.shape = (1,len(Y))
label = Y.transpose()

weight = np.array([0.25,0.25,0.25,0.25])

# pdb.set_trace()
we = weakClassifier(X,label)
we.train(weight)
