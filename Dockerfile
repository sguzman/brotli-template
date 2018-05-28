FROM ubuntu

RUN apt-get update;
RUN apt-get install -y cmake build-essential libboost-system-dev libboost-thread-dev libssl-dev python libtcmalloc-minimal4 libcurl4-openssl-dev

RUN cmake .
RUN make
