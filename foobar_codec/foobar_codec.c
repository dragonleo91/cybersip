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

#define PJMEDIA_HAS_foobar_CODEC 1

#include <pj/assert.h>
#include <pj/log.h>
#include <pj/string.h>
#include <pj/pool.h>
#include <pj/os.h>

#include <pjmedia/format.h>
#include <pjmedia/errno.h>

#if defined(PJMEDIA_HAS_foobar_CODEC) && PJMEDIA_HAS_foobar_CODEC != 0 && \
    defined(PJMEDIA_HAS_VIDEO) && (PJMEDIA_HAS_VIDEO != 0)

#include "foobar_codec.h"

#define THIS_FILE   "foobar_codec.c"

/* Trace the method invoked, for debugging only */
#if __gcc__
#define TRACE_FUNC() PJ_LOG(3,(THIS_FILE, __func__))
#else
#define TRACE_FUNC() 
#endif

/* Prototypes for foobar codecs factory */
static pj_status_t foobar_test_alloc(pjmedia_vid_codec_factory *factory,
        const pjmedia_vid_codec_info *id);

static pj_status_t foobar_default_attr(pjmedia_vid_codec_factory *factory,
        const pjmedia_vid_codec_info *info,
        pjmedia_vid_codec_param *attr);

static pj_status_t foobar_enum_info(pjmedia_vid_codec_factory *factory,
        unsigned *count,
        pjmedia_vid_codec_info codecs[]);

static pj_status_t foobar_alloc_codec(pjmedia_vid_codec_factory *factory,
        const pjmedia_vid_codec_info *info,
        pjmedia_vid_codec **p_codec);

static pj_status_t foobar_dealloc_codec(pjmedia_vid_codec_factory *factory,
        pjmedia_vid_codec *codec);


/* Prototypes for foobar codecs implementation. */


static pj_status_t foobar_codec_init(pjmedia_vid_codec *codec,
        pj_pool_t *pool);

static pj_status_t foobar_codec_open(pjmedia_vid_codec *codec,
        pjmedia_vid_codec_param *attr);

static pj_status_t foobar_codec_close(pjmedia_vid_codec *codec);

static pj_status_t foobar_codec_modify(pjmedia_vid_codec *codec,
        const pjmedia_vid_codec_param *attr);

static pj_status_t foobar_codec_get_param(pjmedia_vid_codec *codec,
        pjmedia_vid_codec_param *param);

static pj_status_t foobar_codec_encode_begin(pjmedia_vid_codec *codec,
        const pjmedia_vid_encode_opt *opt,
        const pjmedia_frame *input, unsigned out_size,
        pjmedia_frame *output, pj_bool_t *has_more);

static pj_status_t foobar_codec_encode_more(pjmedia_vid_codec *codec,
        unsigned out_size, pjmedia_frame *output, pj_bool_t *has_more);

static pj_status_t foobar_codec_decode(pjmedia_vid_codec *codec,
        pj_size_t pkt_count, pjmedia_frame packets[],
        unsigned out_size, pjmedia_frame *output);


/*
 * Definition for foobar codec operations.
 * No modify() and recover() support.
 */
static pjmedia_vid_codec_op foobar_codec_op =
{
    &foobar_codec_init,
    &foobar_codec_open,
    &foobar_codec_close,
    NULL,
    &foobar_codec_get_param,
    &foobar_codec_encode_begin,
    &foobar_codec_encode_more,
    &foobar_codec_decode,
    NULL
};

/* Definition for foobar codecs factory operations. */
static pjmedia_vid_codec_factory_op foobar_codec_factory_op =
{
    &foobar_test_alloc,
    &foobar_default_attr,
    &foobar_enum_info,
    &foobar_alloc_codec,
    &foobar_dealloc_codec
};

/* foobar factory data */
typedef struct foobar_factory_data
{
    pj_pool_factory *pool_factory;
    pj_pool_t *pool;
}
foobar_factory_data;

/* foobar codec data */
typedef struct foobar_codec_data
{
    pj_pool_t *pool;
}
foobar_codec_data;

/* Definition for foobar codecs factory. */
static pjmedia_vid_codec_factory foobar_codec_factory;

/* Definition for simple pool factory. */
static pj_caching_pool caching_pool;

/* Definition for foobar codec format ID */
#define PJMEDIA_FORMAT_foobar_ARRAY  \
            PJMEDIA_FORMAT_PACK('A', 'R' ,'A', 'Y')

/**
 * Definition for foobar codec RTP Payload Type.
 *
 * PJMEDIA_RTP_PT_DYNAMIC is defined in <pjmedia/codec.h>. It is defined
 * to be 96.
 *
 * @see pjmedia/codec.h
 * @see pjmedia-codec/types.h
 */
