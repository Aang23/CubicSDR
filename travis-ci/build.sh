# Liquid-DSP
mkdir jgaeddert/
git clone https://github.com/jgaeddert/liquid-dsp.git jgaeddert/liquid-dsp
pushd .
cd jgaeddert/liquid-dsp/
./bootstrap.sh
./configure
make
sudo make install
popd

# Soapy SDR
mkdir pothosware/
git clone https://github.com/pothosware/SoapySDR.git pothosware/SoapySDR
mkdir pothosware/SoapySDR-build
cmake pothosware/SoapySDR pothosware/SoapySDR-build
pushd .
cd pothosware/SoapySDR-build
make
sudo make install
popd

# CubicSDR
mkdir cjcliffe/CubicSDR-build
cmake cjcliffe/CubicSDR cjcliffe/CubicSDR-build
pushd .
cd cjcliffe/CubicSDR-build
make
