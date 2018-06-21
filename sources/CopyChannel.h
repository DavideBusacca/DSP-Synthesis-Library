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

#ifndef CopyChannel_BUSACCA_H
#define CopyChannel_BUSACCA_H

class CopyChannel{
public:
	CopyChannel();
	~CopyChannel();  	
	
	struct Param{
		int channelToPaste, channelToCopy;
	};
	
	int  setParam(CopyChannel::Param newParam);
	void setCopy(int channelPaste, int channelCopy);
	void setChannelToPaste(int ch);
	void setChannelToCopy (int ch);
	
	bool CopyChannel::getParam(CopyChannel::Param* theParam);
	int  getChannelToPaste() { return channelToPaste; }
	int  getChannelToCopy () { return channelToCopy;  }
	
	int process (float** samples, int nSamples, int nChannels);
	void clockProcess (float &pasteSample, float const &copySample);
	
	void triggerUpdateData(){ if(mNeedsUpdate) updateData(); }
	
private:
	bool updateData();
	
	bool mNeedsUpdate;
	
	CopyChannel::Param mParam;
	int channelToPaste, channelToCopy; 
};

#endif //CopyChannel_BUSACCA_H
