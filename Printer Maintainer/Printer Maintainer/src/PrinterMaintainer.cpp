#include "../inc/PrinterMaintainer.h"
#include <utility>
#include <fstream>
#include <chrono>

using std::string;
using std::exception;
using std::chrono::seconds;
using std::chrono::duration_cast;
using std::chrono::system_clock;

PrinterMaintainer::PrinterMaintainer(string configFileName, string lastPrintTimeFilename) :
	configFilename(std::move(configFileName)), lastPrintTimeFilename(lastPrintTimeFilename)
{
	try
	{
		SafeInitialization();
	}
	catch (std::ios_base::failure&)
	{
		throw exception("Error loading config or last print time file.");
	}
	catch (exception&)
	{
		throw;
	}
}

void PrinterMaintainer::SafeInitialization()
{
	InitializeConfig();
	InitializeLastPrintTime();
}

void PrinterMaintainer::InitializeConfig()
{
	configFile.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	configFile.open(configFilename, std::ios::in);
	configFile >> printToPrintTimeInDays;
	configFile.get(); //Gets newline character.
	std::getline(configFile, printingCommand);
	configFile.close();
}

void PrinterMaintainer::InitializeLastPrintTime()
{
	lastPrintTimeFile.exceptions(std::ios_base::badbit | std::ios_base::failbit);
	lastPrintTimeFile.open(lastPrintTimeFilename, std::ios::in);
	lastPrintTimeFile >> lastPrintTimeInSeconds;
	lastPrintTimeFile.close();
}

bool PrinterMaintainer::ShouldPrintTestPage() const
{
	const seconds lastPrintTime(lastPrintTimeInSeconds);
	const auto now = duration_cast<seconds>(system_clock::now().time_since_epoch());
	const auto timeSinceLastPrintingInSeconds = duration_cast<seconds>(now - lastPrintTime);
	const seconds printToPrintTimeInSeconds(printToPrintTimeInDays * 24 * 60 * 60);
	return timeSinceLastPrintingInSeconds > printToPrintTimeInSeconds;
}

void PrinterMaintainer::PrintTestPage()
{
	SavePrintingTime();
	system(printingCommand.c_str());
}

void PrinterMaintainer::SavePrintingTime(const int delayInDays)
{
	try
	{
		SafeSavePrintingTime(delayInDays);
	}
	catch (std::ios_base::failure&)
	{
		throw exception("Error saving last print time.");
	}
	catch (exception&)
	{
		throw;
	}
}

void PrinterMaintainer::SafeSavePrintingTime(const int delayInDays)
{
	lastPrintTimeFile.open(lastPrintTimeFilename, std::ios::out);
	const auto now = duration_cast<seconds>(system_clock::now().time_since_epoch());
	const seconds delayInSeconds(delayInDays * 24 * 60 * 60);
	lastPrintTimeFile << (now - delayInSeconds).count();
	lastPrintTimeFile.close();
}