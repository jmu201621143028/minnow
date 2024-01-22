#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  Address addr(host, "http");
  TCPSocket tcpsk;
  tcpsk.connect(addr);
  vector<string> buffs;
  size_t send_sz = 0;
  buffs.push_back("GET " + string(path) + " HTTP/1.1\r\n");
  send_sz += buffs.back().size();
  buffs.push_back("Host: cs144.keithw.org\r\n");
  send_sz += buffs.back().size();
  buffs.push_back("Connection: close\r\n");
  send_sz += buffs.back().size();
  buffs.push_back("\r\n");
  send_sz += buffs.back().size();
  size_t ret = tcpsk.write(buffs);
  if (ret != send_sz) {
    cerr << "tcp socket error" << endl;
  }
  // cout << "tcpsk write " << ret << endl;
  string content;
  string hash_str;
  while (1) {
    tcpsk.read(content);
    if (content.size() == 0) { break; }
    if (content.size() == 1) {
      hash_str = hash_str + content;
    }
  }
  cout << hash_str ;
  tcpsk.close();
  cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  cerr << "Warning: get_URL() has not been implemented yet.\n";
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
