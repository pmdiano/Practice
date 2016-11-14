# coding=utf8
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', 5500))

if __name__ == '__main__':
    while 1:
        data, addr = sock.recvfrom(1024)
        print('new client from %s:%s' % addr)
        sock.sendto(data, addr)
