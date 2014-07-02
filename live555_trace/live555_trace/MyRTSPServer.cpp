//
//  MyRTSPServer.cpp
//  live555_trace
//
//  Created by Liao KuoHsun on 2014/6/25.
//  Copyright (c) 2014年 albert. All rights reserved.
//

#include "MyRTSPServer.h"

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
#include "arpa/inet.h"

UsageEnvironment* env;

// To make the second and subsequent client for each stream reuse the same
// input stream as the first client (rather than playing the file from the
// start for each client), change the following "False" to "True":
Boolean reuseFirstSource = False;

static void announceStream(RTSPServer* rtspServer, ServerMediaSession* sms,
                           char const* streamName, char const* inputFileName); // fwd

int myRTSPServer(){
    // Begin by setting up our usage environment:
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
        //char const* inputFileName = "/Users/liaokuohsun/Downloads/slamtv10.264";
        //char const* audioFileName = "/Users/liaokuohsun/Downloads/test.aac";
        char const* inputFileName = "/Users/miuki001/Downloads/slamtv10.264";
        char const* audioFileName = "/Users/miuki001/Downloads/test.aac";
        
        reuseFirstSource = True;
        
        
        // Stream 1: H.264 video
        ServerMediaSession* sms
        = ServerMediaSession::createNew(*env, streamName, streamName,
                                        descriptionString);
        H264VideoFileServerMediaSubsession *sub =H264VideoFileServerMediaSubsession
            ::createNew(*env, inputFileName, reuseFirstSource);
        
        sms->addSubsession(sub);
        
        // Stream 2: AAC audio stream (ADTS-format file):
        ADTSAudioFileServerMediaSubsession *sub2 =ADTSAudioFileServerMediaSubsession
            ::createNew(*env, audioFileName, reuseFirstSource);
            
        sms->addSubsession(sub2);

        
        // Stream 3: backchannel AAC audio
        // TODO: modify here to support backchannel
        
        // use RTPSource to receive data and use ADTSAudioFileSink to save data to file
        // ADTSBackChannelAudioFileServerMediaSubsession
        ADTSAudioFileServerMediaSubsession *sub3 =ADTSAudioFileServerMediaSubsession
        ::createNew(*env, audioFileName, reuseFirstSource);
        
        sms->addSubsession(sub3);
        
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
