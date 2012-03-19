#define PJMEDIA_VIDEO_DEV_HAS_CBAR_SRC 0

#define PJMEDIA_SDP_NEG_PREFER_REMOTE_CODEC_ORDER 0
#define PJ_HAS_IPV6 0

#define PJ_STUN_KEEP_ALIVE_SEC 90
#define PJ_ICE_SESS_KEEP_ALIVE_MIN 90

// Fix google voice problem with RTP DTMF events
#define PJMEDIA_RTP_PT_TELEPHONE_EVENTS          101
#define PJMEDIA_RTP_PT_TELEPHONE_EVENTS_STR      "101"

#if defined(PJ_ANDROID) && PJ_ANDROID!=0

    // Disable SRTP
    #define PJMEDIA_HAS_SRTP 0

    #define PJSUA_DEFAULT_AUDIO_FRAME_PTIME 20

    // Optimizations
    #define PJ_ENABLE_EXTRA_CHECK   0

    // Conference switch board
    #define PJMEDIA_CONF_USE_SWITCH_BOARD 0
    #define PJ_OS_HAS_CHECK_STACK 0
    #define PJSIP_HAS_DIGEST_MJMD5_AUTH 1
    #define PJ_QOS_IMPLEMENTATION    PJ_QOS_BSD
    #define PJSIP_CHECK_VIA_SENT_BY 0

    // PJMEDIA settings

    // Disable non-Android audio devices
    #define PJMEDIA_AUDIO_DEV_HAS_PORTAUDIO     0
    #define PJMEDIA_AUDIO_DEV_HAS_WMME          0
    #define PJMEDIA_AUDIO_DEV_HAS_ANDROID       1

    // Select codecs to disable
    #define PJMEDIA_HAS_L16_CODEC               0

    // Fine tune Speex's default settings for best performance/quality
    #define PJMEDIA_CODEC_SPEEX_DEFAULT_QUALITY 5

    // For CPU reason, disable speex AEC and use the echo suppressor. */
    #define PJMEDIA_HAS_SPEEX_AEC 0

    // Enable Video
    #define PJMEDIA_HAS_VIDEO 1
    
    // Enabel FFMPEG
    #define PJMEDIA_HAS_FFMPEG 0


    /* Previously, resampling is disabled due to performance reason and
     * this condition prevented some 'light' wideband codecs (e.g: G722.1)
     * to work along with narrowband codecs. Lately, some tests showed
     * that 16kHz <-> 8kHz resampling using libresample small filter was 
     * affordable on ARM9 222 MHz, so here we decided to enable resampling.
     * Note that it is important to make sure that libresample is created
     * using small filter. For example PJSUA_DEFAULT_CODEC_QUALITY must
     * be set to 3 or 4 so pjsua-lib will apply small filter resampling.
     */
    #define PJMEDIA_RESAMPLE_IMP                PJMEDIA_RESAMPLE_LIBRESAMPLE

    // Use the lighter WSOLA implementation
    #define PJMEDIA_WSOLA_IMP                   PJMEDIA_WSOLA_IMP_WSOLA_LITE

    // PJSUA settings.
    #define PJSUA_DEFAULT_CODEC_QUALITY         4
    #define PJSUA_REG_RETRY_INTERVAL 60

    // Set maximum number of dialog/transaction/calls to minimum
    #define PJSIP_MAX_TSX_COUNT 31
    #define PJSIP_MAX_DIALOG_COUNT 31
    #define PJSUA_MAX_CALLS 4

    // Other pjsua settings
    #define PJSUA_MAX_ACC 1
    #define PJSUA_MAX_PLAYERS 4
    #define PJSUA_MAX_RECORDERS 4
    #define PJSUA_MAX_CONF_PORTS (PJSUA_MAX_CALLS+2*PJSUA_MAX_PLAYERS)
    #define PJSUA_MAX_BUDDIES 32

#endif
