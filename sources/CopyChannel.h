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