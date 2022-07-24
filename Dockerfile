FROM ubuntu:latest

WORKDIR /sharksshapp

RUN apt update -y
RUN apt install -y openssh-server build-essential cmake

COPY ["cmake", "."]
RUN cmake -S . -B o
RUN cmake --build o

RUN mv /sharksshapp/o/sharkc /
RUN rm -rf /sharksshapp
RUN mv /sharkc /sharksshapp

RUN apt remove -y build-essential cmake

#SETUP USER
RUN useradd -d /home/testuser -m testuser -p testuser
RUN echo 'testuser:testuser' | chpasswd
#RUN echo 'root:3298z9sigaiGWszud8723i' | chpasswd
RUN usermod --shell /sharksshapp/sharkc testuser
#END USER

EXPOSE 22
#start with  ssh -q -o UserKnownHostsFile=/dev/null testuser@localhost
# and type testuser as password

RUN mkdir /run/sshd

RUN service ssh start

CMD ["/usr/sbin/sshd","-D"]
