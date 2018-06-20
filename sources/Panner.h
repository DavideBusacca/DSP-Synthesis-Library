#ifndef PANNER_BUSACCA_H
#define PANNER_BUSACCA_H

#include <cmath>
#include "CopyChannel.h"
/*
PANNER CLASS
The mono signal is copied on all the channels (if required),then an individual multiplier factor is applied on each one.
The even channels are considered as left, whereas the odd ones are considered as right. If the total number of channel is odd, the last channel is used as central.

USAGE
The method process() allows to apply the multiplication factors.

PARAMETERS
panCostant:	Constant used to compute the multipliers factors.
                    Has range {0,1} (0 left, 0.5 center, 1 right).
                    It can be set using setPanCostant().
needsCopy:	Enables/disables the copy of the channel using the object CopyChannel.
                    It can be set using setCopy(). The source and destination channels need to be specified.

COMPUTATION OF STEREO FACTORS - CHARLES DOGE'S METHOD 
Based on the notation that the perceived intensity decreases following the power of the amplitude.
The square root is applied to the amplitude values in order to use a scale similar to the perceptual one.
Viene applicata la radice quadrata al valore d'ampiezza per utilizzare una scala di valori che segua la percezione:
	LEFT CONSTANT = SQRT(panCostant)
	RIGHT CONSTANT   = SQRT(1 - panCostant)
*/
class Panner{
public:
	Panner();	
	~Panner();
					
	struct Param{
		float panCostant;
		bool  needsCopy;
		CopyChannel::Param copyParam;
	};
	
	int  setParam(Panner::Param newParam);
	void setCopy(bool copyBool, int channelPaste, int channelCopy);
	void setPanCostant(float p);
	void setNeedsCopy(bool n);
	void setChannelToPaste(int p);
	void setChannelToCopy (int c);
			
	bool  getParam(Panner::Param* theParam);
	float getPanCostant();
	bool  getNeedsCopy(); 
	int   getChannelToPaste();
	int	  getChannelToCopy ();
		
															
	int process (float** samples, int nSamples, int nChannels);
	void clockProcess (float &sample);
	void clockProcess (float &sample, int channel);
		
private:
	bool updateData();

	void chooseCostant(int channel);
	
	bool mNeedsUpdate;
	
	Panner::Param mParam; 
	float panCostant; 	
	bool  needsCopy;	
	
	CopyChannel copy;
	
	float leftCostant, rightCostant, tempCostant;
};

#endif //PANNER_BUSACCA_H