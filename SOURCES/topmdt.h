typedef struct
{
 char mdt_name[32];
 char path[256];
 char addip[256];
 char nomhost[16];
 long openf;
 long getattrf;
 long opf;
 long getf;
} io_mds;

typedef struct
{
 char nomcli[16];
 char ipcli[32];
} clitemp;
