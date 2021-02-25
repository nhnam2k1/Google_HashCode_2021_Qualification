#pragma once
#include "Dataset.h"
#include "Solution.h"

#include <stdio.h>     
#include <stdlib.h>     
#include <time.h>  
class Random {
public:
	
	Random() {
		srand(time(NULL));
	}

	Solution generateRandomSolution(Dataset dataset);

};