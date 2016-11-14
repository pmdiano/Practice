# coding=utf8
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(('', 5500))
sock.send('hello socket world')
print(sock.recv(1024))
