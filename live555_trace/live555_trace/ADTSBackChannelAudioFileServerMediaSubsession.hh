//
//  ADTSBackChannelAudioFileServerMediaSubsession.h
//  live555_trace
//
//  Created by albert on 2014/7/3.
//  Copyright (c) 2014年 albert. All rights reserved.
//

#ifndef __live555_trace__ADTSBackChannelAudioFileServerMediaSubsession__
#define __live555_trace__ADTSBackChannelAudioFileServerMediaSubsession__

#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class ADTSBackChannelAudioFileServerMediaSubsession: public FileServerMediaSubsession{
//class ADTSBackChannelAudioFileServerMediaSubsession: public OnDemandServerMediaSubsession{

public:
    static ADTSBackChannelAudioFileServerMediaSubsession*
    createNew(UsageEnvironment& env, char const* fileName, Boolean reuseFirstSource);
    
protected:
    ADTSBackChannelAudioFileServerMediaSubsession(UsageEnvironment& env,
                                       char const* fileName, Boolean reuseFirstSource);
    // called only by createNew();
    virtual ~ADTSBackChannelAudioFileServerMediaSubsession();
    
protected: // redefined virtual functions

    // Below functions should be redefined,
    // But they won't use in backchannel
    virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
                          unsigned& estBitrate);
    //"estBitrate" is the stream's estimated bitrate, in kbps
    virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                    unsigned char rtpPayloadTypeIfDynamic,
                    FramedSource* inputSource);
    
    
    // Below is for backchannel
    // reference MediaSession.cpp
    FileSink* createNewSink(unsigned clientSessionId, unsigned& estBitrate);
    
    virtual Boolean createSourceObjects(int useSpecialRTPoffset);
    
    unsigned char fRTPPayloadFormat;
    unsigned fRTPTimestampFrequency;
    char* fMediumName;
    
    Groupsock* fRTPSocket; Groupsock* fRTCPSocket; // works even for unicast
    RTPSource* fRTPSource; RTCPInstance* fRTCPInstance;
    FramedSource* fReadSource;
    
    // Other fields:
    char* fSessionId; // used by RTSP
    
};


#endif /* defined(__live555_trace__ADTSBackChannelAudioFileServerMediaSubsession__) */
