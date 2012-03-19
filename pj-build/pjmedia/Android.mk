#    Copyright (C) 2012 Kyan <kyan.ql.he@gmail.com>
#
#    Makefile for pjmedia.
#
#    This file is part of CyberSIP.
#
#    Foobar is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Foobar is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with CyberSIP.  If not, see <http://www.gnu.org/licenses/>.

# Pjmedia depends on resample.
include $(PJ_BUILD_ROOT)/third_party/resample/Android.mk

LOCAL_PATH := $(PJ_ROOT)/pjmedia

include $(CLEAR_VARS)

PJMEDIA_ROOT := $(LOCAL_PATH)
PJMEDIA_SRC_DIR := src/pjmedia
PJMEDIADEV_SRC_DIR := src/pjmedia-audiodev
PJMEDIAVDEV_SRC_DIR := src/pjmedia-videodev
PJMEDIACODEC_SRC_DIR := src/pjmedia-codec

LOCAL_MODULE := pjmedia

LOCAL_C_INCLUDES := \
	$(PJ_INCLUDES) \
	$(RESAMPLE_INCLUDES)

LOCAL_CFLAGS := $(PJ_CFLAGS)

## Hint for reduce code size.
#
# types.c
##

# pjmedia depends on resample.
LOCAL_STATIC_LIBRARIES := resample

LOCAL_SRC_FILES := \
	$(PJMEDIA_SRC_DIR)/alaw_ulaw.c \
	$(PJMEDIA_SRC_DIR)/alaw_ulaw_table.c \
	$(PJMEDIA_SRC_DIR)/avi_player.c \
	$(PJMEDIA_SRC_DIR)/bidirectional.c \
	$(PJMEDIA_SRC_DIR)/clock_thread.c \
	$(PJMEDIA_SRC_DIR)/codec.c \
	$(PJMEDIA_SRC_DIR)/conference.c \
	$(PJMEDIA_SRC_DIR)/conf_switch.c \
	$(PJMEDIA_SRC_DIR)/converter.c \
	$(PJMEDIA_SRC_DIR)/converter_libswscale.c \
	$(PJMEDIA_SRC_DIR)/delaybuf.c \
	$(PJMEDIA_SRC_DIR)/echo_common.c \
	$(PJMEDIA_SRC_DIR)/echo_speex.c \
	$(PJMEDIA_SRC_DIR)/echo_port.c \
	$(PJMEDIA_SRC_DIR)/echo_suppress.c \
	$(PJMEDIA_SRC_DIR)/endpoint.c \
	$(PJMEDIA_SRC_DIR)/errno.c \
	$(PJMEDIA_SRC_DIR)/event.c \
	$(PJMEDIA_SRC_DIR)/format.c \
	$(PJMEDIA_SRC_DIR)/ffmpeg_util.c \
	$(PJMEDIA_SRC_DIR)/g711.c \
	$(PJMEDIA_SRC_DIR)/jbuf.c \
	$(PJMEDIA_SRC_DIR)/master_port.c \
	$(PJMEDIA_SRC_DIR)/mem_capture.c \
	$(PJMEDIA_SRC_DIR)/mem_player.c \
	$(PJMEDIA_SRC_DIR)/null_port.c \
	$(PJMEDIA_SRC_DIR)/plc_common.c \
	$(PJMEDIA_SRC_DIR)/port.c \
	$(PJMEDIA_SRC_DIR)/splitcomb.c \
	$(PJMEDIA_SRC_DIR)/resample_resample.c \
	$(PJMEDIA_SRC_DIR)/resample_libsamplerate.c \
	$(PJMEDIA_SRC_DIR)/resample_port.c \
	$(PJMEDIA_SRC_DIR)/rtcp.c \
	$(PJMEDIA_SRC_DIR)/rtcp_xr.c \
	$(PJMEDIA_SRC_DIR)/rtp.c \
	$(PJMEDIA_SRC_DIR)/sdp.c \
	$(PJMEDIA_SRC_DIR)/sdp_cmp.c \
	$(PJMEDIA_SRC_DIR)/sdp_neg.c \
	$(PJMEDIA_SRC_DIR)/session.c \
	$(PJMEDIA_SRC_DIR)/silencedet.c \
	$(PJMEDIA_SRC_DIR)/sound_port.c \
	$(PJMEDIA_SRC_DIR)/stereo_port.c \
	$(PJMEDIA_SRC_DIR)/stream.c \
	$(PJMEDIA_SRC_DIR)/tonegen.c \
	$(PJMEDIA_SRC_DIR)/transport_adapter_sample.c \
	$(PJMEDIA_SRC_DIR)/stream_common.c \
	$(PJMEDIA_SRC_DIR)/vid_stream.c \
	$(PJMEDIA_SRC_DIR)/transport_ice.c \
	$(PJMEDIA_SRC_DIR)/transport_loop.c \
	$(PJMEDIA_SRC_DIR)/transport_srtp.c \
	$(PJMEDIA_SRC_DIR)/transport_udp.c \
	$(PJMEDIA_SRC_DIR)/vid_codec.c \
	$(PJMEDIA_SRC_DIR)/vid_port.c \
	$(PJMEDIA_SRC_DIR)/vid_codec_util.c \
	$(PJMEDIA_SRC_DIR)/vid_tee.c \
	$(PJMEDIA_SRC_DIR)/wav_player.c \
	$(PJMEDIA_SRC_DIR)/wav_playlist.c \
	$(PJMEDIA_SRC_DIR)/wav_writer.c \
	$(PJMEDIA_SRC_DIR)/wave.c \
	$(PJMEDIA_SRC_DIR)/wsola.c \
	$(PJMEDIA_SRC_DIR)/types.c \
	$(PJMEDIADEV_SRC_DIR)/audiodev.c \
	$(PJMEDIADEV_SRC_DIR)/audiotest.c \
	$(PJMEDIADEV_SRC_DIR)/errno.c  \
	$(PJMEDIAVDEV_SRC_DIR)/videodev.c \
	$(PJMEDIAVDEV_SRC_DIR)/ffmpeg_dev.c \
	$(PJMEDIAVDEV_SRC_DIR)/colorbar_dev.c \
	$(PJMEDIAVDEV_SRC_DIR)/errno.c \
	$(PJMEDIAVDEV_SRC_DIR)/v4l2_dev.c \
	$(PJMEDIACODEC_SRC_DIR)/audio_codecs.c \
	$(PJMEDIACODEC_SRC_DIR)/ffmpeg_codecs.c \
	$(PJMEDIACODEC_SRC_DIR)/h263_packetizer.c


