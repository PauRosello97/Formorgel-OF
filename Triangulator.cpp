#include "Triangulator.h"
#include <algorithm>

bool Triangulator::sharedVertex(Triangle t1, Triangle t2) {
    return t1.p1.equals(t2.p2) || t1.p1.equals(t2.p2) || t1.p1.equals(t2.p3) ||
        t1.p2.equals(t2.p1) || t1.p2.equals(t2.p2) || t1.p2.equals(t2.p3) ||
        t1.p3.equals(t2.p1) || t1.p3.equals(t2.p2) || t1.p3.equals(t2.p3);
}

void Triangulator::sortXList(vector<Node> ps) {
    int l = ps.size();
    ofVec2f p1, p2, pi;
    int r;
    for (int i = 0; i < l - 1; i++)
    {
        pi = ps[i].pos;
        p1 = ps[i].pos;
        p2 = ps[i].pos;
        r = i;
        for (int j = i + 1; j < l; j++)
        {
            p1 = ps[j].pos;
            if (p1.x < p2.x)
            {
                p2 = p1;
                r = j;
            }
        }
        if (r != i)
        {
            Node tmpv = ps[r];
            ps[r] = ps[i];
            ps[i] = tmpv;
        }
    }
}

void Triangulator::sortXArray(vector<ofVec2f> ps) {
    int l = ps.size();
    ofVec2f p1, p2, pi;
    int r;
    for (int i = 0; i < l - 1; i++)
    {
        pi = ps[i];
        p1 = pi;
        p2 = pi;
        r = i;
        for (int j = i + 1; j < l; j++)
        {
            p1 = ps[j];
            if (p1.x < p2.x)
            {
                p2 = p1;
                r = j;
            }
        }
        if (r != i)
        {
            ps[r] = pi;
            ps[i] = p2;
        }
    }
}

vector<Triangle> Triangulator::triangulate(vector<Node> pxyz) {
    
    vector<Triangle> triangles;
    
    // sort vertex array in increasing x values
    sortXList(pxyz);

    // Find the maximum and minimum vertex bounds. This is to allow calculation of the bounding triangle
    float
        xmin = pxyz[0].pos.x,
        ymin = pxyz[0].pos.y,
        xmax = xmin,
        ymax = ymin;

    for (Node p : pxyz) {
        if (p.pos.x < xmin) xmin = p.pos.x;
        else if (p.pos.x > xmax) xmax = p.pos.x;
        if (p.pos.y < ymin) ymin = p.pos.y;
        else if (p.pos.y > ymax) ymax = p.pos.y;
    }

    float
        dx = xmax - xmin,
        dy = ymax - ymin,
        dmax = dx > dy ? dx : dy,
        two_dmax = dmax * 2,
        xmid = (xmax + xmin) * .5,
        ymid = (ymax + ymin) * .5;

    vector<Triangle> complete; // for complete Triangles

    // Set up the supertriangle. This is a triangle which encompasses all the sample points.
    // The supertriangle coordinates are added to the end of the vertex list. The supertriangle is the first triangle in the triangle list.

    Triangle superTriangle = Triangle(Node(xmid - two_dmax, ymid - dmax), Node(xmid, ymid + two_dmax), Node(xmid + two_dmax, ymid - dmax));
    triangles.push_back(superTriangle);
    
    //Include each point one at a time into the existing mesh
    vector<Edge> edges;
    ofVec2f circle;
    bool inside;

    for (Node p : pxyz) {
        edges.clear();

        //Set up the edge buffer. If the point (xp,yp) lies inside the circumcircle then the three edges of that triangle are added to the edge buffer and that triangle is removed.
        ofVec3f circle;

        for (int j = triangles.size() - 1; j >= 0; j--)
        {
            Triangle t = triangles[j];
            auto ite = find_if(complete.begin(), complete.end(), [&t](Triangle triangle) {
                return triangle.equals(t);
            });
            bool contains = ite != complete.end();
            if (contains) continue;

            CircumCircle circumCircle;
            inside = circumCircle.circumCircle(p.pos, t, circle);

            if (circle.x + circle.z < p.pos.x) complete.push_back(t);
            if (inside)
            {
                edges.push_back(Edge(t.p1, t.p2));
                edges.push_back(Edge(t.p2, t.p3)); 
                edges.push_back(Edge(t.p3, t.p1));

                auto it = find_if(triangles.begin(), triangles.end(), [&t](Triangle triangle) {
                    return triangle.equals(t);
                });
                triangles.erase(it);
                
            }
        }

        
        // Tag multiple edges. Note: if all triangles are specified anticlockwise then all interior edges are opposite pointing in direction.
        int eL = edges.size() - 1, eL_ = edges.size();
        Edge e1 = Edge(), e2 = Edge();

        for (int j = 0; j < eL; e1 = edges[j++]) {
            for (int k = j + 1; k < eL_; e2 = edges[k++]) {
                if (e1.p1.equals(e2.p2) && e1.p2.equals(e2.p1)) {
                    e1.p1 = Node();
                    e1.p2 = Node();
                    e2.p1 = Node(); 
                    e2.p2 = Node();
                }
            }
        }

        //Form new triangles for the current point. Skipping over any tagged edges. All edges are arranged in clockwise order.
        for (Edge e : edges) {
            if (e.p1.getIsNull() || e.p2.getIsNull()) continue;
            triangles.push_back(Triangle(e.p1, e.p2, p));
        }
        
    }

    
    //Remove triangles with supertriangle vertices
    
    for (int i = triangles.size() - 1; i >= 0; i--) {
        if (sharedVertex(triangles[i], superTriangle)) {
            Triangle tri = triangles[i];
            auto iterator = find_if(triangles.begin(), triangles.end(), [&tri](Triangle triangle) {
                return triangle.equals(tri);
            });
            triangles.erase(iterator);
            //triangles.erase(std::remove(triangles.begin(), triangles.end(), i), triangles.end());
        }
    }

    return triangles;
    
}


