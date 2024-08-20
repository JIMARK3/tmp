/* Process ORION */

#include <descrip.h>
#include <iodef.h>
#include <lib$routines.h>
#include <ssdef.h>
#include <starlet.h>
#include <stdio.h>
#define MBXBUFSIZ 128
#define MBXBUFQUO 384

/* I/O status block */
struct {
                unsigned short iostat, iolen;
                unsigned int remainder;
}mbxiosb;


main() {
        void *p1, mbxast();
        char mbuffer[MBXBUFSIZ], prmflg=0;
        unsigned short mbxchan, mbxiosb;
        unsigned int status, outlen;
        unsigned int mbuflen=MBXBUFSIZ, bufquo=MBXBUFQUO, promsk=0;
        $DESCRIPTOR(mblognam,"GROUP100_MAILBOX");

/* Create a mailbox */
        status = SYS$CREMBX( prmflg,      /* Permanent or temporary */  1
                             &mbxchan,    /* chan - channel number */
                             mbuflen,     /* maxmsg - buffer length */
                             bufquo,      /* bufquo - quota */
                             promsk,      /* promsk - protection mask */
                             0,           /* acmode - access mode */
                             &mblognam,   /* lognam - mailbox logical name */
                             0);          /* flags -  options */
        if (!$VMS_STATUS_SUCCESS(status))
                LIB$SIGNAL(status);
   .
   .
   .
/* Request I/O */
        status = SYS$QIO(0,               /* efn - event flag */   2
                          mbxchan,        /* chan - channel number */
                          IO$_READVBLK,   /* func - function modifier */
                          &mbxiosb,       /* iosb - I/O status block */
                          &mbxast,        /* astadr - AST routine */
                          &mbuffer,       /* p1 - output buffer */
                          mbuflen);       /* p2 - length of buffer */
        if (!$VMS_STATUS_SUCCESS(status))
                LIB$SIGNAL(status);
   .
   .
   .

}

void mbxast(void) {                                                             3

        if (mbxiosb.iostat != SS$_NORMAL)

        status = SYS$QIOW(..., &mbuffer, &outlen,...)
        if (!$VMS_STATUS_SUCCESS(status))
                LIB$SIGNAL(status);

        return;
}


/* Process Cygnus */

#include <descrip.h>
#include <iodef.h>
#include <lib$routines.h>
#include <ssdef.h>
#include <starlet.h>
#include <stdio.h>
#include <stsdef.h>
#define MBXBUFSIZ 128

main() {

        unsigned short int mailchan;
        unsigned int status, outlen;
        char outbuf[MBXBUFSIZ];
        $DESCRIPTOR(mailbox,"GROUP100_MAILBOX");

        status = SYS$ASSIGN(&mailbox, &mailchan, 0, 0, 0);  4
        if (!$VMS_STATUS_SUCCESS(status))
                LIB$SIGNAL(status);
   .
   .
   .

        status = SYS$QIOW(0, mailchan, 0, 0, 0, 0, &outbuf, outlen, 0, 0, 0, 0)
        if (!$VMS_STATUS_SUCCESS(status))
                LIB$SIGNAL(status);
   .
   .
   .

}