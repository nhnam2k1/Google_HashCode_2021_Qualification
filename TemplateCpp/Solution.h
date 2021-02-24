#pragma once
class Solution
{
public:
	Solution();
	long long score;
	unsigned short int age;
	
	bool operator < (const Solution other) const;
private:
};

