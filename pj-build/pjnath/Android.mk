#    Copyright (C) 2012 Kyan <kyan.ql.he@gmail.com>
#
#    Makefile for pjnath.
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

LOCAL_PATH := $(PJ_ROOT)/pjnath

include $(CLEAR_VARS)

PJNATH_ROOT := $(LOCAL_PATH)
PJNATH_SRC_DIR := src/pjnath

LOCAL_MODULE := pjnath

LOCAL_C_INCLUDES += $(PJ_INCLUDES)

LOCAL_CFLAGS := $(PJ_CFLAGS)

LOCAL_SRC_FILES := \
	$(PJNATH_SRC_DIR)/errno.c \
	$(PJNATH_SRC_DIR)/ice_session.c \
	$(PJNATH_SRC_DIR)/ice_strans.c \
	$(PJNATH_SRC_DIR)/nat_detect.c \
	$(PJNATH_SRC_DIR)/stun_auth.c \
	$(PJNATH_SRC_DIR)/stun_msg.c \
	$(PJNATH_SRC_DIR)/stun_msg_dump.c \
	$(PJNATH_SRC_DIR)/stun_session.c \
	$(PJNATH_SRC_DIR)/stun_sock.c \
	$(PJNATH_SRC_DIR)/stun_transaction.c \
	$(PJNATH_SRC_DIR)/turn_session.c \
	$(PJNATH_SRC_DIR)/turn_sock.c

include $(BUILD_STATIC_LIBRARY)
