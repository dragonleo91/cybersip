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
#ifndef __FOOBAR_CONVERTER_H__
#define __FOOBAR_CONVERTER_H__

#include <pj/types.h>

PJ_BEGIN_DECL

PJ_DECL(pj_status_t) pjmedia_vid_converter_foobar_init();

PJ_DECL(pj_status_t) pjmedia_vid_converter_foobar_deinit();

PJ_END_DECL

#endif /* __FOOBAR_CONVERTER_H__ */
