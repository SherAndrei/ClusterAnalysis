#include <fstream>
#include "interface.h"

using namespace std;

void/*???*/ Interface::get_command(istream& os)
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
            // ok = ok && os.eof();
            if (!ok) {
                cout << "Wrong format!" << endl;
                return;
            }
            controller.generate_cloud(meanX, meanY, varianceX, varianceY, N);
        } else if (command == "GC") {
            controller.generate_cloud(0., 0., 1., 1., 1000);
        } else if (command == "PRINT") {
            string filename;
            bool ok = true;
            ok = ok && (os >> filename);
            // ok = ok && os.eof();
            if (!ok) {
                cout << "Wrong format: " << filename << endl;
                return;
            }
            controller.print_to_file(filename); 
        }
    }
}

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
        ifstream input;
        string filename;
        cout << "Enter filename:" << endl;
        cin >> filename;
        filename = "in/" + filename;
        input.open(filename);
        cout << "Reading commands from file..." << endl;
        get_command(input);
        break;
    }
    default:
        cout << "Wrong input!" << endl;
        break;
    }
}