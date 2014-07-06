
#ifndef _ADTS_AUDIO_SOURCE_HH
#define _ADTS_AUDIO_SOURCE_HH

#ifndef _MPEG4_GENERIC_RTP_SOURCE_HH
#include "MPEG4GenericRTPSource.hh"
#endif

class ADTSAudioSource: public MPEG4GenericRTPSource {
public:

protected:
//  ADTSAudioSource(UsageEnvironment& env, Groupsock* RTPgs,
//	    unsigned char rtpPayloadFormat,
//	    unsigned rtpTimestampFrequency,
//	    char const* mediumName,
//	    char const* mode, unsigned sizeLength, unsigned indexLength,
//	    unsigned indexDeltaLength
//	    // add other parameters later
//	    );
	// virtual base class
  virtual ~ADTSAudioSource();

private:
  // redefined virtual functions:
  virtual Boolean isADTSAudioSource() const;

protected:
};

#endif
