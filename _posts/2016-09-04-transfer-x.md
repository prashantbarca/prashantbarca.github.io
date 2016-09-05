---
title: Transfer-X

author:
  name: Prabhakaran Senthilnathan
  info: (@<a href="https://www.linkedin.com/in/prabhakaran9397">prabhakaran9397</a>)
  
summary: Transfer-X, transfer files/folders faster.
---

[Transfer-X](https://github.com/lost-plus-found/transfer-x) is a tool that enables one to transfer files/folders from any Laptop with Ubuntu(or any GNU/Linux distro) to any other devices on the same network by zipping them and starting a HTTP server.

### Story Behind This Venture

*One of my friends bought a new laptop and had to transfer approximately 100 GB data from her old laptop to the new one. Doing this using an 8 gb pendrive was proving to be a tedious task, so I came up with the idea of transferring data from one laptop to another; by taking advantage of the fact that the old laptop had Ubuntu on it and both the laptops are connected to her home network.*

### Initial Instructions That Were Executed
1) Connect both the laptops to the Home Wi-Fi network.

2) Find the IP address assigned to the Ubuntu laptop and note it down.

```
$ ifconfig | awk '/inet addr/{print substr($2,6)}' | tail -1
```
3) Change to the folder to be sent, disable the firewall and start the HTTP server

```
$ cd /media/User/
$ sudo ufw disable
$ python -m  SimpleHTTPServer
```

*The old laptops IP address when opened in the new laptop's browser provides all the data from the folder to be sent as hyperlinks which she could click to download. `http://<old laptop's ip>:8000`
But, a major drawback in this was that the files had to be downloaded one by one and not folder by folder.
This increased the manual work and became inconvenient. In order to make the process faster, I racked my brain for better ideas; one of it was to configure FTP but that turned out to be tedious, because HTTP server comes in handy with python!*

### The Golden Idea

*Finally I thought of zipping each and every file and folder to be sent and starting the HTTP server, but she still had quite a bit of trouble in typing the commands. Thus I ended up automating it using Bash. I had some corner cases to be handled, such as:*

* *What if the User mistypes the file/folder name.*
* *If the user forgets to connect to the network.*
* *If the user mistypes the command*

*Finally, I managed to code it and made it open source as well.*

### Using Transfer-X

I'll just give a quick run through of Transfer-X

1) Install [Transfer-X](https://github.com/lost-plus-found/transfer-x)

2) Connect the laptop from which files/folders are to be transferred, as well as the receiving devices to the same network (*use home Wi-Fi or use hotspot from any device or connect with ethernet incase if both are laptops and you have ethernet*)

3) Add the files and folders to be sent

```
$ ls
file1 file2 folder1
$ transfer-x file1 file2 folder1
  adding: transfer-box/ (stored 0%)
  adding: transfer-box/folder1/ (stored 0%)
  adding: transfer-box/file1 (stored 0%)
  adding: transfer-box/file2 (stored 0%)

Hey! Just want to off the firewall till the tranfer is done!
Firewall stopped and disabled on system startup

Hi! The server is running!

 http://192.168.1.3:8000/transfer-box.zip 

** Paste the link in receiver browser **
$ 
```

note: transfer-x supports all file paths
a) `file`
b) `./file`
c) `/home/user/file` 
d) `~/file`


4) After pasting the link in the browser, wait for it to download (*The download speed depends on the home Wi-Fi router or ethernet cable*)

5) After the transfer is done, unzip it and stop the server. 

```
$ transfer-x --stop
```
Hope this article helps you, feel free to share your views, bugs can be reported [here](https://github.com/lost-plus-found/transfer-x/issues)