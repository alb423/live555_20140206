//
//  ADTSBackChannelAudioFileServerMediaSubsession.cpp
//  live555_trace
//
//  Created by albert on 2014/7/3.
//  Copyright (c) 2014年 albert. All rights reserved.
//

#include "ADTSBackChannelAudioFileServerMediaSubsession.hh"
#include "MPEG4GenericRTPSource.hh"
#include "ADTSAudioFileSink.hh"

ADTSBackChannelAudioFileServerMediaSubsession*
ADTSBackChannelAudioFileServerMediaSubsession::createNew(UsageEnvironment& env,
                                                     char const* fileName,
                                                     Boolean reuseFirstSource) {
    return new ADTSBackChannelAudioFileServerMediaSubsession(env, fileName, reuseFirstSource);
}

ADTSBackChannelAudioFileServerMediaSubsession::ADTSBackChannelAudioFileServerMediaSubsession(UsageEnvironment& env,
                                                char const* fileName, Boolean reuseFirstSource)
: FileServerMediaSubsession(env, fileName, reuseFirstSource){
    
}


ADTSBackChannelAudioFileServerMediaSubsession
::~ADTSBackChannelAudioFileServerMediaSubsession() {
}


FileSink* ADTSBackChannelAudioFileServerMediaSubsession::createNewSink(unsigned clientSessionId,
                                                                          unsigned& estBitrate)
{
    estBitrate = 8; // kbps, estimate
    
    //return ADTSAudioFileSource::createNew(envir(), fFileName);
    //Johnson_DBG
    printf("%s %s %d \n",__FILE__, __FUNCTION__ , __LINE__);
    return ADTSAudioFileSink::createNew(envir(), fFileName,  1024, 0);
}




// mimic
// function Boolean MediaSubsession::createSourceObjects(int useSpecialRTPoffset) in MediaSession.cpp
Boolean ADTSBackChannelAudioFileServerMediaSubsession::createSourceObjects(int useSpecialRTPoffset) {

//            if (strcmp(fCodecName, "MPEG4-GENERIC") == 0)
//            {
//                fReadSource = fRTPSource
//                = MPEG4GenericRTPSource::createNew(envir(), fRTPSocket,
//                                               fRTPPayloadFormat,
//                                               fRTPTimestampFrequency,
//                                               fMediumName,
//                                               attrVal_str("mode"),
//                                               attrVal_unsigned("sizelength"),
//                                               attrVal_unsigned("indexlength"),
//                                               attrVal_unsigned("indexdeltalength"));
//            }
    
    //a=fmtp: 96 ;profile-level-id=15;mode=AAC-hbr;config=1588;sizeLength=13;indexLength=3;indexDeltaLength=3;profile=1;bitrate=12000
    fReadSource = fRTPSource
    = MPEG4GenericRTPSource::createNew(envir(), fRTPSocket,
                                            fRTPPayloadFormat,
                                            fRTPTimestampFrequency,
                                            "audio",
                                            "AAC-hbr",
                                            13,
                                            3,
                                            3
                                            );

    if(fReadSource)
        return True;
    else
        return False; // an error occurred
}


// implment virtual function defined in OnDemandServerMediaSubsession.hh
// new virtual functions, defined by all subclasses
FramedSource* ADTSBackChannelAudioFileServerMediaSubsession::createNewStreamSource(unsigned clientSessionId,
                                            unsigned& estBitrate)
{ return NULL;}

// "estBitrate" is the stream's estimated bitrate, in kbps
RTPSink* ADTSBackChannelAudioFileServerMediaSubsession::createNewRTPSink(Groupsock* rtpGroupsock,
                                  unsigned char rtpPayloadTypeIfDynamic,
                                  FramedSource* inputSource)
{ return NULL;}



