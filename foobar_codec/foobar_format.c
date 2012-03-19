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

#include <pj/assert.h>
#include <pj/log.h>
#include <pjmedia/format.h>

#include "foobar_format.h"

#define THIS_FILE   "foobar_format.c"

#define MEMBER(m)

static pj_status_t apply_foobar_fmt(
        const pjmedia_video_format_info *fi,
        pjmedia_video_apply_fmt_param *aparam)
{
    unsigned i;

    aparam->framebytes = 20;
    aparam->planes[0] = aparam->buffer;
    aparam->strides[0] = 0;
    aparam->plane_bytes[0] = aparam->framebytes;

    // Zero unused planes */
    for (i = 1; i < PJMEDIA_MAX_VIDEO_PLANES; ++i){
        aparam->strides[i] = 0;
        aparam->planes[i] = NULL;
    }

    return PJ_SUCCESS;
}

static pjmedia_video_format_info foobar_format_info =
{
    MEMBER(id) PJMEDIA_FORMAT_FOOBAR_RENDERER,
    MEMBER(name) "FOOBAR",
    MEMBER(color_model) PJMEDIA_COLOR_MODEL_RGB,
    MEMBER(bpp) 1,
    MEMBER(plane_cnt) 1,
    MEMBER(apply_fmt) &apply_foobar_fmt,
};

PJ_DEF(pj_status_t) pjmedia_vid_format_foobar_init()
{
    return pjmedia_register_video_format_info(NULL, &foobar_format_info);
}

