---
title: Transfer-X

author:
  name: Prabhakaran Senthilnathan
  info: (@<a href="https://www.linkedin.com/in/prabhakaran9397">Prabhakaran Senthilnathan</a>)
  
summary: Transfer-X, transfer files/folders faster.
---

Transfer-X tool enables you to transfer files/folders from any Laptop with Ubuntu(or any GNU/Linux distro) to any other device on the same network by zipping them and starting a http server.

### Story

*One of my friends bought a new laptop and had to transfer approximately 100 GB data from her old laptop to the new one. Doing this using an 8 gb pendrive was proving to be a tedious task, so I came up with the idea of transferring data from one laptop to another; by taking advantage of the fact that the old laptop had Ubuntu on it and both the laptops are connected to her home network.*

### Steps that I told
1) Connect both the laptops to the Home Wi-Fi network.

2) Find the IP address assigned to the Ubuntu laptop and note it down.

```
ifconfig | awk '/inet addr/{print substr($2,6)}' | tail -1
```
3) Change to the folder to be sent, disable the firewall and start the httpserver

{% highlight Bash %}
cd /media/User/
sudo ufw disable
python -m  SimpleHTTPServer
{% endhighlight %}

*The old laptops IP address when opened in the new laptop's browser provides all the data from the folder to be sent as hyperlinks which she could click to download. `http://<old laptop's ip>:8000`
But a major drawback in this was that the files had to be downloaded one by one and not folder by folder.
This increased the manual work and became inconvenient. In order to make this alright, the first idea which came to my mind was to configure fpt but that turned out to be tedious, because httpserver comes in handy with python!*

Then I thought of zipping each and every file and sending it via the http server, but she still had quite a bit of trouble in finding the the IP address. Thus i ended up automating it by taking advantage of the inherent features of Linux.
Certain important corner cases had to be handled, such as; whether the user is connected to the network, wrong name of file/folder being entered.
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
Tada!!! 
Files were transferred in no time... And I became a hero :P