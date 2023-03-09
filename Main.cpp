/**********************************************************************
* Author:
* Date Created:
* Last Modification Date:
* Lab Number:
* File Name:
*
*	  Overview:
*
*		 Input:
*
*		Output:
*
**********************************************************************/
#include "Graph.h"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

void Display(string& data);

int main()
{
	void (*visit)(string&);
	visit = &Display;

	Graph< string, string > test;

	try
	{
		test.BreadthFirst(visit);
	}
	catch (Exception& except)
	{
		cout << except << endl;
	}

	test.InsertVertex("A");
	test.InsertVertex("X");
	test.InsertVertex("G");
	test.InsertVertex("H");
	test.InsertVertex("P");
	test.InsertVertex("E");
	test.InsertVertex("Y");
	test.InsertVertex("M");
	test.InsertVertex("J");
	test.InsertArc("A", "X", "AXA");
	test.InsertArc("X", "G", "XGX");
	test.InsertArc("X", "H", "XHX");
	test.InsertArc("H", "E", "HEH");
	test.InsertArc("H", "P", "HPH");
	test.InsertArc("G", "P", "GPG");
	test.InsertArc("E", "M", "EME");
	test.InsertArc("E", "Y", "EYE");
	test.InsertArc("M", "Y", "MYM");
	test.InsertArc("M", "J", "MJM");


	//test.DeleteArc( "Node 1", "Node 2", 12 );
	//test.InsertArc( "Node 1", "Node 1", 1 );
	//test.DeleteArc( "Node 1", "Node 1", 1 );
	//test.DeleteVertex( "Node 1" );
	test.BreadthFirst(visit);
	cout << endl;
	//test.BreadthFirst( visit );
	//cout << endl;
	test.DepthFirst(visit);
	cout << endl;
	//test.DepthFirst( visit );
	//cout << endl;

	Graph< string, string > test2;

	test2 = test;

	test2.InsertVertex("Z");
	test2.InsertVertex("W");
	test2.InsertArc("M", "Z", "MZM");
	test2.InsertArc("Z", "W", "ZWZ");

	test2.BreadthFirst(visit);
	cout << endl;

	Graph< string, string > test3(test);

	test3.BreadthFirst(visit);
	cout << endl;

	Graph< string, string > test4;

	test2 = test4;

	try
	{
		cout << "Test 2" << endl;
		test2.BreadthFirst(visit);
	}
	catch (Exception& except)
	{
		cout << except << endl;
	}

	try
	{
		cout << "Test 4" << endl;
		test4.BreadthFirst(visit);
	}
	catch (Exception& except)
	{
		cout << except << endl;
	}

	//test.~Graph(  );
	//test2.~Graph(  );

	//try
	//{
	//	test.InsertArc( "Node 0", "Node 3", "12" );
	//}
	//catch( Exception & except )
	//{
	//	cout << except << '\n';
	//}

	//try
	//{
	//	test.DeleteArc( "Node 1", "Node 3", "12" );
	//}
	//catch( Exception & except )
	//{
	//	cout << except << '\n';
	//}
	//

	////test.InsertVertex( "Node 3" );
	////test.DeleteVertex( "Node 3" );

	//try
	//{
	//	test.DeleteVertex( "Node 4" );
	//}
	//catch( Exception & except )
	//{
	//	cout << except << '\n';
	//}

	return 0;
}

void Display(string& data)
{
	cout << data << ' ';
}