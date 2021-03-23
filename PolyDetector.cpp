
#include <assert.h>
#include "PolyDetector.h"

#include <set>

#if 0
#undef logoutf
#define logoutf(...) do {} while(false)
#endif

#define arToStr(arg) #arg

const char* RmLinesTypeStr(RmLinesType type)
{
    switch (type)
    {
    case RmLinesType::TakenTwice: return "TakenTwice";
    case RmLinesType::Collinear: return "Collinear";
    case RmLinesType::NoPointNeigh: return "NoPointNeigh";
    case RmLinesType::PointConsumed: return "PointConsumed";
    }
    return "UNKN";
}

bool PolyLine::contains(const PolyLine& line) const
{
    return contains(line.a) && contains(line.b);
}

bool PolyLine::contains(const PointType& point) const
{
    return between(point, a, b);
}

bool PolyLine::collinear(const PolyLine& line) const
{
    return !doIntersect(a, b, line.a, line.b);
}

bool PolyLine::IntersectionPoint(const PolyLine& line, PointType& pos) const
{
    return LineLineIntersectionPoint(line, pos);
}

static float Area(const PointType& a, const PointType& b, const PointType& c)
{
    return 0.5 * ((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}


bool PolyLine::bCompareLineOrder(const PolyLine& l1, PolyLine& l2)
{
    return iCompareLineOrder(l1, l2) < 0;
}
int PolyLine::iCompareLineOrder(const PolyLine& l1, PolyLine& l2)
{
    int result = iComparePointOrder(l1.a, l2.a);

    if (result == 0)
    {
        // in case lines share first point
        // we must order the lines by its slope

        auto dx1 = l1.b.x - l1.a.x;
        auto dy1 = l1.b.y - l1.a.y;
        auto dx2 = l2.b.x - l2.a.x;
        auto dy2 = l2.b.y - l2.a.y;

        // by definition of first and last point we are sure that dy > 0

        if (dx1 > 0 && dx2 < 0)
            // line 1 in 1st quadrant, line 2 in 2nd quadrant
            // this means line 2 cames first
            return 1;

        if (dx1 < 0 && dx2>0)
            // line 1 in 2nd quadrant, line 2 in 1st quadrant
            // this means line 1 cames first
            return -1;

        if (dx1 == 0) {
            // first line is vertical
            if (dx2 > 0)
                // second line in 1st quadrant
                // first line is previous
                return -1;

            if (dx2 < 0)
                // second line in 2nd quadrant
                // second line is previous
                return 1;
            // this should no happen
            return 0;
        }

        if (dx2 == 0) {
            // second line is vertical
            if (dx1 > 0)
                // first line in 1st quadrant
                // second line is previous
                return 1;

            if (dx1 < 0)
                // first line in 2nd quadrant
                // first line is previous
                return -1;

            // this should not happen
            return 0;
        }


        // calculate the slopes
        double m1 = dy1 / dx1;
        double m2 = dy2 / dx2;
        // line 1 and line 2 in 2nd quadrant
        if (m1 > m2)
            return -1;
        if (m1 < m2)
            return 1;

        // in this case we have the same slope in both lines,
        // which means that both lines are coincident.
        return 0;
    }

    return result;
}



bool PolyLine::HasCommonIdxPoints(const PolyLine& line) const
{
    return
        aIdx == line.aIdx ||
        aIdx == line.bIdx ||
        bIdx == line.aIdx ||
        bIdx == line.bIdx;
}

// https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
bool PolyLine::LineLineIntersectionPoint(const PolyLine& line, PointType& pos) const
{
    auto& c = line.a;
    auto& d = line.b;

    // Line AB represented as a1x + b1y = c1
    double a1 = b.y - a.y;
    double b1 = a.x - b.x;
    double c1 = a1 * (a.x) + b1 * (a.y);

    // Line CD represented as a2x + b2y = c2
    double a2 = d.y - c.y;
    double b2 = c.x - d.x;
    double c2 = a2 * (c.x) + b2 * (c.y);

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return false;
    }

    double x = (b2 * c1 - b1 * c2) / determinant;
    double y = (a1 * c2 - a2 * c1) / determinant;
    pos = PointType(x, y, 0.0f);

    return true;
}

void PolyLine::SortIntersectionsList(PolyDetector& pd)
{
    std::sort(intersections.begin(), intersections.end(), [&pd, this](const uint32_t& p1, const uint32_t& p2) {
        return pd.intersectionPoints[p1].squaredist(a) < pd.intersectionPoints[p2].squaredist(a);
    });
}

PolyLine PolyDetector::newLine(uint32_t i, uint32_t j, PolyLine& origLine)
{
    PolyLine l;

    l.aIdx = origLine.intersections[i];
    l.bIdx = origLine.intersections[j];
    l.a = intersectionPoints[l.aIdx];
    l.b = intersectionPoints[l.bIdx];
    l.origLine = origLine.id;
    l.lastDissolveStep = origLine.lastDissolveStep;
    l.attr0 = origLine.attr0;
    l.calcCenter();

    return l;
}

bool PolyDetector::CreateLines()
{

    uint32_t n = 0;
    for (auto& l : origLines)
    {
        l.id = n++;
    }

    // prior to removing overlapping, one must
    // remove all zero length line, otherwise the results
    // will be unpredictable
    RemoveZeroLengthLines();

    // then we must remove line overlapping
    RemoveOverlappings();

    // finally we detect intersections between lines
    int intersection_count = DetectAllIntersections();
    if (intersection_count == 0)
        return true;

    // sweep all lines
    lines.clear();
    for (auto& line : origLines)
    {
        if (line.ignore) continue;

        // check if current line has intersections
        if (line.intersections.size() >= 2)
        {
            line.SortIntersectionsList(*this);

            for (uint32_t i = 1; i < line.intersections.size(); ++i)
            {
                bool foundDup = false;
                auto
                    aIdx = line.intersections[i - 1],
                    bIdx = line.intersections[i];

                assert(aIdx != bIdx);

                auto& p1 = intersectionPoints[aIdx];
                auto& p2 = intersectionPoints[bIdx];
                if (!pointsDiffer(p1, p2))
                {
                    assert(pointsDiffer(p1, p2));
                }

                assert(p1.squaredist(line.a) <= p2.squaredist(line.a));

                for (auto& lDup : lines)
                {
                    if ((lDup.minPid() == std::min(aIdx, bIdx)) &&
                        lDup.maxPid() == std::max(aIdx, bIdx))
                    {
                        foundDup = true;
                    }
                }

                if (foundDup)
                {
                    
                }
                else if (!pointsDiffer(p1, p2))
                {
                }
                else
                {
                    lines.push_back(newLine(i - 1, i, line));
                }
            }
        }
    }

    for (uint32_t i = 0; i < lines.size(); i++)
    {
        auto& l1 = lines[i];

        for (uint32_t j = i + 1; j < lines.size(); j++)
        {
            auto& l2 = lines[j];

            auto aIdx1 = l1.minPid();
            auto bIdx1 = l1.maxPid();

            auto aIdx2 = l2.minPid();
            auto bIdx2 = l2.maxPid();
        }
    }


    return true;
}

void PolyDetector::dumpLines(const char* msg, bool useIgnore)
{
    for (auto& l : lines)
    {
        if (useIgnore && l.ignore) continue;
    }
}

/***
* @desc removes all lines with zero length
*/
void PolyDetector::RemoveZeroLengthLines(void)
{
    for (auto it = origLines.begin(); it != origLines.end(); )
    {
        if (!pointsDiffer(it->a, it->b)) // find a zero length line
            it = origLines.erase(it);
        else
            ++it;
    }
}

bool PolyDetector::addPointToLine(uint32_t pid, uint32_t lid)
{
    auto& v = pointToLines[pid];
    if (std::find(v.begin(), v.end(), lid) == v.end())
    {
        v.push_back(lid);
        return true;
    }
    return false;
}

/***
* @descr removes line overlappings
* @note must be called before applying Bentley-Ottmann algorithm
*/
void PolyDetector::RemoveOverlappings()
{
    uint32_t i, j, count = uint32_t(origLines.size());

    for (auto& l : origLines)
    {
        l.calcCenter();
    }

    PolyLine line;

    // lets find overlapping lines
    uint32_t countBefore = count;
    for (i = 0; i < count; i++)
    {
        auto& line_i = origLines[i];

        for (j = i + 1; j < count; j++)
        {
            auto& line_j = origLines[j];
            if (overlap(line_i, line_j))
            {
                int ret = simplifiedLine(line_i, line_j, line);

                if (ret == 1)
                {
                    origLines.erase(origLines.begin() + j);
                    j--;
                    count--;
                }
                else
                {
                    if (ret != 2)
                    {
                        line.id = line_i.id;

                        // must remove both line_i and line_j and add a new one
                        origLines.erase(origLines.begin() + j);

                        line.calcCenter();
                        origLines.push_back(std::move(line));
                    }

                    // must remove line_i
                    origLines.erase(origLines.begin() + i);

                    // update counters
                    i--;
                    count--;

                    // skip inner loop an go to next step of outer loop
                    break;
                }
            }
        }
    }
}

uint32_t PolyDetector::DetectAllIntersections()
{
    uint32_t ret = 0;
    size_t counter = origLines.size();
    PointType intersection;

    intersectionPoints.clear();
    collinearLineMap.clear();

    for (auto& l : origLines)
    {
        l.calcCenter();
    }

    // sort to always have the same results
    std::sort(origLines.begin(), origLines.end(), PolyLine::bCompareLineOrder);

    uint32_t n = 0;
    for (auto& l : origLines)
    {
        l.id = n++;
        l.intersections.clear();
        l.intersectedLines.clear();
    }

    // intersected lines: remove lines with only one intersection
    for (uint32_t i = 0; i < counter; i++)
    {
        auto& l1 = origLines[i];
        for (uint32_t j = i + 1; j < counter; j++)
        {
            auto& l2 = origLines[j];
            if (doIntersect(l1.a, l1.b, l2.a, l2.b))
            {
                l1.intersectedLines.insert(l2.id);
                l2.intersectedLines.insert(l1.id);
            }
        }
    }

    for (uint32_t i = 0; i < counter; i++)
    {
        auto& l1 = origLines[i];
        if (l1.intersectedLines.size() == 1)
        {

            for (uint32_t j = 0; j < counter; j++)
            {
                if (i != j)
                {
                    auto& l2 = origLines[j];

                    for (auto it = l2.intersectedLines.begin(); it != l2.intersectedLines.end(); )
                    {
                        if (*it == l1.id)
                        {
                            it = l2.intersectedLines.erase(it);
                            i = 0; // recheck all lines
                        }
                        else
                            ++it;
                    }
                }
            }

            l1.intersectedLines.clear();
        }
    }

    // intersection points
    std::set<std::pair<uint32_t, uint32_t>> took;
    for (auto& l1 : origLines)
    {
        for (auto& lid2 : l1.intersectedLines)
        {
            auto& l2 = origLines[lid2];

            if (took.find(std::make_pair(l1.id, l2.id)) == took.end())
            {
                intersection = vec(0);
                if (l1.IntersectionPoint(l2, intersection)) // checks if not parallel
                {
                    uint32_t intersectionIdx = uint32_t(intersectionPoints.size());

                    // Check if the same intersection point exists
                    bool dupPoint = false;
                    for (uint32_t pi = 0; pi < intersectionPoints.size(); ++pi)
                    {
                        auto& p = intersectionPoints[pi];
                        if (!pointsDiffer(p, intersection))
                        {
                            dupPoint = true;
                            intersectionIdx = pi;
                            intersection = p;
                            break;
                        }
                    }

                    if (!dupPoint)
                    {
                        intersectionPoints.push_back(intersection);
                    }

                    for (auto& l : { &l1, &l2 })
                    {
                        if (std::find(l->intersections.begin(), l->intersections.end(), intersectionIdx) != l->intersections.end())
                        {
                        }
                        else
                        {
                            l->intersections.push_back(intersectionIdx);
                        }
                    }

                    took.insert(std::make_pair(l1.id, l2.id));
                    took.insert(std::make_pair(l2.id, l1.id));

                    ret++;
                }
            }
        }
    }
    
    uint32_t nCol = 0;
    std::vector<uint32_t> pids;

    uint32_t times = 0;
    bool ok = false;
    do
    {
        took.clear();

        ok = true;

        for (auto& l1 : origLines)
        {
            if (l1.ignore) continue;
            if (l1.intersections.size() < 2) continue;

            float a, b, c;
            vec::line(vec(l1.a.x, l1.a.y), vec(l1.b.x, l1.b.y), a, b, c);
            if (a + b == 0.0f)
            {
                continue;
            }

            for (auto& l2 : origLines)
            {
                if (l2.ignore) continue;
                if (l2.intersections.size() < 2) continue;

                {

                    took.insert(std::make_pair(l1.id, l2.id));
                    took.insert(std::make_pair(l2.id, l1.id));

                    if (l1.id == l2.id) continue;
                    if (l2.intersections.empty()) continue;
                    assert(&l1 != &l2);

                    uint32_t nFound = 0;
                    float maxLineDist = 0;
                    pids.clear();
                    for (auto& pid1 : l1.intersections)
                    {
                        for (auto& pid2 : l2.intersections)
                        {
                            if (pid1 == pid2)
                            {
                                nFound++;
                                pids.push_back(pid1);
                            }

                            float d = vec::lineDist(a, b, c, vec(intersectionPoints[pid2].x, intersectionPoints[pid2].y));
                            if (d > maxLineDist)
                                maxLineDist = d;
                        }
                    }

                    if (nFound >= 2)
                    {
                        ok = false;

                        if (maxLineDist <= minPointDiff)
                        {
                            // TODO: merge point of l2 into l1
                            uint32_t nMerged = 0;
                            for (auto& pid : l2.intersections)
                            {
                                if (std::find(l1.intersections.begin(), l1.intersections.end(), pid) == l1.intersections.end())
                                {
                                    l1.intersections.push_back(pid);
                                    nMerged++;
                                }
                            }

                            l2.intersections.clear();
                            l2.a = l2.b = l2.center = vec(0);
                            l2.ignore = true;

                            nCol++;
                        }
                        else
                        {

                            // remove them
                            uint32_t nRm1 = 0, nRm2 = 0;
                            for (auto& pid : pids)
                            {
                                for (auto it = l1.intersections.begin(); it != l1.intersections.end();)
                                {
                                    if (*it == pid)
                                    {
                                        it = l1.intersections.erase(it);
                                        nRm1++;
                                    }
                                    else
                                        ++it;
                                }
                                for (auto it = l2.intersections.begin(); it != l2.intersections.end();)
                                {
                                    if (*it == pid)
                                    {
                                        it = l2.intersections.erase(it);
                                        nRm2++;
                                    }
                                    else
                                        ++it;
                                }
                            }
                            auto keepPid = pids[0];
                            l1.intersections.push_back(keepPid);
                            l2.intersections.push_back(keepPid);
                        }
                    }
                }
            }
        }
        times++;
    } while (!ok);

    return ret;
}

void PolyLine::CalculateFirstAndLastPoint()
{
    if (!bComparePointOrder(a, b))
    {
        std::swap(a.x, b.x);
        std::swap(a.y, b.y);

        std::swap(aIdx, bIdx);
    }
}

/***
* @descr sort the lines
*/
void PolyDetector::SortLines(void)
{
    for (auto& line : lines)
    {
        if (!line.ignore)
            line.CalculateFirstAndLastPoint();
    }
    std::sort(lines.begin(), lines.end(), PolyLine::bCompareLineOrder);
}

std::string PolyLine::toString(PolyDetector& pd) const
{
    uint32_t nNeigh = 0;
    std::string neighStr = neighToString(pd, &nNeigh);
    std::string str = "L{[" + std::to_string(id) + "] nNeigh:";
    str += std::to_string(nNeigh);

    str += " [";
    str += neighToString(pd);
    str += "] [P";
    str += std::to_string(aIdx < bIdx ? aIdx : bIdx);
    str += " P";
    str += std::to_string(aIdx < bIdx ? bIdx : aIdx);
    str += ']';

    str += " took:" + std::to_string(took);

    if (ignore)
        str += " ING!";

    str += '}';

    return str;
}

std::string PolyLine::neighToString(PolyDetector& pd, uint32_t* retNNeigh) const
{
    auto search = pd._neighbors.find(id);
    if (search == pd._neighbors.end())
        return "[]";
    std::string str;
    uint32_t nNeigh = 0;
    for (auto& n : search->second)
    {
        auto l = pd.findLine(n);
        if (l)
        {
            str += std::to_string(n) + " ";
            nNeigh++;
        }
    }
    if (!str.empty())
        str.pop_back();
    if (retNNeigh)
        *retNNeigh = nNeigh;
    return str;
}

uint32_t PolyLine::numNeigh(PolyDetector& pd) const
{
    auto search = pd._neighbors.find(id);
    if (search == pd._neighbors.end())
        return 0;
    uint32_t ret = 0;
    for (auto& n : search->second)
    {
        auto l = pd.findLine(n);
        if (l)
            ret++;
    }
    return ret;
}
uint32_t PolyLine::numIntersections(PolyDetector& pd) const
{
    return uint32_t(intersections.size());
}

uint32_t PolyLine::canBeRemoved(PolyDetector& pd, RmLinesType type) const
{
    assert(!ignore);

    if (type == RmLinesType::NoPointNeigh)
    {
        // Remove lines having points with no neighbors
        for (auto& abId : { aIdx, bIdx })
        {
            auto& neigh = pd.pointToLines[abId];
            if (neigh.size() <= 1) // including self
            {
                return true;
            }

            // check also ignore flag
            uint32_t nNeigh = 0;
            for (auto& n : neigh)
            {
                auto l = pd.findLine(n);
                if (l && l->id != id)
                    nNeigh++;
            }
            if (nNeigh == 0)
            {
                return true;
            }
        }
    }
    if (type == RmLinesType::TakenTwice)
    {
        if (took >= 2)
        {
            for (auto& lid : pd._neighbors[id])
            {
                auto l = pd.findLine(lid);
                if (l && l->id != id)
                {
                    if (l->took < 0)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }

    return false;
}

bool PolyDetector::DetectPolygons()
{
    polys.clear();

    if (!CreateLines())
    {
        return false;
    }

    while (true)
    {
        bool stop = false;

        SortLines();

        if (!FindPolys())
        {
            return false;
        }

        SimplifyPolys(0.0);

        auto beforeCount = dissolveCount;

        if (!dissolve())
            stop = true;

        if (stop)
            break;
    }

    return true;
}

PointType PolyPol::center()
{
    if (p.empty())
        return PointType(0);

    PointType c(0);
    for (auto& pt : p)
        c.add(pt);
    c.div(p.size());

    return c;
}

/***
* @desc simplifies current polygon, subtracting <p>, in case there are
*       an single relationship between them
* @return true if polygon were changed, false otherwise
*/
bool PolyPol::Minus(const PolyPol& other)
{
    for (auto itOther = other.p.begin(); itOther != other.p.end(); ++itOther)
    {
        for (auto it = p.begin(); it != p.end();)
        {
            if (!pointsDiffer(*itOther, *it))
            {
                it = p.erase(it);
            }
            else
                ++it;
        }
    }
    return true;
}

void PolyPol::CalculateFirstAndLastPoint()
{
    // if there are only one vertex it is not a polyline
    if (p.size() < 2)
    {
        p.clear();
        return;
    }

    // the case of the closed polyline
    // here we're going to find the first point by seeing them all
    //Point2D *vertex=NULL, *first_vertex=_vertex_array[0];
    PointType* firstVertex = nullptr;
    for (size_t i = 0; i < p.size(); ++i)
    {
        auto& vertex = p[i];
        if (!firstVertex || !bComparePointOrder(*firstVertex, vertex))
        {
            firstVertex = &vertex;
            firstIdx = i;
        }
    }
}

/***
* @desc simplifies the polygons in this set
* @note removes inclusions and disposes small polygons
*/
void PolyDetector::SimplifyPolys(double smaller_polygon_length)
{
    // remove small polygons
    uint32_t nRemoved = 0;
    for (auto it = polys.begin(); it != polys.end(); )
    {
        if (it->GetCount() < smaller_polygon_length)
        {
            it = polys.erase(it);
            nRemoved++;
        }
        else {
            ++it;
        } 
    }
}

void PolyDetector::AddLine(const PolyLine& line)
{
    origLines.push_back(line);
}

void PolyPol::addLine(const PolyLine& l)
{
    p.push_back(l.a);
    p.push_back(l.b);
}

PolyLine* PolyDetector::findLine(uint32_t pidA, uint32_t pidB, bool useIgnore)
{
    auto m = std::min(pidA, pidB);
    auto M = std::max(pidA, pidB);

    for (auto& l : lines)
    {
        if (useIgnore && l.ignore) continue;
        if (l.minPid() == m && l.maxPid() == M)
            return &l;
    }
    return nullptr;
}

PolyLine* PolyDetector::findLine(uint32_t id, bool useIgnore)
{
    auto search = lineIdToIdx.find(id);
    if (search != lineIdToIdx.end())
    {
        auto& l = lines[search->second];
        if (useIgnore && l.ignore)
        {
            return nullptr;
        }

        return &l;
    }
    return nullptr;
}

PolyLine* PolyDetector::findOrigLine(uint32_t id)
{
    for (auto& l : origLines)
    {
        if (l.id == id)
        {
            return &l;
        }
    }
    return nullptr;
}

bool similarCycle(const PolyCycles & cycles, const PolyCycle & cycle)
{
    for (auto& c : cycles)
    {
        bool equal = true;

        // set already sorted
        for (auto itC = c.idx.cbegin(), itCycle = cycle.idx.cbegin(); itC != c.idx.cend();)
        {
            if (*itC != *itCycle)
            {
                equal = false;
                break;
            }
            bool cEnd = ++itC == c.idx.cend();
            bool cycleEnd = ++itCycle == cycle.idx.cend();
            if (cEnd || cycleEnd)
            {
                if (cEnd != cycleEnd) // contained!
                {
                    return true;
                }
                break;
            }
        }

        if (equal) return true;
    }
    return false;
}

bool PolyCycle::Equals(const PolyCycle & p) const
{
    if (idx.size() != p.idx.size())
        return false;
    for (auto it1 = idx.cbegin(), it2 = p.idx.cbegin(); it1 != idx.cend(); ++it1, ++it2)
    {
        if (*it1 != *it2)
            return false;
    }
    return true;
}

bool PolyCycle::AddLineId(PolyDetector & pd, uint32_t id)
{
    auto l = pd.findLine(id);
    if (!l)
    {
        return false;
    }

    if (l->took >= 2)
    {
        return false;
    }

    l->test0 = 0; // a cnt
    l->test1 = 0; // b cnt

    bool shareA = false, shareB = false;
    bool collinear = false;

    for (auto& id1 : idx)
    {
        auto l1 = pd.findLine(id1);
        if (!l1) continue;

        shareA = l->aIdx == l1->aIdx || l->aIdx == l1->bIdx;
        shareB = l->bIdx == l1->aIdx || l->bIdx == l1->bIdx;
        collinear = false;

        // share a point
        if (shareA)
            l->test0++;

        // share b point
        if (shareB)
            l->test1++;

        if (l->test0 >= 2 || l->test1 >= 2)
        {
            return false;
        }

        if (shareA || shareB)
        {
            collinear = pd.CollinearIdx(*l, *l1);
            if (collinear)
            {
                return false;
            }
        }

        for (auto& id2 : idx)
        {
            if (id2 != id && id2 != id1)
            {
                auto l2 = pd.findLine(id2);

                if (l2 && doIntersect(l->center, l1->center, l2->a, l2->b))
                {
                    return false;
                }
            }
        }
    }

    for (auto& pid : { l->aIdx, l->bIdx })
    {
        auto& pl = pd.pointToLines[pid];
        if (pl.size() >= 2)
        {
            for (auto it1 = pl.begin(); it1 != pl.end(); ++it1)
            {
                auto& nlid1 = *it1;

                if (nlid1 != id && contains(nlid1))
                {
                    for (auto it2 = pl.begin(); it2 != pl.end(); ++it2)
                    {
                        if (*it1 == *it2) continue;

                        auto nlid2 = *it2;

                        if (nlid2 != id && !contains(nlid2))
                        {
                            auto l1 = pd.findLine(nlid1, false);
                            auto l2 = pd.findLine(nlid2);
                            if (l1 && l2)
                            {
                                if (l2->betweenNeighbors(pd, *l1, *l))
                                    return false;
                            }
                        }
                    }
                }
            }
        }
    }

    idx.insert(id);
    lastIdx = id;
    l->processed = startIdx + 1;
    return true;
}

bool PolyCycle::accepted(PolyDetector & pd)
{
    for (auto& lid : idx)
    {
        auto l = pd.findLine(lid);
        if (l)
        {
            l->incTook(pd);
            l->processed = startIdx + 1;
        }
    }
    return true;
}

bool PolyDetector::BuildCycle(uint32_t id, PolyCycle cycle) // as value!
{

    auto l = findLine(id);
    if (!l)
        return true;

    if (_neighbors[id].size() < 2)
    {
        return true;
    }

    if (cycle.canBeClosed(*this, id))
    {
        cycle.isClosed = true;

        if (!similarCycle(_cycles, cycle))
        {
            if (cycle.accepted(*this))
            {
                _cycles.push_back(cycle);
            }
        }

        return true;
    }

    if (!cycle.AddLineId(*this, l->id))
    {
        return true;
    }

    for (auto& nid : _neighbors[id])
    {
        if (_neighbors[nid].size() < 2) continue;
        if (cycle.canBeClosed(*this, nid) || !cycle.contains(nid))
        {
            if (!BuildCycle(nid, cycle))
            {
                return false;
            }
        }
    }

    return true;
}

bool PolyLine::betweenNeighbors(PolyDetector & pd, const PolyLine & l1, const PolyLine & l2) const
{
    auto cpid = commonPid(l1);
    if (cpid < 0)
    {
        return false;
    }
    auto cpid2 = commonPid(l2);
    if (cpid != cpid2)
    {
        return false;
    }

    vec cp = pd.intersectionPoints[cpid];
    vec p = pd.intersectionPoints[otherPid(cpid)];

    bool ret = doIntersect(cp, p, l1.center, l2.center);

    return ret;
}

bool PolyLine::compareNeigh(PolyDetector & pd, uint32_t nid1, uint32_t nid2) const
{
    auto nl1 = pd.findLine(nid1);
    auto nl2 = pd.findLine(nid2);
    if (!nl1 || !nl2)
    {
        assert(false);
        return true;
    }

    auto dl1 = nl1->center.squaredist(center);
    auto dl2 = nl2->center.squaredist(center);
    return dl1 < dl2;
}

bool PolyLine::sortNeigh(PolyDetector & pd) const
{
    auto& neigh = pd._neighbors[id];
    std::sort(neigh.begin(), neigh.end(), [this, &pd](uint32_t nid1, uint32_t nid2)
    {
        return compareNeigh(pd, nid1, nid2);
    });

    return true;
}

uint32_t& PolyLine::incTook(PolyDetector & pd)
{
    if (took >= 2)
        return took;
    took++;

    return took;
}

bool PolyDetector::FindPolys()
{
    pointToLines.clear();
    collinearLineMap.clear();

    // assign line ids
    uint32_t n = 0;
    lineIdToIdx.clear();
    for (auto& l : lines)
    {

        if (dissolveCount == 0) // only on first step
        {
            l.id = n;
        }

        if (!l.ignore)
        {
            addPointToLine(l.aIdx, l.id);
            addPointToLine(l.bIdx, l.id);
        }

        lineIdToIdx[l.id] = n; // lineIdToIdx[l.id] = lines[n]

        n++;
    }

    // build collinearLineMap
    for (auto& lo : origLines)
    {
        for (uint32_t i = 0; i < lines.size(); ++i)
        {
            auto& l1 = lines[i];
            if (!l1.ignore && l1.origLine == lo.id)
            {
                for (uint32_t j = i + 1; j < lines.size(); ++j)
                {
                    auto& l2 = lines[j];
                    if (!l2.ignore && l2.origLine == lo.id)
                    {
                        setCollinear(l1.id, l2.id);
                    }
                }
            }
        }
    }

    // Build neighbors
    std::vector<uint32_t> neigh;
    _neighbors.clear();
    for (uint32_t i = 0; i < lines.size(); ++i)
    {
        auto& l1 = lines[i];
        if (!l1.ignore)
        {
            neigh.clear();
            for (uint32_t j = i + 1; j < lines.size(); ++j)
            {
                auto& l2 = lines[j];
                if (!l2.ignore && l1.HasCommonIdxPoints(l2))
                {
                    neigh.push_back(l2.id);
                }
            }
            if (!neigh.empty())
            {
                for (auto& nid : neigh)
                {
                    _neighbors[l1.id].push_back(nid);
                    _neighbors[nid].push_back(l1.id);
                }
            }
        }
    }
    for (auto& kv : _neighbors)
    {
        auto l = findLine(kv.first);
        if (l)
            l->sortNeigh(*this);
    }

    if (1)
    {
        for (uint32_t i = 0; i < lines.size(); ++i)
        {
            auto& l1 = lines[i];
            for (uint32_t j = i + 1; j < lines.size(); ++j)
            {
                auto& l2 = lines[j];
                if (l1.id == l2.id)
                {
                    assert(false);
                }
            }
        }
    }


    if (dissolveCount == 0)
    {
        for (auto& l : lines)
            l.processed = 0;
    }

    for (auto& kv : _neighbors) // point by point
    {
        if (_neighbors[kv.first].size() < 2) continue;

        PolyCycle cycle;
        cycle.startIdx = cycle.lastIdx = kv.first;
        cycle.isClosed = false;
        BuildCycle(kv.first, cycle);
    }

    std::sort(_cycles.begin(), _cycles.end(), [](const PolyCycle& a, const PolyCycle& b) {
        return a.idxToString().compare(b.idxToString()) < 0;
    });

    for (auto& cycle : _cycles)
    {
        cycle.fine = true;
        if (!cycle.convex(*this))
            cycle.fine = false;
    }

    for (auto& cycle : _cycles)
    {
        if (!cycle.fine) continue;

        // other the lines for proper triangulation
        std::vector<uint32_t> lidx;
        lidx.reserve(cycle.idx.size());
        for (auto& lid : cycle.idx)
            lidx.push_back(lid);
        std::sort(lidx.begin(), lidx.end(), [this](const uint32_t& lid1, const uint32_t& lid2) {
            auto l1 = findLine(lid1, false);
            auto l2 = findLine(lid2, false);
            if (!l1 || !l2)
            {
                assert(false);
                return true;
            }
            return PolyLine::bCompareLineOrder(*l1, *l2);
        });

        // check if not already exists
        bool exists = false;
        for (auto& p : polys)
        {
            if (p.cycle.Equals(cycle))
            {
                exists = true;
                break;
            }
        }
        if (exists)
        {
            continue;
        }

        PolyPol poly;
        PointType* last = nullptr;
        for (auto& id : lidx)
        {
            auto lPtr = findLine(id);
            if (lPtr)
            {
                lPtr->CalculateFirstAndLastPoint();

                auto& a = intersectionPoints[lPtr->aIdx];
                auto& b = intersectionPoints[lPtr->bIdx];

                //lPtr->incTook(*this);

                poly.addPointChecked(a);

                last = &b;
            }
        }
        if (last)
            poly.addPointChecked(*last);

        poly.id = cycle.startIdx;
        poly.cycle = cycle;

        poly._area = poly.TriangleArea(*this);
        poly.dissolveStep = dissolveCount;
        poly.c = poly.center();
        poly.color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
        std::sort(poly.p.begin(), poly.p.end(), [&, this](const PointType& p1, const PointType& p2) {
            float aA = (atan((p1.y - poly.c.y) / (p1.x - poly.c.x))) * 57.29;
            float aB = (atan((p2.y - poly.c.y) / (p2.x - poly.c.x))) * 57.29;

            float angleA = p1.x-poly.c.x >= 0 ? (p1.y-poly.c.y >= 0 ? aA : 360+aA) : 180+aA;
            float angleB = p2.x-poly.c.x >= 0 ? (p2.y-poly.c.y >= 0 ? aB : 360+aB) : 180+aB;

            return angleA < angleB;
        });
        polys.push_back(std::move(poly));
    }

    return true;
}

double PolyPol::TriangleArea(PolyDetector & pd)
{
    if (p.size() <= 2)
        return 0.0f;
    double area = 0.0;

    auto c = center();
    for (auto& n : cycle.idx)
    {
        auto l = pd.findLine(n);
        if (!l)
            return 0.0f;
        area += abs(::Area(c, l->a, l->b));
    }
    return area;
}

bool PolyPol::addPointChecked(const PointType & v)
{
    for (auto& pt : p)
        if (!pointsDiffer(pt, v))
            return false;
    p.push_back(v);
    return true;
}

void PolyPol::draw() {
    //ofSetColor(0, 0, 0);
    //ofDrawCircle(c.x, c.y, 10);
    ofSetColor(color);
    ofBeginShape();
        for (int i = 0; i < p.size(); i++) {
            ofVertex(p.at(i).x, p.at(i).y);
        }
    ofEndShape();
}

void PolyLine::calcCenter()
{
    CalculateFirstAndLastPoint();
    center = a;
    center.add(b);
    center.mul(0.5f);
}

bool PolyDetector::dissolveCollinear(PolyLine & l1, PolyLine & l2)
{
    assert(&l1 != &l2);

    uint32_t* p1 = nullptr, * p2 = nullptr;
    if (l1.aIdx == l2.aIdx || l1.aIdx == l2.bIdx)
    {
        p1 = &l1.bIdx; // other point (B)
        p2 = l1.aIdx == l2.aIdx ? &l2.bIdx : &l2.aIdx; // aidx is common point. other point
    }
    else if (l1.bIdx == l2.aIdx || l1.bIdx == l2.bIdx)
    {
        p1 = &l1.aIdx; // other point (A)
        p2 = l1.bIdx == l2.aIdx ? &l2.bIdx : &l2.aIdx; // bidx is common point. other point
    }
    if (!p1 || !p2)
    {
        assert(p1 && p2);
        return false;
    }

    auto search = findLine(*p1, *p2, false);
    if (search)
    {
        l1.setIgnore(*this, "rmCollinear.l1 (dup)");
        l2.setIgnore(*this, "rmCollinear.l2 (dup)");

        return false;
    }

    PolyLine nl;
    nl.id = uint32_t(lines.size());
    nl.aIdx = *p1;
    nl.bIdx = *p2;
    nl.a = intersectionPoints[nl.aIdx];
    nl.b = intersectionPoints[nl.bIdx];
    nl.calcCenter(); // calls CalculateFirstAndLastPoint
    nl.origLine = l1.origLine; // will be used to construct collinearLineMap
    nl.lastDissolveStep = l1.lastDissolveStep;
    nl.attr0 = l1.attr0;

    // build point to lines link
    addPointToLine(nl.aIdx, nl.id);
    addPointToLine(nl.bIdx, nl.id);

    // build neighbors
    for (auto& id : { l1.id, l2.id })
    {
        for (auto& n : _neighbors[id])
        {
            if (n != l1.id && n != l2.id)
            {
                auto l = findLine(n);
                if (l)
                {
                    _neighbors[nl.id].push_back(n);
                    _neighbors[n].push_back(nl.id);
                }
            }
        }
    }

    // set proper collinearities
    for (auto& kv : collinearLineMap)
    {
        if (kv.first == l1.id || kv.first == l2.id)
        {
            for (auto& c : kv.second)
                setCollinear(nl.id, c);
        }
    }

    // after neigh built!
    l1.setIgnore(*this, "rmCollinear.l1");
    l2.setIgnore(*this, "rmCollinear.l2");

    lineIdToIdx[nl.id] = uint32_t(lines.size());
    lines.push_back(nl);
    lines.back().sortNeigh(*this);

    return true;
}

bool PolyDetector::dissolveCollinearLine(PolyLine & l)
{
    for (auto id : { l.aIdx, l.bIdx })
    {
        uint32_t nValid = 0;
        PolyLine* l1 = nullptr;
        for (auto& n : pointToLines[id])
        {
            if (n != l.id)
            {
                auto lPtr = findLine(n);
                if (lPtr)
                {
                    if (lPtr->took < 2)
                        //if (lPtr->took == 0)
                        //if (lPtr->numNeigh(*this) < 2)
                    {
                        l1 = lPtr;
                        nValid++;
                    }
                }
            }
        }
        if (nValid == 1 && CollinearIdx(l, *l1))
        {
            return dissolveCollinear(l, *l1);
        }
    }
    return false;
}

bool PolyDetector::dissolve()
{
    uint32_t nLinesBefore = uint32_t(lines.size());
    uint32_t nIgnoredBefore = 0;
    for (auto& l : lines)
        if (l.ignore)
            nIgnoredBefore++;

    if (_cycles.empty())
    {
        return false;
    }

    rmLines(RmLinesType::PointConsumed);
    rmLines(RmLinesType::TakenTwice); // points taken twice
    rmLines(RmLinesType::NoPointNeigh);
    rmLines(RmLinesType::Collinear);

    uint32_t nIgnored = 0;
    uint32_t nValid = 0;
    for (auto& l : lines)
    {
        if (!l.ignore)
        {
            nValid++;
        }
        else
        {
            nIgnored++;
        }
    }

    if (!nValid)
    {
        return false;
    }

    if (nIgnored == nIgnoredBefore)
    {
        return false;
    }

    // also clear prev cycles
    _cycles.clear();

    dissolveCount++;

    for (auto& l : lines)
    {
        if (!l.ignore) {
            l.lastDissolveStep = dissolveCount;
        }
    }

    return true;
}

void PolyDetector::setCollinear(uint32_t l1, uint32_t l2)
{
    collinearLineMap[l1].push_back(l2);
    collinearLineMap[l2].push_back(l1);
}

bool PolyDetector::CollinearIdx(uint32_t l1, uint32_t l2)
{
    auto search = collinearLineMap.find(l1);
    if (search == collinearLineMap.end())
        return false;
    return std::find(search->second.begin(), search->second.end(), l2) != search->second.end();
}

bool PolyDetector::CollinearIdx(const PolyLine & l1, const PolyLine & l2)
{
    return CollinearIdx(l1.id, l2.id);
}

bool PolyCycle::canBeClosed(PolyDetector & pd, uint32_t idToAdd) const
{
    return idx.size() > 2 && startIdx == idToAdd;
}

bool PolyCycle::pointConsumed(PolyDetector & pd, uint32_t pid) const
{
    auto& neigh = pd.pointToLines[pid];
    if (neigh.size() <= 1) // including self
    {
        return true;
    }

    uint32_t lid1 = 0, lid2 = 0;
    uint32_t nValid = 0, nTaken = 0;
    for (auto& n : neigh)
    {
        auto l = pd.findLine(n);
        if (l)
        {
            nValid++;
            //if (l->took)
            if (l->took)
            {
                if (nTaken == 0) {
                    lid1 = l->id;
                }
                else if (nTaken == 1) {
                    lid2 = l->id;
                } 
                nTaken++;
            }
        }
    }

    if (nValid == 2 && nValid == nTaken)
    {
        if (pd.CollinearIdx(lid1, lid2))
            return false;

        // must be in the cycle!
        if (std::find(idx.begin(), idx.end(), lid1) == idx.end())
        {
            return false;
        }
        if (std::find(idx.begin(), idx.end(), lid2) == idx.end())
        {
            return false;
        }
        return true;
    }

    return false;
}

void PolyLine::setIgnore(PolyDetector & pd, const char* msg)
{
    if (ignore)
        return;

    ignore = true;
}

bool PolyDetector::rmEarPoints()
{
    std::vector<PolyLine*> torm;

    std::set<uint32_t> pids;
    for (auto& cycle : _cycles)
    {
        for (auto& lid : cycle.idx)
        {
            auto l = findLine(lid);
            if (l)
            {
                for (auto& pid : { l->aIdx, l->bIdx })
                {
                    if (cycle.pointConsumed(*this, pid))
                    {
                        torm.push_back(l);
                    }
                }
            }
        }
    }
    for (auto& l : torm)
    {
        l->setIgnore(*this, "rmEarPoints");
    }
    return true;
}

bool PolyDetector::rmLines(RmLinesType type)
{

    if (type == RmLinesType::Collinear)
    {
        // rm collinear lines
        uint32_t nCollinearRemoved = 0;
        for (uint32_t i = 0; i < lines.size(); ++i)
        {
            auto& l = lines[i];
            if (!l.ignore)
            {
                if (dissolveCollinearLine(l))
                {
                    nCollinearRemoved++;
                    i = 0; // again
                }
            }
        }
        return true;
    }

    if (type == RmLinesType::PointConsumed)
    {
        rmEarPoints();
        return true;
    }

    for (uint32_t i = 0; i < lines.size(); ++i)
    {
        auto& l = lines[i];
        if (!l.ignore && l.canBeRemoved(*this, type))
        {
            l.setIgnore(*this, (std::string("rmLines.") + RmLinesTypeStr(type)).c_str());

            // reprocess same position
            if (i > 0) i--;
        }
    }

    return true;
}

bool PolyCycle::convex(PolyDetector & pd) const
{
    for (auto it1 = idx.begin(); it1 != idx.end(); ++it1)
    {
        auto l1 = pd.findLine(*it1, false);
        if (!l1) continue;

        auto it2 = it1;
        ++it2;

        for (; it2 != idx.end(); ++it2)
        {
            auto l2 = pd.findLine(*it2, false);
            if (!l2) continue;

            PolyLine ls(l1->center, l2->center);
            for (auto it3 = idx.begin(); it3 != idx.end(); ++it3)
            {
                if (it3 != it1 && it3 != it2)
                {
                    auto l3 = pd.findLine(*it3);

                    if (l3 && doIntersect(ls.a, ls.b, l3->a, l3->b))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void PolyDetector::reset()
{
    _cycles.clear();
    origLines.clear();
    lines.clear();
    polys.clear();
    _neighbors.clear();
    collinearLineMap.clear();
    intersectionPoints.clear();
    pointToLines.clear();
    dissolveCount = 0;
}
