#ifndef PANNER_BUSACCA_CPP
#define PANNER_BUSACCA_CPP

#include "Panner.h"

Panner::Panner(){
	setPanCostant(0.5);
	setNeedsCopy(true);
	copy.getParam( & (mParam.copyParam) );
}		

Panner::~Panner() {}
	
int Panner::setParam(Panner::Param newParam){
	setPanCostant(newParam.panCostant);
	setCopy(newParam.needsCopy, newParam.copyParam.channelToPaste, newParam.copyParam.channelToCopy);
		
	return 1;
}	 
void Panner::setCopy(bool copyBool, int channelPaste, int channelCopy){
	setNeedsCopy(copyBool);
	copy.setCopy(channelPaste, channelCopy);
	
	mNeedsUpdate = 1;
}

void Panner::setPanCostant(float p){
	if(panCostant != p)
		if (p >= 0 &&  p <= 1){
			mParam.panCostant = p;
			mNeedsUpdate = 1;
		}
}
void Panner::setNeedsCopy(bool n){
	mParam.needsCopy = n;
	mNeedsUpdate = 1;
}

void Panner::setChannelToPaste(int p){
    copy.setChannelToPaste(p); 
}

void Panner::setChannelToCopy (int c){
    copy.setChannelToCopy(c); 
}
		
bool Panner::getParam(Panner::Param* theParam){
	theParam->panCostant = getPanCostant();
	theParam->needsCopy  = getNeedsCopy();
	copy.getParam(& (theParam->copyParam) );
	
	return 1;
}	


float Panner::getPanCostant(){
    return panCostant;
}
bool  Panner::getNeedsCopy()  {
    return needsCopy;
} 
int Panner::getChannelToPaste(){ 
    return copy.getChannelToPaste();
}
int Panner::getChannelToCopy (){ 
    return copy.getChannelToCopy();  
}
	
int Panner::process (float** samples, int nSamples, int nChannels){		
	if(mNeedsUpdate) updateData();
			
	if(needsCopy){
		copy.process(samples, nSamples, nChannels);
	}
	
	if(nChannels%2) nChannels--; //se il numero di canali è dispari, l'ultimo canale non viene processato (viene lasciato centrale)
	
	for(int channel = 0; channel < nChannels; channel++){
		chooseCostant(channel);
		for(int i = 0; i < nSamples; i++){
			clockProcess(samples[channel][i]);
		}
	}
	
	return 1;
}

void Panner::clockProcess (float &sample){
	sample *= tempCostant;
}

void Panner::clockProcess (float &sample, int channel){
	if(channel%2 == 0)
		sample *= leftCostant;  
	else
		sample *= rightCostant;
}

void Panner::chooseCostant(int channel){
	if(channel%2 == 0)
			tempCostant = leftCostant; 
		else
			tempCostant = rightCostant;
}

bool Panner::updateData(){
	panCostant = mParam.panCostant;
	needsCopy  = mParam.needsCopy;
	
	// triggerUpdateData() //not necessary because is already handled inside process()
		
	leftCostant  = sqrt(1-panCostant);
	rightCostant = sqrt(panCostant);
	
	mNeedsUpdate = 0;
	
	return 1;
}	

#endif //PANNER_BUSACCA_CPP