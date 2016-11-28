#coding=utf-8
from random import randint
import codecs
import random
important= ["北京","上海","广州","深圳","南京","天津"]
def makeData(count):
	f = open("cities.txt","r")
	cities=f.readline().split(" ")
	f.close()
	number = {}
	maps = {}
	limit={}
	n= 0
	for city in cities:
		print city
		city = city.decode('gbk')
		number[n] = city
		if city in important:
			limit[n] = 0.15
		else:
			limit[n] = 0.02
		maps[n]=0
		n+=1
	#print cities
	n-=1
	i = 0
	f = codecs.open("randomData.txt","w","utf-8")
	while i<count:
		startC = randint(0,n)
		endC = randint(0,n)
		if startC == endC or maps[startC]/count > limit[startC]:
			continue
		maps[startC] = maps[startC]+1
		startTime = randint(0,24*60-1)
		categories= randint(1,3)
		if categories == 1:			# train
			lastTime = randint(30,1800)
			cost = randint(15,700)
			bian = ''.join(random.sample('KTGZC',1)+random.sample("1234567890",4))
		elif categories == 2: #bus
			lastTime = randint(30,480)
			cost = randint(2,300)
			length = randint(2,3)
			bian = ''.join(random.sample('ABCDEFGHIJKLMNOPQRSTUVWXYZ',length)+random.sample("1234567890",6-length))
		else:	#plane
			lastTime = randint(40,240)
			cost = randint(300,4000)
			bian = ''.join(random.sample("PMB",1)+random.sample("1234567890",4))
		f.write(str(categories) + " "+bian+" "+ number[startC] + " " + number[endC] + " " + str(startTime)+" "+\
			str(lastTime) + " "+ str(cost) +"\r\n")
		i+=1
	f.close()