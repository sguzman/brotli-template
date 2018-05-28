FROM ubuntu

RUN apt-get update;
RUN apt-get install -y cmake build-essential libboost-system-dev git libboost-thread-dev libssl-dev python libtcmalloc-minimal4 libcurl4-openssl-dev
RUN git clone https://github.com/ipkn/crow

WORKDIR crow
RUN mkdir build

WORKDIR build
RUN cmake ..
RUN make

WORKDIR ../../
RUN cmake .
RUN make