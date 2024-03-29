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

#ifndef GAIN_BUSACCA_CPP
#define GAIN_BUSACCA_CPP

#include "Gain.h"

Gain::Gain(){
	mParam.level = 0.0;
	level = mParam.level;
	mNeedsUpdate = 1;
}			
Gain::~Gain() {}

int Gain::setParam (Gain::Param newParam){
	setLevel(newParam.level);
	return 1;
}		
void Gain::setLevel(float l){
	if (l != this->level)	
		if (l >= 0 && l <= 1){
			mParam.level = l;
			mNeedsUpdate = 1;
		}
}

bool Gain::getParam (Gain::Param* theParam){ 
    theParam->level = getLevel(); return 1; 
}
float Gain::getLevel(){ 
    return level; 
}

void Gain::process (float** samples, int nSamples, int nChannels){
	if(mNeedsUpdate) updateData(nSamples); else delta = 0;
	
	tempLevel = level;
	for(int channel = 0; channel < nChannels; channel++){
		level = tempLevel;
		for(int i = 0; i < nSamples; i++)
			clockProcess(samples[channel][i]);
	}

}

void Gain::clockProcess (float &sample){
	level += delta;
	sample *= level; 
}

bool Gain::updateData(int nSamples){ 
	delta = (mParam.level - level)/nSamples;
	mNeedsUpdate = 0;
	
	return 1;
}

#endif //GAIN_BUSACCA_CPP
