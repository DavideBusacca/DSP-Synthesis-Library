#ifndef TABLE_BUSACCA_H
#define TABLE_BUSACCA_H

#define TABLE_DIMENSION 16384


class Table{
/*
    The class Table acts as base class for the derived classes: Wavetable, ADSR.
    It contains all the basic shared methods and variables which all the tables should implement.
*/
public:	
	Table()  {}
	~Table() {}
	
	/*virtual*/ void triggerUpdateData() { 
    // Checks whether the slave class need to update the parameters. If that is the case, they are updated.
        if(mNeedsUpdate) 
            updateData(); 
    } 
	virtual void getSample(float &sample, int index) { 
    // Insert in the variable sample the index-th sample of the table.
        sample = table[index]; 
    } 
	
protected:
	bool mNeedsUpdate;                                        // If an instance needs to be updated mNeedsUpdate is set to 1.
	
	static const int nSample = TABLE_DIMENSION;     // Number of samples
	float table[nSample];						               // Array containing the waveform
	
	virtual bool updateData() = 0;
};

#endif //TABLE_BUSACCA_H