# Vowelizer

Learned about client-server network applications, UDP and TCP data transfer protocols.
This application splits and merges texts given as input. Incoming text like "Hello there!" is split into two parts "H ll  th r !" sent to server using TCP, and the second part " e o e e " sent using UDP, this is recieved on the server end and merged together to form the final message "Hello there!" and sent back to the client using TCP. The focus of this application is to handle the inconsistencies of using UDP to transfer data from server to client since it is unreliable and does not always transmit data, this was handled by requesting the data multiple times on either side if 0 bytes were recieved from the recvfrom() calls.
