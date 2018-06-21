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
