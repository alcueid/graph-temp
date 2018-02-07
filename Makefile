upload:
	git add -A
	git commit
	git push origin working-branch

compile: aggre.c
	gcc aggre.c -Wall -g -o aggre

aggregate:
	./aggre /mnt/dd/Dropbox/github/graph-temp/sample/ 2018-02-07 2018-02-13

