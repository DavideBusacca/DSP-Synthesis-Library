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

#ifndef TABLELOOKUP_BUSACCA_H
#define TABLELOOKUP_BUSACCA_H

#include "Wavetable.h"
#include "FilterIIR.h"
#include "ADSR.h"

enum TableLookUpMode {wavetableMode = 0, adsrMode};

/*
TABLE LOOK-UP CLASS
Generates a mono voice that can be uses to synthesize using TableLookUp.
A voice is a digital oscillator, which reproduces a periodic signal at a fixed frequency.
A Wavetable object which contains the waveform (or the ADSR) to be read is created.
The choice between the object Wavetable or ADSR is done using the mode parameter.

USAGE
The reading of the samples can be carried out using the process() or clockProcess() methods . 

PARAMETERS
frequency:	Defines the output frequency.
                It can be set using setFrequency().
sampleRate: Defines the sample rate.
			     It can be set using setSampleRate().
nSample:	Defines the number of samples in the wavetable to be read.
			    It can be set using setNSample().
mode:		Defines the usage mode. 
                Possible values are wavetableMode o adsrMode.
			    It can be set using setMode().
			
PARAMETERS DERIVED FROM WAVEFORM
typeWaveform
startAngle

PARAMETERS DERIVED FROM ADSR
attackTime
decayTime
sustainTime
susL
releaseTime

HANDLING OF THE OUTPUT FREQUENCY
The output frequency depends on the sample rate, on the number of samples in the reading table and on the step used to read the table's indexes.
The output frequency desired can be obtained by computing the reading step depending on the sample rate.
The following formula can be used:
	STEP = (OUTPUT FREQUENCY * NUMBER OF SAMPLES) / SAMPLE RATE
NB: It is assumed that the reading table contains exactly one cycle.
The next index is computed circularly using the modulo operation:
	NEXT INDEX = (CURRENT INDEX + STEP) % NUMBER OF SAMPLES
	
LINEAR INTERPOLATION BETWEEN SAMPLES
In order to reduce the noise added by the table look-up, the value of the wavetable is interpolated. 
The index computed contains a decimal part. This is used in the interpolation process.
The linear interpolation is carried out using a wheigting average between the values of the 2 indexes which are the nearest to the one computed.
*/
class TableLookUp{
public:
	TableLookUp();
	~TableLookUp();
	
	struct Param{		
		float frequency; 
		int   sampleRate, nSample;
		TableLookUpMode mode;		
		Wavetable::Param wavetableParam;
		ADSR::Param adsrParam;
	};
	
	int  setParam (TableLookUp::Param newParam);
	void setFrequency(float newFreq);
	void setSampleRate(int sr);
	void setNSample(int n);
	void setMode(TableLookUpMode m);
	
	void setWavetableType(wavetableType type);
	void setStartAngle(float a);
	
	void setAttackTime(float a);
	void setDecayTime(float d);
	void setSustainTime(float s);
	void setSusL(float l);
	void setReleaseTime(float r);
	
	bool  getParam (TableLookUp::Param* theParam);
	float getFrequency();
	int   getSampleRate();
	int   getNSample();
	TableLookUpMode setMode();
	
	wavetableType getWavetableType();
	float getStartAngle();
	

	void process (float** samples, int nSamples, int nChannels);
	void clockProcess (float &sample);
	
	void retrigger();
		
private:
	bool updateData();
	void getSample(float &sample, float index);
	
	bool mNeedsUpdate;
	
	TableLookUp::Param mParam; 	
	
	float frequency;		    //Output Frequency
	int   sampleRate; 		//Sample Rate
	int   nSample;  	  	    //Number of Samples of the Wavetable
	
	TableLookUpMode mode; 	//Usage Mode {wavetableMode, adsrMode}	
	
	Table *table;
	Wavetable wavetable;	
	ADSR adsr;
		
	
	//Storage of the current state
	float currentIndex, deltaSample;
	
	//Temporary variables used in getSample()
	int intIndex; float tempSample1, tempSample2, weight;

};

#endif //TABLELOOKUP_BUSACCA_H
