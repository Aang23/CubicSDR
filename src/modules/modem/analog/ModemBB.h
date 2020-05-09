// Copyright (c) Charles J. Cliffe
// SPDX-License-Identifier: GPL-2.0+

#pragma once
#include "Modem.h"
#include <fstream>

class ModemBB : public Modem {
public:
    ModemBB();
    ~ModemBB();

    std::ofstream outputFile;
    long long lastSampleRate = 0;

    std::string getType();
    std::string getName();
    
    static ModemBase *factory();

    int checkSampleRate(long long sampleRate, int audioSampleRate);
    int getDefaultSampleRate();

    ModemKit *buildKit(long long sampleRate, int audioSampleRate);

    void disposeKit(ModemKit *kit);
    
    void demodulate(ModemKit *kit, ModemIQData *input, AudioThreadInput *audioOut);

    void startRecord();

    bool useSignalOutput();

private:
    
};