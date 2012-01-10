/* 
 * Copyright (C) 2012 Kyan He <kyan.ql.he@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

// Configuration for M$ Windows.
#if defined(PJ_WIN32) && PJ_WIN32 != 0

#define PJMEDIA_HAS_VIDEO    1
#define PJMEDIA_HAS_FFMPEG    1
#define PJMEDIA_VIDEO_DEV_HAS_SDL   1
#define PJMEDIA_VIDEO_DEV_HAS_DSHOW 1

#endif
