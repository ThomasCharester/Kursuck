#include "Choice.h"
#include "Database.h"
int main() {

	UI<Database> ui;


	Database* labs = new Database(ui);

	UI<Database>::Choice taskChoices[7]{
		UI<Database>::Choice(labs,&Database::showParticipants,"Show participants"),
		UI<Database>::Choice(labs,&Database::showTeams,"Show teams"),
		UI<Database>::Choice(labs,&Database::editDatabase,"Edit database"),
		UI<Database>::Choice(labs,&Database::file,"File"),
		UI<Database>::Choice(labs,&Database::search,"Search"),
		UI<Database>::Choice(labs,&Database::specialTask,"Special task"),
		UI<Database>::Choice(labs,&Database::sort,"Sort")
	};

	return ui.choose(taskChoices, 7, "Choose action");

	return 0;
}