#include <iostream>
#include "plan.h"

using namespace std;

void showPlan (CookingPlan* plan) {
	vector<string> v = plan->cook();
	for (string s : v) cout << s << endl;
}

int main () {
	string dishName = "Trailmix";

	vector<CookingPlan*> plans {
		new OvenPlan(dishName),
		new StovetopPlan(dishName),
		new CampingPlan(dishName)
	};

	for (CookingPlan* p : plans) { showPlan(p); cout << endl; }

	return 0;
}