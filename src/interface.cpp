#include <fstream>
#include "interface.h"

using namespace std;

void Interface::start()
{
    int from_file = 0;
    cout << "Read commands from file 1, from konsole 0:" << endl;
    cin >> from_file;
    switch (from_file)
    {
    case 0:
    {
        cout << "Enter commands here:" << endl;
        get_command(cin);
        break;
    }
    case 1:
    {
        string filename;
        cout << "Enter filename:" << endl;
        cin >> filename;
        filename = "in/" + filename;

        ifstream input(filename);
        cout << "Reading commands from file..." << endl;
        get_command(input);
        break;
    }
    default:
        cout << "Wrong input!" << endl;
        break;
    }
}
void Interface::get_command(istream& os)
{
    string command;
    while(os >> command)
    {
        if(command == "GEN CLOUD") {
            double meanX, meanY, varianceX, varianceY;
            int N;

            bool ok = true;
            ok = ok && (os >> meanX);
            ok = ok && (os >> meanY);
            ok = ok && (os >> varianceX);
            ok = ok && (os >> varianceY);
            ok = ok && (os >> N);
            if (!ok) {
                cout << "Wrong format!" << endl;
                return;
            }
            if(record_log) {
                _log << command << ' ' << meanX 
                                << ' ' << meanY
                                << ' ' << varianceX
                                << ' ' << varianceY
                                << ' ' << N << '\n';
            }
            controller.generate_cloud(meanX, meanY, varianceX, varianceY, N);
        } else if (command == "GC") {
             if(record_log) 
                _log << command << '\n';
            controller.generate_cloud(0., 0., 1., 1., 1000);
        } else if (command == "PRINT") {
            if(record_log)
                _log << "HELP" << '\n';
            controller.print_to_file(); 
        } else if (command == "HELP") {
            if(record_log)
                _log << "HELP" << '\n';
            help();
        } else if (command == "LOG") {
            if(record_log)
                _log << "LOG" << '\n';
            log();
        }
        
    }
}

void Interface::log() 
{
    ofstream out("log.txt");
    out << _log.str();
    out.close();
}

void Interface::help() const 
{
    cout << "Possible commands:\n"
         << "\tGEN CLOUD <meanX> <meanY> <varianceX> <varianceY> <N>\n"
         << "\t\tGenerates cloud with listed parameters\n"
         << "\tGC\n"
         << "\t\tGenerates cloud with default parameters:\n"
         << "\t\tmeanX = 0, meanY = 0, varianceX = 1, varianceY = 1, N = 1'000\n"
         << "\tPRINT\n"
         << "\t\tPrints all data to output.txt\n"
         << "\tLOG\n"
         << "\t\tLogs all used commands in log.txt\n";
}