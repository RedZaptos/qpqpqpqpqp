make:
	@gcc mainfile.c -o mainfile
	@gcc dateIST.c -o dateIST
	@gcc dateUTC.c -o dateUTC
	@gcc mkdir.c -o mkdir
	@gcc rm.c -o rm
	@gcc cat.c -o cat
	@gcc cd.c -o cd
	@gcc 'ls -a'.c -o ls
	@gcc ls_r.c -o ls_r
	@gcc cat2.c -o cat2
	@gcc datetoday.c -o datetoday
	@clear
	@ ./mainfile
	



