#ifndef CopyChannel_BUSACCA_CPP
#define CopyChannel_BUSACCA_CPP

#include "CopyChannel.h"

CopyChannel::CopyChannel(){
	mParam.channelToPaste = 1;
	mParam.channelToCopy  = 0;		
	
	mNeedsUpdate = 1;
}		
CopyChannel::~CopyChannel() {} 	
				
int CopyChannel::setParam(CopyChannel::Param newParam){
	if(channelToPaste != newParam.channelToPaste)
		if (newParam.channelToPaste >= 0){
			mParam.channelToPaste = newParam.channelToPaste;
			mNeedsUpdate = 1;
		}
	if(channelToCopy != newParam.channelToCopy)
		if (newParam.channelToCopy >= 0){
			mParam.channelToCopy = newParam.channelToCopy;
			mNeedsUpdate = 1;
		}
	
	return 1;
}	 
void CopyChannel::setCopy(int channelPaste, int channelCopy){
	setChannelToPaste(channelPaste);
	setChannelToCopy(channelCopy);
}

void CopyChannel::setChannelToPaste(int ch){
	if(ch != channelToPaste)
		if (ch >= 0){
			mParam.channelToPaste = ch;
			mNeedsUpdate = 1;
		}
}

void CopyChannel::setChannelToCopy(int ch){
	if(ch != channelToCopy)
		if (ch >= 0){
			mParam.channelToCopy = ch;
			mNeedsUpdate = 1;
		}
}
												
bool CopyChannel::getParam(CopyChannel::Param* theParam){
	theParam->channelToPaste = getChannelToPaste();
	theParam->channelToCopy  = getChannelToCopy ();
	
	return 1;
}	
														

int CopyChannel::process (float** samples, int nSamples, int nChannels){		
	if(mNeedsUpdate) updateData();
	
	if(channelToCopy < nChannels && channelToPaste < nChannels){
		for(int i = 0; i < nSamples; i++){
			clockProcess(samples[channelToPaste][i], samples[channelToCopy][i]);
		}
	}

	return 1;
}

void CopyChannel::clockProcess (float &pasteSample, float const &copySample){
	pasteSample = copySample;
}

bool CopyChannel::updateData(){
	channelToPaste = mParam.channelToPaste;
	channelToCopy  = mParam.channelToCopy;
	
	mNeedsUpdate = 0;
	
	return 1;
}		

#endif //CopyChannel_BUSACCA_CPP