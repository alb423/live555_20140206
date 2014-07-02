/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// Copyright (c) 1996-2014, Live Networks, Inc.  All rights reserved
// A test program that demonstrates how to stream - via unicast RTP
// - various kinds of file on demand, using a built-in RTSP server.
// main program

#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"

UsageEnvironment* env;

// To make the second and subsequent client for each stream reuse the same
// input stream as the first client (rather than playing the file from the
// start for each client), change the following "False" to "True":
Boolean reuseFirstSource = False;

// To stream *only* MPEG-1 or 2 video "I" frames
// (e.g., to reduce network bandwidth),
// change the following "False" to "True":
Boolean iFramesOnly = False;

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
			   char const* streamName, char const* inputFileName); // fwd

int main(int argc, char** argv) {
    TaskScheduler* scheduler = BasicTaskScheduler::createNew();
    env = BasicUsageEnvironment::createNew(*scheduler);
    
    UserAuthenticationDatabase* authDB = NULL;
    
    // Create the RTSP server:
    RTSPServer* rtspServer = RTSPServer::createNew(*env, 8554, authDB);
    if (rtspServer == NULL) {
        *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
        exit(1);
    }
    
    char const* descriptionString
    = "Session streamed by \"testOnDemandRTSPServer\"";
    
    // Set up each of the possible streams that can be served by the
    // RTSP server.  Each such stream is implemented using a
    // "ServerMediaSession" object, plus one or more
    // "ServerMediaSubsession" objects for each audio/video substream.
    
    // A H.264 video elementary stream:
    {
        char const* streamName = "h264ESVideoTest";
        char const* inputFileName = "/Users/liaokuohsun/Downloads/slamtv10.264";
        char const* audioFileName = "/Users/liaokuohsun/Downloads/test.aac";
        
        reuseFirstSource = True;
        
        ServerMediaSession* sms
        = ServerMediaSession::createNew(*env, streamName, streamName,
                                        descriptionString);
        H264VideoFileServerMediaSubsession *sub =H264VideoFileServerMediaSubsession
        ::createNew(*env, inputFileName, reuseFirstSource);
        
        sms->addSubsession(sub);
        
        // An AAC audio stream (ADTS-format file):
        ADTSAudioFileServerMediaSubsession *sub2 =ADTSAudioFileServerMediaSubsession
        ::createNew(*env, audioFileName, reuseFirstSource);
        
        sms->addSubsession(sub2);
        
        rtspServer->addServerMediaSession(sms);
        
        announceStream(rtspServer, sms, streamName, inputFileName);
    }
    
    // Also, attempt to create a HTTP server for RTSP-over-HTTP tunneling.
    // Try first with the default HTTP port (80), and then with the alternative HTTP
    // port numbers (8000 and 8080).
    
    if (rtspServer->setUpTunnelingOverHTTP(80) || rtspServer->setUpTunnelingOverHTTP(8000) || rtspServer->setUpTunnelingOverHTTP(8080)) {
        *env << "\n(We use port " << rtspServer->httpServerPortNum() << " for optional RTSP-over-HTTP tunneling.)\n";
    } else {
        *env << "\n(RTSP-over-HTTP tunneling is not available.)\n";
    }
    
    env->taskScheduler().doEventLoop(); // does not return
    
    return 0; // only to prevent compiler warning
}

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
			   char const* streamName, char const* inputFileName) {
  char* url = rtspServer->rtspURL(sms);
  UsageEnvironment& env = rtspServer->envir();
  env << "\n\"" << streamName << "\" stream, from the file \""
      << inputFileName << "\"\n";
  env << "Play this stream using the URL \"" << url << "\"\n";
  delete[] url;
}

// 20140703 albert.liao modified start
#pragma mark - Below is test for backchannel
//#include "ADTSAudioBufferSource.hh"
//#define TEST_WITH_NEW_CLASS_AUDIO_BUFFER_SOURCE 1

#pragma mark - MediaSubsession virtual function

FramedSource* MediaSubsession
::createNewStreamSource(unsigned /*clientSessionId*/, unsigned& estBitrate) {
    estBitrate = 96; //96; // kbps, estimate
    
#ifdef TEST_WITH_NEW_CLASS_AUDIO_BUFFER_SOURCE
    FramedSource *pTmp = ADTSAudioBufferSource::createNew(fParent.envir(), 1, 11 /*8000*/, 1);
    //ADTSAudioBufferSource* createNew(UsageEnvironment& env, unsigned int vProfile, unsigned int vSmaplingFrequenceIndex, unsigned int vChannels);
#else
    // The test file is get from http://www.live555.com/liveMedia/public/aac/
    //FramedSource *pTmp = ADTSAudioFileSource::createNew(fParent.envir(), "/Users/liaokuohsun/Work/AudioTestSample/test.aac");
    FramedSource *pTmp = ADTSAudioFileSource::createNew(fParent.envir(), "/Users/liaokuohsun/Downloads/1024.aac");
#endif
    return pTmp;
}

RTPSink* MediaSubsession
::createNewRTPSink(Groupsock* rtpGroupsock,
                   unsigned char rtpPayloadTypeIfDynamic,
                   FramedSource* inputSource) {
    
#ifdef TEST_WITH_NEW_CLASS_AUDIO_BUFFER_SOURCE
    ADTSAudioBufferSource* adtsSource = (ADTSAudioBufferSource*)inputSource;
#else
    ADTSAudioFileSource* adtsSource = (ADTSAudioFileSource*)inputSource;
#endif
    
    RTPSink *pTmp = MPEG4GenericRTPSink::createNew(fParent.envir(), rtpGroupsock,
                                                   rtpPayloadTypeIfDynamic,
                                                   adtsSource->samplingFrequency(),
                                                   "audio", "AAC-hbr", adtsSource->configStr(),
                                                   adtsSource->numChannels());
    return pTmp;
}

Boolean MediaSubsession::createSinkObjects(int useSpecialRTPoffset)
{
    do {
        // TODO: Fix me
        clientSessionId = 0;
        streamBitrate = 12000;
        
        fReadSource = createNewStreamSource(clientSessionId, streamBitrate);
        if(!fReadSource)
        {
            fprintf(stderr, "MediaSubsession::createSinkObjects()  fReadSource==NULL\n");
            break;
        }
        
        fRTPSink = createNewRTPSink(fRTPSocket, 96, fReadSource);
        
        if(!fRTPSink)
        {
            fprintf(stderr, "MediaSubsession::createSinkObjects()  fRTPSink==NULL\n");
            break;
        }
        
        return True;
    } while (0);
    
    return False; // an error occurred
}
// 20140703 albert.liao modified end
