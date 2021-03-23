#include "PolyDetector.h"

struct PolyCycle
{
    CycleSet idx;

    uint32_t startIdx, lastIdx;
    bool isClosed;
    bool fine;
    //uint32_t colStep = 0; // use it to increase the recursive colliniar length

    bool canBeClosed(PolyDetector& pd, uint32_t idToAdd) const;

    bool contains(uint32_t idP) const
    {
        return std::find(idx.begin(), idx.end(), idP) != idx.end();
    }

    uint32_t numCuts(PolyDetector& pd, const PolyLine& l) const;

    bool AddLineId(PolyDetector& pd, uint32_t id);

    std::string idxToString() const
    {
        std::string str;
        for (auto& n : idx)
        {
            str += std::to_string(n) + " ";
        }
        if (!str.empty())
            str.pop_back();
        return str;
    }

    std::string toString() const
    {
        std::string str = "C{[" + std::to_string(startIdx) + "] nLines:";
        str += std::to_string(idx.size());

        str += " [";
        str += idxToString();
        str += "]}";

        return str;
    }

    void print(const char* msg = nullptr) const
    {
        logoutf("%s%s", msg ? msg : "", toString().c_str());
    }

    bool Equals(const PolyCycle& p) const;

    bool convex(PolyDetector& pd) const;

    bool pointConsumed(PolyDetector& pd, uint32_t pid) const;

    bool accepted(PolyDetector& pd);
};