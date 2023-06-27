main: main.c WKdmCompress.c WKdmDecompress.c
	cc -O3 main.c WKdmCompress.c WKdmDecompress.c -o main

clean:
	rm -rf main