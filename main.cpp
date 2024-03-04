#include "Choice.h"
#include "Database.h"
int main() {

	UI<Database> ui;

	Database* labs = new Database(ui);

	UI<Database>::Choice taskChoices[5]{
		UI<Database>::Choice(labs,&Database::addParticipant,"Add participant"),
		UI<Database>::Choice(labs,&Database::removeParticipant,"Remove participant"),
		UI<Database>::Choice(labs,&Database::showParticipants,"Show participants"),
		UI<Database>::Choice(labs,&Database::readFile,"Read file"),
		UI<Database>::Choice(labs,&Database::writeFile,"Rewrite file")
	};

	return ui.choose(taskChoices, 5, "Choose action");

	return 0;
}