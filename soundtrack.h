/************************************************
*			Jeff Stanton						*
*			CS M20   							*
*			Topic D Project						*
*												*
*			Soundtrack.h			 			*
*			Status: Working              		*
************************************************/

#ifndef _SOUND_TRACK
#define _SOUND_TRACK

#include <string>
#include <iostream>
using namespace std;

class soundtrack
{
	// Overloaded stream insertion and extraction operators
	friend std::ostream &operator<<(std::ostream &, const soundtrack &);
	friend std::istream &operator>>(std::istream&, soundtrack&);

private:
	string composer;
	string title;
	string label;
	string catalogNumber;
	string dateRecorded;
	int dateReleased;

public:
	soundtrack();
	soundtrack(const string& theComposer, const string& theTitle, const string& theLabel,
		const string& theCatalogNumber, const string& theDateRecorded, const int& theDateReleased);

	void setComposer(const string& theComposer);
	void setTitle(const string& theTitle);
	void setLabel(const string& theLabel);
	void setCatalogNumber(const string& theCatalogNumber);
	void setDateRecorded(const string& theDateRecorded);
	void setDateReleased(const int& theDateReleased);

	string getComposer() const;
	string getTitle() const;
	string getLabel() const;
	string getCatalogNumber() const;
	string getDateRecorded() const;
	int getDateReleased() const;

	bool operator==(const soundtrack&) const;
	bool operator>(const soundtrack&) const;
	bool operator<(const soundtrack&) const;
}; // end soundtrack

#endif