#
#
#		Date 		: 		2016-9-26
#		Author 		: 		lampson
#		Input 		: 		an array of numbers
#		Output 		: 		a sorted array by the binary heap
#
#

import numpy as np

def heapSort(data):
	lastRoot = len(data)/2 - 1
	lastInd = len(data)-1

	for i in range(lastRoot,-1,-1):
		heapAdjust(data,i,lastInd)
		# print i

	for i in range(lastInd,0,-1):
		data[i],data[0] = data[0],data[i]
		heapAdjust(data,0,i-1)

	print data


def heapAdjust(data,start,end):
	root = start
	
	while(1):
		child = root*2+1
		if(child > end):
			break

		if(child+1 <= end and data[child] < data[child+1]):
			child = child + 1
		
		if(data[child] > data[root]):
			data[root],data[child] = data[child],data[root]
			root = child
		else:
			break


def main():
	input_array = np.array([3,4,6,1,3,2,8,7])
	heapSort(input_array)


if __name__ == "__main__":
	main()


