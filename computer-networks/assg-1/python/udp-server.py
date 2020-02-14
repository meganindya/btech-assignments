import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 5050


while True:
	sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) 
	sock.bind((UDP_IP, UDP_PORT))
	data, addr = sock.recvfrom(1024)
	print ("Received message: ", data)
	if(data=="bye"):
		break
	    
