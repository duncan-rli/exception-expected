#include <string>

class Stats{
    int tmin;
    int tmax;
    int tavg;
    // big val protected
    int tprotect;
    int tpmax;
    int tpavg;

    int count;
    int protCount;
    
public:
    Stats(int prot=4000) :tprotect(prot){
        tmin = INT32_MAX;
        tmax = 0;
        tavg = 0;
        tpmax = 0;
        tpavg = 0;
        count = 0;
        protCount = 0;
    }

    void addData(int t){
        if (t < tmin)
            tmin = t;
        if (t > tmax)
            tmax = t;
        tavg += t;       

        count++;

        // if data value is over limit then ignore 
        if (t < tprotect){
            if (t > tpmax)
                tpmax = t;

            tpavg += t;
            protCount++;
        }
        else{
            int a = 0; // add break point to find big values
        }
    }

    // get unprotected average
    int getAvg(){
        return tavg/count;
    }

    std::string getString(){
        std::string s;
        s = " min: " + std::to_string(tmin) + " \tmax: " + std::to_string(tmax) + " \tavg: " + 
        ((count>0)?std::to_string(tavg/count):"0") + "\tc: " + std::to_string(count) +
            " \tpmax: " + std::to_string(tpmax) + " \tpavg: " + 
        ((protCount>0)?std::to_string(tpavg/protCount):"0") + "\tpc: " + std::to_string(protCount);
        return s;
    }
};
