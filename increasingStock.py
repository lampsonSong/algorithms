#input : no
#output : all increasing stocks(name, increasing number) for the last week
#author : lampson
#date : 2015-8-17

#coding:utf-8

import tushare as ts
import time
import os
import xlrd


# currentT = time.localtime()
# print currentT

# day = time.localtime(time.time()-3600*24)
# end = time.strftime("%Y-%m-%d %H:%M:%S",day)
# print end

# day = '2014-01-07 09:30:00'
# start = time.strptime(day, "%Y-%m-%d %H:%M:%S")
# print time.mktime(start)

# # data = ts.get_today_all()
# data = ts.get_tick_data('300348','2015-08-12')

# input : back k days
def period(k):
	nowFloat = time.time()

	now = time.localtime(nowFloat)
	back = time.localtime(nowFloat - 3600*24*k)
	backOne = time.localtime(nowFloat - 3600*24*(k+1))

	start = time.strftime("%Y-%m-%d",now)
	end = time.strftime("%Y-%m-%d",back)
	endBefore = time.strftime("%Y-%m-%d",backOne)

	return (start,end,endBefore)


start,end,endBefore = period(7)

path = 'data/basic/'
fileName = start + '.xlsx'
file = path + fileName

if not os.path.exists(file):
	data_today = ts.get_today_all()
	data_today.to_excel(file)

data = xlrd.open_workbook(file)

table = data.sheets()[0]

#row numeber, column number
number_rows = table.nrows
number_columns = table.ncols

# python, convert encode to utf-8
# name = table.cell(1,2).value

# print name.encode('utf-8')

count = 0
#iterate all stocks
for i in range(1,number_rows):
	code = table.cell(i,1).value
	data_end = ts.get_hist_data(code,endBefore,end)
	
	if data_end.close.values.size == 0:
		continue
	
	end_value = data_end.close.values[0]
	start_value = table.cell(i,4).value
	
	diff_price = start_value - end_value
	# print diff_price
	if diff_price > 0:
		count = count + 1
		code_p = table.cell(i,1).value
		name = table.cell(i,2).value
		print code_p.encode('utf-8') + '   ' + name.encode('utf-8')

print 'test'
print count