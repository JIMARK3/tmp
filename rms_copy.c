/*
                RECORD OPERATIONS

        This program looks up records by key and then

           *  copies the record to an output file,
           *  deletes the record, or
           *  updates the record
*/

#include        <rms>        /* defines for rabs and fabs */
#include        <stdio>      /* defins printf... */
#include        <string>     /* defines strlen */
#include        <stdlib>     /* defines exit */
#include        <starlet>    /* defines sys$open et al */

#define INPUT_NAME      "INFILE:"
#define OUTPUT_NAME     "OUTFILE:"
#define RECORD_SIZE     132
#define TYPING_SIZE     100

struct  FAB     infab, outfab;
struct  RAB     inrab, outrab;

error_exit (code, value)
long    code;
long    value;
{
        void lib$signal();
        lib$signal (code, value);
        exit (0);
}
main ()
{
     char    record [RECORD_SIZE];           /* record buffer */
     char    key [RECORD_SIZE];              /* key buffer */
     char    choice [TYPING_SIZE];           /* typing buffer */
     long    status;

     /* set up input fab */
     infab = cc$rms_fab;
     infab.fab$b_fac = FAB$M_GET | FAB$M_PUT | FAB$M_UPD | FAB$M_DEL;
     infab.fab$b_shr = FAB$M_SHRGET | FAB$M_SHRPUT | FAB$M_SHRUPD
                       | FAB$M_SHRDEL;       /* read/write sharing */
     infab.fab$l_fna = (char *) &INPUT_NAME; /* logical name INFILE */
     infab.fab$b_fns = sizeof INPUT_NAME - 1;

     /* set up output fab */
     outfab = cc$rms_fab;
     outfab.fab$b_fac = FAB$M_PUT;
     outfab.fab$l_fna = (char *) &OUTPUT_NAME; /* logical name OUTFILE */
     outfab.fab$b_fns = sizeof OUTPUT_NAME - 1;
     outfab.fab$w_mrs = RECORD_SIZE;      /* record size */
     outfab.fab$b_org = FAB$C_REL;        /* relative file */
     outfab.fab$b_rat = FAB$M_CR;         /* implied carriage return */

     /* set up input rab */
     inrab = cc$rms_rab;
     inrab.rab$l_fab = &infab;
     inrab.rab$b_rac = RAB$C_KEY;          /* key access */
     inrab.rab$b_krf = 0;                  /* access by primary key */
     inrab.rab$l_kbf = key;                /* key buffer */
     inrab.rab$l_ubf = record;             /* record buffer */
     inrab.rab$w_usz = RECORD_SIZE;        /* maximum record size */

     /* set up output rab */
     outrab = cc$rms_rab;
     outrab.rab$l_fab = &outfab;
     outrab.rab$l_rbf = record;             /* record buffer */

     /* open files and connect streams */
     status = sys$open (&infab);
     if (! (status & 1))
             error_exit (status, infab.fab$l_stv);
     status = sys$connect (&inrab);
     if (! (status & 1))
             error_exit (status, inrab.rab$l_stv);
     status = sys$create (&outfab);
     if (! (status & 1))
             error_exit (status, outfab.fab$l_stv);
     status = sys$connect (&outrab);
     if (! (status & 1))
             error_exit (status, outrab.rab$l_stv);

     while (1)
     {
             /* get a key and a record */
             printf ("Please input key value: ");
             gets (key);                     /* get key from user */
             if (feof (stdin))               /* stop on ctrl-Z */
                     break;
             inrab.rab$b_ksz = strlen (key); /* set key length */
             status = sys$get (&inrab);
             if (! (status & 1))
                     error_exit (status, inrab.rab$l_stv);

             /* display the record */
             record[inrab.rab$w_rsz] = '\0';
             printf ("Record: {%s}\n", record);

             /* choose what to do */
             printf ("Please choose C(opy), D(elete), or U(pdate):");
             gets (choice);                  /* get choice from user */
             if (feof (stdin))               /* stop on ctrl-Z */
                     break;
             switch (choice[0])
             {
                     case 'c':
                     case 'C':
                             /* copy the record */
                             outrab.rab$w_rsz = inrab.rab$w_rsz;
                                          /* out length = in length */
                             status = sys$put (&outrab);
                             if (! (status & 1))
                                     error_exit (status, outrab.rab$l_stv);
                             break;
                     case 'd':
                     case 'D':
                             /* delete */
                             status = sys$delete (&inrab);
                             if (! (status & 1))
                                     error_exit (status, inrab.rab$l_stv);
                             break;
                     case 'u':
                     case 'U':
                             /* get a new record */
                             printf ("Please input record value: ");
                             gets (record);  /* get record from user */
                             inrab.rab$w_rsz = strlen (record);
                                             /* set record length */
                             status = sys$update (&inrab);
                             if (! (status & 1))
                                     error_exit (status, inrab.rab$l_stv);
                             break;
                     default:
                             /* do nothing */
                             break;
             }
     }

     /* close files */
     status = sys$close (&infab);
     if (! (status & 1))
             error_exit (status, infab.fab$l_stv);
     status = sys$close (&outfab);
     if (! (status & 1))
             error_exit (status, outfab.fab$l_stv);
}