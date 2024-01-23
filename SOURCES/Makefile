CC=gcc
CFLAGS= -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -lglib-2.0
topmdt_EXEC=topmdt
topmdt: parse_arg.o li_stat.o initialize_mds.o compte_nid.o rempli_structure.o affiche_mds.o compte_mdt.o topmdt.o
	$(CC) $(CFLAGS) -o $(topmdt_EXEC) parse_arg.o li_stat.o initialize_mds.o compte_nid.o rempli_structure.o affiche_mds.o compte_mdt.o topmdt.o
