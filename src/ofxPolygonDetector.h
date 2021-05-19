
#pragma once

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

static const float minPointDiff = 0.001;
static const float minPointDiffSq = minPointDiff * minPointDiff;

struct PolyLine;
struct ofxPolygonDetector;

struct vec
{
    float x, y;

    vec() {}

    vec(float a, float b) : x(a), y(b) {}
    vec(float a) : x(a), y(a) {}
    vec(float a, float b, float c) : x(a), y(b) {}

    vec& sub(const vec& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    vec& add(const vec& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    vec& mul(const float& v)
    {
        x *= v;
        y *= v;
        return *this;
    }
    vec& div(const float& v)
    {
        x /= v;
        y /= v;
        return *this;
    }

    float squaredlen() const
    {
        return x * x + y * y;
    }

    float squaredist(const vec& v) const
    {
        return vec(*this).sub(v).squaredlen();
    }

    static void line(const vec& p, const vec& q, float& a, float& b, float& c)
    {
        // Line AB represented as a*x + b*y = c
        a = p.y - q.y;
        b = q.x - p.x;
        c = (p.x - q.x) * p.y + (q.y - p.y) * p.x;
    }

    static float lineDist(float a, float b, float c, const vec& p)
    {
        if (a + b == 0.0f) return std::numeric_limits<float>::max();;
        return fabs(a * p.x + b * p.y + c) / sqrtf(a * a + b * b);
    }

    static float lineDist(const vec& la, const vec& lb, const vec& p)
    {
        float a, b, c;
        line(la, lb, a, b, c);
        return lineDist(a, b, c, p);
    }
};

using CycleSet = std::set<uint32_t>;
using PointType = vec;

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


enum class RmLinesType : int
{
    TakenTwice = 0, // rm lines taken twice
    Collinear, // dissolve collinear lines
    NoPointNeigh, // rm lines with one point not having neighbors
    PointConsumed, // point has 2 lines connected all taken
};

struct PolyCycle
{
    CycleSet idx;
    int startIdx, lastIdx;
    bool isClosed;
    bool fine;
    bool canBeClosed(ofxPolygonDetector& pd, uint32_t idToAdd) const;
    bool contains(uint32_t idP) const;
    bool AddLineId(ofxPolygonDetector& pd, uint32_t id);
    string idxToString() const;
    string toString() const;
    bool Equals(const PolyCycle& p) const;
    bool convex(ofxPolygonDetector& pd) const;
    bool pointConsumed(ofxPolygonDetector& pd, uint32_t pid) const;
    bool accepted(ofxPolygonDetector& pd);
};

using PolyCycles = std::vector<PolyCycle>;

struct PolyLine
{
    PointType a, b;

    PolyLine() {}
    PolyLine(const PointType& aP, const PointType& bP) : a(aP), b(bP) {}

    std::vector<uint32_t> intersections;
    std::set<uint32_t> intersectedLines;
    PointType center;
    uint32_t id = 0;
    uint32_t test0 = 0, test1 = 0;
    int32_t origLine = -1;
    int32_t attr0 = -1; // used for testing
    bool ignore = false;
    uint32_t took = 0;
    uint32_t processed = 0;
    uint32_t aIdx = 0, bIdx = 0;
    uint32_t lastDissolveStep = 0;
    void calcCenter();
    bool HasCommonIdxPoints(const PolyLine& line) const;
    void SortIntersectionsList(ofxPolygonDetector& pd);
    bool IntersectionPoint(const PolyLine& line, PointType& pos) const;
    bool LineLineIntersectionPoint(const PolyLine& line, PointType& pos) const;
    void CalculateFirstAndLastPoint();
    static bool bCompareLineOrder(const PolyLine& l1, PolyLine& l2);
    static int iCompareLineOrder(const PolyLine& l1, PolyLine& l2);
    string neighToString(ofxPolygonDetector& pd, uint32_t* retNNeigh = nullptr) const;
    string toString(ofxPolygonDetector& pd) const;
    uint32_t numNeigh(ofxPolygonDetector& pd) const;
    uint32_t numIntersections(ofxPolygonDetector& pd) const;
    uint32_t canBeRemoved(ofxPolygonDetector& pd, RmLinesType type) const;
    PolyLine& mul(float m);
    PolyLine& add(const PointType& p);
    void setIgnore(ofxPolygonDetector& pd, const char* msg);
    bool contains(const PointType& point) const;
    bool contains(const PolyLine& line) const;
    bool collinear(const PolyLine& l) const;
    uint32_t minPid() const;
    uint32_t maxPid() const;
    int32_t commonPid(const PolyLine& l) const;
    uint32_t otherPid(uint32_t pid) const;
    bool compareNeigh(ofxPolygonDetector& pd, uint32_t nid1, uint32_t nid2) const;
    bool sortNeigh(ofxPolygonDetector& pd) const;
    uint32_t& incTook(ofxPolygonDetector& pd);
    bool betweenNeighbors(ofxPolygonDetector& pd, const PolyLine& l1, const PolyLine& l2) const;
};

struct PolyPol
{
    vector<PointType> p;
    PointType c;
    size_t firstIdx = 0;
    ofColor color;
    PolyCycle cycle;
    uint32_t id;
    uint32_t dissolveStep = 0;
    double _area;
    uint32_t GetCount() const;
    void CalculateFirstAndLastPoint();
    bool Minus(const PolyPol& other);
    void addLine(const PolyLine& l);
    int roundArea();
    bool addPointChecked(const PointType& v);
    void setColor(ofColor color);
    void draw();
    PointType center();
    double TriangleArea(ofxPolygonDetector& pd);
};

struct ofxPolygonDetector
{
    using LineVector = std::vector<PolyLine>;
    using LineList = std::list<PolyLine>;
    using PolyVector = std::vector<PolyPol>;

    // members {
    PolyCycles _cycles;

    //std::vector<CycleSet> processed;

    LineVector
        origLines, // from user
        lines; // active lines
    PolyVector polys;

    std::map<uint32_t, std::vector<uint32_t>> _neighbors; // key: lid, val: vec(neighborLine)
    std::map<uint32_t, std::vector<uint32_t>> collinearLineMap; // key: lid, val: vec(collinearLine)

    std::vector<PointType> intersectionPoints;
    std::map<uint32_t, std::vector<uint32_t>> pointToLines; // key: pid, val: list of nids
    std::unordered_map<uint32_t, int32_t> lineIdToIdx; // key: lid, val: index in lines

    uint32_t dissolveCount = 0;

    void reset();
    void AddLine(const PolyLine& line);
    bool DetectPolygons();
    PolyVector& getPolys() { return polys; }

    bool addPointToLine(uint32_t pid, uint32_t lid);

    PolyLine* findLine(uint32_t id, bool useIgnore = true);
    PolyLine* findLine(uint32_t pidA, uint32_t pidB, bool useIgnore = true);
    PolyLine* findOrigLine(uint32_t id);

    uint32_t GetPolyCount() const { return (uint32_t)polys.size(); };
    void SortLines();

    // The order of operations
    void RemoveZeroLengthLines();
    void RemoveOverlappings(); 
    uint32_t DetectAllIntersections();
    bool CreateLines();
    bool FindPolys();
    void SimplifyPolys(double smaller_polygon_length);

    bool BuildCycle(uint32_t id, PolyCycle cycle); // as value!

    PolyLine newLine(uint32_t i, uint32_t j, PolyLine& origLine);

    // collinearity
    void setCollinear(uint32_t l1, uint32_t l2);
    bool CollinearIdx(uint32_t l1, uint32_t l2);
    bool CollinearIdx(const PolyLine& l1, const PolyLine& l2);

    bool rmLines(RmLinesType type);
    bool rmEarPoints();

    // dissolve
    bool dissolveCollinearLine(PolyLine& l);
    bool dissolveCollinear(PolyLine& l1, PolyLine& l2);
    bool dissolve();

    void dumpLines(const char* msg, bool useIgnore = false);

    
};
