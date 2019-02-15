#include "../inc/PrinterMaintainer.h"
#include <Windows.h>

using std::string;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	const string configFilename = "config.txt";
	const string lastPrintTimeFilename = "lastPrintTime.dat";

	try {
		PrinterMaintainer printerMaintainer(configFilename, lastPrintTimeFilename);
		if (printerMaintainer.ShouldPrintTestPage()) {
			const int button = MessageBox(NULL, "Print test page?", "Printer Maintainer", MB_YESNOCANCEL | MB_ICONINFORMATION);
			switch (button)
			{
			case IDYES:
				printerMaintainer.PrintTestPage();
				break;
			case IDNO:
				printerMaintainer.SavePrintingTime(printerMaintainer.GetPrintToPrintTimeInDays()/2);
				break;
			default:
				break;
			}
		}
	}
	catch(std::exception& ex)
	{
		MessageBox(NULL, ex.what(), "Printer Maintainer", MB_OK | MB_ICONERROR);
		return 1;
	}

	return 0;
}
