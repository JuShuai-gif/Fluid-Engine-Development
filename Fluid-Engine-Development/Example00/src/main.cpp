#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstring>
#include <string>
#include <thread>
using namespace std;
using namespace chrono;

#define M_PI 3.1415926

const size_t kBufferSize = 80;
const char* kGrayScaleTable = " .:-=+*#%@";
const size_t kGrayScaleTableSize = sizeof(kGrayScaleTable) / sizeof(char);

// every frame update position and v
void updateWave(const double timeInterval,double* x,double* speed) {
	(*x) += timeInterval * (*speed);

	if ((*x) > 1.0f)
	{
		(*speed) *= -1.0f;
		(*x) = 1.0f + timeInterval * (*speed);
	}
	else if((*x) < 0.0f){
		(*speed) *= -1.0f;
		(*x) = timeInterval * (*speed);
	}
}

void accumulateWaveToHeightField(
	const double x,
	const double waveLength,
	const double maxHeight,
	array<double, kBufferSize>* heightField) {
	const double quarterWaveLength = 0.25f * waveLength;
	const int start = static_cast<int>((x - quarterWaveLength) * kBufferSize);
	const int end = static_cast<int>((x + quarterWaveLength) * kBufferSize);

	for (int i = start; i < end; ++i)
	{
		int iNew = i;
		if (i < 0)
		{
			iNew = -i - 1;
		}
		else if (i >= static_cast<int>(kBufferSize)) {
			iNew = 2 * kBufferSize - i - 1;
		}

		double distance = fabs((i + 0.5f) / kBufferSize - x);
		double height = maxHeight * 0.5f * (cos(min(distance * M_PI / quarterWaveLength, M_PI)) + 1.0f);
		(*heightField)[iNew] += height;
	}
}

void Draw(const array<double, kBufferSize>& heightField) {
	string buffer(kBufferSize, ' ');

	for (size_t i = 0; i < kBufferSize; ++i)
	{
		double height = heightField[i];
		size_t tableIndex = min(static_cast<size_t>(floor(kGrayScaleTableSize * height)), kGrayScaleTableSize - 1);
		buffer[i] = kGrayScaleTable[tableIndex];
	}

	for (size_t i = 0; i < kBufferSize; ++i)
	{
		printf("\b");
	}

	printf("%s", buffer.c_str());
	fflush(stdout);
}

int main() {
	const double waveLengthX = 0.8f;
	const double waveLehgthY = 1.2f;

	const double maxHeightX = 0.5f;
	const double maxHeightY = 0.4f;

	double x = 0.0f;
	double y = 1.0f;
	double speedX = 1.0f;
	double speedY = -0.5f;

	const int fps = 100;
	const double timeInterval = 1.0f / fps;

	array<double, kBufferSize> heightField;

	for (size_t i = 0; i < 1000; ++i)
	{
		updateWave(timeInterval, &x, &speedX);
		updateWave(timeInterval, &y, &speedY);

		for (double& height : heightField)
		{
			height = 0.0f;
		}
		accumulateWaveToHeightField(x, waveLengthX, maxHeightX, &heightField);
		accumulateWaveToHeightField(x, waveLengthX, maxHeightX, &heightField);
		Draw(heightField);
		this_thread::sleep_for(milliseconds(1000 / fps));
	}
	printf("\n");
	fflush(stdout);


	return 0;
}