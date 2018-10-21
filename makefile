main: *.c
	gcc *.c -o lol_shell  -L/usr/local/lib -I/usr/local/include -lreadline -Wall 
