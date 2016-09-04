---
title: Transfer-X

author:
  name: Prabhakaran Senthilnathan
  info: (@<a href="https://www.linkedin.com/in/prabhakaran9397">Prabhakaran Senthilnathan</a>)
  
summary: Transfer-X, transfer files/folders faster.
---

Transferring files among devices in a same network
In Today's world, the lifespan of electronics devices is quiet short as well as new features keep coming every so often.
It so happened that one of my friends bought a new laptop and had to transfer approximately 100 GB data from her old laptop to the new one. 
Doing this using an 8 gb pendrive was proving to be a tedious task, so i came up with the idea of trnsfrerring data from laptop to another by taking advantage of the fact that the old laptop had linux on it and the laptops are connected to her home network.

One of the prerequisites for accomplishing this was to Stop the firewall 
The server then had to be started 
The old laptops IP address when opened in the new laptop provides all the data in the first laptop as hyperlinks which she could click to download 
But a major drawback in this was that the files had to be downloaded one by one and not folder by folder
This increases manual work and became inconvenient 
In order to make this alright, the first idea which came to my mind was to configure fpt but that turned out to be tedious, because httpserver comes in handy with debian

Then I thought of zipping each and every file and sending it via the http server, but she still had quite a bit of trouble in finding the the IP address. Thus i ended up automating it by taking advantage of the inherent features of Linux
Certain important corner cases had to be handled, such as; whether the user is connected to the network, wrong name of file/folder entered.
Now I'll just give you a quick run through of how to transfer files 
1)Connect the transmitting laptop as well as the receiving  device on the same network (use home wifi or use hotspot from device or connect both with lan)
2) File or Folder to be transferred <file -1 or folder-1> <file-2 or folder-2> ..........
file-1 or folder-1 can have current location or location from root
a) ./file
b) /home/user/file
c) file
d) ~/file
3) Now simply click on the link which is displayed in the browser of the receiving device
4) Inorder to stop the transfer process just make use of the command transfer-x --stop