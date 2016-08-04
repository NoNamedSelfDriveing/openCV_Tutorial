import numpy
import cv2 as cv
import socket

if __name__ == '__main__':
    UDP_IP = "127.0.0.1"
    UDP_PORT = 2303

    sock = socket.socket(socket.AF_INET,
            socket.SOCK_DGRAM)

    sock.bind((UDP_IP, UDP_PORT))

    cv.namedWindow('image', cv.WINDOW_NORMAL)

    while True:
        data, addr = sock.recvfrom(1024*65)
        img = cv.imdecode(numpy.frombuffer(data, numpy.uint8), 1 )
        cv.imshow('image', img)
        cv.waitKey(1)
