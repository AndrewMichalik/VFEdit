/*
 * Copyright 1992 by Jutta Degener and Carsten Bormann, Technische
 * Universitaet Berlin.  See the accompanying file "COPYRIGHT" for
 * details.  THERE IS ABSOLUTELY NO WARRANTY FOR THIS SOFTWARE.
 */

static const char     ident[] = "$Header: /home/kbs/jutta/src/gsm/gsm-1.0/src/RCS/gsm_create.c,v 1.1 1992/10/28 00:15:50 jutta Exp $";

#include        "config.h"

#ifdef  HAS_STDLIB_H
#include                <stdlib.h>
#else
#       include "proto.h"
		extern char     * memset P((char *, long, long));
#endif
#include <stdio.h>

#include "gsm.h"
#include "private.h"
#include "proto.h"

gsm gsm_create P0()
{
		gsm  r;

#ifdef  USE_TABLE_MUL

		static long mul_init = 0;
		if (!mul_init) {
				mul_init = 1;
				init_umul_table();
		}

#endif

		r = Malloc(sizeof(struct gsm_state));
		if (!r) return r;

		gsm_init(r);

		return r;
}
