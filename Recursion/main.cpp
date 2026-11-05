#include "Question.h"

using namespace std;

int main () {
	Resolution cmbkRes("My guy, it's a chromebook what do you expect?");
	Resolution mdaCtr("Go ask the media center for help");
	Resolution idk("Idk bro, you're on your own");

	Question slow("Is it just slow or not working at all?");
	slow.addOption("Just slow",cmbkRes);
	slow.addOption("Not working at all", mdaCtr);

	Question cmbk("Are you using a chromebook?");
	cmbk.addOption("Yes",slow);
	cmbk.addOption("No",idk);

	Question learning("Did you use \"learning\" as the password?");
	learning.addOption("Yes", cmbk);
	Resolution goLearning("Go do that");
	goLearning.optQuestion = &learning;
	learning.addOption("No",goLearning);

	Resolution internetRes("Turn on your internet");
	internetRes.optQuestion = &learning;
	
	Resolution airplaneRes ("Turn off airplane mode");
	airplaneRes.optQuestion = &internetRes;

	Question inAir ("Are you in an airplane?");
	inAir.addOption("Yes",idk);
	inAir.addOption("No",airplaneRes);

	Question airMode ("Are you in Airplane mode?");
	airMode.addOption("Yes", inAir);
	airMode.addOption("No", internetRes);

	Question internet ("Is your internet on?");
	internet.addOption("Yes", learning);
	internet.addOption("No", airMode);


	internet.resolve();

	return 0;
}