#include <iostream>
#include "libsqlite.hpp" // sqlite library
using namespace std;
int main()
{
sqlite::sqlite db( "testData.db" ); // open database
auto cur = db.get_statement(); // create query
cur->set_sql( "SELECT * FROM dataTest;" );
cur->prepare(); // run query
while( cur->step() ) // loop over results
cout << cur->get_int(0) << " " << cur->get_text(1) << cur->get_text(2) << endl;
}