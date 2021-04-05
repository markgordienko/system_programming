FROM ubuntu
COPY sp3.cpp .
RUN apt-get update
RUN apt-get install build-essential -y
RUN apt-get install gcc-multilib -y
RUN g++ sp3.cpp
CMD ./a.out