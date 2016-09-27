#
#
#
#		Date 		:  			2016-9-27
#		Author 		: 			lampson
#		Input 		: 			a random array of integers
# 		Outpur 		: 			a sorted array
#
#

def merge(left,right):

	result = []
	left_i = right_i = 0
	
	while(left_i < len(left) and right_i < len(right)):
		if(left[left_i] < right[right_i]):
			result.append(left[left_i])
			left_i = left_i+1
		else:
			result.append(right[right_i])
			right_i = right_i+1

		print result

	result += right[right_i:]
	result += left[left_i:]

	return result


def mergeSort(data):
	
	if (len(data)<=1):
		return data

	middle = len(data)/2

	left = data[:middle]
	right = data[middle:]

	left = mergeSort(left)
	right = mergeSort(right)

	return merge(left,right)
	


def main():
	data = [4,3,5,2,15,6,7,3,2]
	print mergeSort(data)


if __name__ == "__main__":
	main()