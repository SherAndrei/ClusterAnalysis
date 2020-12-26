#include "interface.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "parser.h"

Interface::Interface(int new_id, bool record_rule)
    : logger(new_id, record_rule) {}

void Interface::start(int argc, char* argv[]) {
    if (!(argc == 1 || argc == 2)) {
        throw std::invalid_argument("Usage: " + std::string(argv[0]) + " [optional: filename]");
    }
    switch (argc) {
    case 1: {
        std::cout << "Enter commands here:" << std::endl;
        read(std::cin);
        break;
    }
    case 2: {
        std::string filename(argv[1]);
        std::ifstream input(filename);
        if (!input)
            std::cout << "Cannot open file" << std::endl;
        else
            std::cout << "Reading commands..." << std::endl;

        read(input);
        break;
    }
    default:
        break;
    }
}

void Interface::read(std::istream& is) {
    std::string command;
    if (is.peek() == '\n') is.get();

    while (std::getline(is, command)) {
        logger.log(command);
        try {
            auto token = parse(command);
            token->Evaluate(controller);
        } catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl
                      << "Logs dumped in log.txt" << std::endl;
            logger.log(ex.what());
            log_out();
        } catch (UTILS uti) {
            switch (uti) {
            case UTILS::HELP: help();
                break;
            case UTILS::LOG: log_out();
                break;
            default:
                break;
            }
            if (uti == UTILS::END) {
                break;
        }
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
