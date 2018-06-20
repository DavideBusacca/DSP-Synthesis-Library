#ifndef WAVETABLE_BUSACCA_H
#define WAVETABLE_BUSACCA_H

#include "Table.h"
#include "BusaccaDefines.h"

// Enum which defines the waveform types which can be used with an instance of Waveform
enum  wavetableType {sine = 1, triangle, squareWavetable, sawtooth};
std::string wavetableTypeString[];

//Cast functions between wavetableType and float
float wavetableType2Float(wavetableType type);
wavetableType float2WavetableType(float x);

//Cast functions between wavetableType and std::string
std::string  wavetableTypeToText(float value);
float textToWavetableType(const std::string& text);

/*
WAVETABLE CLASS
An instance of Wavetable can be read by instances of other object, for example by a TableLookUp instance.
A wavetable contains a floating point array which represents exactly a waveform cycle. 

INHERITANCE
The derived class Wavetable inherits from the base class Table. 

USAGE
The method getSample() allows the reading access to specified index location samples.

PARAMETERS
nSamples:	        Defines the dimension of the array.
                        Initially, it could be set using setNSamples().
                        In the current implementation, its value is forced by the value in the macro TABLE_DIMENSION, declared in the class Table
startAngle:         Defines the starting phase of the generated waveform.
                        It can be selected using the method setStartAngle(). Its default value is 0.
typeWavetable:   Defines the type of waveform contained in the array.
                        It can be selected using the method setWavetableType(). Its default value is Sine.
			  
TABLE READING AND GENERATED FREQUENCY
The table indexes are supposed to be read in increasing order. Once that the maximum index is passed, it is necessary to reset the reading index value. This can be easily achieved by the modulo operation. 
The reading step of the table and its reproduction speed (i.e. sampling rate) determines the generated frequency.

WAVEFORMS
Functions which compute sinusoidal, triangular, square, sawtooth and ramp waveforms are implemented.	

SLAVE OBJECTS
All the update (calls to updateData()) are supposed to be called from the process() callback of the master object (i.e. TableLookUp)

*/
class Wavetable: public Table{
public:	
	Wavetable();
	~Wavetable();
	
	/*
	PARAM
    Param contains the variables which could be used in the interface of an instance of the class.
    A param is always used inside the instance to store the 'intermediate' values of the parameters, which will be used to update the internal variables of the instance.
    An additional param can be used outside the instance, to easily handle all the parameters accessing only one single struct.
    The method setParam() can be used to modify the current value of the instance's parameters.
    The method getParam() can be used to obtain the current value of the instance's parameters.
	*/
	struct Param{		
		int   nSamples; 
		float startAngle;
		wavetableType typeWavetable; 	
	};
		
    // Setter functions
	int  setParam(Wavetable::Param newParam);
	// void setNSamples(int n);                                   // this value is hard-coded
	void setWavetableType(wavetableType type);
	void setStartAngle(float a);
	
    // Getter functions
	bool getParam(Wavetable::Param* theParam);
	int  getNSamples();       
    
	wavetableType getWavetableType();
	float getStartAngle();
	

	//void triggerUpdateData() override { if(mNeedsUpdate) updateData(); }
	
	// Insert in the variable sample the index-th sample of the table.
	void getSample(float &sample, int index);
	
private:
	bool release();
	bool updateData() override; 
	
	//Functions which loads the waveforms into the table
	void buildSineWavetable();	
	void buildTriangleWavetable();	
	void buildSquareWavetable();	
	void buildSawtoothWavetable();
	void buildRampWavetable();
		
	bool mNeedsUpdate;                                         // If an instance needs to be updated mNeedsUpdate is set to 1.
	Wavetable::Param mParam;                               // Param containing the 'intermediate' parameters
		            
	float startAngle;			                                    // Starting phase of the waveform
	wavetableType typeWavetable;                         // Waveform type
	
	//float* wavetable; 			 
    
	// Variables inherited by the abstract class Table
	static const int nSamples = TABLE_DIMENSION;     // Number of samples for a waveform. Its value is hard-coded in the class Table
	float table[nSamples];                                       // Table containing the waveform
	
};

#endif //WAVETABLE_BUSACCA_H