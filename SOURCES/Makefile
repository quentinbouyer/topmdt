CC=gcc
CFLAGS= -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -lglib-2.0
topmdt_EXEC=topmdt
topmdt: traite_arg.o li_stat.o initialize_mds.o read_conf_file.o affiche_mds.o compte_mdt.o topmdt.o
	$(CC) $(CFLAGS) -o $(topmdt_EXEC) traite_arg.o li_stat.o initialize_mds.o read_conf_file.o affiche_mds.o compte_mdt.o topmdt.o
