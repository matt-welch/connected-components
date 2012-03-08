/*******************************************************************************
 * FILENAME:	README.txt
 * DESCRIPTION:	Connected Graph Components README
 * AUTHOR: 		James Matthew Welch [JMW]
 * SCHOOL:		Arizona State University
 * CLASS:		CSE430::Operating Systems
 * INSTRUCTOR:	Dr. Violet Syrotiuk
 * SECTION:		19464
 * TERM:		Spring 2012
******************************************************************************/

To compile my connected-components program, navigate to the folder containing the
source code and Makefile.  I you want to build with the G++ compier, simply type 
"make" or "make all" and both the serial(connectd) and parallel(paralel) versions
of the program will be built with G++.  To build with the Intel icpc compiler, 
again navigate to the folder containing source and Makefile.  Then, type 
"module load intel" to make the Intel compiler available.  Finally, type 
"make intel" and the Intel compiler will build both serial and parallel versions 
of the program.  To run the program simply type the program name followed by the 
name of the graph file to analyze (e.g. "./parallel graph.txt").  This will output 
the number of sets in the graph followed by a list of the sets with their sizes, 
then by program execution time as specified in the assignment sheet.  
If no set-list output is required, the program may be called with the "-q" option
(e.g. "./connected graph.txt -q").

Assumptions: 
(1) programs installed on the system include: g++, make, icpc

