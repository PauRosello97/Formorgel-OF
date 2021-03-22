#include "PolyCicle.h"


bool PolyCycle::Equals(const PolyCycle& p) const
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

bool PolyCycle::AddLineId(PolyDetector& pd, uint32_t id)
{
    auto l = pd.findLine(id);
    if (!l)
    {
        logoutf("findLine(%u) failed!", id);
        return false;
    }

    if (l->took >= 2)
    {
        if (pd.verbose > 3)
            logoutf("line %u can't be added to cycle! tooked %u times!", id, l->took);
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
            if (pd.verbose > 2)
                logoutf("line %u can't be added to cycle! ta:%d tb:%d ids: [%s]", id, l->test0, l->test1, idxToString().c_str());
            return false;
        }

        if (shareA || shareB)
        {
            collinear = pd.CollinearIdx(*l, *l1);
            if (pd.verbose > 2)
                logoutf("l(%u), l1(%u) sa:%d sb:%d col:%d", l->id, l1->id, shareA, shareB, collinear);
            if (collinear)
            {
                if (pd.verbose > 2)
                    logoutf("line %u can't be added to cycle! colliniar with %u sa:%d sb:%d", id, id1, shareA, shareB);
                return false;
            }
        }

        for (auto& id2 : idx)
        {
            if (id2 != id && id2 != id1
                //&& !pd.CollinearIdx(id2, id) && !pd.CollinearIdx(id2, id1)
                )
            {
                auto l2 = pd.findLine(id2);

                if (l2 && doIntersect(l->center, l1->center, l2->a, l2->b))
                    //if (l2 && !Collinear(ls, *l2) && ls.PolyIntersects(*l2))
                {
                    if (pd.verbose > 2)
                        logoutf("line %u can't be added to cycle (coll test)! id2:%u intersects with middle(%u, %u)", id, id2, l->id, l1->id);
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
                            //auto l1 = pd.findLine(nlid1, false);
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

bool PolyCycle::accepted(PolyDetector& pd)
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