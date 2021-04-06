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
struct PolyLine;

// This variable is really important!
static const float minPointDiff = 0.01;
static const float minPointDiffSq = minPointDiff * minPointDiff;

bool doIntersect(const PointType& p1, const PointType& q1, const PointType& p2, const PointType& q2);
int orientation(const PointType& p, const PointType& q, const PointType& r);
bool onSegment(const PointType& p, const PointType& q, const PointType& r);
bool collinearVecs(const PointType& p, const PointType& q, const PointType& r);
bool between(const PointType& p, const PointType& a, const PointType& b);
bool pointsDiffer(const PointType& a, const PointType& b, bool aprox = true);
bool overlap(const PolyLine& l1, const PolyLine& l2);
int simplifiedLine(const PolyLine& line_1, const PolyLine& line_2, PolyLine& ret);
int iComparePointOrder(const PointType& p1, const PointType& p2);
bool bComparePointOrder(const PointType& p1, const PointType& p2);
