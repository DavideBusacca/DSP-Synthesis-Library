/*
 * Copyright (C) 2017  Busacca Davide
 *
 * This file is part of DSP-Synthesis-Library
 *
 * DSP-Synthesis-Library is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the Free
 * Software Foundation (FSF), either version 3 of the License, or (at your
 * option) any later version.
 *
 * DSP-Synthesis-Library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the Affero GNU General Public License
 * version 3 along with DSP-Synthesis-Library.  If not, see http://www.gnu.org/licenses/
 */

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
