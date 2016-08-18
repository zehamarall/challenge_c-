FROM ubuntu:xenial 
MAINTAINER Leandro Amaral <zehamarall@gmail.com> 
ENV DEBIAN_FRONTEND noninteractive 
RUN apt-get -qq update \
&& apt-get upgrade \
&& apt-get -qqy install \
    build-essential \
    libboost-all-dev \
    g++ \
    vim \
&& rm -rf /var/lib/apt/lists/*


EXPOSE  5000
CMD ["/code/stream_server" "5000" "150"]
#ENTRYPOINT /bin/bash
