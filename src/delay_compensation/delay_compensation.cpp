#include "delay_compensation.h"

using std::vector;

namespace {
  const int MAX_DELAY_SAMPLES = 1000;
}

AudioEffect* createEffectInstance(audioMasterCallback audio_master) {
  return new DelayCompensation(audio_master);
}

DelayCompensation::DelayCompensation(audioMasterCallback audio_master)
  : AudioEffectX(audio_master, 1, 1)
  , samples_to_delay(0)
  , cur_pos(0) {
  setNumInputs(1);
  setNumOutputs(1);
  setUniqueID('DelayCompensation');
  canProcessReplacing();
  canDoubleReplacing();

  buffer.resize(MAX_DELAY_SAMPLES);

  vst_strncpy(program_name, "Default", kVstMaxProgNameLen);
}

DelayCompensation::~DelayCompensation() {}

void DelayCompensation::setProgramName(char* name) {
  vst_strncpy(program_name, name, kVstMaxProgNameLen);
}

void DelayCompensation::getProgramName(char* name) {
  vst_strncpy(name, program_name, kVstMaxProgNameLen);
}

void DelayCompensation::setParameter(VstInt32 index, float value) {
  if (value < 0.) {
    value = 0.;
  }

  if (value > 1.) {
    value = 1.;
  }

  samples_to_delay = MAX_DELAY_SAMPLES * value;
  cur_pos = 0;
}

float DelayCompensation::getParameter(VstInt32 index) {
  return samples_to_delay;
}

void DelayCompensation::getParameterName(VstInt32 index, char* label) {
  vst_strncpy(label, "Samples to delay", kVstMaxParamStrLen);
}

void DelayCompensation::getParameterDisplay(VstInt32 index, char* text) {
  sprintf(text, "%d", samples_to_delay);
}

void DelayCompensation::getParameterLabel(VstInt32 index, char* label) {
  vst_strncpy(label, "samples", kVstMaxParamStrLen);
}

bool DelayCompensation::getEffectName(char* name) {
  vst_strncpy(name, "DelayCompensation", kVstMaxEffectNameLen);
  return true;
}

bool DelayCompensation::getProductString(char* text) {
  vst_strncpy(text, "DelayCompensation", kVstMaxProductStrLen);
  return true;
}

bool DelayCompensation::getVendorString(char* text) {
  vst_strncpy(text, "None", kVstMaxVendorStrLen);
  return true;
}

VstInt32 DelayCompensation::getVendorVersion() {
  return 1;
}

void DelayCompensation::processReplacing(
  float** inputs, float** outputs, VstInt32 sample_frames) {
  processXReplacing<float>(inputs, outputs, sample_frames);
}

void DelayCompensation::processDoubleReplacing(
  double** inputs, double** outputs, VstInt32 sample_frames) {
  processXReplacing<double>(inputs, outputs, sample_frames);
}

template <typename X>
void DelayCompensation::processXReplacing(X** inputs, X** outputs,
                                          VstInt32 sample_frames) {
  X* in  =  inputs[0];
  X* out = outputs[0];

  while (--sample_frames >= 0) {
    if (samples_to_delay == 0) {
      (*out++) = (*in++);
      continue;
    }

    (*out++) = buffer[cur_pos];
    buffer[cur_pos] = (*in++);

    cur_pos++;
    if (cur_pos == samples_to_delay) {
      cur_pos = 0;
    }
  }
}
