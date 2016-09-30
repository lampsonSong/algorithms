#
#
#
#		Date 		:  			2016-9-30
#		Author 		: 			lampson
#		Input 		: 			a random array of integers
# 		Outpur 		: 			a sorted array
#		Objective	: 			an implementation of quick sort in python, to understand recursion
#
#

import pdb

def sort(data):
	num = len(data)-1
	print num
	if(num>1):
		select_value = data[num/2]
		print select_value
		forword_i = 0
		end_i = num

		while(forword_i < end_i):
			while(forword_i < end_i and data[forword_i] < select_value):
				forword_i += 1

			while(forword_i < end_i and data[end_i] > select_value):
				end_i -= 1

			if(forword_i < end_i):
				data[forword_i],data[end_i] = data[end_i],data[forword_i]
			
		# print len(data[:end_i])
		# print len(data[end_i:])
		sort(data[:end_i])
		sort(data[end_i:])
	else:
		print data




def main():
	data = [7,4,5,2,45,6,2,1,3]
	sort(data)


if __name__ == "__main__":
	main()