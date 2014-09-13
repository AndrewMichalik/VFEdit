/* Created file -- JMS */

#include <stdlib.h>
#include "config.h"     /* JMS */
#include "gsm.h"
#include "private.h"
#include "proto.h"

/* (Re-)Init a gsm block */
void gsm_init P1((g), gsm g)
{
	Memset(g, 0, sizeof(*g));
	g->nrp = 40;
}
