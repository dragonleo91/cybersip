#    Copyright (C) 2012 Kyan <kyan.ql.he@gmail.com>
#
#    Makefile for pjlib-util.
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

LOCAL_PATH := $(PJ_ROOT)/pjlib-util

include $(CLEAR_VARS)

PJLIB_UTIL_ROOT := $(LOCAL_PATH)
PJLIB_UTIL_SRC_DIR := src/pjlib-util

LOCAL_MODULE := pjlib-util

LOCAL_C_INCLUDES += $(PJ_INCLUDES)

LOCAL_CFLAGS := $(PJ_CFLAGS)

LOCAL_SRC_FILES := \
	$(PJLIB_UTIL_SRC_DIR)/base64.c \
	$(PJLIB_UTIL_SRC_DIR)/crc32.c \
	$(PJLIB_UTIL_SRC_DIR)/errno.c \
	$(PJLIB_UTIL_SRC_DIR)/dns.c \
	$(PJLIB_UTIL_SRC_DIR)/dns_dump.c \
	$(PJLIB_UTIL_SRC_DIR)/dns_server.c \
	$(PJLIB_UTIL_SRC_DIR)/getopt.c \
	$(PJLIB_UTIL_SRC_DIR)/hmac_md5.c \
	$(PJLIB_UTIL_SRC_DIR)/hmac_sha1.c \
	$(PJLIB_UTIL_SRC_DIR)/md5.c \
	$(PJLIB_UTIL_SRC_DIR)/pcap.c \
	$(PJLIB_UTIL_SRC_DIR)/resolver.c \
	$(PJLIB_UTIL_SRC_DIR)/scanner.c \
	$(PJLIB_UTIL_SRC_DIR)/sha1.c \
	$(PJLIB_UTIL_SRC_DIR)/srv_resolver.c \
	$(PJLIB_UTIL_SRC_DIR)/string.c \
	$(PJLIB_UTIL_SRC_DIR)/stun_simple.c \
	$(PJLIB_UTIL_SRC_DIR)/stun_simple_client.c \
	$(PJLIB_UTIL_SRC_DIR)/xml.c

include $(BUILD_STATIC_LIBRARY)
