//
//  ADTSAudioFileSink.cpp
//  live555_trace
//
//  Created by albert on 2014/7/3.
//  Copyright (c) 2014年 albert. All rights reserved.
//

// reference AMRAudioFileSink.cpp
#include "ADTSAudioFileSink.h"
#include "AMRAudioFileSink.hh"
#include "AMRAudioSource.hh"
#include "OutputFile.hh"

////////// ADTSAudioFileSink //////////

ADTSAudioFileSink
::ADTSAudioFileSink(UsageEnvironment& env, FILE* fid, unsigned bufferSize,
                   char const* perFrameFileNamePrefix)
: FileSink(env, fid, bufferSize, perFrameFileNamePrefix),
fHaveWrittenHeader(False) {
}

ADTSAudioFileSink::~ADTSAudioFileSink() {
}

ADTSAudioFileSink*
ADTSAudioFileSink::createNew(UsageEnvironment& env, char const* fileName,
                            unsigned bufferSize, Boolean oneFilePerFrame) {
    do {
        FILE* fid;
        char const* perFrameFileNamePrefix;
        if (oneFilePerFrame) {
            // Create the fid for each frame
            fid = NULL;
            perFrameFileNamePrefix = fileName;
        } else {
            // Normal case: create the fid once
            fid = OpenOutputFile(env, fileName);
            if (fid == NULL) break;
            perFrameFileNamePrefix = NULL;
        }
        
        return new ADTSAudioFileSink(env, fid, bufferSize, perFrameFileNamePrefix);
    } while (0);
    
    return NULL;
}

Boolean ADTSAudioFileSink::sourceIsCompatibleWithUs(MediaSource& source) {
    // The input source must be a AMR Audio source:
    return source.isAMRAudioSource();
}

void ADTSAudioFileSink::afterGettingFrame(unsigned frameSize,
                                         unsigned numTruncatedBytes,
                                         struct timeval presentationTime) {
    //ADTSAudioSource* source = (ADTSAudioSource*)fSource;

    // write file here
    
    // Call the parent class to complete the normal file write with the input data:
    FileSink::afterGettingFrame(frameSize, numTruncatedBytes, presentationTime);
}
