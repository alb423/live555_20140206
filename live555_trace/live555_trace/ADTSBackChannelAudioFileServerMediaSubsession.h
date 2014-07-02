//
//  ADTSBackChannelAudioFileServerMediaSubsession.h
//  live555_trace
//
//  Created by albert on 2014/7/3.
//  Copyright (c) 2014年 albert. All rights reserved.
//

#ifndef __live555_trace__ADTSBackChannelAudioFileServerMediaSubsession__
#define __live555_trace__ADTSBackChannelAudioFileServerMediaSubsession__

#ifndef _ADTS_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH
#define _ADTS_AUDIO_FILE_SERVER_MEDIA_SUBSESSION_HH

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class ADTSBackChannelAudioFileServerMediaSubsession: public FileServerMediaSubsession{
public:
    static ADTSBackChannelAudioFileServerMediaSubsession*
    createNew(UsageEnvironment& env, char const* fileName, Boolean reuseFirstSource);
    
protected:
    ADTSBackChannelAudioFileServerMediaSubsession(UsageEnvironment& env,
                                       char const* fileName, Boolean reuseFirstSource);
    // called only by createNew();
    virtual ~ADTSBackChannelAudioFileServerMediaSubsession();
    
protected: // redefined virtual functions
//    virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
//                                                unsigned& estBitrate);
//    virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
//                                      unsigned char rtpPayloadTypeIfDynamic,
//                                      FramedSource* inputSource);
    
    virtual Boolean createSourceObjects(int useSpecialRTPoffset);
};



#endif
#endif /* defined(__live555_trace__ADTSBackChannelAudioFileServerMediaSubsession__) */
