/**********************************************************************
 *This program is basically an Almost Useless Data Structure (AUDS).
 *This data structure will hold any type of object, through the use
 *  of a class template.
 *
 * @author Nicholas English
 * @version 1.0
 * @date 2/5/2018
 *
 **********************************************************************/

#ifndef __H_AUDS__
#define __H_AUDS__

#include <algorithm>
#include <iostream>
#include <random>
#include <string>

template <typename T>

class AUDS {

	public:

		/*****************************************************
		 *
		 * Default constructor.
		 *
		 ****************************************************/  
		AUDS() {
			data = new T[ maxSize ];
		}

		/*****************************************************
		 *
		 * This is the copy constructor. It will take as a 
		 * parameter a reference to another AUDS object and 
		 * will perform a DEEP copy of the object.
		 *
		 ****************************************************/  
		// (1) https://www.geeksforgeeks.org/copy-constructor-in-cpp/
		AUDS( const AUDS &other ) {

			// Sets the AUDS to the same size as the other AUDS.
			currentSize = other.currentSize;
			maxSize = other.maxSize;

			// Creates the data array.
			data = new T[ maxSize ];

			// The new AUDS copies the other AUDS' objects (deep copies).
			for ( int i = 0; i < currentSize; i++ )
				data[ i ] = other.data[ i ];

		}

		/*****************************************************
		 *
		 * This is the copy operator=. It will perform the 
		 * copy-and-swap we learned about in class to set one 
		 * object equal to another. It also performs a DEEP 
		 * copy.
		 *
		 * @param other is another AUDS array.
		 *
		 * @return *this points to a reference of the obect.
		 *
		 ****************************************************/  
		AUDS& operator=( AUDS other ) {

			// Using the swap function (also a deep copy).
			// https://gitpitch.com/irawoodring/263/master?p=cpp#/101
			std::swap( currentSize, other.currentSize );
			std::swap( maxSize, other.maxSize );
			std::swap( data, other.data );

			// Returns a reference to this object.
			return *this;

		}

		/*****************************************************
		 *
		 * This is the destructor. It will give back any 
		 * memory we borrowed from the OS to hold the data we
		 * stored.
		 *
		 ****************************************************/  
		~AUDS() {
			delete[] data;
		}

		/*****************************************************
		 *
		 * Returns the current number of objects we are
		 * holding.
		 *
		 * @return currentSize, the total number of objects in
		 * 	the array.
		 *
		 ****************************************************/  
		int size() {
			return currentSize;
		}

		/*****************************************************
		 *
		 * Adds the generic element to the data structure.
		 *
		 * @param x is a generic element that needs to be
		 * 	added to the array.
		 *
		 ****************************************************/  
		void push (T x) {

			// Temp array to hold the data during transfer to the larger array.
			T* tempData;

			if( currentSize >= maxSize ) {

				// Resizes the max size by 50%.
				maxSize = maxSize * 1.5;

				// Creates the temp array.
				tempData = new T[ maxSize ];

				// Adds the items from the smaller array to the temp array.
				for( int i = 0 ; i < currentSize; i++ )			
					tempData[ i ] = data[ i ];


				// Deletes the smaller array.
				delete[] data;

				// Reassigns the temp array back to the original array.			
				data = tempData;
			}

			data[ currentSize++ ] = x;
		}

		/*****************************************************
		 *
		 * Removes a random item from the list. Moves the last 
		 * item in the array to the spot that was occupied by 
		 * the element we removed.
		 *
		 * @return tempItem is whatever item was removed from
		 * 	the array.
		 *
		 ****************************************************/ 
		T pop( ) {

			// Holds a random number to be generated.
			int randomNum;

			// Generates a random number.
			// (1) http://en.cppreference.com/w/cpp/header/random
			// (2) http://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
			std::random_device rd;
			std::mt19937 gen( rd() );
			std::uniform_int_distribution<> dis( 0, currentSize );

			// Calls and creates a random number to be removed.
			randomNum = dis( gen );

			// Sets a temp value to the item being removed.
			T tempItem = data[ randomNum ];

			// Last item is sent to the address of the object removed.
			data[ randomNum ] = data[ currentSize - 1 ];

			// Reduces the size of the array.
			currentSize = currentSize - 1;

			// Returns whatever item was removed.
			return tempItem;
		}

	private:

		/* Variable(s) */
		// Holds the current max size of the array.
		int maxSize = 100;

		// Holds the current number of spaces taken.
		int currentSize = 0;

		// Points to the data array.
		T* data;
};

#endif // __H_AUDS__

