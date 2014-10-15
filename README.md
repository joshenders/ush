ush
=====

A friend asked if there was a way for him to let his friends use his linux 
server as a SOCKS proxy without giving them full access to the machine. I've 
wanted to do something like this for role accounts in the past so it stoked my 
curiosity. I immediately thought of [rbash](http://www.gnu.org/software/bash/manual/html_node/The-Restricted-Shell.html)
but the world is a dangerous place. The less access the better.

The simplest way I thought of doing this was by replacing the user's login 
shell with a program with no functionality. Thus, useless shell was born.

Building
========

Build with gcc

    gcc -o ush ush.c

Copy somewhere

    cp ush /some/where/

Append path to `/etc/shells`

    echo '/some/where/ush' >> /etc/shells

Change user's shell

    usermod --shell /some/where/ush username

Disclaimer
==========

~~I imagine there's some ssh client configuration that could be used to 
circumvent this. This is just a study, don't trust this to offer you any kind 
of security.~~

**Update:** In fact there is! Either via the `PermitTunnel` or `X11Forwarding`,
users without a "working" shell can still create an L2 tunnel or (unconfirmed)
potentially launch X11 applications not to mention forwarding of arbitrary
ports.

This was a fun project but a more practical implementation would be to set the
restricted user's shell to `/bin/false` or `/bin/nologin` and then set a `Match`
directive in your `sshd_config` for the user or group you wish to restrict.

```
Match User foo
    AllowTcpForwarding yes
    X11Forwarding no
    PermitTunnel no
```

Prepend the following to the user's `authorized_keys` file to ensure they can
only forward what is explicitly allowable.

```
command="/bin/false",no-agent-forwarding,no-pty,no-usr-rc,no-X11-forwarding,permitopen="127.0.0.1:8080" KEY_TYPE KEY COMMENT
```

While you're at it, I would suggest changing the location of where users'
`authorized_file`s are stored to a location only root can write to. This means
a user is forced to contact root in order to update their key. This gives root
the opportunity to revoke the key (set the location of `RevokedKeys` in your
`sshd_config`) and ask if the user is storing their key encrypted.

```
AuthorizedKeysFile /etc/ssh/authorized_keys/%u.pub
```

The user would then use the `-N` flag to ssh to their ssh client to connect.

```
     -N      Do not execute a remote command.  This is useful for just forwarding ports (protocol version 2 only).
```

You may also want to enable/disable ssh keep-alive support depending on your
network policies. Review the following directives in your `sshd_config` and
your clients' `~/.ssh/config`

```
    ClientAliveInterval
    ClientAliveCountMax
    TCPKeepAlive
```
