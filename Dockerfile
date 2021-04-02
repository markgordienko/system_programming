FROM ubuntu
COPY array.s .
RUN apt-get update
RUN apt-get install binutils -y
RUN apt-get install nasm
RUN nasm -f elf64 array.s
RUN ld array.o
CMD ./a.out