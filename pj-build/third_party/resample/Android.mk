#    Copyright (C) 2012 Kyan <kyan.ql.he@gmail.com>
#
#    Makefile for resample.
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

LOCAL_PATH := $(PJ_ROOT)/third_party/resample

include $(CLEAR_VARS)

RESAMPLE_ROOT := $(LOCAL_PATH)

# pjmedia use "third_party/resample/include/resamplesubs.h".
# resamplebus.c depend on config.h, located at build dir.
RESAMPLE_INCLUDES := \
	$(RESAMPLE_ROOT)/include \
	$(PJ_ROOT)/third_party/build/resample \
	$(PJ_ROOT)
RESAMPLE_SRC_DIR := src

LOCAL_MODULE := resample

LOCAL_C_INCLUDES += $(RESAMPLE_INCLUDES)

LOCAL_SRC_FILES := $(RESAMPLE_SRC_DIR)/resamplesubs.c

include $(BUILD_STATIC_LIBRARY)

