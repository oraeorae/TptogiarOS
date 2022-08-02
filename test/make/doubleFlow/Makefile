include ./second/Makefile
include ./first/Makefile


.PHONY:mainFirst
mainFirst:first
	echo "mainFirst"

.PHONY:main1
main1:mainFirst
	echo "main"



.PHONY:main2
main2:mainSecond
	echo "main"


.PHONY:mainSecond
mainSecond:
	echo "mainSecond"