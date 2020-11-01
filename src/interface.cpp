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
    case 0: {
        cout << "Enter commands here:" << endl;
        get_command(cin);
        break;
    }
    case 1: {
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
    if(is.peek() == '\n') is.get();
    while(getline(is, command))
    {   
        logger.log(command);
        try {
            auto token = parse(command);
            token->Evaluate(controller);
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
            logger.log(ex.what());
        } catch (UTILS cmd) {
            switch (cmd)
            {
            case UTILS::HELP: help(); break;
            case UTILS::LOG: log_out(); break;
            default:
                break;
            }
            if(cmd == UTILS::END)
                break;
        }
    }
}

void Interface::log_out() const
{
    ofstream out("log.txt");
    out << logger.str();
}

void Interface::help() const 
{
    ofstream help_f("help.txt");
    ostringstream os;
    os << "Usage:\n"
       << "\tSETUP <mode>\n"
       << "\tSetup mode for working with field:\n"
       << "\t\tMode usage:\n"
       << "\t\tGENERATE\n"
       << "\t\tSEARCH\n"
       << "\tGENERATE <entity> ...params\n"
       << "\tGenerates cluster - entity - with listed parameters\n"
       << "\t\tEntity usage: \n"
       << "\t\tCLOUD   <meanX> <meanY> <varianceX> <varianceY> <N> \n"
       << "\t\tSTARSKY <minX> <maxX> <minY> <maxY> <N>\n"
       << "\tSEARCH <algorithm> ...params\n"
       << "\tSearch clusters with algorithm\n"
       << "\t\tAlogrithm usage:\n"
       << "\t\tWAVE <delta>\n"
       << "\t\tDBSCAN <D> <K>\n"
    //    << "\tPRINT\n"
    //    << "\t\tPrints all clusters to 'data' folder\n\n"
       << "\tLOG\n"
       << "\t\tLogs all used commands in log.txt\n\n"
       << "\tEND\n"
       << "\t\tEnd of session\n\n";

    cout << os.str();
    help_f << os.str();
}