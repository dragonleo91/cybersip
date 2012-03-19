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
#ifndef __FOOBAR_FORMAT_H__
#define __FOOBAR_FORMAT_H__

#include <pjmedia-codec/types.h>
#include <pjmedia/vid_codec.h>

/* Definition for foobar codec encoded format ID */
#define PJMEDIA_FORMAT_FOOBAR  \
            PJMEDIA_FORMAT_PACK('F', 'B' ,'A', 'R')

#define PJMEDIA_FORMAT_FOOBAR_RENDERER  \
            PJMEDIA_FORMAT_PACK('F', 'B' ,'R', 'D')

PJ_DECL(pj_status_t) pjmedia_vid_format_foobar_init();

#endif /* __FOOBAR_FORMAT_H__ */
