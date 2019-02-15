# Printer-Maintainer

A program that helps user in keeping printer's head in good health.

## Usage

The program prints a test page in pdf format every X days, where X is a number of days specified by user. You can find whole program ready to use [here](Printer%20Maintainer/Printer%20Maintainer/v1.0). The easiest way of using it is putting a shortcut to the program in Windows autostart folder so the program will run once every system startup. If printing is needed, a window will pop up asking if you want to print a test page. Options are:
* Yes - print test page.
* No - doesn't print test page, window will pop up again after X/2 days.
* Cancel/Exit - window will pop up again next time the program is launched.

## Config file

Config file has 2 lines:
* Time interval in days (integer value).
* String, which is a system command using PDFtoPrinter program for printing test page. It's format is "*printing_program_name*.exe *test_file_name*.pdf *printer_name*". You can read more about available options on [PDFToPrinter website](http://www.columbia.edu/~em36/pdftoprinter.html).

## Notes

* Remember that config.txt, lastPrintTime.dat, PDFToPrinter.exe and the program itself has to be in the same directory to work properly.
* Program doesn't run in background, after running it just checks if printing is needed. If printing is not needed the program won't show up at all.
* Program measures time from printing one test page to another. It does not track for how long a printer haven't been printing.
* You can use your own program for printing from command line or your own test page. The only thing you have to do is to modify config file following the format.
* Program uses PDFToPrinter program by Edward Mendelson, you can read more about it [here](http://www.columbia.edu/~em36/pdftoprinter.html).