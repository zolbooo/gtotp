#!/usr/bin/env bash

cd ../../
make

mv libtotp.a examples/sshtotp/
cd examples/sshtotp/

g++ --std=c++11 sshtotp.cpp libtotp.a -o sshtotp -lcrypto
mv sshtotp ~
chmod 100 ~/sshtotp

if [ "$USER" == "root" ]
    if [ "$(uname)" == "Darwin" ]
        dscl localhost -change /Local/Default/Users/$USER UserShell $SHELL ~/sshtotp
    else
        usermod --shell ~/sshtotp $USER
    fi
else
    if [ "$(uname)" == "Darwin" ]
        sudo dscl localhost -change /Local/Default/Users/$USER UserShell $SHELL ~/sshtotp
    else
        sudo usermod --shell ~/sshtotp $USER
    fi
fi

if [ ! -d ~/.ssh ]; then
    mkdir ~/.ssh
fi
touch ~/.ssh/id_totp
chmod 600 ~/.ssh/id_totp
