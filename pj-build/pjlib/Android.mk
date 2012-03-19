#    Copyright (C) 2012 Kyan <kyan.ql.he@gmail.com>
#
#    Makefile for pjlib.
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

LOCAL_PATH := $(PJ_ROOT)/pjlib

include $(CLEAR_VARS)

PJLIB_ROOT := $(LOCAL_PATH)
PJLIB_SRC_DIR := src/pj

LOCAL_MODULE := pjlib

LOCAL_C_INCLUDES += $(PJ_INCLUDES)

LOCAL_CFLAGS := $(PJ_CFLAGS)

# TODO:
ifeq ($(PJ_ENABLE_TLS),1)
    LOCAL_C_INCLUDES += $(OPENSSL_INCLUDE)
endif

## Hint for reduce code size.
#
# ssl_sock_dump.c used in pjsip-apps/pjsua
##

LOCAL_SRC_FILES  := \
	$(PJLIB_SRC_DIR)/addr_resolv_sock.c \
	$(PJLIB_SRC_DIR)/file_access_unistd.c \
	$(PJLIB_SRC_DIR)/file_io_ansi.c \
	$(PJLIB_SRC_DIR)/guid_simple.c \
	$(PJLIB_SRC_DIR)/log.c \
	$(PJLIB_SRC_DIR)/log_writer_stdout.c \
	$(PJLIB_SRC_DIR)/os_info.c \
	$(PJLIB_SRC_DIR)/os_core_unix.c \
	$(PJLIB_SRC_DIR)/os_error_unix.c \
	$(PJLIB_SRC_DIR)/os_time_common.c \
	$(PJLIB_SRC_DIR)/os_time_unix.c \
	$(PJLIB_SRC_DIR)/os_timestamp_common.c \
	$(PJLIB_SRC_DIR)/os_timestamp_posix.c \
	$(PJLIB_SRC_DIR)/pool_policy_malloc.c \
	$(PJLIB_SRC_DIR)/sock_common.c \
	$(PJLIB_SRC_DIR)/sock_qos_common.c \
	$(PJLIB_SRC_DIR)/sock_qos_bsd.c \
	$(PJLIB_SRC_DIR)/ssl_sock_common.c \
	$(PJLIB_SRC_DIR)/ssl_sock_ossl.c \
	$(PJLIB_SRC_DIR)/ssl_sock_dump.c \
	$(PJLIB_SRC_DIR)/sock_bsd.c \
	$(PJLIB_SRC_DIR)/sock_select.c \
	$(PJLIB_SRC_DIR)/activesock.c \
	$(PJLIB_SRC_DIR)/array.c \
	$(PJLIB_SRC_DIR)/config.c \
	$(PJLIB_SRC_DIR)/ctype.c \
	$(PJLIB_SRC_DIR)/errno.c \
	$(PJLIB_SRC_DIR)/except.c \
	$(PJLIB_SRC_DIR)/fifobuf.c \
	$(PJLIB_SRC_DIR)/guid.c \
	$(PJLIB_SRC_DIR)/hash.c \
	$(PJLIB_SRC_DIR)/ip_helper_generic.c \
	$(PJLIB_SRC_DIR)/list.c \
	$(PJLIB_SRC_DIR)/lock.c \
	$(PJLIB_SRC_DIR)/pool.c \
	$(PJLIB_SRC_DIR)/pool_buf.c \
	$(PJLIB_SRC_DIR)/pool_caching.c \
	$(PJLIB_SRC_DIR)/pool_dbg.c \
	$(PJLIB_SRC_DIR)/rbtree.c \
	$(PJLIB_SRC_DIR)/string.c \
	$(PJLIB_SRC_DIR)/rand.c \
	$(PJLIB_SRC_DIR)/timer.c \
	$(PJLIB_SRC_DIR)/types.c \
	$(PJLIB_SRC_DIR)/ioqueue_select.c

include $(BUILD_STATIC_LIBRARY)
