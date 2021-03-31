#ifndef _LIBRARY_HXX_
#define _LIBRARY_HXX_

#include <iostream>      // input output
#include <string>        // library for string variables
#include <regex>         // regular expressions
#include <fstream>       // file text scanner
#include <vector>        // vectors library
#include <deque>         // deque library
#include <unordered_map> // unordered hash table read/write: O(1)
#include <algorithm>     // for toLower() and the shuffle()
#include <windows.h>     // FullScreen mode (Operations constructor)


class Global{

    private:
        inline static bool colorMode = true;
    public:

        void setColor(bool b);
        bool getCstate();
        
        //string to lower case
        std::string toLower(std::string s);
        //get color
        std::string color(std::string);
        //get color reset
        std::string colorReset();
        //getting loading status
        std::string loading(unsigned long long size, unsigned long long index);
        //print navigation and get choice
        std::string navOptions(std::vector<std::string> options, int minimum);
        //string to long long
        long long sToll(std::string s);

        //this is a string printer
        template <typename... Ts>
        void println(Ts const & ... vals){
            using unused = int[];
            std::vector<std::string> args;
            (void)unused { 0, (args.push_back(vals), 0)... };

            std::string start = "";
            std::string end = "";

            if(args.size() > 1){
                std::string colors [] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"};
                for (unsigned int i=0; i< sizeof(colors)/sizeof(*colors); i++){
                    if(toLower(args.back()) == colors[i]){
                        start = "\033[1;3"+std::to_string(i)+"m";
                        end = "\033[0m";
                        args.erase(args.end());
                    }
                }
            }
            
            std::string print = "";
            for(unsigned int i=0; i< args.size(); i++){
                print +=args[i];
            }
            
            if(!getCstate()){
                start = end = "";
            }
            std::cout << start+print+end << std::endl;
        }

        //the holly strings splitter
        std::vector<std::string> split(std::string s, std::string delim);
        //an enanched and actually workin cin
        std::string cinln();
        //table generator
        std::string tableMaker(std::deque<std::deque<std::string>> &allData, std::vector<unsigned int> longest);
        //get user choice
        int getChoice(int options);
        // display options and get choice
        int navChoice(std::vector<std::string> options, int minimum);
};


class Books: public Global {

    private:
        
        const std::string title;
        const std::string author;
        const std::string isbn;
        unsigned int qty;
        const std::vector<std::string> splittedTitle;

    public:
        //Books constructor
        Books() : title(""), author(""), isbn(""), qty(0), splittedTitle({})  {}
        Books(std::string t, std::string a, std::string i, std::string q);
        ~Books();

        // book title getter
        std::string getTitle();
        // book author getter
        std::string getAuthor();
        // book id getter
        std::string getId();
        // to get the book quantity
        unsigned int getQty();
        //get splitted title
        std::vector<std::string> getSplittedT();
        // modifing book quantity attribute
        unsigned int setQty(int qty, bool mode);
        //checking wether a book is empty or not
        bool emptyCheck();
        // printing book values
        std::string bookPrint();
        // book dashboard
        int bookManager();
};
        


class Collection: public Global {

    protected:
        //great dummy data
        std::deque<Books*> data;
        //sorted data in memory
        std::deque<std::deque<Books*>> sortedDataInMemory;
        //mark if data is sorted
        bool booksSorted = false;

    public:
        //erasing book collection
        void collectionClear();
        //remove a book
        bool removeBook(std::vector<double> indexes);
        //get book index
        std::vector<double> bookIndexes(Books *book);
        //add a book
        void addBook(Books *book);
        //get a book
        Books* getBook(unsigned long long index);
                

        //find a book
        bool findBook();
        //adding a new book
        void addNewBook();
        //building booksTable
        std::string booksTable(std::deque<Books*> &books);
        //print all books
        void printCollection();
        //select book from table
        int booksChoice(std::deque<Books*> &books);
        //quick-sort
        void quicksort(std::deque<Books*>& a, long long l, long long r, unsigned int titleIndex);
        //binary-search
        bool binarySearch(std::deque<Books*> &arr,std::string word);
        //data shuffle       
        void shuffle(std::deque<Books*> &data);
        // entire books search
        std::vector<unsigned long long> bookSearch(std::deque<Books*>& arr, Books* book, unsigned int index);
        //improved performance sorting data in memory
        void sortDataInMemory();


};



class Operations: public Collection{

    public:
        Operations();
        ~Operations(){};

        //file reader
        bool reader(std::string fileName);
        //main menu
        bool options();
};


#endif