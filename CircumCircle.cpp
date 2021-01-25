#include "CircumCircle.h"

bool CircumCircle::circumCircle(ofVec2f p, Triangle t, ofVec3f circle) {
    float m1, m2, mx1, mx2, my1, my2, dx, dy, rsqr, drsqr;
    float EPSILON = 1e-5;
    /* Check for coincident points */
    if (abs(t.p1.pos.y - t.p2.pos.y) < EPSILON && abs(t.p2.pos.y - t.p3.pos.y) < EPSILON) {
        //println("CircumCircle: Points are coincident.");
        return false;
    }

    if (abs(t.p2.pos.y - t.p1.pos.y) < EPSILON) {
        m2 = -(t.p3.pos.x - t.p2.pos.x) / (t.p3.pos.y - t.p2.pos.y);
        mx2 = (t.p2.pos.x + t.p3.pos.x) * .5;
        my2 = (t.p2.pos.y + t.p3.pos.y) * .5;
        circle.x = (t.p2.pos.x + t.p1.pos.x) * .5;
        circle.y = m2 * (circle.x - mx2) + my2;
    }
    else if (abs(t.p3.pos.y - t.p2.pos.y) < EPSILON) {
        m1 = -(t.p2.pos.x - t.p1.pos.x) / (t.p2.pos.y - t.p1.pos.y);
        mx1 = (t.p1.pos.x + t.p2.pos.x) * .5;
        my1 = (t.p1.pos.y + t.p2.pos.y) * .5;
        circle.x = (t.p3.pos.x + t.p2.pos.x) * .5;
        circle.y = m1 * (circle.x - mx1) + my1;
    }
    else {
        m1 = -(t.p2.pos.x - t.p1.pos.x) / (t.p2.pos.y - t.p1.pos.y);
        m2 = -(t.p3.pos.x - t.p2.pos.x) / (t.p3.pos.y - t.p2.pos.y);
        mx1 = (t.p1.pos.x + t.p2.pos.x) * .5;
        mx2 = (t.p2.pos.x + t.p3.pos.x) * .5;
        my1 = (t.p1.pos.y + t.p2.pos.y) * .5;
        my2 = (t.p2.pos.y + t.p3.pos.y) * .5;
        circle.x = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        circle.y = m1 * (circle.x - mx1) + my1;
    }

    dx = t.p2.pos.x - circle.x;
    dy = t.p2.pos.y - circle.y;
    rsqr = dx * dx + dy * dy;
    circle.z = sqrt(rsqr);

    dx = p.x - circle.x;
    dy = p.y - circle.y;
    drsqr = dx * dx + dy * dy;

    return drsqr <= rsqr;
}
