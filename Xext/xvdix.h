/***********************************************************
Copyright 1991 by Digital Equipment Corporation, Maynard, Massachusetts,
and the Massachusetts Institute of Technology, Cambridge, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the names of Digital or MIT not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/

#ifndef XVDIX_H
#define XVDIX_H
/*
** File:
**
**   xvdix.h --- Xv device independent header file
**
** Author:
**
**   David Carver (Digital Workstation Engineering/Project Athena)
**
** Revisions:
**
**   29.08.91 Carver
**     - removed UnrealizeWindow wrapper unrealizing windows no longer
**       preempts video
**
**   11.06.91 Carver
**     - changed SetPortControl to SetPortAttribute
**     - changed GetPortControl to GetPortAttribute
**     - changed QueryBestSize
**
**   15.05.91 Carver
**     - version 2.0 upgrade
**
**   24.01.91 Carver
**     - version 1.4 upgrade
**
*/

#include "scrnintstr.h"
#include <X11/extensions/Xvproto.h>

typedef struct {
    int numerator;
    int denominator;
} XvRationalRec, *XvRationalPtr;

typedef struct {
    char depth;
    unsigned long visual;
} XvFormatRec, *XvFormatPtr;

typedef struct {
    unsigned long id;
    ClientPtr client;
} XvGrabRec, *XvGrabPtr;

typedef struct _XvPortNotifyRec *XvPortNotifyPtr;

typedef struct {
    int id;
    ScreenPtr pScreen;
    char *name;
    unsigned short width, height;
    XvRationalRec rate;
} XvEncodingRec, *XvEncodingPtr;

typedef struct _XvAttributeRec {
    int flags;
    int min_value;
    int max_value;
    char *name;
} XvAttributeRec, *XvAttributePtr;

typedef struct {
    int id;
    int type;
    int byte_order;
    char guid[16];
    int bits_per_pixel;
    int format;
    int num_planes;

    /* for RGB formats only */
    int depth;
    unsigned int red_mask;
    unsigned int green_mask;
    unsigned int blue_mask;

    /* for YUV formats only */
    unsigned int y_sample_bits;
    unsigned int u_sample_bits;
    unsigned int v_sample_bits;
    unsigned int horz_y_period;
    unsigned int horz_u_period;
    unsigned int horz_v_period;
    unsigned int vert_y_period;
    unsigned int vert_u_period;
    unsigned int vert_v_period;
    char component_order[32];
    int scanline_order;
} XvImageRec, *XvImagePtr;

typedef struct {
    unsigned long base_id;
    unsigned char type;
    char *name;
    int nEncodings;
    XvEncodingPtr pEncodings;
    int nFormats;
    XvFormatPtr pFormats;
    int nAttributes;
    XvAttributePtr pAttributes;
    int nImages;
    XvImagePtr pImages;
    int nPorts;
    struct _XvPortRec *pPorts;
    ScreenPtr pScreen;
    int (*ddPutVideo) (DrawablePtr, struct _XvPortRec *, GCPtr,
                       INT16, INT16, CARD16, CARD16,
                       INT16, INT16, CARD16, CARD16);
    int (*ddPutStill) (DrawablePtr, struct _XvPortRec *, GCPtr,
                       INT16, INT16, CARD16, CARD16,
                       INT16, INT16, CARD16, CARD16);
    int (*ddGetVideo) (DrawablePtr, struct _XvPortRec *, GCPtr,
                       INT16, INT16, CARD16, CARD16,
                       INT16, INT16, CARD16, CARD16);
    int (*ddGetStill) (DrawablePtr, struct _XvPortRec *, GCPtr,
                       INT16, INT16, CARD16, CARD16,
                       INT16, INT16, CARD16, CARD16);
    int (*ddStopVideo) (struct _XvPortRec *, DrawablePtr);
    int (*ddSetPortAttribute) (struct _XvPortRec *, Atom, INT32);
    int (*ddGetPortAttribute) (struct _XvPortRec *, Atom, INT32 *);
    int (*ddQueryBestSize) (struct _XvPortRec *, CARD8,
                            CARD16, CARD16, CARD16, CARD16,
                            unsigned int *, unsigned int *);
    int (*ddPutImage) (DrawablePtr, struct _XvPortRec *, GCPtr,
                       INT16, INT16, CARD16, CARD16,
                       INT16, INT16, CARD16, CARD16,
                       XvImagePtr, unsigned char *, Bool, CARD16, CARD16);
    int (*ddQueryImageAttributes) (struct _XvPortRec *, XvImagePtr,
                                   CARD16 *, CARD16 *, int *, int *);
    DevUnion devPriv;
} XvAdaptorRec, *XvAdaptorPtr;

typedef struct _XvPortRec {
    unsigned long id;
    XvAdaptorPtr pAdaptor;
    XvPortNotifyPtr pNotify;
    DrawablePtr pDraw;
    ClientPtr client;
    XvGrabRec grab;
    TimeStamp time;
    DevUnion devPriv;
} XvPortRec, *XvPortPtr;

typedef struct {
    int version, revision;
    int nAdaptors;
    XvAdaptorPtr pAdaptors;
    void *_dummy1; // required in place of a removed field for ABI compatibility
    void *_dummy2; // required in place of a removed field for ABI compatibility
    void *_dummy3; // required in place of a removed field for ABI compatibility
} XvScreenRec, *XvScreenPtr;

extern _X_EXPORT int XvScreenInit(ScreenPtr);
extern _X_EXPORT DevPrivateKey XvGetScreenKey(void);
extern _X_EXPORT unsigned long XvGetRTPort(void);

#endif                          /* XVDIX_H */
