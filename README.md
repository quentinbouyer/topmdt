## topmdt
topmdt display top clients by open file, get attributes and unlink requests<br>
It parse /proc/fs/lustre .... and read stats 2 times , calculate the bandwith used by each client, sort the client by usage<br>
and print them.<br>
Example :
<pre>
# ./topmdt -h
Usage : topmdt
sans argument   : affiche les 10 clients les plus consommateurs
-n X            : limite l'affichage pour X client au max (10 par defaut)
-h              : pour afficher ce message d'aide
-v              : pour afficher la version
  
# ./topmdt -v
topmdt version 2.1
quentin.bouyer@gmail.com

# rpm -qp --changelog topmdt-2.1-0.el7.x86_64.rpm
* Tue Jan 16 2024 quentin.bouyer@gmail.com 2.1
- count unlink

* Fri Jan 12 2024 quentin.bouyer@gmail.com 2.0
- no need topost.conf
</pre>
Display nothing if no activities on MDS<br>
<pre>
# ./topmdt
1 mdt
9 clients
First read
Wait 10s before to read a second time
Second read

Load : 0.00 0.01 0.05

</pre>
