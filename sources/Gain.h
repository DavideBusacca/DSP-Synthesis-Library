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