//enum pjmedia_video_pt PJMEDIA_RTP_PT_foobar = PJMEDIA_RTP_PT_DYNAMIC;
#define PJMEDIA_RTP_PT_foobar   PJMEDIA_RTP_PT_DYNAMIC

/* Definition for foobar codec info, need C99 */
#if __STDC_VERSION__ >= 199901L
static struct pjmedia_vid_codec_info foobar_codec_info =
{
    .fmt_id = PJMEDIA_FORMAT_foobar_ARRAY,
    .pt = PJMEDIA_RTP_PT_foobar,
    .encoding_name = {"foobar", 6},
    .encoding_desc = {"Private Demo Codec, v1", 21},
    .clock_rate = 0,
    .dir = PJMEDIA_DIR_ENCODING | PJMEDIA_DIR_DECODING,
    // TODO: support PJMEDIA_FORMAT_RGB24 & PJMEDIA_FORMAT_foobar_GL
    // lesser than PJMEDIA_VID_CODEC_MAX_DEC_FMT_CNT=8
    .dec_fmt_id_cnt = 1,
    .dec_fmt_id[0] = PJMEDIA_FORMAT_RGB24,
    /* No RTP segements required,
     * the encoded data is even smaller than audio */
    .packings = PJMEDIA_VID_PACKING_PACKETS,
    // TODO: what fps use.
    // lesser than PJMEDIA_VID_CODEC_MAX_FPS_CNT=16
    .fps_cnt = 1,
    .fps[0] = 15,
}
#else
static struct pjmedia_vid_codec_info foobar_codec_info =
{
    /* .fmt_id = */PJMEDIA_FORMAT_foobar_ARRAY,
    /* .pt = */PJMEDIA_RTP_PT_foobar,
    /* .encoding_name = */{"foobar", 6},
    /* .encoding_desc = */{"Private Demo Codec, v1", 21},
    /* .clock_rate = */0,
    /* .dir = */PJMEDIA_DIR_ENCODING | PJMEDIA_DIR_DECODING,
    // TODO: support PJMEDIA_FORMAT_RGB24 & PJMEDIA_FORMAT_foobar_GL
    // lesser than PJMEDIA_VID_CODEC_MAX_DEC_FMT_CNT=8
    /* .dec_fmt_id_cnt = */1,
    /* .dec_fmt_id[0] = */{ PJMEDIA_FORMAT_YUY2, },
    /* No RTP segements required,
     * the encoded data is even smaller than audio */
    /* .packings = */PJMEDIA_VID_PACKING_PACKETS,
    // TODO: what fps use.
    // lesser than PJMEDIA_VID_CODEC_MAX_FPS_CNT=16
    /* .fps_cnt = */1,
    /* .fps[0] = */{15, },
};
#endif

/**
 * Initialize and register foobar codec factory to pjmedia endpoint.
 *
 * There is no deinit().
 */
PJ_DEF(pj_status_t) pjmedia_vid_codec_foobar_init()
{
    pjmedia_vid_codec_mgr *mgr;
    pj_pool_t *pool;
    pj_status_t status;
    foobar_factory_data *afd;

    // Get Codec Manager instance.
    mgr = pjmedia_vid_codec_mgr_instance();
    PJ_ASSERT_RETURN(mgr, PJ_EINVAL);

    afd = (foobar_factory_data *) foobar_codec_factory.factory_data;
    if (afd) {
        // Already initialized.
        return PJ_SUCCESS;
    }

    // Init caching pool and create a pool
    pj_caching_pool_init(&caching_pool,
            &pj_pool_factory_default_policy, 0);
    pool = pj_pool_create(&caching_pool.factory,
                "foobar codec factory", 256, 256, NULL);
    PJ_ASSERT_RETURN(pool, PJ_ENOMEM);

    // Allocate factory data.
    afd = PJ_POOL_ALLOC_T(pool, foobar_factory_data);
    if (!afd) {
        status = PJ_ENOMEM;
        goto on_error;
    }

    // Setup factory data.
    afd->pool_factory = &caching_pool.factory;
    afd->pool = pool;

    // TODO: OpenGL initializing.
    // TODO: cvfoobar codec init.

    // Setup factory data, ensure return PJ_SUCCESS.
    foobar_codec_factory.factory_data = afd;
    foobar_codec_factory.op = &foobar_codec_factory_op;

    // Register codec factory to codec manager.
    status = pjmedia_vid_codec_mgr_register_factory(mgr,
            &foobar_codec_factory);
    if (status != PJ_SUCCESS) goto on_error;

    return PJ_SUCCESS;

on_error:
    pj_pool_release(pool);
    pj_caching_pool_destroy(&caching_pool);
    foobar_codec_factory.factory_data = NULL;

    return status;
}

