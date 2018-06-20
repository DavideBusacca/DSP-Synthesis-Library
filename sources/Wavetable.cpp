#ifndef WAVETABLE_BUSACCA_CPP
#define WAVETABLE_BUSACCA_CPP

#include "Wavetable.h"

// Enum which defines the waveform types which can be used with an instance of Waveform
std::string wavetableTypeString[4] = {"Sine", "Triangle", "Square", "Sawtooth"};

float wavetableType2Float(wavetableType type){
    // Cast function from wavetableType to float
	switch(type){
		case(sine):                    return 0.00f; break;
		case(triangle):               return 1.00f; break;
		case(squareWavetable):  return 2.00f; break;
		case(sawtooth):            return 3.00f; break;
			
		default:                        return 0.00f; break;
	}
}

wavetableType float2WavetableType(float x){
    // Cast function from float to wavetableType
	if	     (x <= 0.99f) return sine; 
	else if(x <= 1.99f) return triangle;
	else if(x <= 2.99f) return squareWavetable;
	else if(x <= 3.99f) return sawtooth;
	
	return sine;
}

std::string wavetableTypeToText(float value){ 
    // Cast function from wavetableType to string
	return wavetableTypeString[(int) (value)]; 
}

float textToWavetableType(const std::string& text){
    // Cast function from string to wavetableType
	if(text == "Sine") 	  return 0.00f;
	if(text == "Triangle")return 1.00f; 
	if(text == "Square")  return 2.00f; 
	if(text == "Sawtooth")return 3.00f; 
			
	return 0.00f; 
}

Wavetable::Wavetable(){
    // Class constructor for an instance of Wavetable. Sets the wavetable type to sine with starting phase equal to 0.
	setWavetableType (sine);
	setStartAngle   (0.0f);	
	
	updateData(); 	
}

Wavetable::~Wavetable(){ // Empty class destructor. 
}

int Wavetable::setParam(Wavetable::Param newParam){
    // The method setParam() modifies the current values of the instance's parameters. These values are read from another Param.
	setWavetableType(newParam.typeWavetable);
	setStartAngle(newParam.startAngle);
	
	return 1;
}


void Wavetable::setWavetableType(wavetableType type){
/*
    The method setWavetableType() modifies the current wavetable type. Only the waveforms defined as wavetableType are valid.
    Actually, only the 'intermediate' param is updated by calling this method. 
    However, the requirement of an update of the instance parameters is signaled by setting mNeedsUpdate to 1.
*/
	if(typeWavetable != type){
		mParam.typeWavetable = type;
		mNeedsUpdate = 1;
	}
}

void Wavetable::setStartAngle(float a){
/*
    The method setWavetableType() modifies the current starting phase of the waveform. Only parameters between 0 to 1 are valid.
    Actually, only the 'intermediate' param is updated. The requirement of an update of the instance parameters is signaled by setting mNeedsUpdate to 1.
*/
	if(startAngle != a){
		if(a >= 0 && a <= 1){
			mParam.startAngle = a;
			mNeedsUpdate = 1;
		}
	}
}

int  Wavetable::getNSamples() {
        return nSamples;       
    }
    
wavetableType Wavetable::getWavetableType() { 
        return typeWavetable; 
    }
    
float Wavetable::getStartAngle() { 
        return startAngle;
    }

bool Wavetable::getParam(Wavetable::Param* theParam){
    // The method getParam() can be used to obtain the current value of the instance's parameters.
	theParam->nSamples      = getNSamples();
	theParam->typeWavetable = getWavetableType();
	theParam->startAngle   = getStartAngle();
	
	return 1;
}

void Wavetable::getSample(float &sample, int index) { 
    // Insert in the variable sample the index-th sample of the table.
    sample = table[index]; 
}


bool Wavetable::updateData(){
    // Update the internal state of the instance. The parameter are updated, and the new wavetable is created.

	typeWavetable = mParam.typeWavetable;
	startAngle    = mParam.startAngle;
	
	switch(typeWavetable){
		case(sine) 	   		 : buildSineWavetable(); 	   break;
		case(triangle) 		 : buildTriangleWavetable(); break;
		case(squareWavetable): buildSquareWavetable();   break;
		case(sawtooth) 		 : buildSawtoothWavetable(); break;
	}
	
	mNeedsUpdate = 0;
	
	return 1;
}

void Wavetable::buildSineWavetable(){
    // Insert in the wavetable a sinusoidal waveform
	float delta = 2.0f * PI / nSamples;
	float angle = startAngle* 2.0f * PI; 
	for(int i = 0; i < nSamples; i++){
		table[i]  = sin(angle);
		angle += delta;
	}
}

void Wavetable::buildTriangleWavetable(){
    // Insert in the wavetable a triangular waveform
	int   angle = ((int)(startAngle*nSamples)) % nSamples;  
	float max   = (nSamples/2.0f) - 1.0f;
	
	float i = 0;
	for( ; i < nSamples/2; i++){
		table[angle] = ((i / max) - 1.0f) * 2.0f+1.0f;
		angle = (angle+1) % nSamples;
	}
	for( ; i < nSamples; i++){
		table[angle] = -((i / max) - 1.0f) * 2.0f+1.0f;
		angle = (angle+1) % nSamples;
	}
}

void Wavetable::buildSquareWavetable(){
    // Insert in the wavetable a square waveform
	int angle = ((int)(startAngle*nSamples)) % nSamples; 

	int i = 0;
	for( ; i < nSamples/2; i++){
		table[angle] = +1;
		angle = (angle+1) % nSamples;
	}
	for( ; i < nSamples; i++){
		table[angle] = -1;
		angle = (angle+1) % nSamples;
	}
}

void Wavetable::buildSawtoothWavetable(){
    // Insert in the wavetable a sawtooth waveform
	int angle = ((int)(startAngle*nSamples)) % nSamples; 
	
	int i, max = (nSamples/2);
	for(i = nSamples-1; i >= 0; --i){
		table[i]  = (((float)angle) / max) - (float)1.0;
		angle = (angle+1) % nSamples;
	}
}

void Wavetable::buildRampWavetable(){
    // Insert in the wavetable a ramp waveform
	int angle = ((int)(startAngle*nSamples)) % nSamples; 
	
	int i, max = (nSamples/2);
	for(i = 0; i < nSamples; ++i){
		table[i]  = (((float)angle) / max) - (float)1.0;
		angle = (angle+1) % nSamples;
	}
}

#endif //WAVETABLE_BUSACCA_CPP