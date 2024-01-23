## topmdt
topmdt display client for all mdt on a lustre mds and sort them by open file and get attribute requests<br>
It parse /proc/fs/lustre .... and read stats 2 times , calculate the bandwith used by each client, sort the client by usage<br>
and print them.<br>
It has been tested on lustre 2.7 with redhat 7.4<br>
It use /etc/topmdt.conf to convert nid to hostname.<br>
/etc/topmdt.conf must contain each lustre client and begin with word client.<br>
Example :
<pre>
[root@oss0 ~]# cat /etc/topmdt.conf
client=client1,123.45.31.2@o2ib1
client=client2,123.45.31.3@o2ib1
</pre>

output example :
<pre>
[root@mds1 ~]# topmdt
10 clients max to display
1 mdt
97 clients in /etc/topmdt.conf
First read
Wait 10s before to read a second time
Second read
--------------------------------------------------------------------------
Open
MDT             CLIENT  NB OPEN FILE
--------------------------------------------------------------------------
lustrefs-MDT0000 client113        20
lustrefs-MDT0000 client109        20
lustrefs-MDT0000  client73        18
lustrefs-MDT0000  client91        18
lustrefs-MDT0000 client112        11
lustrefs-MDT0000 client107        11
lustrefs-MDT0000  client71        10
lustrefs-MDT0000  client63        10
lustrefs-MDT0000  client49        10
lustrefs-MDT0000 client111        7
--------------------------------------------------------------------------
Get attribute
MDT             CLIENT  NB GET ATTRIBUTE
--------------------------------------------------------------------------
lustrefs-MDT0000 clientlogin1     16
lustrefs-MDT0000 client109        15
lustrefs-MDT0000  client63        15
lustrefs-MDT0000  client49        15
lustrefs-MDT0000  client71        14
lustrefs-MDT0000 client113        13
lustrefs-MDT0000 client101        8
lustrefs-MDT0000   client2        6
lustrefs-MDT0000  client58        5
lustrefs-MDT0000 client111        3

Load : 0.00 0.01 0.05
</pre>
