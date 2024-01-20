#include "utils.h"

// LC: kill the terminal window wen the process is terminated
void killTerminal() {
# if defined(_WIN32) || defined(_WIN64)
    system("pause");
    system("TASKKILL /F /IM cmd.exe");
  #elif defined(__unix__) || defined(__APPLE__)
    cout << "Closing the terminal" << endl;
    sleep(1);
    system("kill -9 $(ps -p $PPID -o ppid=)");
  #else
    #error "Unknown system"
  #endif
}

// LC: cleaqr terminal output to display always the same message
void clearTerminal() {
  // Move the cursor to the start position for the messages
  std::cout << "\033[" << 12 << ";1H";
  // Clear the line
  std::cout << "\033[K";
}


// LC: a function to run shell commands inside ROS node
int runShellCommand(string command) {
  int result = system(command.c_str());
  if (result != 0) {
    ROS_ERROR("Failed to execute shell command");
    return 1;
  }
  return 0;
}

// LC: read json configuration file
Json::Value readJson( string in_path) {
  
  cout << "Configuration file path:" << in_path <<  endl;
  Json::Value root; // B.F.N object to hold the parsed json file
  Json::CharReaderBuilder readerBuilder; // B.F.N reader of json file

   ifstream file(in_path,  ifstream::binary); // B.F.N file to read
   cout <<in_path <<  endl;
   string errs; // B.F.N where the errors are memorized

  if (!file.is_open()) {
    cerr << "Could not open the file: " << in_path <<  endl;
    return Json::Value();
  }
  // B.F.N check if the parse is successfull
  bool parsingSuccessful = Json::parseFromStream(readerBuilder, file, &root, &errs);
  if (!parsingSuccessful) {
      cout << "Failed to parse JSON file: " << errs <<  endl;
      return Json::Value();
  }

  file.close();
  return root;
}
