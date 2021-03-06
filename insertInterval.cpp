#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if (intervals.empty()) {
            intervals.push_back(newInterval);
            return intervals;
        }
        for (int i = 0; i < intervals.size(); i++) {
            if(compare(newInterval, intervals.at(i)) <= 0) {
                intervals.insert(intervals.begin() + i, newInterval);
                break;
            } else if (i == intervals.size()-1) intervals.push_back(newInterval);
        }
        for (int i = 0; i < intervals.size()-1; i++) {
            printf("Comparing [%d, %d] & [%d, %d]: %d\n", intervals.at(i).at(0), intervals.at(i).at(1), intervals.at(i+1).at(0), intervals.at(i+1).at(1), isOverlapping(intervals.at(i),intervals.at(i+1)));
            if (isOverlapping(intervals.at(i), intervals.at(i+1))) {
                vector<int> temp = merge(intervals.at(i), intervals.at(i+1));
                intervals.erase(intervals.begin()+i, intervals.begin()+i+2);
                intervals.insert(intervals.begin()+i, temp);
                i--;
            }
        }
        return intervals;
    }

    bool isOverlapping(vector<int> i1, vector<int> i2) {
        if (i1.at(0) == i2.at(0) || i1.at(0) == i2.at(1) || i2.at(0) == i1.at(1) || i1.at(1) == i2.at(1)) return true;
        if (i1.at(0) > i2.at(0) && i1.at(0) < i2.at(0)) return true;
        if (i1.at(0) < i2.at(0) && i1.at(1) > i2.at(0)) return true;
        if (i1.at(0) < i2.at(0) && i1.at(1) > i2.at(1)) return true;
        if (i1.at(0) > i2.at(0) && i1.at(1) < i2.at(1)) return true;
        return false;
    }

    vector<int> merge(vector<int> i1, vector<int> i2){
        if (!isOverlapping(i1, i2)) throw "Cannot merge non overlapping intervals!";
        else {
            return vector<int> {min(i1.at(0),i2.at(0)), max(i1.at(1), i2.at(1))};
        }
    }

    int compare(vector<int> i1, vector<int> i2) {
        if (i1.at(0) == i2.at(0) && i1.at(1) == i2.at(1)) return 0;
        if (i1.at(0) > i2.at(0)) return 1;
        if (i1.at(0) > i2.at(0) && i1.at(1) > i2.at(1)) return 1;
        else return -1;
    }
};

int main(){
    vector<vector<int>> intervals{{1,2},{3,5}, {6,7}, {8,10}, {12,16}};
    vector<int> newInterval{4,8};
    printf("Inputs:\n\tIntervals: [");
    for(vector<int> x: intervals) {
        printf("[%d, %d], ", x.at(0), x.at(1));
    }
    printf("]\n");
    printf("\tNew Interval: [%d, %d]\n", newInterval.at(0), newInterval.at(1));
    Solution sol = Solution();
    vector<vector<int>> result = sol.insert(intervals, newInterval);
    printf("Results:\n\t[");
    for(vector<int> x: result){
        printf("[%d, %d], ", x.at(0),x.at(1));
    }
    printf("]\n");
    return 0;
}