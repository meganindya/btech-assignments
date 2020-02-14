import socket
    
UDP_IP = "127.0.0.1"
UDP_PORT = 5050
while True:
	data =str( input("Message to be sent to server: ") )
	#print("UDP target IP:", UDP_IP)
	#print ("UDP target port:", UDP_PORT)
	print ("Message: ", data) 

	sock = socket.socket(socket.AF_INET, # Internet
		               socket.SOCK_DGRAM) # UDP

	sock.sendto(data, (UDP_IP, UDP_PORT))
	if(data=="bye"):
		break
		
