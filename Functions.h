#pragma once
#include "PolyDetector.h";
#include "geom.h"
#include <algorithm>
#include <cstdint>
#include <string>
#include <cmath>
#include "ofMain.h"
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <vector>

using PointType = vec;

bool doIntersect(const PointType& p1, const PointType& q1, const PointType& p2, const PointType& q2);
int orientation(const PointType& p, const PointType& q, const PointType& r);
bool onSegment(const PointType& p, const PointType& q, const PointType& r);
bool collinearVecs(const PointType& p, const PointType& q, const PointType& r);