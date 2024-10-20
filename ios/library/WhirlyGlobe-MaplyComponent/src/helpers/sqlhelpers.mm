/*  sqlhelpers.mm
 *  WhirlyGlobeLib
 *
 *  Created by Steve Gifford on 9/8/09.
 *  Copyright 2011-2023 mousebird consulting
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#import "sqlhelpers.h"

namespace sqlhelpers
{

// Create a statement, run it, finalize it.
// Expect no results.  Kick out an exception on failure
void OneShot(sqlite3 *db,const char *stmtStr)
{
	sqlite3_stmt *stmt = NULL;
    int res = sqlite3_prepare_v2(db,stmtStr,-1,&stmt,NULL);
	if (res != SQLITE_OK)
		throw res;

    res = sqlite3_step(stmt);
	if (res != SQLITE_DONE)
	{
		sqlite3_finalize(stmt);
		throw res;
	}
	
	sqlite3_finalize(stmt);
}
	
// NSString version
void OneShot(sqlite3 *db,NSString *stmtStr)
{
    if (auto cstr = [stmtStr cStringUsingEncoding:NSASCIIStringEncoding])
    {
        OneShot(db, cstr);
    }
}
	
// Constructor for the read statement
StatementRead::StatementRead(sqlite3 *db,const char *stmtStr,bool justRun)
{
	init(db,stmtStr,justRun);
}
	
// This version take an NSString
StatementRead::StatementRead(sqlite3 *db,NSString *stmtStr,bool justRun)
{
    if (auto cstr = [stmtStr cStringUsingEncoding:NSASCIIStringEncoding])
    {
        init(db, cstr,justRun);
    }
}

void StatementRead::init(sqlite3 *db,const char *stmtStr,bool justRun)
{
    valid = false;
    if (!stmtStr)
        return;    
    
	this->db = db;
	stmt = NULL;
	isFinalized = false;
	curField = 0;
	
	if (sqlite3_prepare_v2(db,stmtStr,-1,&stmt,NULL) != SQLITE_OK)
    {
        return;
    }
	
	if (justRun)
		stepRow();
    
    valid = true;
}
		
// Clean up statement
StatementRead::~StatementRead()
{
	finalize();
}
    
bool StatementRead::isValid()
{
    return valid;
}
	
// Step
bool StatementRead::stepRow()
{
	if (isFinalized || !stmt || !valid)
		return false;
    
    curField = 0;
	
	const int ret = sqlite3_step(stmt);
	if (ret == SQLITE_ROW)
		return true;
	if (ret == SQLITE_DONE)
		return false;
	
	throw ret;
}
	
// Done with the statement
void StatementRead::finalize()
{
	if (!isFinalized && valid)
	{
		sqlite3_finalize(stmt);
		isFinalized = true;
		stmt = NULL;
	}
}
	
// Return int from the current row
int StatementRead::getInt()
{
	if (isFinalized)
		throw SQLITE_IOERR_CLOSE;
	
	return sqlite3_column_int(stmt, curField++);
}
	
// Return double from the current row
double StatementRead::getDouble()
{
	if (isFinalized)
		throw SQLITE_IOERR_CLOSE;
	
	return sqlite3_column_double(stmt, curField++);
}
	
// Return NSString from current row
NSString *StatementRead::getString()
{
	if (isFinalized)
		throw SQLITE_IOERR_CLOSE;
	
	const char *str = (const char *)sqlite3_column_text(stmt, curField++);
	if (str == nil)
		return nil;
	else
		return [NSString stringWithFormat:@"%s",str];
}
	
// Return a bool from the current row
BOOL StatementRead::getBool()
{
	if (isFinalized)
		throw SQLITE_IOERR_CLOSE;
	
	const char *str = (const char *)sqlite3_column_text(stmt, curField++);
	
	if (!strcmp(str,"yes"))
		return YES;
	else
		return NO;
}
    
NSData *StatementRead::getBlob()
{
    if (isFinalized)
        throw SQLITE_IOERR_CLOSE;

    const char *blob = (const char *)sqlite3_column_blob(stmt, curField);
    int blobSize = sqlite3_column_bytes(stmt,curField);
    curField++;

    return [NSData dataWithBytes:blob length:blobSize];
}
	
// Construct a write statement
StatementWrite::StatementWrite(sqlite3 *db,const char *stmtStr)
{
	init(db,stmtStr);
}
	
// Constructor that takes an NSString
StatementWrite::StatementWrite(sqlite3 *db,NSString *stmtStr)
{
    if (auto cstr = [stmtStr cStringUsingEncoding:NSASCIIStringEncoding])
    {
        init(db, cstr);
    }
}
	
void StatementWrite::init(sqlite3 *db,const char *stmtStr)
{
	isFinalized = false;
    const int res = sqlite3_prepare_v2(db,stmtStr,-1,&stmt,NULL);
	if (res != SQLITE_OK)
    {
        NSLog(@"Sqlite error: %s",sqlite3_errmsg(db));
		throw res;
    }
	curField = 1;
}
	
// Destroy a write statement
StatementWrite::~StatementWrite()
{
	finalize();
}
	
// Run the statement
void StatementWrite::go()
{
	if (isFinalized)
		throw SQLITE_IOERR_CLOSE;
	
    const int res = sqlite3_step(stmt);
	if (res != SQLITE_DONE)
		throw res;
}
	
// Finalize the statement
void StatementWrite::finalize()
{
	if (!isFinalized)
	{
		sqlite3_finalize(stmt);
		isFinalized = true;
		stmt = NULL;
	}
}
	
// Add an integer to the row data
void StatementWrite::add(int iVal)
{
	if (isFinalized)
		throw SQLITE_IOERR_CLOSE;
	
	sqlite3_bind_int(stmt,curField++,iVal);
}

// Add a double to the row data
void StatementWrite::add(double dVal)
{
	if (isFinalized)
		throw SQLITE_IOERR_CLOSE;
	
	sqlite3_bind_double(stmt,curField++,dVal);
}

// Add a string to the row data
void StatementWrite::add(NSString *str)
{
	if (str != nil)
	{
		if (const char *strData = [str cStringUsingEncoding:NSASCIIStringEncoding])
        {
            sqlite3_bind_text(stmt, curField++, strData, -1, SQLITE_STATIC);
        }
	}
    else
    {
        sqlite3_bind_null(stmt, curField++);
    }
}

// Add a bool to the row data
void StatementWrite::add(BOOL bVal)
{
	if (isFinalized)
		throw SQLITE_IOERR_CLOSE;
	
	sqlite3_bind_text(stmt, curField++, (bVal ? "yes" : "no"), -1, SQLITE_STATIC);
}
	
}
