#include <fstream>
#include "interface.h"
#include "parser.h"

Interface::Interface(int new_id, bool record_rule)
    : ID(new_id), record_log(record_rule) {}

void Interface::start() {
    char input;
    std::cout << "Do you want to read commands from FILE? y/n" << std::endl;
    input = std::cin.get();
    switch (input) {
    case 'n': {
        std::cout << "Enter commands here:" << std::endl;
        read(std::cin);
        break;
    }
    case 'y': {
        std::string filename;
        std::cout << "Enter filename:" << std::endl;
        std::cin >> filename;

        std::ifstream input(filename);
        if (!input)
            std::cout << "Error reading file" << std::endl;
        else
            std::cout << "Reading commands..." << std::endl;

        read(input);
        break;
    }
    default:
        std::cout << "incorrect input." << std::endl;
        break;
    }
}


void Interface::read(std::istream& is) {
    std::string command, first_word;
    std::istringstream iss;
    if (is.peek() == '\n') is.get();
    while (std::getline(is, command)) {
        logger.log(command);
        try {
            auto token = parse(command);
            token->Evaluate(controller);
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
            logger.log(ex.what());
        } catch (UTILS cmd) {
            switch (cmd) {
            case UTILS::HELP: help(); break;
            case UTILS::LOG: log_out(); break;
            default:
                break;
            }
            if (cmd == UTILS::END)
                break;
        }
    }
}

void Interface::log_out() const {
    std::ofstream out("log.txt");
    out << logger.str();
}

void Interface::help() const  {
    std::ofstream help_f("help.txt");
    std::ostringstream os;
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
       << "\tPRINT <object>\n"
       << "\t\tPrints object to ./data folder\n"
       << "\t\tObject usage:\n"
       << "\t\tALL    - prints all clusters \n"
       << "\t\tALG WAVE   - prints result of wave algorithm\n"
       << "\t\tALG DBSCAN - prints result of DBScan algorithm\n"
       << "\tLOG\n"
       << "\t\tLogs all used commands in log.txt\n\n"
       << "\tEND\n"
       << "\t\tEnd of session\n\n";

    std::cout << os.str();
    help_f << os.str();
}
