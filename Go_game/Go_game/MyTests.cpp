#include <cstring>
#include <iostream>
#include <fstream>


int gDone = 0;
int gFail = 0;


/********************************************************************************/
void NewTests()
{
	std::ofstream log("MyTestsLog.txt");
	log << "===================================================\n"
		<< "                  New Tests\n\n";
}


/********************************************************************************/
void Log_Of_MyTests(bool valid, int line, const char* file, const char* fuNname, const char* expresion)
{
	std::ofstream log("MyTestsLog.txt", std::ios::app);

	const char* fileName = strrchr(file, '\\');
	fileName += 1;

	if (valid)
	{
		log << "DONE: ";
		gDone++;
	}
	else
	{
		log << "FAIL: ";
		gFail++;
	}

	log << fileName << ": " << fuNname << ": " << line << " " << expresion << "\n";
}


/********************************************************************************/
void EndTests()
{
	std::ofstream log("MyTestsLog.txt", std::ios::app);
	log << "\n===============\n"
		<< "Total tests: " << (gDone + gFail)
		<< "\nDone tests: " << gDone
		<< "\nFail tests: " << gFail
		<< "\n===============\n"
		<< "\n                  End Tests\n"
		<< "===================================================\n"
		<< "===================================================\n\n\n";
}

