#pragma once
#include <string>
#include <fstream>

class PrinterMaintainer
{
	std::fstream configFile;
	std::fstream lastPrintTimeFile;
	size_t lastPrintTimeInSeconds;
	int printToPrintTimeInDays;
	std::string configFilename;
	std::string lastPrintTimeFilename;
	std::string printingCommand;
public:
	explicit PrinterMaintainer(std::string configFileName, std::string lastPrintTimeFilename);
	int GetPrintToPrintTimeInDays() const { return printToPrintTimeInDays; }
	bool ShouldPrintTestPage() const;
	void PrintTestPage();
	void SavePrintingTime(const int delayInDays = 0);

private:
	void SafeInitialization();
	void InitializeConfig();
	void InitializeLastPrintTime();
	void SafeSavePrintingTime(const int delayInDays);
};
