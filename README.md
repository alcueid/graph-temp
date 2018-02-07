# Graph temp

Graph temp is programs that acquires the cpu temperature and outputs it on the graph. It cosists of several script files and C program.

# Environment

Graph temp has confirmed the operation with Ubuntu 16.04 and Raspbian.

## Installing

An example of installation.

Move graph-temp to the appropriate directory and change current directory to it.

Make a log directory in suitable directory.
```
$ mv ~/Downloads/graph-temp ~/graph-temp
$ cd ~/graph-temp
$ mkdir log
```

Install gnuplot, because graph-temp uses it to output to the graph.

```
$ sudo apt update
$ sudo apt -y upgrade
$ sudo apt install gnuplot-x11
```
### Register in crond

Register two lines in crond.

savetemp.sh saves cpu temprature.The argument of savetemp.sh specifies the save destination of the log file. Run savetemp.sh every minute by crond.

save_temp_graph.plt output to the graph using cpu temperature and gnuplot. Run save_temp_graph.plt every day by crond.

```
$ crontab -e
* * * * * sh /home/user/graph-temp/savetemp.sh /home/user/graph-temp/log/
0 0 * * * /usr/bin/gnuplot -e "src='/home/usr/graph-temp/log/$(date +\%F --date "1 day ago")_temp.log'; dst='/home/user/graph-temp/log/$(date +\%F --date "1 day ago")_temp'" /home/usr/graph-temp/save_temp_graph.plt
```
