#include "Solution.h"

Solution::Solution()
{
    this->age = 0;
    this->score = 0;
}

bool Solution::operator<(const Solution other) const
{
    // If to have maximumm, else use < 
    return score > other.score;
}