/* helper function to remove foobar codec from pj */
PJ_DEF(pj_status_t) pjmedia_vid_codec_foobar_uninit()
{
    foobar_factory_data *afd;
    pj_status_t status;

    afd = (foobar_factory_data *) foobar_codec_factory.factory_data;
    if (!afd) {
        // Already un-initialized.
        return PJ_SUCCESS;
    }

    // TODO: specific mgr
    status = pjmedia_vid_codec_mgr_unregister_factory(NULL,
            &foobar_codec_factory);

    pj_pool_release(afd->pool);
    pj_caching_pool_destroy(&caching_pool);

    foobar_codec_factory.factory_data = NULL;

    return status;
}

/* ****************************************** */
/* Factory op implementation */

/* Check if factory can allocate the specified codec. */
static pj_status_t foobar_test_alloc(
        pjmedia_vid_codec_factory *factory,
        const pjmedia_vid_codec_info *info)
{
    PJ_ASSERT_RETURN(factory == &foobar_codec_factory, PJ_EINVAL);
    PJ_ASSERT_RETURN(info, PJ_EINVAL);

    // Support any directions.
    if ((info->fmt_id == foobar_codec_info.fmt_id) &&
        (info->pt == foobar_codec_info.pt) &&
        (info->packings == info->packings)) {

        return PJ_SUCCESS;
    }

    return PJMEDIA_CODEC_EUNSUP;
}

/*
 * Generate default attribute.
 */
static pj_status_t foobar_default_attr( pjmedia_vid_codec_factory *factory,
        const pjmedia_vid_codec_info *info,
        pjmedia_vid_codec_param *attr)
{
    TRACE_FUNC();

    PJ_ASSERT_RETURN(factory==&foobar_codec_factory, PJ_EINVAL);
    PJ_ASSERT_RETURN(info && attr, PJ_EINVAL);

    pj_bzero(attr, sizeof(pjmedia_vid_codec_param));

    // Setup pjmedia_vid_codec_param.
    attr->dir = foobar_codec_info.dir;
    attr->packing = foobar_codec_info.packings;

    //TODO: tune.
#define _FOOBAR_ENCODE_WIDTH 320
#define _FOOBAR_ENCODE_HEIGHT 320
    pjmedia_format_init_video(&attr->enc_fmt, foobar_codec_info.fmt_id,
            _FOOBAR_ENCODE_WIDTH, _FOOBAR_ENCODE_HEIGHT,
            (int) foobar_codec_info.fps, (int) foobar_codec_info.fps);
    pjmedia_format_init_video(&attr->dec_fmt,
            foobar_codec_info.dec_fmt_id[0],
            _FOOBAR_ENCODE_WIDTH, _FOOBAR_ENCODE_HEIGHT,
            (int) foobar_codec_info.fps, (int) foobar_codec_info.fps);

    attr->enc_mtu = PJMEDIA_MAX_MTU;

    // Init fmtp.
    attr->enc_fmtp.cnt = 0;
    attr->dec_fmtp.cnt = 0;

    attr->ignore_fmtp = PJ_FALSE;

    return PJ_TRUE;
}

/*
 * Enum codecs supported by this factory.
 */
static pj_status_t foobar_enum_info(
        pjmedia_vid_codec_factory *factory,
        unsigned *count,
        pjmedia_vid_codec_info codecs[])
{
    PJ_ASSERT_RETURN(codecs && *count > 0, PJ_EINVAL);
    PJ_ASSERT_RETURN(factory == &foobar_codec_factory, PJ_EINVAL);

    *count = 1;

    pj_memcpy(&codecs[0], &foobar_codec_info,
            sizeof(pjmedia_vid_codec_info));

    return PJ_SUCCESS;
}

/*
 * Allocate a new codec instance.
 */
