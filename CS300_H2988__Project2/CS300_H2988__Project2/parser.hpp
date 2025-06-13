#ifndef _parse_HPP_
#define _parser_HPP_

#include <iostream>
#include <string>
#include <fstream>
#include "Course.hpp"

using namespace std;




BinaryCourseTree MyFileParser(string filename, BinaryCourseTree DataStructure) {

    string line;
    ifstream CourseListFile (filename);

    if ( CourseListFile.is_open()) {

        while ( getline(CourseListFile,line)) {

                // set default variables 
                string TempString = line;
                int count = 0;
                string name;
                string courseid;
                vector<string> PreRecs = {};
                // count the number of commas in the line
                for ( unsigned i = 0; i < TempString.length(); i++) {
                    if (TempString[i] == ',') {
                        count++;
                    }
                }
               
               // Validate that there is at least 1 comma
                if (count < 1 ) {
                    cout << "Error :: " << TempString << " Is Not A Valid Entry:: No Commas" << endl;
                    cout << "Aborting File Load " << endl << endl;
                    break;
                }
                // Validate that the course id is exactly 7 characters
                if ( TempString.find(",") == 7) {
                           courseid = TempString.substr(0,7);
                }else {
                            cout << "Error :: " << TempString << " Is Not A Valid Entry:: ID is not 7 characters" << endl;
                            cout << "Aborting File Load " << endl << endl;
                            break;
                }

                // store temporary storage for course id & name
                courseid = TempString.substr(0,7);
                name = TempString.substr(8,TempString.find(',',8)-8);
                // store temporary vector storage for pre reqs
                if ( count > 1) {
                    size_t currPos = size_t(TempString.find(',',8));
                    while ( TempString.find(',', currPos) != size_t(-1) ){
                        PreRecs.push_back(TempString.substr(currPos+size_t(1), 7));
                        currPos = size_t(TempString.find(',', currPos+size_t(1)));
                    }
                }
                // Create course object and load it into the data structure
                Course nCourse(courseid,name,PreRecs);
                DataStructure.Insert(nCourse);
                    
            }
          CourseListFile.close();
          cout << "Data Loaded" << endl << endl;          
        } else {
            cout << "File Not Found." << endl << endl;
        }

    return DataStructure;
    }


#endif
