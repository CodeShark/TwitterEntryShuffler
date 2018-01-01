#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "hash.h"

using namespace std;

typedef pair<string, uchar_vector> t_handlehashpair;

uchar_vector secret("50D858E0985ECC7F60418AAF0CC5AB587F42C2570A884095A9E8CCACD0F6545C");
uchar_vector blockHash("00000000000000000024fb37364cbf81fd49cc2d51c09c75c35433c3a1945d04");

string getLowercase(const string& s)
{
    string s_lower(s);
    transform(s_lower.begin(), s_lower.end(), s_lower.begin(), ::tolower);
    return s_lower;
}

string getHandleFromUrl(const string& url)
{
    regex e("https://twitter.com/([^/]*)");
    smatch m;
    if (!regex_search(url, m, e))
    {
        stringstream ss;
        ss << "Invalid url encountered: " << url;
        throw runtime_error(ss.str());
    }

    return m[1];
}

uchar_vector getHandleHash(const string& handle, const uchar_vector& nonce)
{
    uchar_vector hash;
    string handle_lower = getLowercase(handle);
    for (auto c: handle_lower)
    {
        hash.push_back((unsigned char)c);
    }

    hash << nonce;
    return sha256_2(hash);
}

bool sortByHandleHash(const t_handlehashpair& h1, const t_handlehashpair& h2)
{
    return h1.second < h2.second;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "#Usage: " << argv[0] << " <source file> <destination file>" << endl;
        return -1;
    }

    string line;
    vector<t_handlehashpair> handlehashpairs;
    uchar_vector nonce = secret ^ blockHash;

/*
    cout << "secret:     " << secret.getHex() << endl;
    cout << "block hash: " << blockHash.getHex() << endl;
    cout << "nonce:      " << nonce.getHex() << endl;

    return 0;
*/

    ifstream inputFile(argv[1]);
    while (getline(inputFile, line))
    {
        string handle = getHandleFromUrl(line);
        handlehashpairs.push_back(make_pair(handle, getHandleHash(handle, nonce)));
    }

    try
    {
        sort(handlehashpairs.begin(), handlehashpairs.end(), sortByHandleHash);
    }
    catch (exception& e)
    {
        cerr << e.what() << endl;
        return -2;
    }

    ofstream outputFile(argv[2], ofstream::trunc); 
    for (auto handlehashpair: handlehashpairs)
    {
        outputFile << handlehashpair.second.getHex() << " " << handlehashpair.first << endl;
    }

    return 0;
}
