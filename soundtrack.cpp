/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic D Project						*
*												*
*			soundtrack.cpp						*
*			Status: Working              		*
************************************************/
#include "soundtrack.h"

soundtrack::soundtrack() :
	composer(""), title(""), label(""), catalogNumber(""), dateRecorded(""), dateReleased(1900)
{
} // end default constructor

soundtrack::soundtrack(const string& theComposer, const string& theTitle, const string& theLabel, const string& theCatalogNumber,
	const string& theDateRecorded, const int& theDateReleased) :
	composer(theComposer), title(theTitle), label(theLabel), catalogNumber(theCatalogNumber),
	dateRecorded(theDateRecorded), dateReleased(theDateReleased)
{
} // end constructor

void soundtrack::setComposer(const string & theComposer)
{
	composer = theComposer;
} // end setComposer

void soundtrack::setTitle(const string & theTitle)
{
	title = theTitle;
} // end setTitle

void soundtrack::setLabel(const string & theLabel)
{
	label = theLabel;
} // end setLabel

void soundtrack::setCatalogNumber(const string & theCatalogNumber)
{
	catalogNumber = theCatalogNumber;
} // end setCatalogNumber

void soundtrack::setDateRecorded(const string & theDateRecorded)
{
	dateRecorded = theDateRecorded;
} // end setDateRecorded

void soundtrack::setDateReleased(const int & theDateReleased)
{
	dateReleased = theDateReleased;
} // end setDateReleased

string soundtrack::getComposer() const
{
	return composer;
} // end getComposer

string soundtrack::getTitle() const
{
	return title;
} // end getTitle

string soundtrack::getLabel() const
{
	return label;
} // end getLabel

string soundtrack::getCatalogNumber() const
{
	return catalogNumber;
} // end getCatalogNumber

string soundtrack::getDateRecorded() const
{
	return dateRecorded;
} // end getDateRecorded

int soundtrack::getDateReleased() const
{
	return dateReleased;
} // end getDateReleased

bool soundtrack::operator==(const soundtrack& right) const
{
	if ((composer == right.composer) || (title == right.title) || (label == right.label) || (catalogNumber == right.catalogNumber) || (dateRecorded == right.dateRecorded) || (dateReleased == right.dateReleased))
		return true;
	else
		return false;
} // end overloaded == operator

bool soundtrack::operator>(const soundtrack& right) const
{
	if (title > right.title)
		return true;
	else
		return false;
}

bool soundtrack::operator<(const soundtrack& right) const
{
	if (title < right.title)
		return true;
	else
		return false;
}

ostream &operator<<(ostream& out, const soundtrack& cd)
{
	out << cd.getComposer() << "   ";
	out << cd.getTitle() << "   ";
	out << cd.getLabel() << "   ";
	out << cd.getCatalogNumber() << "   ";
	out << cd.getDateRecorded() << "   ";
	out << cd.getDateReleased() << "\n";

	return out;
} // end overloaded << operator

istream &operator>>(istream &in, soundtrack &val)
{
	int iBuf;
	string buffer, temp;
	string delimiter = " \t";  // Remove trailing whitespace

	getline(in, buffer, '\n');

	// 0 - 24
	temp = buffer.substr(0, 24);
	string composer = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	val.setComposer(composer);

	// 24 - 64
	temp = buffer.substr(24, 40);
	string title = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	val.setTitle(title);

	// 64 - 80
	temp = buffer.substr(64, 16);
	string label = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	val.setLabel(label);

	// 80 - 104
	temp = buffer.substr(80, 24);
	string catalogNumber = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	val.setCatalogNumber(catalogNumber);

	// 104 - 112
	temp = buffer.substr(104, 8);
	string dateRecorded = temp.substr(0, temp.find_last_not_of(delimiter) + 1);
	val.setDateRecorded(dateRecorded);

	// 112 - 116
	iBuf = stoi(buffer.substr(112, 4));
	val.setDateReleased(iBuf);

	return in;
} // end overloaded >> operator