static pj_status_t foobar_alloc_codec(
        pjmedia_vid_codec_factory *factory,
        const pjmedia_vid_codec_info *info,
        pjmedia_vid_codec **p_codec)
{
    pjmedia_vid_codec *codec;
    pj_pool_t *pool;
    pj_status_t status;
    foobar_factory_data *afd;
    foobar_codec_data *acd;

    PJ_ASSERT_RETURN(factory && info && p_codec, PJ_EINVAL);
    PJ_ASSERT_RETURN(factory == &foobar_codec_factory, PJ_EINVAL);
    PJ_ASSERT_RETURN(&foobar_codec_factory.factory_data, PJ_EINVAL);

    afd = (foobar_factory_data *) &foobar_codec_factory.factory_data;

    // Alloc pool for pjmedia_vid_codec.
    pool = pj_pool_create(afd->pool_factory,
                "foobar codec", 256, 256, NULL);
    PJ_ASSERT_RETURN(pool, PJ_ENOMEM);

    // Alloc foobar codec data.
    acd = PJ_POOL_ZALLOC_T(pool, foobar_codec_data);
    codec = PJ_POOL_ZALLOC_T(pool, pjmedia_vid_codec);
    if (!acd || !codec) {
        status = PJ_ENOMEM;
        goto on_error;
    }

    // Init foobar_codec_data
    acd->pool = pool;

    // Init codec.
    codec->codec_data = acd;
    codec->factory = factory;
    codec->op = &foobar_codec_op;

    // Assign.
    *p_codec = codec;

    return PJ_SUCCESS;

on_error:
    pj_pool_release(pool);

    return status;
}

/*
 * Free codec.
 */
static pj_status_t foobar_dealloc_codec(
        pjmedia_vid_codec_factory *factory,
        pjmedia_vid_codec *codec)
{
    foobar_codec_data *acd;

    PJ_ASSERT_RETURN(factory && codec, PJ_EINVAL);
    PJ_ASSERT_RETURN(factory == &foobar_codec_factory, PJ_EINVAL);

    acd = (foobar_codec_data*) codec->codec_data;

    // Dealloc.
    codec->codec_data = NULL;
    pj_pool_release(acd->pool);

    return PJ_SUCCESS;
}

/*
 * Init codec. Do nothing for foobar.
 */
static pj_status_t foobar_codec_init( pjmedia_vid_codec *codec,
        pj_pool_t *pool )
{
    TRACE_FUNC();

    PJ_UNUSED_ARG(codec);
    PJ_UNUSED_ARG(pool);

    return PJ_SUCCESS;
}

/*
 * Open codec.
 */
static pj_status_t foobar_codec_open( pjmedia_vid_codec *codec,
        pjmedia_vid_codec_param *attr )
{
    TRACE_FUNC();

    return PJ_SUCCESS;
}

/*
 * Close codec.
 */
static pj_status_t foobar_codec_close( pjmedia_vid_codec *codec )
{
    TRACE_FUNC();

    return PJ_SUCCESS;
}

/*
 * Modify codec settings.
 */
static pj_status_t foobar_codec_modify( pjmedia_vid_codec *codec,
        const pjmedia_vid_codec_param *attr)
{
    TRACE_FUNC();

    return PJ_ENOTSUP;
}

static pj_status_t foobar_codec_get_param(pjmedia_vid_codec *codec,
        pjmedia_vid_codec_param *param)
{
    TRACE_FUNC();

    return PJ_SUCCESS;
}

/*
 * Encode frames.
 */
static pj_status_t foobar_codec_encode_whole(pjmedia_vid_codec *codec,
        const pjmedia_frame *input,
        unsigned output_buf_len,
        pjmedia_frame *output)
{
    TRACE_FUNC();

    return PJ_SUCCESS;
}

static pj_status_t foobar_codec_encode_begin(
        pjmedia_vid_codec *codec,
        const pjmedia_vid_encode_opt *opt,
        const pjmedia_frame *input,
        unsigned out_size,
        pjmedia_frame *output,
        pj_bool_t *has_more)
{
    TRACE_FUNC();

    // Duplicate input to output.
    pj_memcpy(output->buf, input->buf, input->size);
    output->size = input->size;

    if (has_more) *has_more = PJ_FALSE;

    return PJ_SUCCESS;
}

static pj_status_t foobar_codec_encode_more(pjmedia_vid_codec *codec,
        unsigned out_size,
        pjmedia_frame *output,
        pj_bool_t *has_more)
{
    TRACE_FUNC();

    if (has_more) *has_more = PJ_FALSE;

    return PJ_SUCCESS;
}

/*
 * Decode frame.
 */
static pj_status_t foobar_codec_decode_whole(pjmedia_vid_codec *codec,
        const pjmedia_frame *input,
        unsigned output_buf_len,
        pjmedia_frame *output)
{
    TRACE_FUNC();

    return PJ_SUCCESS;
}

static pj_status_t foobar_codec_decode( pjmedia_vid_codec *codec,
        pj_size_t pkt_count,
        pjmedia_frame packets[],
        unsigned out_size,
        pjmedia_frame *output)
{
    TRACE_FUNC();

    return PJ_SUCCESS;
}

#endif
