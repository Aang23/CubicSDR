// Copyright (c) Charles J. Cliffe
// SPDX-License-Identifier: GPL-2.0+

#include "ModemBB.h"
#include <volk/volk.h>
#include "CubicSDR.h"
#include <ctime>

ModemBB::ModemBB()
{
    startRecord();
}

ModemBB::~ModemBB()
{
    outputFile.close();
}

std::string ModemBB::getType()
{
    return "baseband";
}

std::string ModemBB::getName()
{
    return "BB";
}

ModemBase *ModemBB::factory()
{
    return new ModemBB;
}

ModemKit *ModemBB::buildKit(long long sampleRate, int audioSampleRate)
{
    ModemKit *kit = new ModemKit;
    kit->sampleRate = sampleRate;
    kit->audioSampleRate = audioSampleRate;
    return kit;
}

void ModemBB::startRecord()
{
    time_t current_time = time(0);
    std::tm *time = localtime(&current_time);
    std::string path = wxGetApp().getConfig()->getRecordingPath() + "/baseband_" + std::to_string(lastSampleRate) + "_" + std::to_string(time->tm_hour) + "-" + std::to_string(time->tm_min) + "-" + std::to_string(time->tm_sec) + ".raw";
    outputFile = std::ofstream(path, std::ios_base::binary);
}

void ModemBB::disposeKit(ModemKit *kit)
{
    delete kit;
}

int ModemBB::checkSampleRate(long long sampleRate, int /* audioSampleRate */)
{
    if (lastSampleRate != sampleRate)
    {
        lastSampleRate = sampleRate;
        outputFile.close();
        startRecord();
    }
    return sampleRate;
}

int ModemBB::getDefaultSampleRate()
{
    return 14000;
}

bool ModemBB::useSignalOutput()
{
    return false;
}

void ModemBB::demodulate(ModemKit * /* kit */, ModemIQData *input, AudioThreadInput * /* audioOut */)
{
    if (outputFile.is_open())
    {
        size_t bufSize = input->data.size();

        for (size_t i = 0; i < bufSize; i++)
        {
            outputFile.write((char *)&input->data[i], sizeof(liquid_float_complex));
        }
    }
}
