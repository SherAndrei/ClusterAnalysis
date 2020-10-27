#include <fstream>
#include "interface.h"
#include "parser.h"

using namespace std;

Interface::Interface(int new_id, bool record_rule)
	: ID(new_id), record_log(record_rule)
	{}

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


void Interface::get_command(istream& is)
{
    string command, first_word;
    istringstream iss;
    is.get();
    while(getline(is, command))
    {
        try {
            auto token = parse(command);
            token->Evaluate(controller);
        } catch (const std::logic_error& ex) {
            std::cout << ex.what() << std::endl;
        
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
       << "\t\tGenerates cluster with listed parameters\n"
       << "\t\tIf nothing is listed, generates cluster with default parameters:\n"
       << "\t\tmeanX = 0, meanY = 0, varianceX = 1, varianceY = 1, N = 1'000\n\n"
       << "\tSTARSKY <minX>, <maxX>, <minY>, <maxY>, <N>\n"
       << "\t\tGenerates cluster evenly distributed on a rectangle [minX;maxX] x [minY;maxY]\n"
       << "\t\tIf nothing is listed, generates cluster with default parameters:\n"
       << "\t\tminX = 0, maxX = 1, minY = 0, maxY = 1, N = 1'000\n\n"
       << "\tPRINT\n"
       << "\t\tPrints all clusters to 'data' folder\n\n"
       << "\tLOG\n"
       << "\t\tLogs all used commands in log.txt\n\n"
       << "\tEND\n"
       << "\t\tEnd of session\n\n"
       << "\tTo plot clusters type in command line 'cd data && gnuplot' and then type'load 'plot.p'\n\n";

    cout << os.str();
    help_f << os.str();
}