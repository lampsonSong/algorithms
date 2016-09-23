#
#
#	Date 		: 			2016-9-14
# 	Author 		: 			lampson
# 	Input 		: 			A set of numbers and labels
#	Output 		: 			A classifier
#
#

#
# This is an example of AdaBoost, the classifier is a simple decision stump
#

import numpy as np
import scipy as sp
from weakClassifier import weakClassifier

import pdb

X = np.array([[1,2,3,4,12],[5,6,7,8,5],[2,3,19,5,7]])
Y = np.array([1,1,-1,-1,1])


Y.shape = (1,len(Y))
label = Y.transpose()

weight = np.array([0.2,0.2,0.2,0.2,0.2])

# pdb.set_trace()
we = weakClassifier(X,label)
err,threshold,direction = we.train(weight)

print(err,threshold,direction)