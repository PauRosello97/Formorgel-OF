#pragma once
class Tone
{
public:
	Tone() {};
	Tone(int _number, float _luminance) {
		number = _number;
		luminance = _luminance;
	}
	int number;
	float luminance;
};

