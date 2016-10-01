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

def sort(data,forword_i,end_i):
	
	if(forword_i >= end_i):
		return data

	select_value = data[forword_i]
	# print select_value

	start = forword_i
	end = end_i	

	while(forword_i < end_i):
		
		while(forword_i < end_i and data[end_i] >= select_value):
			end_i -= 1

		data[forword_i] = data[end_i]

		while(forword_i < end_i and data[forword_i] <= select_value):
			forword_i += 1

		data[end_i] = data[forword_i]

	data[forword_i] = select_value
		
	# print forword_i,end_i,start,end
	# pdb.set_trace()
	sort(data,start,forword_i-1)
	sort(data,end_i+1,end)

	return data




def main():
	data = [7,4,5,2,45,6,2,1,3]
	num = len(data)-1

	print sort(data,0,num)


if __name__ == "__main__":
	main()