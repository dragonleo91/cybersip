#    Copyright (C) 2012 Kyan <kyan.ql.he@gmail.com>
#
#    Makefile for pjsip.
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

LOCAL_PATH := $(PJ_ROOT)/pjsip

include $(CLEAR_VARS)

PJSIP_ROOT := $(LOCAL_PATH)
PJSIP_SRC_DIR := src/pjsip
PJSIPUA_SRC_DIR := src/pjsip-ua
PJSIPSIMPLE_SRC_DIR := src/pjsip-simple
PJSUA_SRC_DIR := src/pjsua-lib

LOCAL_MODULE := pjsip

LOCAL_CFLAGS := $(PJ_CFLAGS)

LOCAL_C_INCLUDES := $(PJ_INCLUDES)

## Hint for reduce code size.
#
# pjsua_dump.c
##

LOCAL_SRC_FILES := \
	$(PJSIP_SRC_DIR)/sip_config.c \
	$(PJSIP_SRC_DIR)/sip_multipart.c \
	$(PJSIP_SRC_DIR)/sip_errno.c \
	$(PJSIP_SRC_DIR)/sip_msg.c \
	$(PJSIP_SRC_DIR)/sip_parser.c \
	$(PJSIP_SRC_DIR)/sip_tel_uri.c \
	$(PJSIP_SRC_DIR)/sip_uri.c \
	$(PJSIP_SRC_DIR)/sip_endpoint.c \
	$(PJSIP_SRC_DIR)/sip_util.c \
	$(PJSIP_SRC_DIR)/sip_util_proxy.c \
	$(PJSIP_SRC_DIR)/sip_resolve.c \
	$(PJSIP_SRC_DIR)/sip_transport.c \
	$(PJSIP_SRC_DIR)/sip_transport_loop.c \
	$(PJSIP_SRC_DIR)/sip_transport_udp.c \
	$(PJSIP_SRC_DIR)/sip_transport_tcp.c \
	$(PJSIP_SRC_DIR)/sip_auth_aka.c \
	$(PJSIP_SRC_DIR)/sip_auth_client.c \
	$(PJSIP_SRC_DIR)/sip_auth_msg.c \
	$(PJSIP_SRC_DIR)/sip_auth_parser.c \
	$(PJSIP_SRC_DIR)/sip_auth_server.c \
	$(PJSIP_SRC_DIR)/sip_transaction.c \
	$(PJSIP_SRC_DIR)/sip_util_statefull.c \
	$(PJSIP_SRC_DIR)/sip_dialog.c \
	$(PJSIP_SRC_DIR)/sip_ua_layer.c \
	\
	$(PJSIPUA_SRC_DIR)/sip_inv.c \
	$(PJSIPUA_SRC_DIR)/sip_reg.c \
	$(PJSIPUA_SRC_DIR)/sip_replaces.c \
	$(PJSIPUA_SRC_DIR)/sip_xfer.c \
	$(PJSIPUA_SRC_DIR)/sip_100rel.c \
	$(PJSIPUA_SRC_DIR)/sip_timer.c \
	\
	$(PJSIPSIMPLE_SRC_DIR)/errno.c \
	$(PJSIPSIMPLE_SRC_DIR)/evsub.c \
	$(PJSIPSIMPLE_SRC_DIR)/evsub_msg.c \
	$(PJSIPSIMPLE_SRC_DIR)/iscomposing.c \
	$(PJSIPSIMPLE_SRC_DIR)/mwi.c \
	$(PJSIPSIMPLE_SRC_DIR)/pidf.c \
	$(PJSIPSIMPLE_SRC_DIR)/presence.c \
	$(PJSIPSIMPLE_SRC_DIR)/presence_body.c \
	$(PJSIPSIMPLE_SRC_DIR)/publishc.c \
	$(PJSIPSIMPLE_SRC_DIR)/rpid.c \
	$(PJSIPSIMPLE_SRC_DIR)/xpidf.c \
	\
	$(PJSUA_SRC_DIR)/pjsua_acc.c \
	$(PJSUA_SRC_DIR)/pjsua_call.c \
	$(PJSUA_SRC_DIR)/pjsua_core.c \
	$(PJSUA_SRC_DIR)/pjsua_im.c \
	$(PJSUA_SRC_DIR)/pjsua_media.c \
	$(PJSUA_SRC_DIR)/pjsua_pres.c \
	$(PJSUA_SRC_DIR)/pjsua_vid.c \
	$(PJSUA_SRC_DIR)/pjsua_dump.c


# TODO:
ifeq ($(PJ_ENABLE_TLS),1)
    LOCAL_SRC_FILES += $(PJSIP_SRC_DIR)/sip_transport_tls_ossl.c
    LOCAL_C_INCLUDES += $(OPENSSL_INCLUDE)
endif

include $(BUILD_STATIC_LIBRARY)
