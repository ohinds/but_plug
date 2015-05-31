#pragma once

#include <vector>
#include "public.sdk/source/vst2.x/audioeffectx.h"

class DelayCompensation : public AudioEffectX {

 public:

  DelayCompensation(audioMasterCallback audio_master);
  ~DelayCompensation();

  virtual void processReplacing(
    float** inputs, float** outputs, VstInt32 sample_frames);

  virtual void processDoubleReplacing(
    double** inputs, double** outputs, VstInt32 sample_frames);

  virtual void setProgramName(char* name);
  virtual void getProgramName(char* name);

  // Parameters
  virtual void setParameter(VstInt32 index, float value);
  virtual float getParameter(VstInt32 index);
  virtual void getParameterLabel(VstInt32 index, char* label);
  virtual void getParameterDisplay(VstInt32 index, char* text);
  virtual void getParameterName(VstInt32 index, char* text);

  virtual bool getEffectName(char* name);
  virtual bool getVendorString(char* text);
  virtual bool getProductString(char* text);
  virtual VstInt32 getVendorVersion();

 protected:

  template <typename X>
  void processXReplacing(X** inputs, X** outputs, VstInt32 sample_frames);

  char program_name[kVstMaxProgNameLen + 1];

  int samples_to_delay;
  std::vector<double> buffer;
  size_t cur_pos;
};
