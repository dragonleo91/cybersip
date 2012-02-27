/*
 *   Copyright 2012, Kyan He <kyan.ql.he@gmail.com>
 *
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <pjmedia-videodev/videodev_imp.h>
#include <pj/assert.h>
#include <pj/log.h>
#include <pj/os.h>

#define PJMEDIA_VIDEO_HAS_FOOBAR_RENDERER 1
#if defined(PJMEDIA_VIDEO_HAS_FOOBAR_RENDERER) && \
    PJMEDIA_VIDEO_HAS_FOOBAR_RENDERER != 0

#include "foobar_renderer.h"

#define THIS_FILE "foobar_renderer.c"

#define MEMBER(m)


/* Prototypes for factory_op */
static pj_status_t foobar_factory_init(pjmedia_vid_dev_factory *f);
static pj_status_t foobar_factory_destroy(pjmedia_vid_dev_factory *f);
static unsigned foobar_factory_get_dev_count(pjmedia_vid_dev_factory *f);
static pj_status_t foobar_factory_get_dev_info(pjmedia_vid_dev_factory *f,
                        unsigned index, pjmedia_vid_dev_info *info);
static pj_status_t foobar_factory_default_param(pj_pool_t *pool,
                         pjmedia_vid_dev_factory *f, unsigned index,
                         pjmedia_vid_dev_param *param);
static pj_status_t foobar_factory_create_stream(
                    pjmedia_vid_dev_factory *f,
                    pjmedia_vid_dev_param *param,
                    const pjmedia_vid_dev_cb *cb,
                    void *user_data,
                    pjmedia_vid_dev_stream **p_vid_strm);
static pj_status_t foobar_factory_refresh(pjmedia_vid_dev_factory *f);

/* Prototypes for stream_op */
static pj_status_t foobar_stream_get_param(pjmedia_vid_dev_stream *strm,
                    pjmedia_vid_dev_param *param);
static pj_status_t foobar_stream_get_cap(pjmedia_vid_dev_stream *strm,
                      pjmedia_vid_dev_cap cap,
                      void *value);
static pj_status_t foobar_stream_set_cap(pjmedia_vid_dev_stream *strm,
                      pjmedia_vid_dev_cap cap,
                      const void *value);
static pj_status_t foobar_stream_put_frame(pjmedia_vid_dev_stream *strm,
                                        const pjmedia_frame *frame);
static pj_status_t foobar_stream_start(pjmedia_vid_dev_stream *strm);
static pj_status_t foobar_stream_stop(pjmedia_vid_dev_stream *strm);
static pj_status_t foobar_stream_destroy(pjmedia_vid_dev_stream *strm);

/* Factory Operations */
static pjmedia_vid_dev_factory_op foobar_factory_op =
{
    &foobar_factory_init,
    &foobar_factory_destroy,
    &foobar_factory_get_dev_count,
    &foobar_factory_get_dev_info,
    &foobar_factory_default_param,
    &foobar_factory_create_stream,
    &foobar_factory_refresh
};

/* Stream Operations */
static pjmedia_vid_dev_stream_op stream_op =
{
    &foobar_stream_get_param,
    &foobar_stream_get_cap,
    &foobar_stream_set_cap,
    &foobar_stream_start,
    NULL,
    &foobar_stream_put_frame,
    &foobar_stream_stop,
    &foobar_stream_destroy
};

static pjmedia_vid_dev_factory foobar_dev_factory =
{
    MEMBER(sys) { -1 },
    MEMBER(op) &foobar_factory_op,
};

static pjmedia_vid_dev_info foobar_dev_info =
{
    MEMBER(id) -1,
    MEMBER(name) "Foobar Renderer",
    MEMBER(driver) "Foobar Driver",
    MEMBER(dir) PJMEDIA_DIR_RENDER,
    MEMBER(has_callback) PJ_FALSE,
    MEMBER(caps) PJMEDIA_VID_DEV_CAP_FORMAT |
                 PJMEDIA_VID_DEV_CAP_OUTPUT_WINDOW,
    MEMBER(fmt_cnt) 1,
};

typedef struct foobar_dev_factory_data
{
    pj_pool_factory *pool_factory;
} foobar_dev_factory_data;

static foobar_dev_factory_data foobar_factory_data;

static pjmedia_vid_dev_factory* create_foobar_dev_factory(
        pj_pool_factory* pf)
{
    PJ_ASSERT_RETURN(pf, NULL);

    foobar_factory_data.pool_factory = pf;

    return &foobar_dev_factory;
}

PJ_DEF(pj_status_t) pjmedia_vid_dev_foobar_init()
{
    if (foobar_factory_data.pool_factory) {
        // Already init.
        return PJ_EINVAL;
    }

    return pjmedia_vid_register_factory(&create_foobar_dev_factory);
}

static pj_status_t foobar_factory_init(pjmedia_vid_dev_factory *f)
{
    PJ_ASSERT_RETURN(f == &foobar_dev_factory, PJ_EINVAL);

    pjmedia_format_init_video(&foobar_dev_info.fmt[0],
            PJMEDIA_FORMAT_YUY2, 400, 400, 15, 15);

    return PJ_SUCCESS;
}

static pj_status_t foobar_factory_destroy(pjmedia_vid_dev_factory *f)
{
    return PJ_EINVAL;
}

static unsigned foobar_factory_get_dev_count(pjmedia_vid_dev_factory *f)
{
    PJ_ASSERT_RETURN(f == &foobar_dev_factory, PJ_EINVAL);

    return 1;
}

static pj_status_t foobar_factory_get_dev_info(pjmedia_vid_dev_factory *f,
                        unsigned index, pjmedia_vid_dev_info *info)
{
    PJ_ASSERT_RETURN(f == &foobar_dev_factory, PJ_EINVAL);
    PJ_ASSERT_RETURN(index == 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(info, PJ_EINVAL);

    pj_memcpy(info, &foobar_dev_info, sizeof(*info));

    return PJ_SUCCESS;
}

static pj_status_t foobar_factory_default_param(pj_pool_t *pool,
                         pjmedia_vid_dev_factory *f, unsigned index,
                         pjmedia_vid_dev_param *param)
{
}
static pj_status_t foobar_factory_create_stream(
                    pjmedia_vid_dev_factory *f,
                    pjmedia_vid_dev_param *param,
                    const pjmedia_vid_dev_cb *cb,
                    void *user_data,
                    pjmedia_vid_dev_stream **p_vid_strm)
{
}
static pj_status_t foobar_factory_refresh(pjmedia_vid_dev_factory *f)
{
}

/* Prototypes for stream_op */
static pj_status_t foobar_stream_get_param(pjmedia_vid_dev_stream *strm,
                    pjmedia_vid_dev_param *param)
{
}
static pj_status_t foobar_stream_get_cap(pjmedia_vid_dev_stream *strm,
                    pjmedia_vid_dev_cap cap,
                    void *value)
{
}
static pj_status_t foobar_stream_set_cap(pjmedia_vid_dev_stream *strm,
                      pjmedia_vid_dev_cap cap,
                      const void *value)
{
}
static pj_status_t foobar_stream_put_frame(pjmedia_vid_dev_stream *strm,
                                        const pjmedia_frame *frame)
{
}
static pj_status_t foobar_stream_start(pjmedia_vid_dev_stream *strm)
{
}
static pj_status_t foobar_stream_stop(pjmedia_vid_dev_stream *strm)
{
}
static pj_status_t foobar_stream_destroy(pjmedia_vid_dev_stream *strm)
{
}
#endif /* PJMEDIA_VIDEO_HAS_FOOBAR_RENDERER */
