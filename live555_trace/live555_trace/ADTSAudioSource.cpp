
#include "ADTSAudioSource.hh"
#include "MPEG4GenericRTPSource.hh"
//MPEG4GenericRTPSink
//::MPEG4GenericRTPSink(UsageEnvironment& env, Groupsock* RTPgs,
//                      u_int8_t rtpPayloadFormat,
//                      u_int32_t rtpTimestampFrequency,
//                      char const* sdpMediaTypeString,
//                      char const* mpeg4Mode, char const* configString,
//                      unsigned numChannels)
//: MultiFramedRTPSink(env, RTPgs, rtpPayloadFormat,
//                     rtpTimestampFrequency, "MPEG4-GENERIC", numChannels),
//fSDPMediaTypeString(strDup(sdpMediaTypeString)),
//fMPEG4Mode(strDup(mpeg4Mode)), fConfigString(strDup(configString)) {
//

//FileSink(env, fid, bufferSize, perFrameFileNamePrefix),

//ADTSAudioSource::ADTSAudioSource(UsageEnvironment& env, Groupsock* RTPgs,
//	    unsigned char rtpPayloadFormat,
//	    unsigned rtpTimestampFrequency,
//	    char const* mediumName,
//	    char const* mode, unsigned sizeLength, unsigned indexLength,
//	    unsigned indexDeltaLength)
////: MPEG4GenericRTPSource(env, RTPgs,
////                                   rtpPayloadFormat,
////                                   rtpTimestampFrequency,
////                                   mediumName,
////                                   mode, sizeLength, indexLength,
////                                   indexDeltaLength)
//{
//    MPEG4GenericRTPSource::createNew(env, RTPgs,
//                          rtpPayloadFormat,
//                          rtpTimestampFrequency,
//                          mediumName,
//                          mode, sizeLength, indexLength,
//                          indexDeltaLength
//                          // add other parameters later
//                                     );
//
//}

ADTSAudioSource::~ADTSAudioSource() {
}

Boolean ADTSAudioSource::isADTSAudioSource() const {
  return True;
}
