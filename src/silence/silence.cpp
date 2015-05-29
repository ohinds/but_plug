#include "silence.h"

AudioEffect* createEffectInstance(audioMasterCallback audio_master) {
  return new Silence(audio_master);
}

Silence::Silence(audioMasterCallback audio_master)
  : AudioEffectX(audio_master, 1, 1) {
  setNumInputs(2);
  setNumOutputs(2);
  setUniqueID('Silence');
  canProcessReplacing();
  canDoubleReplacing();

  vst_strncpy(program_name, "Default", kVstMaxProgNameLen);
}

Silence::~Silence() {}

void Silence::setProgramName(char* name) {
  vst_strncpy(program_name, name, kVstMaxProgNameLen);
}

void Silence::getProgramName(char* name) {
  vst_strncpy(name, program_name, kVstMaxProgNameLen);
}

void Silence::setParameter(VstInt32 index, float value) {
}

float Silence::getParameter(VstInt32 index) {
  return 0.0;
}

void Silence::getParameterName(VstInt32 index, char* label) {
  vst_strncpy(label, "Nothing", kVstMaxParamStrLen);
}

void Silence::getParameterDisplay(VstInt32 index, char* text) {
  dB2string(0, text, kVstMaxParamStrLen);
}

void Silence::getParameterLabel(VstInt32 index, char* label) {
  vst_strncpy(label, "0", kVstMaxParamStrLen);
}

bool Silence::getEffectName(char* name) {
  vst_strncpy(name, "Silence", kVstMaxEffectNameLen);
  return true;
}

bool Silence::getProductString(char* text) {
  vst_strncpy(text, "Silence", kVstMaxProductStrLen);
  return true;
}

bool Silence::getVendorString(char* text) {
  vst_strncpy(text, "None", kVstMaxVendorStrLen);
  return true;
}

VstInt32 Silence::getVendorVersion() {
  return 1;
}

void Silence::processReplacing(
  float** inputs, float** outputs, VstInt32 sample_frames) {
  float* in1  =  inputs[0];
  float* in2  =  inputs[1];
  float* out1 = outputs[0];
  float* out2 = outputs[1];

  while (--sample_frames >= 0) {
    (*out1++) = 0;
    (*out2++) = 0;
  }
}

void Silence::processDoubleReplacing(
  double** inputs, double** outputs, VstInt32 sample_frames) {
  double* in1  =  inputs[0];
  double* in2  =  inputs[1];
  double* out1 = outputs[0];
  double* out2 = outputs[1];

  while(--sample_frames >= 0) {
    (*out1++) = 0;
    (*out2++) = 0;
  }
}
