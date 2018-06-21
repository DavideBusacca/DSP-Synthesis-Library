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

#ifndef GAIN_BUSACCA_H
#define GAIN_BUSACCA_H

/*
GAIN CLASS
Applies a multiplication factor to a signal (either audio or control)

Usage
The factor can be applied using the method process().

PARAMETERS
level	Defines the multiplication factor to be applied. 
		The factor is real number with  legal values in the interval{0, 1}
		It can be modified using setLevel().
		
SMOOTHING AMPLITUDE VARIATION
In order to avoid clipping due to sudden changes in the amplitude of the signal between frames, the modification of the multiplication factor is done gradually over a whole frame (instead of applying the final factor value from the beggining of the frame).
*/
class Gain{
public:
	Gain();
	~Gain();
	
	struct Param{float level;};
	
	int setParam (Gain::Param newParam);	
	void setLevel(float l);
	
	bool getParam (Gain::Param* theParam);
	float getLevel();
	
	void process (float** samples, int nSamples, int nChannels);
	
	void clockProcess (float &sample);

	
	
private:	
	bool updateData(int nSamples);
	bool mNeedsUpdate;
	
	Gain::Param mParam;
 	
	float level;	//Multiplication Factor 
	
	
	float tempLevel, delta; 			
	
};

#endif //GAIN_BUSACCA_H
