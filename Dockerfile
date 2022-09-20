FROM ubuntu

WORKDIR /app

RUN apt upgrade
RUN apt update
RUN apt install -y build-essential
RUN apt install -y vim
RUN apt install -y emacs
RUN apt install -y net-tools
RUN apt install -y iputils-ping
RUN yes | unminimize

ENTRYPOINT ["bash"]