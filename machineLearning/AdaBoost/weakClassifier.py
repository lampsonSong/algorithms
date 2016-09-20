#
#
#	Date 		: 			2016-9-17
# 	Author 		: 			lampson
# 	Objective 	: 			Give out a weak classifier
#
#


import numpy as np
import pdb

class weakClassifier:
	"This is a weak classifier, decision stump: bigger than a threshold->positive, otherwise negtive"
	'''
	X is a n*m matrix
	Y is a n*1 vector labeled as -1 and 1
	weight is a 1*m vector in the range of [0,1]
	'''

	def __init__(self,X,label):
		self.X = X
		# it is not workable for a one-dimensional vector to transpose in python
		self.label = label
		self.numData = self.X.shape[0]
		self.cols = self.X.shape[1]


	#train objective: adjust the weights
	def train(self,weight):

		for i in range(self.numData):
			item = self.X[i,:]
			# item.shape = [1,self.cols]
			# item = item.transpose()
			self.weight = np.array(weight)
			self.findErrMin(item,1,weight)
			# print self.X[i,:]



	def findErrMin(self,item,direction,weight):

		start = np.min(item)
		end = np.max(item)
		steps = 100

		step_len = float(end-start)/float(steps)

		min_err = 10000

		for threshold in np.arange(start,end,step_len):
			now_label = np.ones((len(item),1))
			err_label = np.zeros((len(item),1))
			# pdb.set_trace()
			now_label[item*direction < threshold*direction] = -1
			err_label[now_label != self.label] = 1
			
			err_label = err_label.transpose()

			err = np.sum(err_label*weight)

			print err

			# if(err<min_err):
