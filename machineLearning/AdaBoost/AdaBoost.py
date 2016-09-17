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

# the input data
value = np.array([0,1,2,3,4,5,6,7,8,9])
labels = np.array([1,1,1,-1,-1,-1,1,1,1,-1])
weight = np.array([0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1])
predict_label = np.array([0,0,0,0,0,0,0,0,0,0])

num_data = len(value)

# initial the threshold value with a random number
threshold_value = 0

value - threshold_value