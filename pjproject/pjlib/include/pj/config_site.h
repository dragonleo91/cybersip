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

// Enable Video function.
#define PJMEDIA_HAS_VIDEO    1

// FFMPEG provide h263/h263+/h264 codec,
// and don't need external libx264 for lastest(2012-2-7) ffmpeg.
#define PJMEDIA_HAS_FFMPEG    1

// Renderer dev depends on SDL.
#define PJMEDIA_VIDEO_DEV_HAS_SDL   1

// Capture dev depends on DirectShow.
#define PJMEDIA_VIDEO_DEV_HAS_DSHOW 1

// Enable H264,
// H264 is disabled by default(pjmedia/include/pjmedia-codec/config.h).
#define PJMEDIA_HAS_FFMPEG_CODEC_H264 1

#endif
