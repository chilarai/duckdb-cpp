/** 
 * =====================================
 * Simple DuckDb C++ integration Test
 * =====================================
 */


#include <iostream>
#include "duckdb.hpp"

using namespace duckdb;

int main(int argc, char* argv[]) {	

	DuckDB db(nullptr);
	Connection con(db);
	auto result = con.Query("SELECT 42");
	
	// Basic create table and insert
	con.Query("CREATE TABLE people(id INTEGER, name VARCHAR)");
    con.Query("CREATE TABLE test");
    con.Query("INSERT INTO people VALUES (0,'Mark'), (1, 'Hannes')");	

	// Insert using appender
	duckdb::Appender appender(con, "people");
    appender.AppendRow(2, "Chilarai");
	appender.AppendRow(3, "Test");
    appender.Close();

	// Update data
	auto prepared = con.Prepare("UPDATE people SET name = $1 WHERE id = $2");
    auto prep = prepared->Execute("DuckDb", 3);
	
	// Delete data
	auto resultDelete = con.Query("DELETE FROM people WHERE id = 3");

	// Read data
	auto resultSelect = con.Query("SELECT * FROM people");
	idx_t a = resultSelect->collection.count;

	return 0;
}