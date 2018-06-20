#ifndef TABLELOOKUP_BUSACCA_CPP
#define TABLELOOKUP_BUSACCA_CPP

#include "TableLookUp.h"

//Constructor
TableLookUp::TableLookUp(){ 
	setFrequency  (1000.0f);
	setSampleRate (44100);
	setNSample    (16384);
	setMode		  (wavetableMode);
	
	//Setting wavetable's object parameters
	wavetable.getParam( &(mParam.wavetableParam) ); 	
    //updating param with the parameters of the wavetable instance. Needed in order to have coherent initialization
    
	//Intialize internal state
	retrigger();
	
	mNeedsUpdate = 1;
}


//Destructor 
TableLookUp::~TableLookUp() { } 

int TableLookUp::setParam (TableLookUp::Param newParam){
	setFrequency (newParam.frequency);
	setSampleRate(newParam.sampleRate);
	setNSample   (newParam.nSample);
	
	wavetable.setParam(newParam.wavetableParam);
	adsr.setParam     (newParam.adsrParam);
	
	mNeedsUpdate = 1;
	
	return 1;
}								

void TableLookUp::setFrequency(float newFreq){
	if(newFreq != this->frequency)
		if(newFreq >= 0 && newFreq <= 20000){
			mParam.frequency = newFreq;
			mNeedsUpdate = 1;
		}
}

void TableLookUp::setSampleRate(int sr){
	if(sr != this->sampleRate){
		mParam.sampleRate = sr;
		adsr.setSampleRate(sr);
		mNeedsUpdate = 1;	
	}
}


void TableLookUp::setNSample(int n){
	if(n != this->nSample){
		mParam.nSample = n;
		mNeedsUpdate = 1;
		//wavetable.setNSample(n); //NSample is hardcoded in this version
	}
}


void TableLookUp::setMode(TableLookUpMode m){
	if(m != this->mode){
		mParam.mode = m;
		mNeedsUpdate = 1;
	}
}

void TableLookUp::setWavetableType(wavetableType type) {
	wavetable.setWavetableType(type);
	mNeedsUpdate = 1;
}
void TableLookUp::setStartAngle(float a) {
	wavetable.setStartAngle(a);
	mNeedsUpdate = 1;
}

void TableLookUp::setAttackTime(float a){
	adsr.setAttackTime(a);
	mNeedsUpdate = 1;
}
void TableLookUp::setDecayTime(float d){
	adsr.setDecayTime(d);
	mNeedsUpdate = 1;
}
void TableLookUp::setSustainTime(float s){
	adsr.setSustainTime(s);
	mNeedsUpdate = 1;
}
void TableLookUp::setSusL(float l){
	adsr.setSusL(l);
	mNeedsUpdate = 1;
}
void TableLookUp::setReleaseTime(float r){
	adsr.setReleaseTime(r);
	mNeedsUpdate = 1;
}


bool TableLookUp::getParam (TableLookUp::Param* theParam){ 
	theParam->frequency  = getFrequency(); 
	theParam->sampleRate = getSampleRate();
	theParam->nSample 	 = getNSample();
	
	wavetable.getParam( &(theParam->wavetableParam) );
	adsr.getParam     ( &(theParam->adsrParam) );
	return 1; 
}

float TableLookUp::getFrequency() {
    return mParam.frequency;
}
int TableLookUp::getSampleRate(){
     return mParam.sampleRate;
}
int TableLookUp::getNSample()   {
    return mParam.nSample;
}

TableLookUpMode TableLookUp::setMode() { 
    return mParam.mode; 
}

wavetableType TableLookUp::getWavetableType(){
    return wavetable.getWavetableType();
}
float TableLookUp::getStartAngle() {
    return wavetable.getStartAngle();
}

void TableLookUp::process (float** samples, int nSamples, int nChannels){
	if(mNeedsUpdate) updateData();

	if(mode == wavetableMode){	
		table = &wavetable;
	}
	else if(mode == adsrMode){
		table = &adsr;
	}
	
	for(int i = 0; i < nSamples; i++){
		clockProcess(samples[0][i]);	//MONO: only the first channel is written
	}	
	
	
	
}

void TableLookUp::clockProcess (float &sample){
	getSample(sample, currentIndex);
	//Index updating (using modulo)
	currentIndex = (float)fmod(currentIndex + deltaSample, nSample);
}
    
void TableLookUp::retrigger() { 
    currentIndex = 0.0; 
}

bool TableLookUp::updateData(){
	wavetable.triggerUpdateData();
	adsr.triggerUpdateData();
	
	mode       = mParam.mode; 
	sampleRate = mParam.sampleRate;
	nSample    = mParam.nSample;
		
	if(mode == adsrMode) frequency = adsr.getFrequency();
		else  			 frequency = mParam.frequency;
	
	deltaSample  = frequency * nSample / sampleRate;
			
	mNeedsUpdate = 0;
	
	return 1;
}	

void TableLookUp::getSample(float &sample, float index){
	//Without Interpolation
	//wavetable.getSample(sample, index); //cast
		
	//Using Linear Interpolation
	weight = modf (index , &index); //weight contains now the decimal part
	intIndex = index; //cast
	
	table->getSample(tempSample1, intIndex);
	table->getSample(tempSample2, (intIndex+1)%nSample );
	
	sample = weight*tempSample1 + (1-weight)*tempSample2;
}

#endif //TABLELOOKUP_BUSACCA_CPP