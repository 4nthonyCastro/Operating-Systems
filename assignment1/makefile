assign1 = wordcount.o

wordcount.o: wordcount.c
gcc -g -c wordcount.c -o wordcount.o

wordcount: ${assign1}
gcc -g -o wordcount ${assign1}

clean:
rm -f ${assign1}
