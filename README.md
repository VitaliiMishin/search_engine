Description

SearchEngine is a console application for searching lists of words in local text files.

This program uses libraries  
JSON for Modern C++ (https://github.com/nlohmann/json)   
GoogleTest (https://github.com/google/googletest)   

The program settings are contained in the config.json file:  
max_responses - the number of responses to display in the answers.json file  
name - the name of the search program, must match the name of the application.  
version - version of the search program, must match the current version of the application.  
files - a list of files that will be searched. Files must contain Latin characters.  
Search queries are contained in the requests.json file.  
The search result is saved to the answer.json file.  

Building the project

1. Clone the repository https://github.com/VitaliiMishin/search_engine
2. Go to the root directory of the project `C:\...\search_engine and execute the sequence of commands:   
   mkdir build  
   cd build  
   cmake..  
   cmake --build .
3. The program is launched by the search_engine.exe file.   
   The config.json and requests.json files should be in the json folder, the text files should be in the resources folder.  
   The answer file answer.json is saved in the json folder.   
   Tests are run by the tests.exe file.

Possible error messages

"Config file is missing" - could not open the config.json file;  
"Config file is empty!" - the config.json file is empty or does not meet the program requirements;  
"Requests file is missing!" - failed to open requests.json file;  
"Requests file is empty!" - the requests.json file is empty or does not meet the program requirements;  
"Text file missing!" - text file not found;  
"No documents to index!" - no text files were found;  
"Answers file not open!" - failed to create or open the answers.json file;  
"Invalid program name!" - the name of the search program in the config.json file did not match the name of the application;  
"Incorrect program version!" - the version of the search program in the config.json file did not match the version of the application.  
"Invalid JSON file!" - error parsing JSON file.