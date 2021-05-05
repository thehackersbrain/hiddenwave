#include <iostream>

using namespace std;

void banner(){
	cout <<
"\033[1;92m  ___ ___ .__    .___  .___            __      __                     \n"
" /   |   \\|__| __| _/__| _/____   ____/  \\    /  \\________  __ ____  \n"
"/    ~    \\  |/ __ |/ __ |/ __ \\ /    \\   \\/\\/   /\\__  \\  \\/ // __ \\ \n"
"\\    Y    /  / /_/ / /_/ \\  ___/|   |  \\        /  / __ \\   /\\  ___/ \n"
" \\___|_  /|__\\____ \\____ |\\___  >___|  /\\__/\\  /  (____ /\\_/  \\___ >\n"
"       \\/         \\/    \\/    \\/     \\/      \\/        \\/         \\/ \n"
"            \033[92mHide Your Secret Message in Audio wave File.\033[0m\n\n"
"                     [Author: \033[1;92mTheHackersBrain\033[0m]\n\n";
}

void help(string packageName){
	cout << "Usage: " << packageName << " [-h] [-f AUDIOFILE] [-m SECRETMSG] [-o OUTFILE]\n\nArguments:\n"
    "   -h, --help     Show this help message and exit\n" 
    "   -f AUDIOFILE   Select Audio File\n"
    "   -m SECRETMSG   Enter Your Message\n"
    "   -o OUTPUTFILE  Name of the output file (with .wav extension)\n\n" << endl;
	system("read -p 'Press Enter to Continue...' var");
}

int argsHandler(int argc, char** argv) {
	if (argc == 7) {
		if ((string) argv[1] == "-f" || (string) argv[1] == "--file" && (string) argv[3] == "-m" || (string) argv[3] == "--message" && (string) argv[5] == "-o" || (string) argv[5] == "--output") {
			return 1;
		} else {
			help((string) argv[0]);
			return 0;
		}
	} else {
		help((string) argv[0]);
		return 0;
	}
}

int main(int argc, char** argv) {
	banner();
	string wavfile, message, outfile;
	// int argStatus = argsHandler(argc, argv);
	if (int argStatus = argsHandler(argc, argv) == 1) {
		wavfile = (string) argv[2];
		message = (string) argv[4];
		outfile = (string) argv[6];
		cout << "Input File: " << wavfile << "\nMessage: " << message << "\nOutFile: " << outfile << endl;
	}
	return 0;
}
