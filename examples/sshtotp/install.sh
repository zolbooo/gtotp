#!/bin/bash

cd ../../
make

mv libtotp.a examples/sshtotp/
cd examples/sshtotp/

g++ --std=c++11 sshtotp.cpp libtotp.a -o sshtotp -lcrypto
mv sshtotp ~
chmod 100 ~/sshtotp

if [ ! -f ~/.bashrc ]; then
    echo ~/sshtotp >> ~/.profile
else
    echo ~/sshtotp >> ~/.bashrc
fi

if [ ! -d ~/.ssh ]; then
    mkdir ~/.ssh
fi
touch ~/.ssh/id_totp
chmod 600 ~/.ssh/id_totp
