# coding=utf8
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', 5500))
sock.listen(5)

def handler(client_dock, addr):
    print('new client from %s:%s' % addr)
    msg = client_sock.recv(1024)
    client_sock.send(msg)
    client_sock.close()
    print('client[%s:%s] socket closed' % addr)

if __name__ == '__main__':
    while 1:
        client_sock, addr = sock.accept()
        handler(client_sock, addr)
