#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <limits.h>
#include "resources.h"
#include "object.h"

typedef struct xf_object
{
  int code;
  void *point;
  struct xf_object *next;
} Xfig_object;

Xfig_object *head;
Xfig_object *current;
Xfig_object *traverse;

void xf_objlist_init(void)
{
  head=current=NULL;
}

void xf_objlist_add(int code, void *point)
{
  if (head==NULL)
    {
      /* First object */
      current=(Xfig_object *)malloc(sizeof(Xfig_object));
      current->code=code;
      current->point=point;
      current->next=NULL;
      head=current;
    }
  else
    {
      current->next=(Xfig_object *)malloc(sizeof(Xfig_object));
      current->next->code=code;
      current->next->point=point;
      current->next->next=NULL;
      current=current->next;
    }
}

void xf_addarc(F_arc *arcpoint)
{
  xf_objlist_add(O_ARC, (void *)arcpoint);
}

void xf_addellipse(F_ellipse *elpoint)
{
  xf_objlist_add(O_ELLIPSE, (void *)elpoint);
}

void xf_addpolyline(F_line *lipoint)
{
  xf_objlist_add(O_POLYLINE, (void *)lipoint);
}

void xf_addspline(F_spline *sppoint)
{
  xf_objlist_add(O_SPLINE, (void *)sppoint);
}

void xf_objlist_tofile(FILE *fl)
{
  Xfig_object *trv;

  trv=head;

  while(trv!=NULL)
    {
      switch(trv->code)
	{
	case O_ELLIPSE:
	  xf_write_ellipse(fl, (F_ellipse *)(trv->point));
	  break;
	case O_POLYLINE:
	  xf_write_polyline(fl, (F_line *)(trv->point));
	  break;
	case O_ARC:
	  xf_write_arc(fl, (F_arc *)(trv->point));
	  break;
	case O_SPLINE:
	  xf_write_spline(fl, (F_spline *)(trv->point));
	  break;
	default:
	  fprintf(stderr," unhandled type %d\n", trv->code);
	  break;
	}
      trv=trv->next;
      }
}

