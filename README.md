clrsh
=====

A friend asked if there was a way for him to let his friends use his linux 
server as a SOCKS proxy without giving them full access to the machine. I've 
wanted to do something like this for role accounts in the past so it stoked my 
curiosity. I immediately thought of [rbash](http://www.gnu.org/software/bash/manual/html_node/The-Restricted-Shell.html)
but the world is a dangerous place. The less access the better.

The simplest way I thought of doing this was by replacing the user's login 
shell with a program with no functionality.

Building
========

Build with gcc

    gcc -o clrsh clrsh.c

Copy somewhere

    cp clrsh /some/where/

Append path to `/etc/shells`

    echo '/some/where/clrsh' >> /etc/shells

Change user's shell

    usermod --shell /some/where/clrsh username

Disclaimer
==========

I imagine there's some ssh client configuration that could be used to 
circumvent this. This is just a study, don't trust this to offer you any kind 
of security.
