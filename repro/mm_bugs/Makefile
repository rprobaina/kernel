all:
	gcc mleak.c -o mleak
	gcc badptr.c -o badptr
	gcc nullptr.c -o nullptr
	gcc uninitdata.c -o uninitdata
	gcc bufoverflow.c -o bufoverflow
	gcc ref_nonexistent_var.c -o ref_nonexistent_var
clean:
	rm mleak badptr nullptr uninitdata bufoverflow ref_nonexistent_var
