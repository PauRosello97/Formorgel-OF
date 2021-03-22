#include "Functions.h"
#include "PolyDetector.h"

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
// https://www.cdn.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool doIntersect(const PointType& p1, const PointType& q1, const PointType& p2, const PointType& q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}


// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(const PointType& p, const PointType& q, const PointType& r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    double val =
        (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);

    if (val == 0.0) return 0;  // colinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}


// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(const PointType& p, const PointType& q, const PointType& r)
{
    if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
        q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
        return true;

    return false;
}

bool collinearVecs(const PointType& p, const PointType& q, const PointType& r)
{
    return orientation(p, q, r) == 0;
}

/***
* @return true is this point is betwen a and b
* @note c must be collinear with a and b
* @see O'Rourke, Joseph, "Computational Geometry in C, 2nd Ed.", pp.32
*/
bool between(const PointType& p, const PointType& a, const PointType& b)
{
    // if this point is not collinear with a and b
    // then it cannot be between this two points
    if (!collinearVecs(p, a, b))
        return false;

    auto& _x = p.x;
    auto& _y = p.y;

    return
        ((a.x <= _x && _x <= b.x) && (a.y <= _y && _y <= b.y)) ||
        ((b.x <= _x && _x <= a.x) && (b.y <= _y && _y <= a.y));
}