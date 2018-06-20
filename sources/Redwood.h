#ifndef REDWOOD_GOODNESS
#define REDWOOD_GOODNESS

//Taken from http://www.redwoodaudio.net/Tutorials/juce_for_vst_development__intro6.html

inline String FloatArrayToString(float* fData, int numFloat)
{//Return String of multiple float values separated by commas 
	String result = "";
	if (numFloat<1)
		return result;
	for (int i = 0; i<(numFloat - 1); i++)
		result << String(fData[i]) << ",";//Use juce::String initializer for each value
	result << String(fData[numFloat - 1]);
	return result;
}
inline int StringToFloatArray(String sFloatCSV, float* fData, int maxNumFloat)
{//Return is number of floats copied to the fData array
 //-1 if there were more in the string than maxNumFloat
	StringArray Tokenizer;
	int TokenCount = Tokenizer.addTokens(sFloatCSV, ",", "");
	int resultCount = (maxNumFloat <= TokenCount) ? maxNumFloat : TokenCount;
	for (int i = 0; i<resultCount; i++)//only go as far as resultCount for valid data
		fData[i] = Tokenizer[i].getFloatValue();//fill data using String class float conversion
	return ((TokenCount <= maxNumFloat) ? resultCount : -1);
}

inline String GetStrValue(float v) { return String(v);};
inline String GetBypassStr(float v) { return (v != 0.0f) ? "Bypassed" : "Enabled";};
#endif //REDWOOD_GOODNESS