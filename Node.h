#pragma once
#include "ofMain.h"

class Node
{
	public:
		Node(float x, float y);
		Node();
		bool getIsNull();
		void draw();

		bool isNull;
		ofVec2f pos;
};

