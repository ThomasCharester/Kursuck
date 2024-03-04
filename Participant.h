#pragma once
#ifndef PARTICIPANT
#define PARTICIPANT
#include <string>

class Participant
{
public:
	Participant(std::string FIO, std::string country, std::string teamName, float weight, float height, int playerID, int age) {
		this->FIO = FIO;
		this->country = country;
		this->teamName = teamName;
		this->weight = weight;
		this->height = height;
		this->playerID = playerID;
		this->age = age;
	}
	~Participant() {}

	std::string print() {
		std::string output = "ID: " + std::to_string(playerID) + "  " + FIO + "\nCountry: " + country + "\nTeam name: " + teamName + "\nWeight: " + std::to_string(weight) + " kg  \nHeight: " + std::to_string(height) + " sm \nAge: " + std::to_string(age) + " years\n";
		return output;
	}
private:

	std::string FIO;
	std::string country;
	std::string teamName;
	float weight;
	float height;
	int playerID;
	int age;
public:

	inline friend const bool operator ==(const Participant& m1, const Participant& m2);
	inline friend const bool operator > (const Participant& m1, const Participant& m2);
	inline friend const bool operator < (const Participant& m1, const Participant& m2);
	inline friend const bool operator <=(const Participant& m1, const Participant& m2);
	inline friend const bool operator >=(const Participant& m1, const Participant& m2);

	inline operator int() const
	{
		return age;
	}

	inline friend std::ostream& operator<<(std::ostream& os, const Participant& participant);
};
inline const bool operator==(const Participant& m1, const Participant& m2)
{
	return m1.age == m2.age;
}
inline const bool operator>= (const Participant& m1, const Participant& m2)
{
	return m1.age >= m2.age;
}
inline const bool operator<=(const Participant& m1, const Participant& m2)
{
	return m1.age <= m2.age;
}
inline const bool operator>(const Participant& m1, const Participant& m2)
{
	return m1.age > m2.age;
}
inline const bool operator<(const Participant& m1, const Participant& m2)
{
	return m1.age < m2.age;
}
inline std::ostream& operator<<(std::ostream& os, const Participant& participant)
{
	return os << std::to_string(participant.playerID) + ' ' + participant.FIO + ' ' + participant.country + ' ' + participant.teamName + ' ' + std::to_string(participant.weight) + ' ' + std::to_string(participant.height) + ' ' + std::to_string(participant.age) + ' ';
}



#endif // !PARTICIPANT
