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
        // filename = "in/" + filename;

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

void get_param(istream& is, bool& ok, double& param)
{
    if(ok) {
        if(is.peek() != ',') {
            ok = ok && is >> param;
        }
        is.ignore(1);
    }
}

void Interface::get_command(istream& is)
{
    string command;
    istringstream iss;
    while(is >> command)
    {
        if(command == "CREATE") {
            string parameters;
            getline(is >> ws, parameters);

            iss.clear();
            iss.str(parameters);
            
            bool ok = true;
            double meanX = 0;
            get_param(iss, ok, meanX);
            double meanY = 0.;
            get_param(iss, ok, meanY);
            double varianceX = 1.;
            get_param(iss, ok, varianceX);
            double varianceY = 1.;
            get_param(iss, ok, varianceY);
            
            int N = 1'000;
            if(ok && iss.peek() != EOF) {
                ok = ok && iss >> N;
            }

            if (!ok) {
                cout << "Wrong format: " << command << ' ' << parameters << '\n';
                log_in("Wrong format: " + command + ' ' + parameters);
                continue;
            }
            log_in(command + ' '  + to_string(meanX) + ", "
                                  + to_string(meanY) + ", "
                                  + to_string(varianceX) + ", "
                                  + to_string(varianceY) + ", "
                                  + to_string(N));
            
            controller.cloud(meanX, meanY, varianceX, varianceY, N);
        } else if (command == "STARSKY") {
            string parameters;
            getline(is >> ws, parameters);

            iss.clear();
            iss.str(parameters);
            
            bool ok = true;
            double minX = 0;
            get_param(iss, ok, minX);
            double maxX = 1.;
            get_param(iss, ok, maxX);
            double minY = 0.;
            get_param(iss, ok, minY);
            double maxY = 1.;
            get_param(iss, ok, maxY);
       
            int N = 1'000;
            if(ok && iss.peek() != EOF) {
                ok = ok && iss >> N;
            }

            if (!ok) {
                cout << "Wrong format: " << command << ' ' << parameters << '\n';
                log_in("Wrong format: " + command + ' ' + parameters);
                continue;
            }
            log_in(command + ' '  + to_string(minX) + ", "
                                  + to_string(maxX) + ", "
                                  + to_string(minY) + ", "
                                  + to_string(maxY) + ", "
                                  + to_string(N));
            

            controller.starsky(minX,maxX,minY,maxY,N);  
        } else if (command == "PRINT") {
            log_in(command);
            controller.print_to_file(); 
        } else if (command == "HELP") {
            log_in(command);
            help();
        } else if (command == "LOG") {
            log_in(command);
            log_out();
        } else if (command == "END") {
            break;
        } else {
            cout << "Unknown command: " << command << '\n'
                 << "Use HELP to see possible commands" << endl;
            log_in("Unknown command: " + command);
        }
        
    }
}

void Interface::log_in(const string& input)
{
    if(record_log)
        _log << input << '\n';
}
void Interface::log_out() const
{
    ofstream out("log.txt");
    out << _log.str();
    out.close();
}

void Interface::help() const 
{
    ofstream help_f("help.txt");
    ostringstream os;
    os << " Please list items with commas. Possible commands:\n"
       << "\tCREATE <meanX>, <meanY>, <varianceX>, <varianceY>, <N>\n"
       << "\t\tGenerates cloud with listed parameters\n"
       << "\t\tIf nothing is listed, generates cloud with default parameters:\n"
       << "\t\tmeanX = 0, meanY = 0, varianceX = 1, varianceY = 1, N = 1'000\n\n"
       << "\tSTARSKY <minX>, <maxX>, <minY>, <maxY>, <N>\n"
       << "\t\tGenerates cloud evenly distributed on a rectangle [minX;maxX] x [minY;maxY]\n"
       << "\t\tIf nothing is listed, generates cloud with default parameters:\n"
       << "\t\tminX = 0, maxX = 1, minY = 0, maxY = 1, N = 1'000\n\n"
       << "\tPRINT\n"
       << "\t\tPrints all clouds to 'data' folder\n\n"
       << "\tLOG\n"
       << "\t\tLogs all used commands in log.txt\n\n"
       << "\tEND\n"
       << "\t\tEnd of session\n\n"
       << "\tTo plot clouds type in command line 'cd data && gnuplot' and then type'load 'plot.p'\n\n";

    cout << os.str();
    help_f << os.str();
}