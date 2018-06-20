# DSP-Synthesis-Library
Basic DSP library for synthesis developed during my undergraduate internship at LIM (Università Statale di Milano).

The library is organized in modules, where each one carries out individual tasks.
In the following, the modules are introduced.

### Table Look-Up Synthesis
- **Wavetable**: Builds a wavetable and allows to access to its content using indexes. Derived from Table.
- **TableLookUp**: Reads a wavetable. Assuming that the table contains exactly one cycle, it allows to choose the frequency being played.

### Volume Controller
- **Copy Channel**: Copy source channels in destination channel. Allows to the conversion of mono signals into stereo.
- **Gain**: Applies a multiplicative factor to a mono signal.
- **Panner**: Applies multiplicative factors on stereo signal.

### Additional Code
- **Table**: Abstract class from which the Wavetable module inherits from.
- **BusaccaLibrary**: Includes the header files.
- **BusaccaDefinitions**: Includes definitions.
- **Redwood**: Code utilities taken from the Redwood tutorials ( http://www.redwoodaudio.net/Tutorials/juce_for_vst_development__intro.html ). Useful for Juce projects.
