__BeLibnids analysing packets use libnids and dpdk__

It is a platform to use multiprocess to combine dpdk and libnids together to support analyse packets in 10G port.

##0.What is ?
  a:It is a platform to use multiprocess to recevie and process packets from one or more ports.
  
  b:It use RSS queue and symmetric hash to Guarantee one tcp stream just be processed by only one process.
  
  c:It use multiprocess to solve the libnids resources Conflict.
  
  d:I work it in CentOS 6.4 and 6.5,you have all codes,of course you can change.
  
  ###Technical Architecture

![architecture](https://github.com/dodng/BeLibnids/blob/master/doc/Technical_Architecture.png)

##1.How to compile ?
  a:compile intel dpdk "http://www.dpdk.org/",you can download or use doc/dpdk-1.5.0r2.tar.gz.
  
  b:cd libnids-1.24/src and compile it until generate a libnids.a
  (I register nids_syslog_return function instead of nids_syslog to improve performance in multiprocess)
  
  c:cd symmetric_mp and make clean;make
  (If you want to learn more,look at 15.1.3 in intel-dpdk-sample-applications-user-guide.pdf)

##2.How to work ?
  cd symmetric_mp and use start.sh
  
  Usage ./start.sh portid lcore_start queue_num
  
  portid:you can use port 0,1... (notice: use start.sh one time just can use only one port)
  lcore_start:you can use cpu 0,1...(the first use cpu id)
  queue_num:use RSS queue numbers for this port(defaultly one queue is just for one cpu or one process)

  Example:
  
 ./start.sh 0 2 8
 
 This command will launch 8 process to receive and process packets from port 0.
 and use cpu 2,3,4,5,6,7,8,9.(The cpu numbers is equal with queue_num)
 The performance in queue numbers or port numbers is in doc/performance.report
 
 ###performance
 ###dns random request ip,every packet len 73 bytes.column:PPS(packets per second)

![performance](https://github.com/dodng/BeLibnids/blob/master/doc/performance.png)

##3.How to begin coding ?

  a: cd pkt_plugin ,you can see sniff.c.It is almost the same with libnids-1.24/samples/sniff.c.
  The 2 files diff is pkt_plugin/sniff.c.diff.
  
  b: you can write you own code to process packets.
  (Defaultly must Follow libnids interface,Of course you also can Abandoned libnids)

-----------------------------------------------------------

author email:dodng12@163.com

welcome to any problems.

If it can help you,I will be very happy.
