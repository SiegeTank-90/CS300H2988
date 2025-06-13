//============================================================================
// Name        : main.cpp
// Author      : C.J. CLINE
// Version     : 1.0
// Description : A demostation of binary tree data structure using a list of CompSci Course
//============================================================================


#include <iostream>
#include <fstream>
#include "Course.hpp"
#include "parser.hpp"


using namespace std;




// Main Program and Where the menu exists
int main() {
    // initilaize menu choice variable and data structure
    char choice = '0';
    BinaryCourseTree CourseCatalog;
    BinaryCourseTree TakenCourses; //Mosely used for the parser abstraction
    char DegChoice = '0';


    cout << "Welcome to the course planner." << endl << endl;

    // Loads until users selects exit (choice 9)
    while ( choice != '9') {
        string filename;


        cout << "\t 1. Load Data Structure." << endl;
        cout << "\t 2. Print Course List." << endl;
        cout << "\t 3. Print Course." << endl;
        cout << "\t 4. Load Previous Courses" << endl;
        cout << "\t 5. Choose & Print Degree Plan" << endl;
        cout << "\t 6. Remainder to Graduate (Must Choose a Degree Plan First)" << endl;
        cout << "\t 9. Exit." << endl << endl;

        cout << "What would you like to do? : " ;
        cin >> choice;
        cout << endl <<endl;
        switch (choice)
        {
        case '1':
            {
            // Parse data and place into Data Structure see parser.hpp
            cout << "Please enter the course catalog :: CourseList.txt :: ";
            cin >> filename;
            CourseCatalog = MyFileParser( filename, CourseCatalog);
            cin.clear();
            cin.ignore();
          
            }
            break;
        case '2':
        {
            // Print Course using BinaryCourseTree Functions see Course.hpp
            cout << "Here is a sammple schedule : " << endl << endl;
            CourseCatalog.PrintAll();
            cout << endl;
            break;
        }
        case '3': 
            // Find Course using BinaryCourse Tree Functions see  
            {
                string findCourseID = "";
                Course FoundCourse;
                cout << "What course whould you do you want to know about? :: ";
                cin >> findCourseID;
                cout << endl;
                FoundCourse = CourseCatalog.FindCourse(findCourseID);
                
                if (!(FoundCourse.getId() == "")) {
                    // Print Methods apart of course
                    FoundCourse.PrintCourse();
                    if (FoundCourse.PreReq.size() == 0 ){
                        cout << "No PreRequisites" << endl << endl;
                    } else {
                        FoundCourse.Prerequisites();
                        cout << endl;
                    }
                } else {
                    cout << findCourseID << " Could Not Be Found :: Case Sensitive" << endl<< endl;
                }       
            }      
            break;
        case '4':
            //Load your previously taken course list
            cout << "Previously taken course list :: ClassesTaken.txt :: ";
            cin >> filename;
            TakenCourses = MyFileParser(filename, TakenCourses);
            cin.clear();
            cin.ignore();
            break;

        case '5':
        {
     
            //Course your degreee program
            while (DegChoice != '4' ) {
                cout << "\t 1. Mathematics" << endl;
                cout << "\t 2. Computer Science" << endl;
                cout << "\t 3. Engineering" << endl;
                cout << "\t 4. Exit" << endl;
                cout << "\t Couse your Degree Program:";

                cin >> DegChoice;
                cin.clear();
                cin.ignore();

                if (DegChoice == '1') {
                    cout << endl << "\t Mathematics Degree Plan" << endl;
                    CourseCatalog.ChooseDegree("MATH310", CourseCatalog);
                    cout << "\t";
                    CourseCatalog.PrintDegree();
                    cout << endl << endl;



                }
                if (DegChoice == '2') {
                    cout << endl << "\t Computer Science Plan" << endl;
                    CourseCatalog.ChooseDegree("CSCI400", CourseCatalog);
                    cout << "\t";
                    CourseCatalog.PrintDegree();
                    cout << endl << endl;



                }
                if (DegChoice == '3') {
                    cout << endl << "\t Engineering Degree Plan" << endl;
                    CourseCatalog.ChooseDegree("ENGE400", CourseCatalog);
                    cout << "\t";
                    CourseCatalog.PrintDegree();
                    cout << endl << endl;



                }
                if (DegChoice == '4') {
                    cout << endl << endl;
                    break;
                }
      

            }

        
            break;

        }
        case '6':
            //Compare two lists
            cout << "Degree Plan:: "; 
            CourseCatalog.PrintDegree();
            cout << endl << "Classes Left to Graduate :: ";
            CourseCatalog.CompareDegreePlans(TakenCourses.getIdList());
            cout << endl << endl;

            break;
        case '9':
            // Exit case
            cout << "Thank you for using the course planner!" << endl << endl; 
            break;

        default:
            cout << choice << ": Is not a valid option." << endl << endl;
            cin.clear();
            cin.ignore();
            break;
        }

    }

    return 0;
}


// 