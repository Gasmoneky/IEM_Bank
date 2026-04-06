#pragma once
#include "sqlite3.h"
#include <iostream>
#include <string>
#include <vector>

class Database {
private:
	sqlite3* db;
public:
	Database() {
		int openFile = sqlite3_open("collection.db", &db);
		if (openFile != SQLITE_OK) {
			std::cerr << "ERROR OPENING THE DATABASE: " << sqlite3_errmsg(db) << std::endl;
		}
		else {
			std::cout << "DATABASE OPENED SUCCESSFULLY MATE" << std::endl;
		
			createTable();
		}
	}
	void createTable() {
		std::string sql = "CREATE TABLE IF NOT EXISTS GEAR("
			"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"NAME TEXT NOT NULL UNIQUE);";
			char* errorMessage = nullptr;
			
			int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errorMessage);
		if (result != SQLITE_OK) {
			std::cerr << "ERROR CREATING TABLE: " << errorMessage << std::endl;
			sqlite3_free(errorMessage);
		}
	}
	std::vector<std::string> SearchGear(const char* query) {
		std::vector<std::string> results;
		sqlite3_stmt* stmt;
		const char* sql = "SELECT NAME FROM GEAR WHERE NAME LIKE?;";

		if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
			std::cerr << "SEARCH PREPARE ERROR" << sqlite3_errmsg(db) << std::endl;
			return results;
		}
		std::string wildcards = "%" + std::string(query) + "%";
		sqlite3_bind_text(stmt, 1, wildcards.c_str(), -1, SQLITE_TRANSIENT);

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			const unsigned char* text = sqlite3_column_text(stmt, 0);

			if (text) {
				results.push_back(std::string(reinterpret_cast<const char*> (text)));
			}
		}
		sqlite3_finalize(stmt);
		return results;
	}
	void AddIem(const char* name) {
		sqlite3_stmt* stmt;
		const char* sql = "INSERT INTO GEAR (NAME) VALUES (?);";
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
			std::cerr << "ERROR PRODUCED WHEN TRYING TO ADD IEM " << sqlite3_errmsg(db) << std::endl;
			return;

		}
		sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);

		if (sqlite3_step(stmt) != SQLITE_DONE) {
			std::cerr << "ERROR GOTTEN WHEN TRYING TO SAVE FILE" << sqlite3_errmsg(db) << std::endl;

		}
		else {
			std::cout << "SUCCESS" << name << "SAVED TO THE DATABASE BRUVVV" << std::endl;
		}
		sqlite3_finalize(stmt);
	}
	void deleteIem(const char* name) {
		sqlite3_stmt* stmt;
		const char* sql = "DELETE FROM GEAR WHERE NAME = ?;";
		if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
			sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
			if (sqlite3_step(stmt) == SQLITE_DONE) {
				std::cout << "THE IEM " << name << "HAS BEEN REMOVED FROM THE DATABASE" << std::endl;

			}
			else {
				std::cerr << "ERROR DELETING IEM FROM THE DATABASE" << sqlite3_errmsg(db) << std::endl;

			}
		}
		sqlite3_finalize(stmt);
	}
	~Database(){
		if (db) {
			sqlite3_close(db);
			std::cout << "DATABASE CONNECTION CLOSED AND CLEANED UP YOOH" << std::endl;
		}
	}
};