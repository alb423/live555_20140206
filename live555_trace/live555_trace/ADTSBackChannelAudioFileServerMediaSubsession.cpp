//
//  ADTSBackChannelAudioFileServerMediaSubsession.cpp
//  live555_trace
//
//  Created by albert on 2014/7/3.
//  Copyright (c) 2014年 albert. All rights reserved.
//

#include "ADTSBackChannelAudioFileServerMediaSubsession.h"


/*
Boolean ADTSBackChannelAudioFileServerMediaSubsession::createSourceObjects(int useSpecialRTPoffset){
    do {
        // First, check "fProtocolName"
        if (strcmp(fProtocolName, "UDP") == 0)
        {
            // A UDP-packetized stream (*not* a RTP stream)
            fReadSource = BasicUDPSource::createNew(env(), fRTPSocket);
            fRTPSource = NULL; // Note!
            
            if (strcmp(fCodecName, "MP2T") == 0) { // MPEG-2 Transport Stream
                fReadSource = MPEG2TransportStreamFramer::createNew(env(), fReadSource);
                // this sets "durationInMicroseconds" correctly, based on the PCR values
            }
        } else {
            // Check "fCodecName" against the set of codecs that we support,
            // and create our RTP source accordingly
            // (Later make this code more efficient, as this set grows #####)
            // (Also, add more fmts that can be implemented by SimpleRTPSource#####)
            Boolean createSimpleRTPSource = False; // by default; can be changed below
            Boolean doNormalMBitRule = False; // default behavior if "createSimpleRTPSource" is True
            if (strcmp(fCodecName, "MPA") == 0) { // MPEG-1 or 2 audio
                fReadSource = fRTPSource
                = MPEG1or2AudioRTPSource::createNew(env(), fRTPSocket,
                                                    fRTPPayloadFormat,
                                                    fRTPTimestampFrequency);
            } else if (strcmp(fCodecName, "MP4A-LATM") == 0) { // MPEG-4 LATM audio
                fReadSource = fRTPSource
                = MPEG4LATMAudioRTPSource::createNew(env(), fRTPSocket,
                                                     fRTPPayloadFormat,
                                                     fRTPTimestampFrequency);
            } else if (strcmp(fCodecName, "MPEG4-GENERIC") == 0) {
                fReadSource = fRTPSource
                = MPEG4GenericRTPSource::createNew(env(), fRTPSocket,
                                                   fRTPPayloadFormat,
                                                   fRTPTimestampFrequency,
                                                   fMediumName, attrVal_str("mode"),
                                                   attrVal_unsigned("sizelength"),
                                                   attrVal_unsigned("indexlength"),
                                                   attrVal_unsigned("indexdeltalength"));
            }else if (strcmp(fCodecName, "H264") == 0) {
                fReadSource = fRTPSource
                = H264VideoRTPSource::createNew(env(), fRTPSocket,
                                                fRTPPayloadFormat,
                                                fRTPTimestampFrequency);
            }
            } else if (  strcmp(fCodecName, "PCMU") == 0 // PCM u-law audio
                       || strcmp(fCodecName, "GSM") == 0 // GSM audio
                       || strcmp(fCodecName, "DVI4") == 0 // DVI4 (IMA ADPCM) audio
                       || strcmp(fCodecName, "PCMA") == 0 // PCM a-law audio
                       || strcmp(fCodecName, "MP1S") == 0 // MPEG-1 System Stream
                       || strcmp(fCodecName, "MP2P") == 0 // MPEG-2 Program Stream
                       || strcmp(fCodecName, "L8") == 0 // 8-bit linear audio
                       || strcmp(fCodecName, "L16") == 0 // 16-bit linear audio
                       || strcmp(fCodecName, "L20") == 0 // 20-bit linear audio (RFC 3190)
                       || strcmp(fCodecName, "L24") == 0 // 24-bit linear audio (RFC 3190)
                       || strcmp(fCodecName, "G726-16") == 0 // G.726, 16 kbps
                       || strcmp(fCodecName, "G726-24") == 0 // G.726, 24 kbps
                       || strcmp(fCodecName, "G726-32") == 0 // G.726, 32 kbps
                       || strcmp(fCodecName, "G726-40") == 0 // G.726, 40 kbps
                       || strcmp(fCodecName, "SPEEX") == 0 // SPEEX audio
                       || strcmp(fCodecName, "ILBC") == 0 // iLBC audio
                       || strcmp(fCodecName, "OPUS") == 0 // Opus audio
                       || strcmp(fCodecName, "T140") == 0 // T.140 text (RFC 4103)
                       || strcmp(fCodecName, "DAT12") == 0 // 12-bit nonlinear audio (RFC 3190)
                       || strcmp(fCodecName, "VND.ONVIF.METADATA") == 0 // 'ONVIF' 'metadata' (a XML document)
                       ) {
                createSimpleRTPSource = True;
                useSpecialRTPoffset = 0;
                if (strcmp(fCodecName, "VND.ONVIF.METADATA") == 0) {
                    // This RTP payload format uses the RTP "M" bit to indicate the end of the content (a XML document):
                    doNormalMBitRule = True;
                }
            } else if (useSpecialRTPoffset >= 0) {
                // We don't know this RTP payload format, but try to receive
                // it using a 'SimpleRTPSource' with the specified header offset:
                createSimpleRTPSource = True;
            } else {
                env().setResultMsg("RTP payload format unknown or not supported");
                break;
            }
            
            if (createSimpleRTPSource) {
                char* mimeType
                = new char[strlen(mediumName()) + strlen(codecName()) + 2] ;
                sprintf(mimeType, "%s/%s", mediumName(), codecName());
                fReadSource = fRTPSource
                = SimpleRTPSource::createNew(env(), fRTPSocket, fRTPPayloadFormat,
                                             fRTPTimestampFrequency, mimeType,
                                             (unsigned)useSpecialRTPoffset,
                                             doNormalMBitRule);
                delete[] mimeType;
            }
        }
        
        return True;
    } while (0);
    
    return False; // an error occurred
}
*/
