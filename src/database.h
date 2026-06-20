/* Code-Scan Static Analyzer - Copyright (C) 2026 XPDevs. All rights reserved. */
#ifndef DATABASE_H
#define DATABASE_H
#include "code_scan.h"
typedef struct DBEntry{Issue issue;struct DBEntry*next;int file_id;int suppressed;char tag[64];}DBEntry;
typedef struct{DBEntry**heads;int nfiles;DBEntry*all;int nall;int last_id;int suppressed_count;}IssueDB;
IssueDB*db_init(int file_count);void db_free(IssueDB*db);int db_add(IssueDB*db,Issue*issue,int file_id);int db_suppress(IssueDB*db,int issue_id);int db_suppress_file(IssueDB*db,const char*file);int db_suppress_code(IssueDB*db,int code);void db_sort_by_severity(IssueDB*db);void db_sort_by_file(IssueDB*db);void db_sort_by_code(IssueDB*db);int db_count_by_severity(IssueDB*db,Severity s);int db_count_by_category(IssueDB*db,Category c);int db_count_by_file(IssueDB*db,int file_id);Issue*db_get(IssueDB*db,int id);Issue**db_get_all(IssueDB*db,int*n);Issue**db_get_by_file(IssueDB*db,int file_id,int*n);Issue**db_get_by_severity(IssueDB*db,Severity s,int*n);Issue**db_get_by_category(IssueDB*db,Category c,int*n);void db_dedup(IssueDB*db);void db_merge(IssueDB*dst,IssueDB*src);
#endif
