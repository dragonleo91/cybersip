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
#define PJMEDIA_HAS_FOOBAR_CONVERTER 1

#if defined(PJMEDIA_HAS_FOOBAR_CONVERTER) && \
            PJMEDIA_HAS_FOOBAR_CONVERTER != 0

#include <pjmedia/converter.h>
#include <pj/log.h>
#include <pj/errno.h>
#include <pj/assert.h>

#include "foobar_converter.h"

#define THIS_FILE "foobar_converter.c"

#define MEMBER(m)

/* Factory op prototypes */
static pj_status_t foobar_factory_create_converter(
        pjmedia_converter_factory *cf,
        pj_pool_t *pool,
        const pjmedia_conversion_param *prm,
        pjmedia_converter **p_cv);
static void foobar_factory_destroy_factory(pjmedia_converter_factory *cf);

/* Converter op prototypes */
static pj_status_t foobar_converter_convert(pjmedia_converter *converter,
        pjmedia_frame *src_frame,
        pjmedia_frame *dst_frame);
static void foobar_converter_destroy(pjmedia_converter *converter);

static pjmedia_converter_factory_op foobar_converter_factory_op =
{
    MEMBER(create_converter) &foobar_factory_create_converter,
    MEMBER(destroy_factory) &foobar_factory_destroy_factory,
};

static pjmedia_converter_op foobar_converter_op =
{
    MEMBER(convert) &foobar_converter_convert,
    MEMBER(destroy) &foobar_converter_destroy,
};

static pjmedia_converter_factory foobar_converter_factory =
{
    MEMBER(list_prev) NULL,
    MEMBER(list_next) NULL,
    MEMBER(name) "foobar_converter",
    MEMBER(priority) PJMEDIA_CONVERTER_PRIORITY_NORMAL,
    MEMBER(op) &foobar_converter_factory_op,
};

static pjmedia_converter foobar_converter =
{
    MEMBER(op) &foobar_converter_op,
};

PJ_DEF(pj_status_t) pjmedia_vid_converter_foobar_init()
{
    return pjmedia_converter_mgr_register_factory(NULL, 
            &foobar_converter_factory);
}

PJ_DEF(pj_status_t) pjmedia_vid_converter_foobar_deinit()
{
    return pjmedia_converter_mgr_unregister_factory(NULL,
            &foobar_converter_factory, PJ_TRUE);
}

static pj_status_t foobar_factory_create_converter(
        pjmedia_converter_factory *cf,
        pj_pool_t *pool,
        const pjmedia_conversion_param *prm,
        pjmedia_converter **p_cv)
{
    PJ_ASSERT_RETURN(cf == &foobar_converter_factory, PJ_EINVAL);
    PJ_ASSERT_RETURN(prm && p_cv, PJ_EINVAL);

    PJ_UNUSED_ARG(pool);

    // Only support video.
    if (prm->src.type != PJMEDIA_TYPE_VIDEO ||
            prm->dst.type != prm->src.type ||
            prm->src.detail_type != PJMEDIA_FORMAT_DETAIL_VIDEO ||
            prm->dst.detail_type != prm->src.detail_type) {

        return PJ_ENOTSUP;
    }

    // TODO: Record pjmedia_conversion_param.

    *p_cv = &foobar_converter;

    return PJ_SUCCESS;
}

static void foobar_factory_destroy_factory(pjmedia_converter_factory *cf)
{
    PJ_UNUSED_ARG(cf);
}

static pj_status_t foobar_converter_convert(pjmedia_converter *conv,
        pjmedia_frame *src_frame,
        pjmedia_frame *dst_frame)
{
    PJ_ASSERT_RETURN(conv == &foobar_converter, PJ_EINVAL);

    return PJ_SUCCESS;
}

static void foobar_converter_destroy(pjmedia_converter *conv)
{
    PJ_UNUSED_ARG(conv);
}

#endif /* PJMEDIA_HAS_FOOBAR_CONVERTER */
