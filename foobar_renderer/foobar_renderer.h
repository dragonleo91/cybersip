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
#ifndef __FOOBAR_RENDER_H__
#define __FOOBAR_RENDER_H__

PJ_BEGIN_DECL

/**
 * Initialize and register foobar dev factory to pjmedia video sub-system.
 */

PJ_DECL(pj_status_t) pjmedia_vid_dev_foobar_init();

PJ_END_DECL

#endif /* __FOOBAR_RENDER_H__ */