ifeq ($(PJ_ENABLE_G729),1)
LOCAL_SRC_FILES += $(PJMEDIACODEC_SRC_DIR)/g729.c
endif

ifeq ($(PJ_ENABLE_G722),1)
LOCAL_SRC_FILES += \
	$(PJMEDIACODEC_SRC_DIR)/g722.c \
	$(PJMEDIACODEC_SRC_DIR)/g722/g722_enc.c \
	$(PJMEDIACODEC_SRC_DIR)/g722/g722_dec.c
endif

ifeq ($(PJ_ENABLE_SPEEX),1)
LOCAL_SRC_FILES += $(PJMEDIACODEC_SRC_DIR)/speex_codec.c
endif

ifeq ($(PJ_ENABLE_ILBC),1)
LOCAL_SRC_FILES += $(PJMEDIACODEC_SRC_DIR)/ilbc.c
endif

ifeq ($(PJ_ENABLE_GSM),1)
LOCAL_SRC_FILES += $(PJMEDIACODEC_SRC_DIR)/gsm.c
endif

ifeq ($(PJ_ENABLE_SILK),1)
LOCAL_SRC_FILES += $(PJMEDIACODEC_SRC_DIR)/silk.c
endif

ifeq ($(PJ_ENABLE_CODEC2),1)
LOCAL_SRC_FILES += $(PJMEDIACODEC_SRC_DIR)/codec2.c
endif

ifeq ($(PJ_ENABLE_VIDEO),1)
LOCAL_SRC_FILES += \
	$(PJMEDIACODEC_SRC_DIR)/ffmpeg_codecs.c \
	$(PJMEDIACODEC_SRC_DIR)/h263_packetizer.c \
	$(PJMEDIACODEC_SRC_DIR)/h264_packetizer.c
endif

include $(BUILD_STATIC_LIBRARY)
