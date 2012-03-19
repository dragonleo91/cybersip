#    Copyright (C) 2012 Kyan <kyan.ql.he@gmail.com>
#
#    Pjsip Top-level makefile.
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


# PJSIP customiztion.
PJ_ENABLE_G729 := 0
PJ_ENABLE_G722 := 0
PJ_ENABLE_SPEEX := 0
PJ_ENABLE_ILBC := 0
PJ_ENABLE_GSM := 0
PJ_ENABLE_SILK := 0
PJ_ENABLE_CODEC2 := 0
PJ_ENABLE_TLS := 0

PJ_ROOT := /home/kyan/project/pjsip

# Dir holds these Android.mk files.
PJ_BUILD_ROOT := $(call my-dir)

# $(PJ_BUILD_ROOT)/include will override the default headers.
PJ_INCLUDES := \
	$(PJ_BUILD_ROOT)/include \
	$(PJ_ROOT)/pjlib-util/include \
	$(PJ_ROOT)/pjlib/include \
	$(PJ_ROOT)/pjnath/include \
	$(PJ_ROOT)/pjmedia/include \
	$(PJ_ROOT)/pjsip/include

# PJ_ANDRIOD must define at this level.
# -D -> config.h -> config_site.h
PJ_CFLAGS := -DPJ_ANDROID=1

ifeq ($(TARGET_ARCH_ABI),armeabi)
    # Legancy armeabi has no FPU.
    PJ_CFLAGS += -DPJ_HAS_FLOATING_POINT=0
else
    # armeabi-v7a x86
    PJ_CFLAGS += -DPJ_HAS_FLOATING_POINT=1
endif

# Pjsip Core, order sensitive.
# pjlib-util depends on pjlib.
include $(PJ_BUILD_ROOT)/pjlib/Android.mk
include $(PJ_BUILD_ROOT)/pjlib-util/Android.mk
include $(PJ_BUILD_ROOT)/pjnath/Android.mk
include $(PJ_BUILD_ROOT)/pjmedia/Android.mk
include $(PJ_BUILD_ROOT)/pjsip/Android.mk

# Build stand-alone pjproject lib.
include $(CLEAR_VARS)

LOCAL_MODULE := pjproject

LOCAL_STATIC_LIBRARIES := pjlib-util pjlib pjnath pjmedia pjsip

include $(BUILD_SHARED_LIBRARY)
