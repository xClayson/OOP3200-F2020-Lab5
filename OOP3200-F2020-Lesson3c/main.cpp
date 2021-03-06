/* OOP 3200 - C++ Lab 5 - Standard Template Library
 * Ryan Clayson and Daniel Hinbest
 * 100558837		100717231
 * October 25, 2020
 */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>

#include "Vector2D.h"

int main()
{
	try
	{
		/************************
		 *	DECLARATIONS
		 ************************/
		std::map<std::string, Vector2D<int>*> coordinatesMap;
		std::string userInput{};
		std::ifstream infile;
		std::string fileName;
		int totalDistance{};
		
		/******************************************************************************
		 *	Reading Labels/Points into the Map:
		 *	Attempt to open the data file.  If the data file opens, read a label,
		 *	followed by a point and insert them into the map using the label as the key.
		 *	Repeat until all the data is read and close the file. If the data file did
		 *	not open, tell the user and remind them to check that the file exists. If
		 *	the file opened but the map is empty after the input loop, report that to
		 *	the user and remind them to check that the file contains valid data in
		 *	the correct format. Only continue processing if the file was opened and the
		 *	map is not empty.
		 ******************************************************************************/
		//Asks user to enter file
		std::cout << "Please enter file to open: ";
		std::cin >> fileName;		
		infile.open(fileName.c_str());

		//Checks to see if file exists or not
		//If exists proceeds. If not show error message
		if (infile.fail())
		{
			std::cout << fileName << " could not be opened. Make sure this file exists.\n";
		}
		//Checks to see if file is empty or not
		//If not empty proceeds. If empty show error message
		else if (infile.peek() == std::ifstream::traits_type::eof())
		{
			std::cout << fileName << " is an empty file. Check to see if the file is in proper format and has valid data.\n";
		}
		//File is opened
		else
		{
			//Declarations
			int x, y;
			std::string points;

			//Loop which grabs important information from file and ignores white space and punctuation
			while (!infile.fail())
			{
				infile >> points;
				infile.ignore(1, ' ');
				infile.ignore(1, '(');
				infile >> x;
				infile.ignore(1, ',');
				infile.ignore(1, ' ');
				infile >> y;
				infile.ignore(1, ')');

				auto* temp_object = new Vector2D<int>(x, y);

				//adds points gathered from file to temp_object
				coordinatesMap[points] = temp_object;
			}
			infile.close();
		}
			

		/******************************************************************************
		 *	Determine the Total Distance Between All Points in Order:
		 *	Use an iterator and a loop to traverse each label/point in the map. For
		 *	each label/point, determine the distance from that point to the previous
		 *	point (or next point depending on how you implement this) and add that
		 *	distance to a total.  Note that the Vector2D class includes a static 
		 *	distance function to determine the distance between two Vector2D
		 *	objects, so you should not need to use any complicated math here.  Report
		 *	to the user how many points the map contains and what the total distance is.
		 ******************************************************************************/

		 //Iterator starts with the first point stored on the map
		std::map<std::string, Vector2D<int>*>::iterator iterate = coordinatesMap.begin();

		//Loop to store all points in the file on the map
		while (iterate != --coordinatesMap.end())
		{
			float distance;
			Vector2D<int> point1 = *iterate->second;

			Vector2D<int> point2 = *std::next(iterate, 1)->second;

			//Calculates distance between the two grabbed points
			distance = Vector2D<int>::Distance(point1, point2);

			//Takes distance between the points and adds it to the totalDistance
			totalDistance += distance;
			//Moves on to the next two points in the file
			iterate++;
		}
		//Display's the total distance all points
		std::cout << "---------------------------------------------" << std::endl;
		std::cout << "Map contains: " << coordinatesMap.size() << " points" << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
		std::cout<< "Total Distance of all points: " << totalDistance << std::endl;
		std::cout << "---------------------------------------------" << std::endl;

		/******************************************************************************
		 *	Determine the Distance Between the Start Point and a User Selected Point:
		 *	Prompt the user to enter a label or to enter "quit" to end.  If the user
		 *	entered anything other than "quit", attempt to find the label they entered
		 *	in the map. If it was found, report the distance between the point for the
		 *	label they entered and the start point (i.e. the point labeled "AA").
		 *	Otherwise, tell the user that the label they entered is not in the map.
		 *	Repeat these steps until the user enters "quit".
		 ******************************************************************************/
		
		 //Loop that allows user to enter coordinates. If user wants to end program, types 'end'
		 while (userInput != "end")
		 {
			//User prompt
			std::cout << "Enter the map's label (Enter \"end\" to exit): ";
			//Retrieves the user input to search 
			std::getline(std::cin, userInput);
			std::cout << std::endl;

			iterate = coordinatesMap.find(userInput);

			//Searches for points that matches
		 	if (iterate != coordinatesMap.end())
		 	{
				int distance = Vector2D<int>::Distance(*coordinatesMap.begin()->second, *coordinatesMap[userInput]);
				std::cout << "----------------------------------------------------" << std::endl;
				std::cout << "The distance between " << coordinatesMap.begin()->first << " " << coordinatesMap.begin()->second->ToString() << " and " << userInput << coordinatesMap[userInput]->ToString() << " is " << distance << std::endl;
		 		std::cout << "----------------------------------------------------" << std::endl;
			}
			//Point user entered does not match. Show error message
			else if (userInput != "end")
			{
				std::cout << "The point " << userInput << " does not exist" << std::endl;
			}
		 }
	}
	/******************************************************************************
	 *	Exception Handling:
	 *	Catch any std::exception thrown. Report to the user that a run-time error
	 *	occurred and show what exception was thrown.
	 ******************************************************************************/
	catch(std::exception ex)  // an exception was thrown
	{
		std::cerr << ex.what();
	}

	// END-OF-PROGRAM
	
	return 0;
}

