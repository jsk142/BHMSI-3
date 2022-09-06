/*
* main.cpp
*
* COSC 051 Spring 2019
* Project #3
*
* Due on: March 21, 2019
* Author: jsk142
*
*
* In accordance with the class policies and Georgetown's
* Honor Code, I certify that, with the exception of the
* class resources and those items noted below, I have neither
* given nor received any assistance on this project.
*
* References not otherwise commented within the program source code.
* Note that you should not mention any help from the TAs, the professor,
* or any code taken from the class textbooks.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

const string PROMPT_WELCOME = "\nWelcome to the BHMSI move cost calculator.";
const string PROMPT_CHOICE = "\n\nPlease enter your choice: ";
const string PROMPT_ENTER = "The user entered: ";
const string ERROR_CHOICE = "Your previous selection was not a valid option...";
const string PROMPT_FILE = "Please enter the full path and filename to load: ";
const string PROMPT_CLEAR = "ALL vectors have been emptied of data.";
const string ERROR_CLEAR = "Nothing to do, vectors are already empty.";
const string ERROR_DISPLAY = "Please load at least one data file before attempting to display" 
                             "data.";
const string PROMPT_ESTIMATE = "Enter the estimate number to display: ";
const string PROMPT_BYE = "\nThank you for using the BHMSI move calculator" 
                          "(Menu Driven Version).";
const string ERROR_FILE_OPEN = "ERROR opening input data file, please check name and path:";
const string SUCCESS_FILE_OPEN = "File succesfully opened for input:";
const string PROMPT_TEST = "TESTING: output of each row of the file:";
const string ERROR_MOVE_SOON = "ERROR: the move date is too soon after the estimate date";
const string ERROR_MOVE_LONG = "ERROR: the move date is too long after the estimate date"; 
const string ERROR_MOVE_TYPE = "ERROR: the move type is not valid";
const string ERROR_DISTANCE = "ERROR: the distance of this move is over the maximum allowed";
const string ERROR_WEIGHT_MIN = "ERROR: the weight of items moved is under the minimum allowed";
const string ERROR_WEIGHT_MAX = "ERROR: the weight of items moved is over the maximum allowed";
const string ERROR_PIANO = "ERROR: the number of pianos moved is over the maximum allowed";
const string ERROR_ORIGIN = "ERROR: the answer for stairs > 15 at origin is not valid";
const string ERROR_DESTINATION = "ERROR: the answer for stairs > 15 at destination is not valid";
const string ERROR_CONTACT = "Conctact customer to resolve issues:  ";

const double PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B = 0.065;   
const double PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W = 0.256;
const double PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C = 0.459;
const double PRICE_PER_POUND_PER_MILE_B = 0.0011;
const double PRICE_PER_POUND_PER_MILE_W = 0.0011;
const double PRICE_PER_POUND_PER_MILE_C = 0.0012;

const int PIANO_SURCHARGE_0 = 275;
const int PIANO_SURCHARGE_1 = 575;
const int PIANO_SURCHARGE_2 = 1075;
const int STAIRS_SURCHARGE = 132;
const int DISTANCE_MAX = 3200;
const int WEIGHT_MAX = 18000;
const int PIANO_MAX = 3;

char displayMenu();


void loadFile(string fName, bool &loadSuccess, vector<char> &vTyp,
              vector<int> &vDst, vector<int> &vWgt, vector<int> &vPno,
              vector<char> &vSO, vector<char> &vSD,
              vector<string> &vNum, vector<string> &vReg);


void allDetails(const vector<char> &vTyp,
                const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                const vector<char> &vSO, const vector<char> &vSD,
                const vector<string> &vNum, const vector<string> &vReg);


void estimateDetails(const vector<char> &vTyp,
                     const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                     const vector<char> &vSO, const vector<char> &vSD,
                     const vector<string> &vNum, const vector<string> &vReg);


void summaryByType(const vector<char> &vTyp,
                   const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                   const vector<char> &vSO, const vector<char> &vSD,
                   const vector<string> &vNum, const vector<string> &vReg);


void summaryByRegion(const vector<char> &vTyp,
                     const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                     const vector<char> &vSO, const vector<char> &vSD,
                     const vector<string> &vNum, const vector<string> &vReg);

int main()
{
    char userChoice = '?';

    string fName = "";
  
    bool loadSuccess = true;

    vector<char> vTyp;
    vector<int> vDst;
    vector<int> vWgt;
    vector<int> vPno;
    vector<char> vSO; 
    vector<char> vSD;
    vector<string> vNum;
    vector<string> vReg;

    cout << PROMPT_WELCOME;


    do
    {
        userChoice = displayMenu();

        switch ( userChoice )
        {
            case 'L': cout << PROMPT_FILE;
                      cin >> fName;
                      loadFile(fName, loadSuccess, vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                      break;
            case 'A': allDetails(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                      break;
            case 'E': estimateDetails(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                      break;
            case 'T': summaryByType(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                      break;
            case 'R': summaryByRegion(vTyp, vDst, vWgt, vPno, vSO, vSD, vNum, vReg);
                      break;
            case 'C': if ( vTyp.size() == 0 )
                      {   cout << ERROR_CLEAR;
                      }
                      else
                      {   vTyp.clear();
                          vDst.clear();
                          vWgt.clear();
                          vPno.clear();
                          vSO.clear();
                          vSD.clear();
                          vNum.clear();
                          vReg.clear();
                      
                          cout << PROMPT_CLEAR;
                      }
        }

    } while ( userChoice != 'Q' );

    cout << PROMPT_BYE << endl << endl;

    return 0;
}

char displayMenu()
{
    char userChoice = '?';

    do
    {
        cout << "\n\n\n\n               Load a regional move data file     L" << endl;
        cout << "            display details (ALL loaded data)     A" << endl;
        cout << "    list details for specific Estimate number     E" << endl;
        cout << "                 display summary by move Type     T" << endl;
        cout << "                    display summary by Region     R" << endl;
        cout << "                               Clear all data     C" << endl;
        cout << "                                         Quit     Q" << endl;

        cout << PROMPT_CHOICE;
  
        cin >> userChoice;
        cin.ignore(500, '\n');
        userChoice = toupper(userChoice);

        if ( userChoice != 'L' && userChoice != 'A' && userChoice != 'E' && userChoice != 'T' &&
             userChoice != 'R' && userChoice != 'C' && userChoice != 'Q' )
        {   cout << ERROR_CHOICE;
        }

    } while ( userChoice != 'L' && userChoice != 'A' && userChoice != 'E' && userChoice != 'T' &&
              userChoice != 'R' && userChoice != 'C' && userChoice != 'Q' );

    cout << PROMPT_ENTER << userChoice << endl;

    return userChoice;
}

void loadFile(string fName, bool &loadSuccess, vector<char> &vTyp,
              vector<int> &vDst, vector<int> &vWgt, vector<int> &vPno,
              vector<char> &vSO, vector<char> &vSD,
              vector<string> &vNum, vector<string> &vReg)
{  
   ifstream inFile;
   string headings = "";
   string moveNumber = "";
   string nameAndEmail = "";
   string moveState = "";
   string moveRegion = "";
   
   char moveType, 
        originStairs,
        destinationStairs;
   char ch = '?';

   int orderYear,
       orderMonth,
       orderDay,
       moveYear,
       moveMonth,
       moveDay,
       moveDistance,
       minimumWeight,
       moveWeight,
       movePiano;
   int moveStairs = 0;
   int rowCount = 0;
   int errorCount = 0;
   int basicCount = 0;
   int wallCount = 0;
   int completeCount = 0;
   int distanceBTotal = 0;
   int distanceWTotal = 0;
   int distanceCTotal = 0;
   int weightBTotal = 0;
   int weightWTotal = 0;
   int weightCTotal = 0;

   double packingCost, 
          movingCost, 
          pianoCost, 
          stairsCost,
          totalCost;
   double costBTotal = 0;
   double costWTotal = 0;
   double costCTotal = 0;

   bool boolMove = true;
   bool boolDistance = true;

   cout << vTyp.size() << " records currently loaded." << endl;

   inFile.open( fName.c_str () );

   if ( !inFile ) //If file fails to open, output error message
   {   cout << ERROR_FILE_OPEN << endl << fName;
       loadSuccess = false;
   }

   if ( loadSuccess ) //If file succesfully opens, process data rows
   {   cout << SUCCESS_FILE_OPEN << endl << fName << endl;
              
       getline( inFile, headings );
   
       cout << "heading row: " << endl << headings << endl << endl;
       cout << PROMPT_TEST << endl << endl << endl;
       cout << "   Order       Move    Move      Dist.    Weight   Number    Stairs   Move" 
            << "          Total" << endl;
       cout << "   Date        Date    Code    (miles)   (pounds)  Pianos    O    D   Number" 
            << "        Cost ($)" << endl;
       cout << "-----------------------------------------------------------------------------" 
            << "----------------" << endl;

       while ( inFile >> moveNumber >> orderYear >> ch >> orderMonth >> ch >> orderDay >> moveYear
               >> ch >> moveMonth >> ch >> moveDay >> moveType >> moveDistance >> moveWeight 
               >> movePiano >> originStairs >> destinationStairs >> moveState >> moveRegion
               && getline( inFile, nameAndEmail ) )
       {
           rowCount++; 
           
           cout << setfill('0');
           cout << orderYear << "/" << setw(2) << orderMonth << "/" << setw(2) <<orderDay << "  ";
           cout << moveYear << "/" << setw(2) << moveMonth << "/" << setw(2) << moveDay << "  ";
           
           //Data validation
           //Output appropriate error messages

           if (moveDistance < 1)
           {   moveDistance = 1;
               minimumWeight = 1200;
           }

           else if (moveDistance >= 1 && moveDistance <= 600)
           {   minimumWeight = 1200;
           }

           else if (moveDistance > 600 && moveDistance <= DISTANCE_MAX)
           {   minimumWeight = 2 * moveDistance;
           }

           else
           {   boolDistance = false;
           }

           if (movePiano < 0)
           {   movePiano = 0;
           }

           cout << setfill(' ');
           cout << moveType << setw(11) << moveDistance << setw(11) << moveWeight << setw(7) 
                << movePiano;
           cout << "       " << originStairs << "    " << destinationStairs;
 
           if (moveYear != orderYear)
           {   moveMonth += 12;
           }

           if (moveMonth - orderMonth < 2)
           {   cout << endl << "        " << ERROR_MOVE_SOON;
               boolMove = false;
           }
 
           if (moveMonth - orderMonth >= 7)
           {   cout << endl << "        " << ERROR_MOVE_LONG;
               boolMove = false;
           }

           if (moveType != 'B' && moveType != 'b' && moveType != 'W' && moveType != 'w' 
               && moveType != 'C' && moveType != 'c')
           {   cout << endl << "        " << ERROR_MOVE_TYPE;
               boolMove = false;
           }

           if (!boolDistance)
           {   cout << endl << "        " << ERROR_DISTANCE;
               boolMove = false;
           }

           if (moveWeight < minimumWeight)
           {   cout << endl << "        " << ERROR_WEIGHT_MIN;
               boolMove = false;
           }

           if (moveWeight > WEIGHT_MAX)
           {   cout << endl << "        " << ERROR_WEIGHT_MAX;
               boolMove = false;
           }

           if (movePiano > PIANO_MAX)
           {   cout << endl << "        " << ERROR_PIANO;
               boolMove = false;
           }

           if (originStairs != 'Y' && originStairs != 'y' && originStairs != 'N' 
               && originStairs != 'n')
           {   cout << endl << "        " << ERROR_ORIGIN;
               boolMove = false;
           }

           if (destinationStairs != 'Y' && destinationStairs != 'y' && destinationStairs != 'N' 
               && destinationStairs != 'n')
           {   cout << endl << "        " << ERROR_DESTINATION;
               boolMove = false;
           }

           //If record contains errors, output customer's name and email

           if (!boolMove) 
           {   cout << endl << "        " << ERROR_CONTACT << nameAndEmail << endl << endl;
               errorCount++; 
           }
             
           //If record is correct, output the move estimate number and the total cost of the move

           if (boolMove) 
           {   vTyp.push_back(moveType);
               vDst.push_back(moveDistance);
               vWgt.push_back(moveWeight);
               vPno.push_back(movePiano);
               vSO.push_back(originStairs);
               vSD.push_back(destinationStairs);
               vNum.push_back(moveNumber);
               vReg.push_back(moveRegion);

               if (moveType == 'B' || moveType == 'b')
               {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B * moveWeight;
                   movingCost = PRICE_PER_POUND_PER_MILE_B * moveWeight * moveDistance;
               } 

               if (moveType == 'W' || moveType == 'w')
               {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W * moveWeight; 
                   movingCost = PRICE_PER_POUND_PER_MILE_W * moveWeight * moveDistance;
               } 

               if (moveType == 'C' || moveType == 'c')
               {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C * moveWeight;
                   movingCost = PRICE_PER_POUND_PER_MILE_C * moveWeight * moveDistance;
               } 

               if (originStairs == 'Y' || originStairs == 'y')
               {   moveStairs += 1;
               }

               if (destinationStairs == 'Y' || destinationStairs == 'y')
               {   moveStairs += 1;
               }

               if (moveStairs == 0)
               {   pianoCost = movePiano * PIANO_SURCHARGE_0;
                   stairsCost = moveStairs * STAIRS_SURCHARGE;
               }
               if (moveStairs == 1)
               {
                   pianoCost = movePiano * PIANO_SURCHARGE_1;
                   stairsCost = moveStairs * STAIRS_SURCHARGE;
               }

               if (moveStairs == 2)
               {   pianoCost = movePiano * PIANO_SURCHARGE_2;
                   stairsCost = moveStairs * STAIRS_SURCHARGE;
               }
     
               totalCost = packingCost + movingCost + pianoCost + stairsCost;

               //Keep counters and running totals for each type of move

               if (moveType == 'B' || moveType == 'b')
               {   basicCount++;
                   distanceBTotal += moveDistance;
                   weightBTotal += moveWeight;
                   costBTotal += totalCost;
               } 

               if (moveType == 'W' || moveType == 'w')
               {   wallCount++;
                   distanceWTotal += moveDistance;
                   weightWTotal += moveWeight;
                   costWTotal += totalCost;
               }        

               if (moveType == 'C' || moveType == 'c')
               {   completeCount++;
                   distanceCTotal += moveDistance;
                   weightCTotal += moveWeight;
                   costCTotal += totalCost;
               }   

               cout << fixed << showpoint << setprecision(2);
               cout << "  " << moveNumber << setw(12) << totalCost << endl;
           }

           boolMove = true;
           boolDistance = true;
           moveStairs = 0;
       }

       inFile.close();

       //Output summary table
  
       cout << endl << endl << endl << "Total Records = " << rowCount;
       cout << "  Records with Errors = " << errorCount;
       cout << "  Records without Errors = " << (rowCount - errorCount) << endl << endl;
       cout << "                  " << "TOTALS (records without errors)" << endl << endl;
       cout << "       Type        Count    Distance     Weight        Cost" << endl;
       cout << "       ----------------------------------------------------------" << endl;
       cout << "       Basic" << setw(11) << basicCount << setw(12) << distanceBTotal 
            << setw(12) << weightBTotal << "   $" << setw(12) << costBTotal << endl;
       cout << "       Wall Pack" << setw(7) << wallCount << setw(12) << distanceWTotal 
            << setw(12) << weightWTotal << "   $" << setw(12) << costWTotal << endl;
       cout << "       Complete" << setw(8) << completeCount << setw(12) << distanceCTotal 
            << setw(12) << weightCTotal << "   $" << setw(12) << costCTotal << endl << endl;
       cout << "        " << (rowCount - errorCount) << " added to vectors, " << vTyp.size()
            << " total records now loaded.";

   }

}     

void allDetails(const vector<char> &vTyp,
                const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                const vector<char> &vSO, const vector<char> &vSD,
                const vector<string> &vNum, const vector<string> &vReg)
{  
   int moveStairs = 0;

   double packingCost, 
          movingCost, 
          pianoCost, 
          stairsCost;

   double totalCost = 0;
   double finalTotalCost = 0;

    if ( vTyp.size() == 0 )
    {   cout << ERROR_DISPLAY;
    }
    else
    {   cout << "    Move      Dist.    Weight   Number    Stairs   Move         Total" << endl;
        cout << "    Type    (miles)   (pounds)  Pianos    O    D   Number       Cost ($)" 
             << endl;
        cout << "----------------------------------------------------------------------------" 
             << endl;

        for (int count = 0; count < vTyp.size(); count++)
        {
            if (vTyp.at(count) == 'B' || vTyp.at(count) == 'b')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B * vWgt.at(count);
                movingCost = PRICE_PER_POUND_PER_MILE_B * vWgt.at(count) * vDst.at(count);
            } 

            if (vTyp.at(count) == 'W' || vTyp.at(count) == 'w')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W * vWgt.at(count); 
                movingCost = PRICE_PER_POUND_PER_MILE_W * vWgt.at(count) * vDst.at(count);
            } 

            if (vTyp.at(count) == 'C' || vTyp.at(count) == 'c')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C * vWgt.at(count);
                movingCost = PRICE_PER_POUND_PER_MILE_C * vWgt.at(count) * vDst.at(count);
            } 

            if (vSO.at(count) == 'Y' || vSO.at(count) == 'y')
            {   moveStairs += 1;
            }

            if (vSD.at(count) == 'Y' || vSD.at(count) == 'y')
            {   moveStairs += 1;
            }

            if (moveStairs == 0)
            {   pianoCost = vPno.at(count) * PIANO_SURCHARGE_0;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }
  
            if (moveStairs == 1)
            {
                pianoCost = vPno.at(count) * PIANO_SURCHARGE_1;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }

            if (moveStairs == 2)
            {   pianoCost = vPno.at(count) * PIANO_SURCHARGE_2;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }

            totalCost = packingCost + movingCost + pianoCost + stairsCost;

            finalTotalCost += totalCost;

            cout << "     " << vTyp.at(count) << setw(11) << vDst.at(count) << setw(11) 
                 << vWgt.at(count) << setw(7) << vPno.at(count) << "       " << vSO.at(count)
                 << "    " << vSD.at(count) << "  " << vNum.at(count) << setw(12) << totalCost 
                 << endl;

            moveStairs = 0;
        }

    cout << endl << endl << setw(14) << vTyp.size() << " total records." << endl;
    cout << setw(14) << finalTotalCost << " total of all move charges." << endl;
    cout << setw(14) << (finalTotalCost / vTyp.size()) << " average of all move charges.";


    }
}

void estimateDetails(const vector<char> &vTyp,
                     const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                     const vector<char> &vSO, const vector<char> &vSD,
                     const vector<string> &vNum, const vector<string> &vReg)
{  
    string estimateNumber = "";
    bool numberFound = false;
    int count = 0;
    int i = 0;

    int moveStairs = 0;

    double packingCost, 
           movingCost, 
           pianoCost, 
           stairsCost;

    double totalCost = 0;

    if ( vTyp.size() == 0 )
    {   cout << ERROR_DISPLAY;
    }
    else 
    {   cout << PROMPT_ESTIMATE << endl;
        cin >> estimateNumber;

        while ( i < vTyp.size() && !numberFound )
        {            
            if ( vNum.at(i) == estimateNumber )
            {   numberFound = true;
                count = i;
            }

            i++;
        }
       
        if ( !numberFound )
        {   cout << "Estimate number: " << estimateNumber << " not found.";

        }
        else
        {   if (vTyp.at(count) == 'B' || vTyp.at(count) == 'b')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B * vWgt.at(count);
                movingCost = PRICE_PER_POUND_PER_MILE_B * vWgt.at(count) * vDst.at(count);
            } 

            if (vTyp.at(count) == 'W' || vTyp.at(count) == 'w')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W * vWgt.at(count); 
                movingCost = PRICE_PER_POUND_PER_MILE_W * vWgt.at(count) * vDst.at(count);
            } 

            if (vTyp.at(count) == 'C' || vTyp.at(count) == 'c')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C * vWgt.at(count);
                movingCost = PRICE_PER_POUND_PER_MILE_C * vWgt.at(count) * vDst.at(count);
            } 

            if (vSO.at(count) == 'Y' || vSO.at(count) == 'y')
            {   moveStairs += 1;
            }

            if (vSD.at(count) == 'Y' || vSD.at(count) == 'y')
            {   moveStairs += 1;
            }

            if (moveStairs == 0)
            {   pianoCost = vPno.at(count) * PIANO_SURCHARGE_0;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }
  
            if (moveStairs == 1)
            {
                pianoCost = vPno.at(count) * PIANO_SURCHARGE_1;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }

            if (moveStairs == 2)
            {   pianoCost = vPno.at(count) * PIANO_SURCHARGE_2;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }

            totalCost = packingCost + movingCost + pianoCost + stairsCost;

            cout << "    Move      Dist.    Weight   Number    Stairs   Move         Total" 
                 << endl;
            cout << "    Type    (miles)   (pounds)  Pianos    O    D   Number       Cost ($)" 
                 << endl;
            cout << "----------------------------------------------------------------------------"
                 << endl;
            cout << "     " << vTyp.at(count) << setw(11) << vDst.at(count) << setw(11) 
                 << vWgt.at(count) << setw(7) << vPno.at(count) << "       " << vSO.at(count) 
                 << "    " << vSD.at(count) << "  " << vNum.at(count) << setw(12) << totalCost;
        }
    }
}

void summaryByType(const vector<char> &vTyp,
                   const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                   const vector<char> &vSO, const vector<char> &vSD,
                   const vector<string> &vNum, const vector<string> &vReg)
{   
    int basicCount = 0;
    int wallCount = 0;
    int completeCount = 0;
    int distanceBTotal = 0;
    int distanceWTotal = 0;
    int distanceCTotal = 0;
    int weightBTotal = 0;
    int weightWTotal = 0;
    int weightCTotal = 0;
    int distanceTotal = 0;
    int weightTotal = 0;

    int moveStairs = 0;

    double packingCost, 
           movingCost, 
           pianoCost, 
           stairsCost;

    double costBTotal = 0;
    double costWTotal = 0;
    double costCTotal = 0;

    double totalCost = 0; 
    double finalTotalCost = 0;

    if ( vTyp.size() == 0 )
    {   cout << ERROR_DISPLAY;
    }        
    else
    {   for (int count=0; count < vTyp.size(); count++)
        {   
            if (vTyp.at(count) == 'B' || vTyp.at(count) == 'b')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B * vWgt.at(count);
                movingCost = PRICE_PER_POUND_PER_MILE_B * vWgt.at(count) * vDst.at(count);
            } 

            if (vTyp.at(count) == 'W' || vTyp.at(count) == 'w')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W * vWgt.at(count); 
                movingCost = PRICE_PER_POUND_PER_MILE_W * vWgt.at(count) * vDst.at(count);
            } 

            if (vTyp.at(count) == 'C' || vTyp.at(count) == 'c')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C * vWgt.at(count);
                movingCost = PRICE_PER_POUND_PER_MILE_C * vWgt.at(count) * vDst.at(count);
            } 

            if (vSO.at(count) == 'Y' || vSO.at(count) == 'y')
            {   moveStairs += 1;
            }

            if (vSD.at(count) == 'Y' || vSD.at(count) == 'y')
            {   moveStairs += 1;
            }

            if (moveStairs == 0)
            {   pianoCost = vPno.at(count) * PIANO_SURCHARGE_0;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }
  
            if (moveStairs == 1)
            {
                pianoCost = vPno.at(count) * PIANO_SURCHARGE_1;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }

            if (moveStairs == 2)
            {   pianoCost = vPno.at(count) * PIANO_SURCHARGE_2;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }

            totalCost = packingCost + movingCost + pianoCost + stairsCost;

            moveStairs = 0;

            if ( vTyp.at(count) == 'b' || vTyp.at(count) == 'B' )
            {   basicCount++;
                distanceBTotal += vDst.at(count);
                weightBTotal += vWgt.at(count);
                costBTotal += totalCost;  
            }
            if ( vTyp.at(count) == 'w' || vTyp.at(count) == 'W' )
            {   wallCount++;
                distanceWTotal += vDst.at(count);
                weightWTotal += vWgt.at(count);
                costWTotal += totalCost;
            }
            if ( vTyp.at(count) == 'c' || vTyp.at(count) == 'C' )
            {   completeCount++;
                distanceCTotal += vDst.at(count);
                weightCTotal += vWgt.at(count);
                costCTotal += totalCost;
            }
        }   
  
        distanceTotal = distanceBTotal + distanceWTotal + distanceCTotal;
        weightTotal = weightBTotal + weightWTotal + weightCTotal;
        finalTotalCost = costBTotal + costWTotal + costCTotal;
        
        cout << "                   TOTALS ( " << vTyp.size() << " records )" << endl << endl;
        cout << "        Type        Count    Distance     Weight        Cost" << endl;
        cout << "------------------------------------------------------------------" << endl;
        cout << "        Basic" << setw(11) << basicCount << setw(12) << distanceBTotal 
             << setw(12) << weightBTotal << "   $" << setw(12) << costBTotal << endl;
        cout << "        Wall Pack" << setw(7) << wallCount << setw(12) << distanceWTotal 
             << setw(12) << weightWTotal << "   $" << setw(12) << costWTotal << endl;        
        cout << "        Complete" << setw(8) << completeCount << setw(12) << distanceCTotal 
             << setw(12) << weightCTotal << "   $" << setw(12) << costCTotal << endl;
        cout << "------------------------------------------------------------------" << endl;
        cout << "        Total" << setw(11) << vTyp.size() << setw(12) << distanceTotal 
             << setw(12) << weightTotal << "   $" << setw(12) << finalTotalCost << endl;
    }
}

void summaryByRegion(const vector<char> &vTyp,
                     const vector<int> &vDst, const vector<int> &vWgt, const vector<int> &vPno,
                     const vector<char> &vSO, const vector<char> &vSD,
                     const vector<string> &vNum, const vector<string> &vReg)
{   
    int westCount = 0;
    int southCount = 0;
    int northCount = 0;
    int eastCount = 0;
    int otherCount = 0;
    int distanceWTotal = 0;
    int distanceSTotal = 0;
    int distanceNTotal = 0;
    int distanceETotal = 0;
    int distanceOTotal = 0;
    int weightWTotal = 0;
    int weightSTotal = 0;
    int weightNTotal = 0;
    int weightETotal = 0;
    int weightOTotal = 0;
    int distanceTotal = 0;
    int weightTotal = 0;

    int moveStairs = 0;

    double packingCost, 
           movingCost, 
           pianoCost, 
           stairsCost;

    double costWTotal = 0;
    double costSTotal = 0;
    double costNTotal = 0;
    double costETotal = 0;
    double costOTotal = 0;

    double totalCost = 0; 
    double finalTotalCost = 0;


    if ( vTyp.size() == 0 )
    {   cout << ERROR_DISPLAY;
    }        
    else
    {   for (int count=0; count < vTyp.size(); count++)
        {
            if (vTyp.at(count) == 'B' || vTyp.at(count) == 'b')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_B * vWgt.at(count);
                movingCost = PRICE_PER_POUND_PER_MILE_B * vWgt.at(count) * vDst.at(count);
            } 

            if (vTyp.at(count) == 'W' || vTyp.at(count) == 'w')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_W * vWgt.at(count); 
                movingCost = PRICE_PER_POUND_PER_MILE_W * vWgt.at(count) * vDst.at(count);
            } 

            if (vTyp.at(count) == 'C' || vTyp.at(count) == 'c')
            {   packingCost = PRICE_PER_POUND_FOR_PACKING_AND_LOADING_C * vWgt.at(count);
                movingCost = PRICE_PER_POUND_PER_MILE_C * vWgt.at(count) * vDst.at(count);
            }
            if (vSO.at(count) == 'Y' || vSO.at(count) == 'y')
            {   moveStairs += 1;
            }

            if (vSD.at(count) == 'Y' || vSD.at(count) == 'y')
            {   moveStairs += 1;
            }

            if (moveStairs == 0)
            {   pianoCost = vPno.at(count) * PIANO_SURCHARGE_0;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }
  
            if (moveStairs == 1)
            {
                pianoCost = vPno.at(count) * PIANO_SURCHARGE_1;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }

            if (moveStairs == 2)
            {   pianoCost = vPno.at(count) * PIANO_SURCHARGE_2;
                stairsCost = moveStairs * STAIRS_SURCHARGE;
            }

            totalCost = packingCost + movingCost + pianoCost + stairsCost;

            moveStairs = 0;

            if ( vReg.at(count) == "West" )
            {   westCount++;
                distanceWTotal += vDst.at(count);
                weightWTotal += vWgt.at(count);
                costWTotal += totalCost;
            }
            if ( vReg.at(count) == "South" )
            {   southCount++;
                distanceSTotal += vDst.at(count);
                weightSTotal += vWgt.at(count);
                costSTotal += totalCost;
            }
            if ( vReg.at(count) == "North" )
            {   northCount++;
                distanceNTotal += vDst.at(count);
                weightNTotal += vWgt.at(count);
                costNTotal += totalCost;
            }
            if ( vReg.at(count) == "East" )
            {   eastCount++;
                distanceETotal += vDst.at(count);
                weightETotal += vWgt.at(count);
                costETotal += totalCost;
            }     
            if ( vReg.at(count) == "Other" )
            {   otherCount++;
                distanceOTotal += vDst.at(count);
                weightOTotal += vWgt.at(count);
                costOTotal += totalCost;
            }     
        }

        distanceTotal = distanceWTotal + distanceSTotal + distanceNTotal + distanceETotal + 
                        distanceOTotal;
        weightTotal = weightWTotal + weightSTotal + weightNTotal + weightETotal + weightOTotal;
        finalTotalCost = costWTotal + costSTotal + costNTotal + costETotal + costOTotal;

        cout << "                   TOTALS ( " << vTyp.size() << " records )" << endl << endl;
        cout << "        Type        Count    Distance     Weight        Cost" << endl;
        cout << "------------------------------------------------------------------" << endl;
        cout << "        South" << setw(11) << southCount << setw(12) << distanceSTotal 
             << setw(12) << weightSTotal << "   $" << setw(12) << costSTotal << endl;
        cout << "        West" << setw(12) << westCount << setw(12) << distanceWTotal 
             << setw(12) << weightWTotal << "   $" << setw(12) << costWTotal << endl;
        cout << "        North" << setw(11) << northCount << setw(12) << distanceNTotal 
             << setw(12) << weightNTotal << "   $" << setw(12) << costNTotal << endl;
        cout << "        East" << setw(12) << eastCount << setw(12) << distanceETotal 
             << setw(12) << weightETotal << "   $" << setw(12) << costETotal << endl;
        cout << "        Other" << setw(11) << otherCount << setw(12) << distanceOTotal 
             << setw(12) << weightOTotal << "   $" << setw(12) << costOTotal << endl;
        cout << "------------------------------------------------------------------" << endl;
        cout << "        Total" << setw(11) << vTyp.size() << setw(12) << distanceTotal 
             << setw(12) << weightTotal << "   $" << setw(12) << finalTotalCost << endl;
     
    }
}







    